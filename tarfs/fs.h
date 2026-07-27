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
 * @file fs.h
 * @brief Public file system API
 */


#pragma once

#include <stdlib.h>
#include <stdatomic.h>
#include <stddef.h>
#include <errno.h>
#include <time.h>

#include "config.h"
#include "os.h"

#define TARFS_MAX_FS  CONFIG_TARFS_MAX_FS
#define TARFS_MAX_FDS CONFIG_TARFS_MAX_FDS

#if CONFIG_TARFS_LOG
#  define log( Format_, ... ) do { printf( "%s(): " Format_, __func__,  ##__VA_ARGS__ ); } while(0)
#else
#  define log( Format_, ... ) do {} while(0)
#endif
#define logerr( Format_, ... ) do { printf( "%s(): " Format_, __func__,  ##__VA_ARGS__ ); } while(0)

#include "refc.h"
#include "file.h"
#include "inode.h"


/**
 * @brief ioctl() commands which are supported by this driver.
 *
 * @note  TARFS supports one special ioctl (FIOGETFD) to convert system-wide FD numbers to
 *        local fd numbers. This is required for POSIX mmap() implementation
 * 
 */
#define TARFS_IOCTL_BASE  0x54415200 /* "TAR\0" */

#ifndef FIOGETFD
#  define FIOGETFD (TARFS_IOCTL_BASE + 0)     /*!< Convert global fd number to local fd number. arg=&int */
#endif
#ifndef FIONREAD
#  define FIONREAD (TARFS_IOCTL_BASE + 1)   /*!< Support FIONREAD (compatibility layer) */
#endif
#ifndef FIONBIO
#  define FIONBIO (TARFS_IOCTL_BASE + 2)    /*!< Support FIONBIO (compatibility layer) */
#endif

/** 
 * Return/Request argument for FIOGETFD ioctl 
 */
struct ioctl_req {
  int fs_idx; /*!< filesystem index, [0..TARFS_MAX_FS) */
  int fd;     /*!< fd number */
};

/* Useful runtime stats on mounted filesystem. This one is required by statvfs() API
 * unlike counters, this structure is populated once at mount and never changed
 */
struct tarfs_stats {

  unsigned int badblocks; /*!< Number of bad/unrecognized 512-byte blocks */
  unsigned int files;    /*!< Number of files */
  unsigned int links;    /*!< Number of links */
  unsigned int dirs;     /*!< Number of directories */
  unsigned int ram;      /*!< Total RAM used by the FS */

};


/**
 * This descriptor holds all file descriptors opened. Created by tarfs_mount()
 * destroyed by a refcounter mechanism

 * @brief TARFS filesystem descriptor.
 *
 * @note Descriptor lifetime is defined by its refcounter fs_ref. Once it reaches zero (upon unrefx() call)
 *       the descriptor gets destroyed, memory is freed. These structures are managed by addref() and unrefx()
 *       calls only.
 */
struct tarfs_fs {

  refc_t                        fs_ref;               /*!< Reference counter: open files and active mmap() */
  uintptr_t                     fs_handle;            /*!< OS-specific opaque handle for the whole partition mmap */
  void const                   *fs_vaddr;             /*!< Virtual address to access whole partition */
  size_t                        fs_dsize;             /*!< Data size: Partition size minus size of all TARFS headers */
  size_t                        fs_size;              /*!< Total size: Partition size */
  uint32_t                      fs_nino;              /*!< Number of entries in fs_ino array */
  struct tarfs_inode const * const *fs_ino;           /*!< Sorted (in_hash) array of pointers to inodes. */
  struct tarfs_inode const *    fs_root;              /*!< First record of alphasorted (in_path) list of entries (linked via in_next) */
  _Atomic(uint32_t)             fs_usedfd;            /*!< A bitmask for fs_fd[] array: 0100 means FD #2 is 
                                                           used. Indicates which elements of fs_fd[] array are used */
  struct tarfs_fp               fs_fd[TARFS_MAX_FDS]; /*!< Open files descriptors */
  time_t                        fs_mtime;             /*!< time() at mount. Used by stat()/fstat() to populate mtime field (mtime does not change on ROFS) */
  uint16_t                      fs_opencrc:1;         /*!< A flag to enable/disable CRC64 verification on open() */
  uint16_t                      fs_reserved:15;       /*!< Reserved for future extensions */
  struct tarfs_stats            fs_stats;             /*!< FS immutable statistics */
#if CONFIG_TARFS_COUNTERS                             /*!< Mutable statistics: */
  uint64_t                      fs_bmmap;             /*!< Number of bytes mmaped through mmap() (sum active mmapings only) */
  uint64_t                      fs_bread;             /*!< Number of bytes read by read() (sum of all read() and pread() ) */
  uint32_t                      fs_nfail;             /*!< Number of failed open() calls */
#endif

