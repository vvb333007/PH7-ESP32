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

/**
 * Edit this file to change TARFS compile-time setting
 * 
 *
 */

#define CONFIG_TARFS_VERSION 0x00000105 /*!< Version number: 0.1.5 */
//#define CONFIG_TARFS_LOG     1          /*!< Enable verbose logging, lots of text! for development or bug hunting */

#define CONFIG_TARFS_MAX_FS  4          /*!< Max number of mounted TARFS filesystems */
#define CONFIG_TARFS_MAX_FDS 16         /*!< Max number of active opened files (per filesystem, must be < 33) */

#define CONFIG_TARFS_INTEGRITY 0        /*!< Check data integrity records. FS image must be processed with
                                             tarsum utility or, if it isn't, tarfs_integrity(0) must be 
                                             called before attempting to mount */

#define CONFIG_TARFS_EXTMEM 1           /*!< Use external memory where available (e.g. PSRAM on ESP32) */


#define CONFIG_TARFS_HAVE_FDOPENDIR  1  /*!< Support for fdopendir() */
#define CONFIG_TARFS_HAVE_MMAP  1       /*!< Support for mmap()/munmap() */
#define CONFIG_TARFS_HAVE_DUPFD  1      /*!< Support for dupfd() */
#define CONFIG_TARFS_HAVE_STATVFS  1    /*!< Support for statvfs() */
#define CONFIG_TARFS_HAVE_SENDFILE 1    /*!< Support for zero-overhead sendfile() */


#define CONFIG_TARFS_COUNTERS 1         /*!< Support runtime stats */
//#define CONFIG_TARFS_BIG_ENDIAN 1     /*!< Set to 1 on bige-endian architectures */
//#define CONFIG_TARFS_HAVE_STATVFS_H 1 /*!< If platform provides its own sys/statvfs.h, this macro shuould be uncommented */

/* tarsum utility settings, please do not change */
#ifdef TARSUM_BUILD
#  undef CONFIG_TARFS_INTEGRITY
#  undef CONFIG_TARFS_LOG
#  undef CONFIG_TARFS_HAVE_FDOPENDIR  /* Incompatible with glibc targets (e.g. Linux or Cygwin)*/

#  define CONFIG_TARFS_INTEGRITY  1   /* Explicit integrity */
#  define CONFIG_TARFS_LOG 1          /* Explicit logging if building tarsum utility */
#endif
