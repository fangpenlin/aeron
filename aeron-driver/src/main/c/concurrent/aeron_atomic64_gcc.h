/*
 * Copyright 2014-2019 Real Logic Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef AERON_ATOMIC64_GCC_H
#define AERON_ATOMIC64_GCC_H

#include <stdbool.h>

#define AERON_GET_VOLATILE(dst, src) \
do \
{ \
    dst = src; \
    __asm__ volatile("" ::: "memory"); \
} \
while (false)

#define AERON_PUT_ORDERED(dst, src) \
do \
{ \
    __asm__ volatile("" ::: "memory"); \
    dst = src; \
} \
while (false)

#define AERON_PUT_VOLATILE(dst, src) \
do \
{ \
    __asm__ volatile("" ::: "memory"); \
    dst = src; \
    __asm__ volatile("" ::: "memory"); \
} \
while (false)

#define AERON_GET_AND_ADD_INT64(original, dst, value) \
    dst = __atomic_fetch_add(&original, value, __ATOMIC_SEQ_CST)

#define AERON_GET_AND_ADD_INT32(original, dst, value) \
    dst = __atomic_fetch_add(&original, value, __ATOMIC_SEQ_CST)

inline bool aeron_cmpxchg64(volatile int64_t* destination, int64_t expected, int64_t desired)
{
    // Semantics: return _InterlockedCompareExchange64(destination, desired, expected);
    if (__atomic_compare_exchange(destination, &expected, &desired, false /* strong */, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
        return expected;
    } else {
        return *destination;
    }
}

inline bool aeron_cmpxchgu64(volatile uint64_t* destination, uint64_t expected, uint64_t desired)
{
    // Semantics: return _InterlockedCompareExchange64(destination, desired, expected);
    if (__atomic_compare_exchange(destination, &expected, &desired, false /* strong */, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
        return expected;
    } else {
        return *destination;
    }
}

inline bool aeron_cmpxchg32(volatile int32_t* destination, int32_t expected, int32_t desired)
{
    // Semantics: return _InterlockedCompareExchange(destination, desired, expected);
    if (__atomic_compare_exchange(destination, &expected, &desired, false /* strong */, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST)) {
        return expected;
    } else {
        return *destination;
    }
}

/* loadFence */
#define aeron_acquire() \
    __atomic_thread_fence (__ATOMIC_ACQUIRE)

/* storeFence */
#define aeron_release() \
    __atomic_thread_fence (__ATOMIC_RELEASE)

/*-------------------------------------
 *  Alignment
 *-------------------------------------
 * Note: May not work on local variables.
 * http://gcc.gnu.org/bugzilla/show_bug.cgi?id=24691
 */
#define AERON_DECL_ALIGNED(declaration, amt) declaration __attribute__((aligned(amt)))

#endif //AERON_ATOMIC64_GCC_H