  char                          fs_mountpoint[];      /*!< Mount point */
};


/**
 * enum for statvfs
 */
enum {

  ST_NOATIME     = 1,
  ST_NODEV       = 2,
  ST_NODIRATIME  = 4,
  ST_NOEXEC      = 8,
  ST_NOSUID      = 16,
  ST_RDONLY      = 32,
  ST_RELATIME    = 64,
  ST_SYNCHRONOUS = 128,

};

/**
 * The statvfs structure for systems without it (e.g. newlib)
 */
struct statvfs {

/* TODO: review types below. Right now it is a mess */

  size_t   f_bsize;    /* Filesystem block size */
  size_t   f_frsize;   /* Fragment size */
  size_t   f_blocks;   /* Size of fs in f_frsize units */
  size_t   f_bfree;    /* Number of free blocks */
  size_t   f_bavail;   /* Number of free blocks for unprivileged users */
  size_t   f_files;    /* Number of inodes */
  size_t   f_ffree;    /* Number of free inodes */
  size_t   f_favail;   /* Number of free inodes for unprivileged users */
  size_t   f_fsid;     /* Filesystem ID */
  int      f_flag;     /* Mount flags */
  size_t   f_namemax;  /* Maximum filename length */

/* TARFS extensions: */

  uint64_t f_bread;    /* Total bytes read()+pread() */
  uint64_t f_bmmap;    /* Total bytes mmap() */
  uint32_t f_nfail;    /* Total number of failures (e.g. out-of-memory, inode with NULL address etc) */
  size_t   f_badblocks; /*!< Number of bad/unrecognized 512-byte blocks */
  size_t   f_links;     /*!< Number of links */
  size_t   f_dirs;      /*!< Number of directories */
  size_t   f_ram;       /*!< Total RAM used by the FS */
};



#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Mount a TARFS filesystem from an OS-specific resource.
 *
 * The filesystem image is obtained using the OS abstraction layer function
 * tarfs_os_map_tarfile(). The `label` parameter is passed to this function
 * unchanged and is treated as an opaque identifier by TARFS.
 *
 * Depending on the platform, `label` may represent a partition name,
 * resource name, device identifier, or any other OS-specific object.
 *
 * The mount point is normally obtained from the TARFS image metadata.
 * It can be overridden explicitly by providing `mountpoint`.
 *
 * @param label
 *        Opaque resource identifier passed to tarfs_os_map_tarfile().
 *
 * @param mountpoint
 *        Optional mount point override. If NULL, the mount point stored
 *        in the TARFS image is used.
 *
 * @param link_rebase
 *        Optional path prefix used to rebase symbolic links.
 *
 * @return
 *        Filesystem slot index. The returned value can be passed to
 *        tarfs_getfs() to obtain the raw filesystem pointer.
 *
 * @note
 *        On platforms without a native VFS layer, the returned filesystem
 *        index can be used for direct TARFS access.
 */
int tarfs_mount(const char *label, const char *mountpoint, const char *link_rebase, const char *path_rebase);


/**
 * @brief Mount a TARFS filesystem from an already mapped memory buffer.
 *
 * Unlike tarfs_mount(), this function does not use OS-specific resource
 * mapping. The caller provides a pointer to an existing TAR image and its
 * size directly.
 *
 * This mode is suitable for TARFS images stored as linked firmware resources,
 * embedded binary blobs, or any other memory region accessible by the
 * application.
 * @note
 *        TARFS does not copy the filesystem image. The supplied memory region
 *        must remain valid and unchanged while the filesystem is mounted.
 *
 * @param addr
 *        Pointer to the beginning of the TAR image.
 *
 * @param length
 *        Size of the TAR image in bytes.
 *
 * @param mountpoint
 *        Mount point assigned to the filesystem.
 *
 * @param link_rebase
 *        Optional path prefix used to rebase symbolic links.
 *
 * @param path_rebase
 *        Optional override for a root dir. Will be stripped off every name. 
 *        Normally autodetected, but autodetection MAY fail on damaged filesystem
 *
 * @return
 *        Filesystem slot index. The returned value can be passed to
 *        tarfs_getfs() to obtain the raw filesystem pointer.
 */
int tarfs_mount_memory(const void *addr, size_t length,
                       const char *mountpoint,
                       const char *link_rebase,
                       const char *path_rebase);
/**
 * Unmount tar file system
 * @return 0  on success
 *         <0 FS is scheduled for unmount, but unmount is delayed because FS has some active users
 */
int  tarfs_unmount(const char *mountpoint);

