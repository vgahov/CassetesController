#ifndef SYSTEM_FUNC_H
#define SYSTEM_FUNC_H

#ifndef IAR_PROJECT
#include <stdint-gcc.h>
#endif
#include <stdlib.h>

// See description
// https://stackoverflow.com/questions/7015285/undefined-reference-to-operator-deletevoid
void* operator new(size_t n);

void operator delete(void* p) noexcept;
void operator delete(void* p, size_t n) noexcept;

// placement new
void* operator new(size_t, void* ptr) noexcept;

// placement delete
void operator delete(void*, void*) noexcept;

double get_eps();

uint32_t get_fclk();

#endif  // SYSTEM_FUNC_H