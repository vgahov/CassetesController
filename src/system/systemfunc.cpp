#include "systemfunc.h"

#include <avr/delay.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <port/port.h>

extern Pin m_led_pin;

// See description
// https://stackoverflow.com/questions/7015285/undefined-reference-to-operator-deletevoid
void* operator new(size_t n) {
    void* const p = malloc(n);
    if(!p) {
        // Allocation failed — avoid returning nullptr which would cause
        // undefined behavior when used by callers. Trigger a watchdog reset
        // to recover into a clean startup state.
        cli();
        // wdt_enable(WDTO_15MS);
        while(true) {
            // wait for watchdog to reset the MCU
            m_led_pin.toggle();
            _delay_ms(1000);
        }
    }
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