/**
 * Perform a deep filesystem integrity check.
 *
 * Verifies the integrity of file contents if CRC64 checksums are present
 * in the archive. If there are no CRC64 sums then this function only checks headers
 *
 * @param label Filesystem label.
 * @return Number of entries that failed verification. If the actual TAR archive is smaller than 
 *         size of a flash region where TAR file resides, then trailing garbage will be counted as
 *         "failed etries"
 */
unsigned int tarfs_fsck(const char *label);


/**
 * @brief Enable, disable, or query per-open filesystem integrity checking.
 *
 * Enables or disables CRC64 integrity checking on every open() call for the
 * filesystem identified by @p fs_idx. This provides additional protection
 * against data corruption, but increases the time required to open a file.
 *
 * By default, CRC64 integrity is checked when the filesystem is mounted.
 * For systems with long uptimes, however, checking integrity only at mount
 * time may not be sufficient.
 *
 * @param fs_idx Filesystem index as returned by tarfs_mount() or tarfs_fsindex().
 * @param en     0 to disable checking, 1 to enable checking, or -1 to leave the current setting unchanged
*
* @return The previous setting before applying @p en.
*/

int tarfs_integrity_on_open(int fs_idx, int en);

/**
 * @brief Find the filesystem responsible for a given path.
 *
 * Searches all mounted filesystems and returns the filesystem whose mount
 * point is the longest prefix of the supplied path. This allows nested mount
 * points to work correctly. For example, if both `/data` and `/data/logs`
 * are mounted, the path `/data/logs/app.txt` resolves to the latter.
 *
 * A mount point matches only if it forms a complete path component. For
 * example, `/foo` matches `/foo` and `/foo/bar`, but does not match
 * `/foobar`.
 *
 * @param path
 *        Absolute path to resolve.
 *
 * @return
 *        Filesystem slot index, or -1 if no mounted filesystem matches the
 *        specified path.
 */
int tarfs_fsindex(const char *path);


/**
 * Get filesystem size information.
 *
 * @param mp
 *        Mount point
 *
 * @param[out] raw_size
 *        Receives the total TAR archive size in bytes.
 *        May be NULL.
 *
 * @param[out] data_size
 *        Receives the total size of all file data in bytes.
 *        May be NULL.
 *
 * @return
 *        0 if success, -1 otherwise
 * @note This function may be used to check if FS is mounted by checking if
 *       tarfs_info(mountpoint, NULL, NULL) == 0
 */
int tarfs_info(const char *mp, size_t *raw_size, size_t *data_size);


/**
 * Obtain filesystem statistics.
 *
 * Fills a POSIX statvfs structure with information about the mounted
 * filesystem. Since TARFS is a read-only filesystem, the number of
 * available blocks and inodes is always reported as zero.
 *
 * @param ctx Filesystem context.
 * @param st  Pointer to the statvfs structure to fill.
 *
 * @return 0 on success, or -1 on error with errno set appropriately.
 */
int tarfs_statvfs(void *ctx, struct statvfs *st);



/**
 * Dump internal filesystem information for debugging.
 *
 * @param fs_idx
 *        Filesystem index returned by tarfs_mount().
 *
 */
int tarfs_dump(int fs_idx);



/******************************************************************
 * Internal API, not to be used by user program
 * 
 *******************************************************************/



/**
 * Filesystem reference counting.
 *
 * tarfs_addref() acquires a reference to the filesystem, while
 * tarfs_unref() releases it. When the reference count reaches zero,
 * the filesystem will be destroyed/unmounted.
 */
int tarfs_addref(struct tarfs_fs *fs);
int tarfs_unref(struct tarfs_fs *fs);

/**
 * Obtain raw pointer to the filesystem descriptor by filesystem slot
 * (value returned by tarfs_mount())
 * Used internally
 * Platforms without VFS support will require user to pass FS descriptor manually to
 * tarfs_read()/tarfs_open()/etc. Pointer returned by this function can not be stored
 */
struct tarfs_fs *tarfs_getfs(int i);

/**
 * Obtain raw pointer to the filesystem descriptor by filesystem slot
 * Increment FS refcounter, used internally
 */
struct tarfs_fs *tarfs_getfs_addref(int i);

/* Implementation of a calloc() and a strdup() via memory backend
 *
 */
void *tarfs_calloc(size_t count, size_t size);
char *tarfs_strdup(char const *str);
/**
 * Platform abstraction helpers.
 *
 * tarfs_lock() and tarfs_unlock() protect access to the s_tarfs[] table
 * and the s_numfs counter. tarfs_init() initializes the platform layer.
 */
static inline void tarfs_lock()   { tarfs_os_acquire_mutex(); }
static inline void tarfs_unlock() { tarfs_os_release_mutex(); }
static inline void tarfs_init()   { tarfs_os_init(); }


#ifdef __cplusplus
};
#endif
