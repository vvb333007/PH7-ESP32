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
 * @file dir.h
 * @brief Public directory API
 */

#pragma once

/**
 * TARFS Directory API: tard_opendir(), tard_fdopendir(), tard_closedir(),
 * tard_telldir(), tard_seekdir()
 *
 * tard_fdopendir() is the only function that allocates memory for the DIR
 * structure. tard_opendir() internally calls tard_fdopendir().
 *
 * How it works:
 * opendir() calls open(O_DIRECTORY) and positions its internal inode pointer
 * at the requested directory. Subsequent calls to readdir() advance this
 * pointer through the inode list (inodes are linked alphabetically via
 * ->in_next) until the next inode no longer matches the directory prefix
 * specified in opendir().
 *
 * Note on the dirent structure:
 *
 * Unlike POSIX, where d_off is an opaque implementation-defined value,
 * TARFS stores the logical directory position in this field.
 *
 * Specifically, d_off is the zero-based index of the next directory entry.
 * The value can be saved and later passed to tard_seekdir() to resume
 * directory traversal.
 */

//#ifdef __CYGWIN__
/* Glibc-based systems dont expose DIR so we use a placeholder */
//  typedef struct { int a; int b; } fake_DIR;
//# undef DIR
//# define DIR fake_DIR
//#endif


#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Associate an open directory file descriptor with a directory stream.
 *
 * Creates a directory stream from an existing directory file descriptor.
 * After a successful call, the file descriptor is owned by the returned
 * directory stream and must not be closed directly. It will be closed
 * automatically by tard_closedir().
 *
 * @param ctx TARFS context.
 * @param fd Directory file descriptor obtained by tarf_open() with
 *           O_DIRECTORY.
 *
 * @return
 *   A pointer to a directory stream on success, or NULL on failure with
 *   errno set appropriately.
 */
DIR* tard_fdopendir(void* ctx, int fd);



/**
 * @brief Open a directory for reading.
 *
 * Opens an existing directory and returns a directory stream that can be
 * used with tard_readdir(), tard_telldir(), tard_seekdir() and
 * tard_closedir().
 *
 * @param ctx  TARFS filesystem context.
 * @param name Path to the directory.
 *
 * @return Pointer to a directory stream on success, or NULL on failure.
 */
DIR* tard_opendir(void* ctx, const char* name);

/**
 * @brief Close a directory stream.
 *
 * Releases all resources associated with a directory stream previously
 * returned by tard_opendir().
 *
 * @param ctx  TARFS filesystem context.
 * @param pdir Directory stream.
 *
 * @return 0 on success, or -1 on failure.
 */
int tard_closedir(void* ctx, DIR* pdir);

/**
 * @brief Read the next directory entry.
 *
 * Returns the next direct child of the opened directory. The returned
 * pointer remains valid until the next call to tard_readdir() on the same
 * directory stream.
 *
 * @param ctx  TARFS filesystem context.
 * @param pdir Directory stream.
 *
 * @return Pointer to a dirent structure, or NULL if no more entries are
 *         available or an error occurred.
 */
struct dirent* tard_readdir(void* ctx, DIR* pdir);

/**
 * @brief Return the current directory position.
 *
 * Obtains the current position within the directory stream. The returned
 * value may later be passed to tard_seekdir() to restore the same position.
 *
 * @param ctx  TARFS filesystem context.
 * @param pdir Directory stream.
 *
 * @return Current directory position.
 */
long tard_telldir(void* ctx, DIR* pdir);

/**
 * @brief Reposition a directory stream.
 *
 * Sets the current position within the directory stream to a value
 * previously obtained by tard_telldir().
 *
 * @param ctx    TARFS filesystem context.
 * @param pdir   Directory stream.
 * @param offset Directory position previously returned by tard_telldir().
 */
void tard_seekdir(void* ctx, DIR* pdir, long offset);


/**
 * @brief The function dirfd() returns the file descriptor associated with the directory stream pdir.
 * 
 * This file descriptor is the one used internally by the directory
 * stream.  As a result, it is useful only for functions which do not
 * depend on or alter the file position, such as fstat(2) and
 * fchdir(2).  It will be automatically closed when closedir(3) is
 * called. 
 *
 * @param ctx    TARFS filesystem context.
 * @param pdir   Directory stream.
 * @return a file descriptor
*/
int tard_dirfd(void* ctx, DIR *pdir);


#ifdef __cplusplus
};
#endif
