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
 * @file file.h
 * @brief Public file API
 */

#pragma once

/**
 * TARFS File API: tarf_open(), tarf_close(), tarf_read(),
 * tarf_pread(), tarf_lseek(), tarf_mmap(), tarf_munmap(),
 * tarf_dupfd(), tarf_stat(), tarf_fstat(), tarf_fcntl(), tarf_ioctl()
 *
 * tarf_dupfd() is similar to POSIX dup(), except that the duplicated file
 * descriptor does not share its file position with the original. Instead,
 * a completely independent copy of the file descriptor is created.
 *
 * How it works:
 * open() uses inode_lookup() to find the requested inode, allocates a file
 * descriptor structure, initializes it from the inode, and increments the
 * filesystem reference count.
 *
 * close() decrements the filesystem reference count.
 *
 * read() and pread() are implemented as simple memcpy() operations.
 *
 * Functions that operate on a file descriptor rely on the open()/close()
 * reference-counting protocol. The filesystem reference is acquired by
 * open() and released by close(), guaranteeing that the filesystem remains
 * valid for the lifetime of every open file descriptor.
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include "config.h"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * This internal file descriptor maps to a local fd number 
 * as descriptor_ptr = s_tarfs[slot]->fs_fds[local_fd];
 *
 * @brief TARFS file descriptor, 16 bytes
 *
 */
struct tarfs_fp {

  uintptr_t fp_vaddr;  /*!< file virtual address, absolute. zero indicates unused fd.  */
  uint32_t  fp_pos;    /*!< current file pointer position. can be set 1 byte past the file end, i.e. fp_pos = fp_size */
  size_t    fp_size;   /*!< file size in bytes. NOTE: If fp_size is 0, then fp_vaddr could be invalid and must not be read */
  int       fp_idx;    /*!< associated inode index */
};


/* VFS handlers below are normally invoked through a VFS.
 *
 * On systems without VFS support, applications should call the tarfs_(),
 * tarf_() and tard_() APIs directly. Unlike their POSIX counterparts, these
 * functions take an additional first argument: an index of the mounted
 * filesystem
 *
 * Typical usage without a VFS:
 *
 * 1. Mount the filesystem and save its identifier.
 *
 *      int ctx = tarfs_mount(...);
 *      if (ctx < 0)
 *          exit_error("failed to mount filesystem");
 *
 * 2. Use the context pointer in subsequent filesystem calls.
 *
 *      int fd1 = tarf_open((void *)ctx, "/home/file1.txt", flags);
 *      int fd2 = tarf_open((void *)ctx, "/home/file2.txt", flags);
 *      int fd3 = tarf_open((void *)ctx, "/home/file3.txt", flags);
 */




/* close()
 * FS has at least 1 extra ref, because of open()
 *
 * close() is not thread-safe. It is not as bad as it seems: no crashes, no sigsegv.
 * Just DO NOT close() files being read() at the same time by another thread. Or, if you do, 
 * do not open another file immediately :)
 *
 * This is because of:
 *
 * Closing a file descriptor while another thread is executing read()
 * (or any operation using the same descriptor) is undefined behaviour.
 *
 * Since file descriptor slots are immediately reusable, a concurrent
 * open() may repurpose the same slot for another file before the running
 * operation completes, causing it to access the newly opened file instead
 * of the original one.
 *
 */
int tarf_close(void* ctx, int fd);

/**
 * @brief Open a TARFS file or directory.
 *
 * Opens an existing TAR archive entry and returns a TARFS file descriptor.
 * Both regular files and directories may be opened. Directories cannot be
 * read using read(), but the returned descriptor may be used with functions
 * such as fstat(), fcntl(), ioctl(), close(), etc.
 *
 * TARFS is a read-only filesystem. Attempts to open an entry for writing or
 * with @c O_TRUNC fail with @c EROFS.
 *
 * @param ctx   Filesystem instance.
 * @param path  Absolute path within the mounted TARFS.
 * @param flags POSIX open() flags.
 * @param mode  Creation mode (ignored).
 *
 * @return Non-negative TARFS file descriptor on success.
 * @retval -1 Error. Possible @c errno values include:
 *         - @c EINVAL  Invalid path.
 *         - @c ENOENT  Entry not found.
 *         - @c EROFS   Write access requested on a read-only filesystem.
 *         - @c EMFILE  No free file descriptors.
 *         - @c ENODEV  Filesystem has been unmounted.
 *         - @c EIO     Corrupted inode.
 */
int tarf_open(void* ctx, const char * path, int flags, int mode);

/**
 * @brief Read data from an open TARFS file.
 *
 * Copies up to @p size bytes from the current file position into @p dst and
 * advances the file position by the number of bytes actually read.
 *
 * @return Number of bytes read, or -1 on error.
 */
ssize_t tarf_read(void* ctx, int fd, void *dst, size_t size);

/**
 * @brief Read data from an open TARFS file at a specified offset.
 *
 * Copies up to @p size bytes starting at @p offset into @p dst.
 * Unlike read(), this function does not modify the current file position.
 *
 * @return Number of bytes read, or -1 on error.
 */
ssize_t tarf_pread(void* ctx, int fd, void *dst, size_t size, off_t offset);

