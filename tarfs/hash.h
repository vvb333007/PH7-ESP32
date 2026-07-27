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
 * @file hash.h
 * @brief Public hash functions API
 */


/**
 *  1) CRC64/ECMA182 algorithm implementation (no tables version, slow but memory-efficient
 *  2) Optimized variation of the FNV-1a hash algorithm.
 */

#pragma once

#include <stdint.h>
#include <stddef.h> /* size_t */

#define HASH32_IV     (uint32_t)(2166136261u)   /*!< Init vector for 32bit hash */
#define HASH32_SLASH  (uint32_t)(0x2a0c975eu)   /*!< Hash32 value of a single-character C-string "/". NOTE: must be recomputed if hash32 algo is changed! */
#define HASH64_IV     0ULL                      /*!< Init vector for 64bit hash */

#ifdef __cplusplus
extern "C" {
#endif
/**
 * @brief Compute FNV-1a hash over a byte buffer
 *
 * This function supports incremental hashing:
 *
 *     h = hash32(HASH32_IV, data1, len1);
 *     h = hash32(h,        data2, len2);
 *     h = hash32(h,        data3, len3);
 *     ....
 *
 * @param prev_hash initial hash state (use HASH32_IV for fresh hash)
 * @param data      Input byte buffer
 * @param len       Length of input buffer
 *
 * @return Updated 32-bit FNV-1a hash
 *
 */
uint32_t hash32(uint32_t prev_hash, uint8_t const *data, size_t len);


/**
 * @brief Compute CRC64/ECMA182 hash over a byte buffer
 *
 * This function supports incremental hashing:
 *
 *     h = hash64(HASH64_IV, data1, len1);
 *     h = hash64(h,        data2, len2);
 *     h = hash64(h,        data3, len3);
 *     ....
 *
 * @param prev_hash initial hash state (use HASH32_IV for fresh hash)
 * @param data      Input byte buffer
 * @param len       Length of input buffer
 *
 * @return Updated 64-bit CRC64 sum
 *
 */
uint64_t hash64(uint64_t prev_hash, void const *data, size_t len);

#ifdef __cplusplus
};
#endif
