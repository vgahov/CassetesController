
#ifndef IAR_PROJECT
#include <avr/interrupt.h>
#include <avr/io.h>
#include <platform_dependent/timer.h>
#endif

ISR(TIMER0_COMPA_vect) { Timer0::interrupt_handler(); }