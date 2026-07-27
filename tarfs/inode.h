/*
 * TARFS - Immutable (read-only) filesystem for embedded systems.
 *
 * Copyright (c) 2026 Viacheslav Logunov
 * SPDX-License-Identifier: MMIT
 *
 * Author:
 *   Viacheslav Logunov <vvb333007@gmail.com>
 *
 * Project:
 *   https://github.com/vvb333007/tarfs
 *
 * @file inode.h
 * @brief Public inode API
 */


#pragma once

#include <stdint.h>
#include <time.h>
#include "tar.h"
/**
 * TARFS inode structure, 12..20 bytes per inode; 1000 files require ~16KiB of RAM to store 
 * the filesystem index
 *
 * Inode represents a resolved filesystem object as a mapping:
 *   (hashed pathname) -> (tar header location in archive memory).
 *
 * Each inode corresponds to one usable tar entry.
 *
 * Usable entries are tar record types:
 *   - 0 : regular file
 *   - 1 : hard link
 *   - 2 : symbolic link
 *   - 5 : directory
 *
 * Notes:
 * - inode resolution always follows link targets until a final
 *   FILE (0) or DIRECTORY (5) entry is reached.
 *
 * A structure like this:
 *    name1 -links--> name2 --link--> name4.txt
 *    will result in 3 inodes:
 *
 * inode1.in_vaddr ==> "name1" entry
 * inode1.in_dvaddr ==> "name4.txt" entry
 *
 * inode2.in_vaddr ==> "name2" entry
 * inode2.in_dvaddr ==> "name4.txt" entry
 *
 * inode3.in_vaddr ==> "name4.txt" entry
 * inode3.in_dvaddr ==> "name4.txt" entry
 *
 * TARFS maintains two independent indexes:
 *
 *  - inode_index[] : sorted by in_hash for O(log N) pathname lookup.
 *  - in_next       : linked list sorted by pathname for directory
 *                    enumeration and prefix scans.
 */

struct tarfs_inode  {

  uint32_t   in_hash;    /*!< Hash of full path of the entry */
  uintptr_t  in_path;    /*!< Pointer to the full pathname. The pathname is not guaranteed to be NUL-terminated. It may end at '\0', '\r' or '\n', therefore tar_strcmp() must be used. */
  uintptr_t  in_vaddr;   /*!< Virtual address of the original tarhdr entry */
  uintptr_t  in_dvaddr;  /*!< final resolved target after link resolution, i.e. a file or a directory */
  struct tarfs_inode *in_next;   /*!< Next inode in lexicographical pathname order.
                                      The original inode array is never reordered. Sorting is achieved
                                      solely by relinking inodes through this field. */
};



struct tarfs_fs;


#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Get information about an inode.
 *
 * Retrieves metadata for the inode referenced by an inode index entry.
 * Either @p size or @p mtime may be @c NULL if the corresponding value
 * is not required.
 *
 * @param index Inode index.
 * @param idx   Inode number within the index.
 * @param size  Optional output for file size.
 * @param mtime Optional output for modification time.
 *
 * @return TAR entry type.
 */
tart_t inode_getinfo(struct tarfs_inode const * const *index,
                     int idx,
                     size_t *size,
                     time_t *mtime);

/* 
 * variant of inode_type() which works with raw pointers to inodes 
 * Not MT-Safe. Must be called under addref protocol only
 */
tart_t inode_rawtype(struct tarfs_inode const *ino);

/* Check if inode (raw inode pointer) is one of two link-type inodes
 * Not MT-Safe. Must be called under addref protocol only
 *
 */
bool inode_islink(struct tarfs_inode const *ino);



/**
 * @brief Find an inode by pathname.
 *
 * Performs a pathname lookup in the inode index.
 *
 * @param index      Inode index.
 * @param num_inodes Number of entries in the index.
 * @param path       Absolute path to search for.
 *
 * @return Inode index on success, or -1 if not found.
 */
int inode_lookup(struct tarfs_inode const * const *index,
                 size_t num_inodes,
                 const char *path);





/**
 * @brief Allocate an inode index.
 *
 * Allocates an array of inode pointers capable of holding
 * @p count entries.
 *
 * @param count Number of inode pointers to allocate.
 *
 * @return Newly allocated inode index, or @c NULL on failure.
 */
struct tarfs_inode **inode_alloc(size_t count);


/**
 * @brief Destroy an inode index.
 *
 * Frees an inode index previously created by inode_alloc() together with
 * all associated inode objects.
 *
 * @param index      Inode index.
 * @param count      Number of entries in the index.
 * @param tar_start  Start address of the mounted TAR image.
 * @param tar_length TAR image size in bytes.
 */
void inode_free(struct tarfs_inode **index,
                size_t count,
                uintptr_t tar_start,
                size_t tar_length);


/**
 * @brief Unmount a TAR image.
 *
 * Releases all in-memory data structures associated with a mounted TARFS
 * instance.
 *
 * @param fs        Filesystem instance.
 * @param tar_start Start address of the mounted TAR image.
 * @param tar_size  TAR image size in bytes.
 */
void inode_unmount(struct tarfs_fs *fs,
                   const void *tar_start,
                   size_t tar_size);



/**
 * @brief Build an inode index for a TAR image.
 *
 * Scans the TAR archive, creates the inode index and initializes the
 * filesystem state.
 *
 * @param fs          Filesystem instance.
 * @param buf         Start address of the TAR image.
 * @param size        TAR image size in bytes.
 * @param rebase_link Optional path prefix substracted from symbolic links.
 * @param path_rebase Optional path prefix substracted from every TAR entry.
 *                    Normally this one is autodetected (the very first directory in the archive becomes the
 *                    'path_rebase' parameter) and then substracted from every path in the archive, so archive gets "/" entry
 *                    
 *
 * @retval 0  Success.
 * @retval -1 Mount failed.
 */
int inode_mount(struct tarfs_fs *fs,
                const unsigned char *buf,
                size_t size,
                const char *rebase_link,
                const char *path_rebase);


/**
 * @brief Dump the inode hash table in sorted order.
 *
 * Debug helper used to inspect the inode index.
 *
 * @param index Inode index.
 * @param count Number of entries.
 */
void inode_dumphash_sorted(struct tarfs_inode const * const *index,
                           size_t count);

/**
 * @brief Dump the directory tree sorted by pathname.
 *
 * Debug helper that recursively prints the filesystem hierarchy.
 *
 * @param root Root inode.
 */
void inode_dumppath_sorted(struct tarfs_inode const *root);
#ifdef __cplusplus
};
#endif