/**
 * @brief lseek()
 *
 * Copies up to @p size bytes from the current file position into @p dst and
 * advances the file position by the number of bytes actually read.
 *
 * @param ctx Filesystem instance.
 * @param fd  TARFS file descriptor.
 * @return Number of bytes read, or -1 on error.
 */
off_t tarf_lseek(void* ctx, int fd, off_t offset, int whence);

/**
 * @brief Get file status information.
 *
 * Fills a POSIX @ref stat structure for an open TARFS file descriptor.
 * Since TARFS is read-only, only read permission bits are reported.
 * Directory entries additionally have execute bits set to allow traversal.
 *
 * @param ctx Filesystem instance.
 * @param fd  TARFS file descriptor.
 * @param st  Output structure to receive file information.
 *
 * @retval 0   Success.
 * @retval -1  Invalid file descriptor (@c errno = EBADF).
 */
int tarf_fstat(void* ctx, int fd, struct stat * st);

/**
 * @brief Synchronize file contents.
 *
 * TARFS is a read-only filesystem, therefore there is nothing to flush.
 * This function validates the file descriptor and always succeeds.
 *
 * @param ctx Filesystem instance.
 * @param fd  TARFS file descriptor.
 *
 * @retval 0   Success.
 * @retval -1  Invalid file descriptor (@c errno = EBADF).
 */
int tarf_fsync(void* ctx, int fd);

/**
 * @brief Perform file descriptor control operations.
 *
 * Supports a minimal subset of POSIX @c fcntl() commands.
 * TARFS is inherently non-blocking, therefore @c F_SETFL is accepted
 * but ignored. @c F_GETFL always reports @c O_NONBLOCK.
 *
 * @param ctx Filesystem instance.
 * @param fd  TARFS file descriptor.
 * @param cmd Control command.
 * @param arg Command argument.
 *
 * @retval >=0 Command-dependent result.
 * @retval -1 Unsupported command (@c errno = ENOSYS).
 */
int tarf_fcntl(void *ctx, int fd, int cmd, int arg);

/**
 * @brief Perform TARFS-specific I/O control operations.
 *
 * Supported commands:
 * - @c FIONREAD  - returns the number of unread bytes remaining.
 * - @c FIONBIO   - accepted for compatibility and ignored.
 * - @c FIOGETFD  - exports the TARFS descriptor and local file descriptor.
 *
 * The @c FIOGETFD command increments the filesystem reference count before
 * returning the filesystem pointer. The caller is responsible for releasing
 * it with @c unrefx() when it is no longer needed.
 *
 * @param ctx  Filesystem instance.
 * @param fd   TARFS file descriptor.
 * @param cmd  I/O control command.
 * @param args Command-specific arguments.
 *
 * @retval 0   Success.
 * @retval -1  Error. Possible @c errno values include:
 *             - @c EBADF   Invalid file descriptor.
 *             - @c EINVAL  Invalid command argument.
 *             - @c ENODEV  Filesystem is no longer available.
 *             - @c ENOSYS  Unsupported ioctl command.
 */
int tarf_ioctl(void *ctx, int fd, int cmd, va_list args);

/**
 * Retrieve file status information.
 *
 * This function retrieves information about the file specified by @p path
 * and stores it in the @p struct stat structure pointed to by @p st.
 *
 * TARFS is a read-only filesystem, therefore the returned status information
 * describes the file as a regular file or directory without any write-related
 * filesystem semantics.
 *
 * @param[in]  ctx
 *     TARFS filesystem context.
 *
 * @param[in]  path
 *     Path to the file or directory whose status is to be retrieved.
 *
 * @param[out] st
 *     Pointer to a @p struct stat structure that receives the file status
 *     information.
 *
 * @return 0 on success, <0 on error, with @c errno set to indicate the error.
 *
 * @see stat()
 */
int tarf_stat(void* ctx, const char *path, struct stat *st);



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
 * @param ctx  Filesystem context.
 * @param fd
 *     File descriptor to duplicate.
 *
 * @return
 *     New file descriptor on success, or -1 on error.
 */
int tarf_dupfd(void *ctx, int fd);

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
 * @param ctx  Filesystem context.
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
void *tarf_mmap(void *ctx, void *addr, size_t length, int prot, int flags, int fd, off_t offset);


/**
 * Remove a previously created memory mapping.
 *
 * Since mappings themselves do not allocate runtime resources, failing to call
 * munmap() does not lead to resource leaks. However, an active mapping keeps
 * the filesystem mounted, preventing it from being unmounted until the mapping
 * is removed.
 *
 * @param ctx  Filesystem context.
 * @param addr Address previously returned by mmap().
 * @param length Length of the mapped region.
 *
 * @return 0 on success, or -1 on error.
 */
int tarf_munmap(void *ctx, void *addr, size_t length);

/**
 * Send TARFS file to a socket
 *
 * This function transfers data directly from @p in_fd to @p out_fd without
 * requiring an intermediate user buffer.
 *
 * @param ctx  Filesystem context.
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
ssize_t tarf_sendfile(void *ctx, int sock, int fd, off_t *offset, size_t count);

#ifdef __cplusplus
};
#endif

/* Compile-time sanity checks. */
_Static_assert(TARFS_MAX_FDS > 0 && TARFS_MAX_FDS <= 32, "Code review is required");
