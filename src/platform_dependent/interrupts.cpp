
#ifndef IAR_PROJECT
#include <avr/interrupt.h>
#include <avr/io.h>
#include <platform_dependent/timer.h>
#endif

/*ISR(TIMER0_OVF_vect) {
    static uint32_t cnt = 0;

    if(++cnt >= 4) {
        cnt = 0;
        PORTB ^= (1 << PB4);
    }
}*/

/*ISR(TIMER0_COMPA_vect) {
    // Timer0::interrupt_handler();
    static uint32_t cnt = 0;

    if(++cnt >= 4) {
        cnt = 0;
        // PORTB ^= (1 << PB4);
    }
}*/