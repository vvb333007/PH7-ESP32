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
 */

#pragma once

//#define CONFIG_TARFS_LOG        1       /*!< Enable verbose logging, lots of text! for development or bug hunting */

#define CONFIG_TARFS_MAX_FS  4          /*!< Max number of mounted TARFS filesystems */
#define CONFIG_TARFS_MAX_FDS 32         /*!< Max number of active opened files (per filesystem, must be < 33) */

//#define CONFIG_TARFS_INTEGRITY  1       /*!< Check data integrity records. FS must be processed with tarsum utility or mount will fail */
#define CONFIG_TARFS_EXTMEM 1           /*!< Use external memory where available (e.g. PSRAM on ESP32) */

#define CONFIG_TARFS_HAVE_FDOPENDIR  1  /*!< Support for fdopendir() */
#define CONFIG_TARFS_HAVE_MMAP  1       /*!< Support for mmap()/munmap() */
#define CONFIG_TARFS_HAVE_DUPFD  1      /*!< Support for dupfd() */
#define CONFIG_TARFS_HAVE_STATVFS  1    /*!< Support for statvfs() */
#define CONFIG_TARFS_HAVE_SENDFILE 1    /*!< Support for zero-overhead sendfile() */



#define CONFIG_TARFS_COUNTERS 1        /*!< Support runtime stats */
//#define CONFIG_TARFS_BIG_ENDIAN 1      /*!< Set to 1 on bige-endian architectures */


/*!< Set to 1 to use a .S version of tarfs_os_memcpy().
 *   Currently only available on ESP32-S3 and P4:
 *   Select an appropriate .S file from docs/ports/ folder and copy it to the src/ folder
 *   Uncomment CONFIG_TARFS_HAVE_OPTIMIZED_MEMCPY 
 */
//#define CONFIG_TARFS_HAVE_OPTIMIZED_MEMCPY 1 


/* tarsum utility settings */
#ifdef TARSUM_BUILD
#  undef CONFIG_TARFS_LOG
#  undef CONFIG_TARFS_HAVE_FDOPENDIR  /* Incompatible with glibc targets (e.g. Linux or Cygwin)*/
#  define CONFIG_TARFS_INTEGRITY  1   /* Explicit integrity */
#  define CONFIG_TARFS_LOG 1          /* Explicit logging if building tarsum utility */
#endif
