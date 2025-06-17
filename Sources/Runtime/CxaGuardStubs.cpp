#pragma once

#include <stdint.h>

// to make static variables inside functions work, can work while we single-threaded
extern "C" {
    int __cxa_guard_acquire(uint64_t *guard) {
        return !*(char *)(guard);
    }

    void __cxa_guard_release(uint64_t *guard) {
        *(char *)guard = 1;
    }

    void __cxa_guard_abort(uint64_t *guard) {}
}
