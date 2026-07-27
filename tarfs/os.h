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
 * @file os.h
 * @brief Platform porting layer API
 */


/* Platform abstraction layer.
 *
 * The only mandatory operation is mapping the TAR image into a contiguous
 * read-only memory region. Mutex support is optional and may be implemented
 * as no-ops on single-threaded systems. Likewise, unmap may be a no-op if
 * the mapping has no associated resources.
 */

#pragma once

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <string.h>

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif
/* Platform API */

/* TARFS uses a single recursive mutex to protect its internal state.
 *
 * On single-threaded systems, or systems without suitable synchronization
 * primitives, all three functions may be implemented as no-ops.
 */
void  tarfs_os_init();              
void  tarfs_os_acquire_mutex();
void  tarfs_os_release_mutex();

/* Map a TAR filesystem image into the process address space.
 *
 * TARFS expects the archive to be accessible as a contiguous, read-only
 * memory region. How this is achieved is platform-specific:
 *
 *   - memory-mapped flash (e.g. RP2040 XIP),
 *   - runtime memory mapping (e.g. Linux, ESP-IDF),
 *   - linker-embedded binary image,
 *   - or any other mechanism that provides a linear memory view.
 *
 * The returned pointer must remain valid until tarfs_os_unmap_tarfile()
 * is called.
 */
void const *tarfs_os_map_tarfile(const char *name, void **os_handle_out, size_t *size_out);
void  tarfs_os_unmap_tarfile(void *os_handle, const void *ptr, size_t size);

/* Register or unregister TARFS with the platform VFS.
 *
 * TARFS driver calls this as a final part of the nount() process. Registration function
 * is responsible for registering FS handlers in host VFS
 *
 * On systems providing a Virtual Filesystem layer, these functions should
 * expose TARFS through the native file API (open(), read(), stat(), etc.).
 * See os_esp32.c for the sample implementation
 *
 * On systems without a VFS, both functions may be implemented as `{ return true; }`
 * Applications can then access the filesystem through the TARFS API directly.
 * See os_cygwin.c for the sample implementation
 *
 * @param prefix Path prefix (a mount point)
 * @param context A raw pointer to the driver filesystem descriptor. This pointer will be passed to
 *                each handler function (e.g. to tarfs_open(), tarfs_read() etc)
 * @return
 *   tarfs_os_register_fs():
 *     true  - registration succeeded.
 *     false - registration failed. Mounting is aborted and all resources
 *             allocated during the mount procedure are released.
 *
 *   tarfs_os_unregister_fs():
 *     true  - unregistration succeeded and TARFS may immediately release
 *             all associated resources.
 *
 *     false - unregistration could not complete because the platform may
 *             still issue delayed callbacks into this filesystem. TARFS
 *             will keep critical data structures alive to avoid use-after-
 *             free crashes. This intentionally trades a memory leak for
 *             safety.
 */
bool tarfs_os_register_fs(const char *prefix, void *context);
bool tarfs_os_unregister_fs(const char *prefix);

/**
 * Return the maximum mount point name length supported by the platform.
 *
 * Some operating systems impose a limit on mount point names. TARFS uses
 * this value when validating the archive root directory before mounting.
 *
 * For platforms without such a restriction, return SIZE_MAX.
 *
 * Example:
 *   - ESP-IDF returns 16.
 */
size_t tarfs_os_mp_maxlen();

/**
 * Memory allocation backend.
 *
 * By default, these functions map directly to malloc() and free().
 * Platform-specific implementations may override them to use a custom
 * allocator.
 *
 * Note that default implementation sets `errno` to ENOMEM if allocation fails
 * The same behavior is expected for a custom allocator 
 */
void *tarfs_os_malloc(size_t size);
void  tarfs_os_free(void *buffer);

/**
 * read() uses memcpy(), which can be optimized on many architectures
 */
#if CONFIG_TARFS_HAVE_OPTIMIZED_MEMCPY
/* rely on the .S file; see os_esp32s3.S for sample implementation */
void *tarfs_os_memcpy(void *dst, const void *src, size_t len);
#else
static inline void *tarfs_os_memcpy(void *dst, const void *src, size_t len) { 
  return memcpy(dst, src, len);
}
#endif


#ifdef __cplusplus
};
#endif