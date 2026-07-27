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


/**
 * Use case:
 *
 * @code
 *
 * if (addref(&obj->ref)) { // <-- guarantees object is alive
 *     use_object(obj);
 *     unref(&obj->ref, obj);
 * }
 *
 * @endcode
 */

#pragma once

/* Compilation issues (C / C++): these two languages use different atomic libraries, with different
 * syntax. This is completely safe, as C++ code does not touch tarfs atomics
 */
#ifdef __cplusplus
#  undef _Atomic
#  define _Atomic(X) X
#endif


/**
 * @brief Reference counter type.
 *
 * Native CPU integer size is usually the fastest option.
 */
typedef unsigned int refc_type_t;

/**
 * @brief Atomic reference counter type.
 */
typedef _Atomic(refc_type_t) refc_t;


#ifndef __cplusplus

#include <stdint.h>
#include <stdatomic.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * @brief Initialize reference counter.
 *
 * Set reference counter value to 1.
 *
 * @param ref : pointer to reference counter.
 *
 * @note If /ref/ is NULL, this function does nothing.
 */
static inline void initref(refc_t *ref) {

  if (ref != NULL)
    atomic_init(ref, 1);
}


/**
 * @brief Initialize reference counter with specified value.
 *
 * Set reference counter value to /n/.
 *
 * @param ref : pointer to reference counter.
 * @param n : initial reference counter value.
 *
 * @note If /ref/ is NULL, this function does nothing.
 */
static inline void initrefn(refc_t *ref, refc_type_t n) {

  if (ref != NULL)
    atomic_init(ref, n);
}



/**
 * @brief Increase reference counter by specified value.
 *
 * This function attempts to increase reference counter by /n/.
 *
 * @param ref : pointer to reference counter.
 * @param n : number of references to add.
 *
 * @return : refcount value AFTER addref(). Returned value of Zero means this object
 *           is either dead or can not increase its refcounter anymore (overflow)
 *
 * @note This function fails if reference counter is zero.
 *
 * @note This function fails if incrementing the counter would cause
 *       an overflow.
 *
 * @note If /n/ is zero, function performs a liveness check.
 */
refc_type_t addrefn(refc_t *ref, refc_type_t n);


/**
 * @brief Increase reference counter.
 *
 * Increase reference counter by 1.
 *
 * @param ref : pointer to reference counter.
 *
 * @return : refcounter value after increment or 0
 *
 * @note This function fails if reference counter is zero.
 */
static inline refc_type_t addref(refc_t *ref) {

  return addrefn(ref, 1);
}

/**
 * @brief Release references and optionally destroy object.
 *
 * Decrease reference counter by /n/. When reference counter reaches
 * zero, destructor function /dtor/ is called.
 *
 * @param r : pointer to reference counter.
 *
 * @param object : object controlled by the reference counter.
 *
 * @param n : number of references to release. If `n` is zero, function performs a liveness check.
 *            If /n/ is greater than current reference count, reference
 *            counter is decremented until it reaches zero. Destructor
 *            function is called exactly once.
 *
 * @param dtor : destructor function. standart C function free() can be used here
 *              If `dtor` is NULL, object is not destroyed even when reference counter reaches zero, possibly creating a memory leak.
 * 
 * @return Value of a refcounter before unreferencing. Value of 1 means object was deleted
 *         i.e. if (unrefxn( ... ) == 1) puts("Last reference gone, object has been deleted");
 *
 *         Value of 0 is returned when some fatal eeror is occured: attempt to unref the object which 
 *         is being deleted; pointer to the `r` is NULL
 *
 *
 * @note Destructor function receives /object/ as its argument.
 *       If /object/ is NULL, reference counter pointer /r/ is passed
 *       to the destructor instead. 
 *       If reference counter /ref/ is the first member of the object (i.e. embedded into the object),
 *       /object/ may be NULL.
 *
 *
 * @note It is safe to call unrefxn() with the same /n/ value that
 *       was previously passed to addrefn(), even if current reference
 *       count becomes smaller than /n/.
 */
refc_type_t unrefxn(refc_t *r,
             void *object,
             refc_type_t n,
             void (*dtor)(void *));



/**
 * @brief Release reference and destroy object if no references remain.
 *
 * This function is equivalent to:
 *
 *     unrefxn(ref, object, 1, free);
 *
 * @param ref : pointer to reference counter.
 * @param object : object controlled by the reference counter.
 * 
 * @return Value of a refcounter before unreferencing. Value of 1 means object was deleted
 *         i.e. if (unref( ... ) == 1) puts("Last reference gone, object has been deleted");
 */
static inline refc_type_t unref(refc_t *ref, void *object) {

  return unrefxn(ref, object, 1, free);
}

/**
 * @brief Release multiple references and destroy object if no references remain.
 *
 * This function is equivalent to:
 *
 *     unrefxn(ref, object, n, free);
 *
 * @param ref : pointer to reference counter.
 * @param object : object controlled by the reference counter.
 * @param n : number of references to release.
 * 
 * @return Value of a refcounter before unreferencing. Value of 1 means object was deleted
 *         i.e. if (unrefn( ... ) == 1) puts("Last reference gone, object has been deleted");
 */
static inline refc_type_t unrefn(refc_t *ref, void *object, refc_type_t n) {

  return unrefxn(ref, object, n, free);
}

/**
 * @brief Release reference and call custom destructor.
 *
 * This function is equivalent to:
 *
 *     unrefxn(ref, object, 1, dtor);
 *
 * @param ref : pointer to reference counter.
 * @param object : object controlled by the reference counter.
 * @param dtor : destructor function.
 * 
 * @return Value of a refcounter before unreferencing. Value of 1 means object was deleted
 */
static inline refc_type_t unrefx(refc_t *ref, void *object, void (*dtor)(void *)) {

  return unrefxn(ref, object, 1, dtor);
}

/**
 * @brief Read refcounter atomically
 *
 * @param r : pointer to reference counter.
 *
 * @return : current counter value
 *
 * @note Returned value is intended for diagnostics and statistics.
 *       Reference counter value may change immediately after return.
 *
 */
static inline refc_type_t readref(refc_t *r) {

    return r ? atomic_load_explicit(r, memory_order_relaxed) : 0;
}

#endif /* not __cplusplus */

