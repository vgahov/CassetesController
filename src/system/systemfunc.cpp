#include "systemfunc.h"

// See description
// https://stackoverflow.com/questions/7015285/undefined-reference-to-operator-deletevoid
void* operator new(size_t n) {
    void* const p = malloc(n);
    // handle p == 0
    return p;
}

void operator delete(void* p) noexcept  // or delete(void *, std::size_t)
{
    free(p);
}

void operator delete(void* p, size_t) noexcept { free(p); }

void* operator new(size_t, void* ptr) noexcept { return ptr; }

void operator delete(void*, void*) noexcept {}

namespace
{
    const double EPS = 1e-9;
}

double get_eps() { return EPS; }

uint32_t get_fclk() { return F_CPU; }
