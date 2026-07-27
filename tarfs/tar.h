/*
 * TARFS - Immutable (read-only) filesystem for embedded systems.
 *
 * Copyright (c) 2024-2026 Viacheslav Logunov
 * SPDX-License-Identifier: MMIT
 *
 * Author:
 *   Viacheslav Logunov <vvb333007@gmail.com>
 *
 * Project:
 *   https://github.com/vvb333007/tarfs
 *
 * @file tar.h
 * @brief Public tar file API
 */


#pragma once 

#include "config.h"

/**
 * "TART" == "TAR Type"
 * tarfile entry (header) types, 1-byte wide. The same type is used throughout the 
 * filesystem code as the main type for inodes, tar record etc
 */
typedef enum __attribute__((packed)) {

  TART_AFILE    = '\0',  /*!<  file, old format */
  TART_FILE     = '0',   /*!<  file, common format */

  TART_HARDLINK = '1',   /*!<  hard link */
  TART_SYMLINK  = '2',   /*!<  symbolic link */
  TART_DIR      = '5',   /*!<  directory */

  TART_PAX      = 'x',   /*!<  PaxHeader */

  // Ignored by TARFS
  TART_CHRDEV   = '3',   /*!<  character device */
  TART_BLKDEV   = '4',   /*!<  block device */
  TART_FIFO     = '6',   /*!<  fifo / named pipe */
  TART_CONT     = '7',   /*!<  contigous file, whatever that means */
  TART_PAX_G    = 'g',   /*!<  PaxGlobalHeader */

  /* Not a real type, used as a return value to indicate a bad type */
  TART_BAD       = 255,

} tart_t;

_Static_assert(sizeof(tart_t) == 1, "sizeof(tar_type_t) != 1, code review is required");


/**
 * For TAR files with modified PADDING field (see tarsum.c TARFS Checksum Utility):
 * The type and meaning of the last 8 bytes of the padding field. The very first byte 
 * of the padding[] field MUST be zero, this is checked on mount(). For the same reason
 * the IDs below all have 0x00 byte in them in the first position.
 */

struct tarhdr {

  const char name[100];       /*!< First (if prefix[0] == 0) or Second part of the entry name */
  const char mode[8];         /*!< Ignored: RWX, we are ROFS */
  const char uid[8];          /*!< Ignored: VFS has no user/group concept */
  const char gid[8];          /*!< Ignored: VFS has no user/group concept */
  const char size[12];        /*!< Octal, ASCII string, terminated with a space \20, not \0 */
  const char mtime[12];       /*!< All times are set at mount time and never change (ROFS)  */
        char checksum[8];     /*!< Octal, ASCII */
  const tart_t type;          /*!< Record type */
  const char link_name[100];  /*!< For records type#1 and #2 this field contains a name of the object */
  const char magic[6];        /*!< "ustar\0" signature */
  const char version[2];      /*!< "00" */
  const char user[32];        /*!< Ignored: VFS has no user/group concept */
  const char group[32];       /*!< Ignored: VFS has no user/group concept */
  const char major[8];        /*!< Ignored: device files make no sence */
  const char minor[8];        /*!< Ignored: device files make no sence */
  const char prefix[155];     /*!< First (if prefix[0] != 0) part of the entry name. A slash at the end does not exist but is assumed */
        char zero;            /*!< Must be zero by the standart */  
#if CONFIG_TARFS_INTEGRITY
        char md[3];          /*!< Message Digest algorithm. For TARFS v0 these values are defined:
                                  "C64" - CRC64 algo */
        char digest[8];      /*!< Integrity check value in little-endian byte order (LSB first), */
#else
  const char pad[11];        /*!< Must be zero by the standart */
#endif                                  

} __attribute__((packed));

typedef struct tarhdr tarhdr_t;

_Static_assert(sizeof(tarhdr_t) == 512, "sizeof(tarhdr_t) != 512, code review is required");

