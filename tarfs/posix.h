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
 * @file posix.h
 * @brief POSIX extensions API
 */

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>

/**
 * @brief POSIX mmap()/munmap() support for TARFS
 */
#define PROT_READ     1  /*!< Default memory protection flag. */
#define PROT_WRITE    2  /*!< Ignored, if used together with PROT_READ. Alone causes mmap() error (RO filesystem!) */
#define PROT_EXEC     4  /*!< Ignored */

#define MAP_FILE      0  /*!< Default flag is MAP_FILE, we do not support MAP_ANON, we always expect MAP_FILE */
#define MAP_SHARED    1  /*!< Supported */
#define MAP_PRIVATE   2  /*!< Supported */

#define MAP_FIXED     4  /*!< Ignored, no legit use for this flag :) */
#define MAP_ANONYMOUS 8  /*!< Unsupported, use malloc() instead */
#define MAP_ANON      8 


#define MAP_FAILED   ((void *)(-1))




#ifdef __cplusplus
extern "C" {
#endif
/**
 * Map a file into the process address space.
 *
 * Typical usage:
 *
 * @code
 * int fd = open(...);
 * void *ptr = mmap(NULL, length, PROT_READ, flags, fd, offset);
 * close(fd);
 *
 * // use ptr
 * @endcode
 *
 * The mapping remains valid after the file descriptor has been closed.
 *
 * Since TARFS is a read-only filesystem, this implementation does not support
 * the PROT_WRITE protection flag. MAP_ANONYMOUS is also not supported:
 * mmap() is intended exclusively for mapping files.
 *
 * There is no limit on the number of active mappings. Every file in TARFS may
 * be mapped simultaneously, provided the underlying flash memory can hold it.
 * Mappings do not consume any runtime resources. In contrast, each open file
 * occupies one file descriptor until it is closed.
 *
 * @param addr Must be NULL. Fixed-address mappings are not supported.
 * @param length Number of bytes to map.
 * @param prot Memory protection flags. Only PROT_READ is supported.
 * @param flags Mapping flags. Use MAP_SHARED or MAP_PRIVATE. On a read-only
 *              filesystem both behave identically.
 * @param fd Open file descriptor to map.
 * @param offset File offset where the mapping begins.
 *
 * @return Pointer to the mapped file data, or MAP_FAILED on error.
 */
void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);


/**
 * Remove a previously created memory mapping.
 *
 * Since mappings themselves do not allocate runtime resources, failing to call
 * munmap() does not lead to resource leaks. However, an active mapping keeps
 * the filesystem mounted, preventing it from being unmounted until the mapping
 * is removed.
 *
 * @param addr Address previously returned by mmap().
 * @param length Length of the mapped region.
 *
 * @return 0 on success, or -1 on error.
 */
int munmap(void *addr, size_t length);

#if CONFIG_TARFS_HAVE_FDOPENDIR
/**
 * @brief Associate an open directory file descriptor with a directory stream.
 *
 * Creates a directory stream from an existing directory file descriptor.
 * After a successful call, the file descriptor is owned by the returned
 * directory stream and must not be closed directly. It will be closed
 * automatically by tard_closedir().
 *
 * @param fd Directory file descriptor obtained by tarf_open() with
 *           O_DIRECTORY.
 *
 * @return
 *   A pointer to a directory stream on success, or NULL on failure with
 *   errno set appropriately.
 */
DIR *fdopendir(int fd);
#endif /* CONFIG_TARFS_HAVE_FDOPENDIR */

#if CONFIG_TARFS_HAVE_DUPFD
/**
 * Create an independent duplicate of a file descriptor.
 *
 * This function is similar to POSIX dup(), but the file position is
 * not shared. The new descriptor has its own independent file offset,
 * initialized to the current position of the original descriptor.
 *
 * Both descriptors refer to the same file, but subsequent seek/read
 * operations affect their positions independently.
 *
 * Unlike POSIX dup(), this function does not use shared open file
 * description semantics. It is provided as a lightweight alternative
 * suitable for read-only TARFS files.
 *
 * @param fd
 *     File descriptor to duplicate.
 *
 * @return
 *     New file descriptor on success, or -1 on error.
 */
int dupfd(int fd);
#endif /* CONFIG_TARFS_HAVE_DUPFD */


#if CONFIG_TARFS_HAVE_STATVFS
/**
 * Obtain filesystem statistics.
 *
 * Fills a POSIX statvfs structure with information about the mounted
 * filesystem. Since TARFS is a read-only filesystem, the number of
 * available blocks and inodes is always reported as zero.
 *
 * @param st  Pointer to the statvfs structure to fill.
 *
 * @return 0 on success, or -1 on error with errno set appropriately.
 */
int statvfs(const char *path, struct statvfs *st);
#endif /* CONFIG_TARFS_HAVE_STATVFS */

#if CONFIG_TARFS_HAVE_SENDFILE
/**
 * Copy data from one file descriptor to another.
 *
 * This function transfers data directly from @p in_fd to @p out_fd without
 * requiring an intermediate user buffer.
 *
 * @param out_fd  Destination file descriptor. Must be a socket.
 *
 * @param in_fd   Source file descriptor. A tarfs descriptor
 * @param offset  Optional starting offset in the input file. If NULL, the
 *                current file position is used and advanced. Otherwise,
 *                the value pointed to by @p offset is used and updated,
 *                while the file position of @p in_fd remains unchanged.
 * @param count   Maximum number of bytes to transfer.
 *
 * @return Number of bytes transferred on success, or -1 on error with errno set.
 *
 */
ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
#endif /* #if CONFIG_TARFS_HAVE_SENDFILE */

#ifdef __cplusplus
};
#endif