#ifdef __cplusplus
extern "C" {
#endif

/* Checked TAR String   == "CTS", a byte sequence within a TAR archive terminated
 *                         by '\0', '\r', or '\n'.
 * Unchecked TAR String == "UTS", a byte sequence that may not be terminated.
 * C string             == a byte sequence terminated by '\0'.
 *
 * Strings stored in a TAR archive may or may not include a terminating
 * character. For this reason, TARFS provides a set of string helper
 * functions that mimic the behavior of the standard string.h functions.
 *
 * When operating on an Unchecked TAR String (UTS), the caller must provide
 * a pointer to the end of the string (e.g. tar_strcmp(), tar_strlen(), ...).
 */


/**
 * Compare an UTS/CTS to a CTS
 *
 * TAR string fields are not required to be NUL-terminated. A string ends
 * at the first '\0', '\r' or '\n', or at s1_end if no terminator appears
 * before that point.
 *
 * @param s1      TAR string.
 * @param s1_end  Pointer to the byte immediately following the last valid
 *                character in s1, or NULL if s1 is guaranteed to contain
 *                a TAR string terminator.
 * @param s2      Regular NUL-terminated C string.
 *
 * @return <0 if s1 is lexicographically less than s2,
 *         >0 if s1 is lexicographically greater than s2,
 *          0 if both strings are equal.
 */
int tar_strcmp(const char *s1, const char *s1_end, const char *s2);

/*
 * strncmp() for two CTS, len is the hard limit 
 *
 */
int tar_strncmp(const char *s1, const char *s2, size_t len);


/**
 * Return the length of a TAR string.
 *
 * A TAR string ends at the first '\0', '\r' or '\n'. If none of these
 * characters is present before s1_end, then s1_end is treated as the end
 * of the string.
 *
 * @param s1      TAR string.
 * @param s1_end  Pointer to the byte immediately following the last valid
 *                character in s1, or NULL if s1 contains a TAR string
 *                terminator.
 *
 * @return Length of the string, excluding the terminator.
 */
int tar_strlen(const char *s1, const char *s1_end);

/**
 * Duplicate a TAR string as a regular NUL-terminated C string.
 *
 * The returned buffer contains one additional byte after the terminating
 * NUL, allowing a single character (typically '/') to be appended without
 * reallocating. This is used during link resolution.
 *
 * string\0\0
 *        ^_--- Here one could append one character to extend a string by one character
 *
 * @param s1      TAR string.
 * @param s1_end  Pointer to the byte immediately following the last valid
 *                character in s1, or NULL if s1 contains a TAR string
 *                terminator.
 *
 * @return Newly allocated NUL-NULL-terminated copy of the string,
 *         or NULL on allocation failure.
 */
char *tar_strdup1(const char *s1, const char *s1_end);

/* Parse an octal number from a TAR field.
 *
 * Unlike strtol(), the input is not required to be NUL-terminated.
 * Parsing stops after max_len characters or at the first non-octal
 * character.
 *
 * @param p buffer start
 * @param max_len buffer length in bytes
 * @return decimal value
 */
uint32_t tar_octal(const char *p, size_t max_len);

#if CONFIG_TARFS_LOG
/* Devel only:
 * Displays CTS `buf`; `end` is the UTS_limit
 *
 * We dont go past the `end` pointer even if we didnt find any line 
 * terminator
 */
void tar_print(const char *buf, const char *end);
#endif /* CONFIG_TARFS_LOG */


/** Validate a TAR header.
 *
 * Checks:
 *   - entry type is supported/recognized;
 *   - reserved padding byte is zero;
 *   - checksum field contains only valid TAR characters;
 *   - header checksum matches the calculated value.
 *   - entry size is within the mmaped memory range.
 *
 * @param hdr Pointer to a TAR header.
 * @return true if the header is invalid, corrupted, or unsupported.
 *         In this case no inode should be created for this entry.
 */
bool tar_badhdr(tarhdr_t const * hdr);

/**
 * Quick run through the tarfile to count number of inodes we have to create
 * Bad blocks are skipped; inodes_count = number_of_links + number_files + number_of_directoris
 *
 * @param tar_start  Address where the TAR archive is mapped.
 * @param tar_length Size of the mapped archive.
 * @return Number of inodes required for this filesystem
 */
int tar_getnino(const uint8_t *tar_start, size_t tar_length);


/**
 * Detect the archive root directory.
 *
 * The detected directory is used both as the filesystem mount point and
 * as the path prefix to strip from every inode. For example, if the archive
 * contains:
 *
 *     my_archive/
 *     my_archive/file.txt
 *     my_archive/dir/test.txt
 *
 * then the filesystem will expose:
 *
 *     /file.txt
 *     /dir/test.txt
 *
 * Detection relies on the following assumptions:
 *
 *   - the first directory entry (type 5) is the archive root;
 *   - all archive entries reside under that directory.
 *
 * These assumptions are not verified. It is the caller's responsibility to
 * provide a well-formed TAR archive.
 *
 * Since the root directory becomes the mount point, it must satisfy the
 * ESP-IDF mount-point limitations (currently no more than 16 characters,
 * excluding the terminating NUL).
 *
 * The root directory name always fits into tarhdr->name, so it is guaranteed
 * to be NUL-terminated and never uses the TAR 'prefix' field.
 *
 * @param tar_start  Address where the TAR archive is mapped.
 * @param tar_length Size of the mapped archive.
 * @param base_dir   Output buffer receiving the detected root directory.
 * @param base_dir_len Output buffer size. Recommended size is 100 bytes
 *
 * @return true if a root directory was found.
 */
bool tar_rootdir(const uint8_t *tar_start, size_t tar_length, char *base_dir, size_t base_dir_len);



/* Calculate the checksum of a TAR header.
 *
 * While the checksum is being calculated, the checksum field itself
 * must be treated as eight ASCII space characters, as required by the
 * TAR format specification.
 *
 * The checksum field occupies bytes [148..156).
 *
 * @param hdr Pointer to the TAR header.
 * @return Header checksum.
 */
uint32_t tar_hdrsum(const tarhdr_t *hdr);


/**
 *  Verify CRC64 checksums stored in a TAR archive, if present.
 *  hdr must pass tar_badhdr() check!!
 */
bool tar_baddata(struct tarhdr const *hdr, size_t size);


#ifdef TARSUM_BUILD
/**
 * Calculate and insert CRC64 checksums into a TAR archive.
 *
 * The checksum of each file entry is stored in the corresponding TAR
 * header. Existing CRC64 values are overwritten.
 *
 * This function is intended for use by the `tarsum.c` utility.
 *
 * @param tar_start Pointer to the beginning of the TAR archive, must be WRITEABLE memory!
 * @param tar_length Size of the TAR archive in bytes.
 * @return Number of entries for which a CRC64 checksum was written,
 *         or a negative value on error.
 */
int tar_addsum(uint8_t *tar_start, size_t tar_length);
#endif /* TARSUM_BUILD */

      
#ifdef __cplusplus
};
#endif
