#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <dispatcher/dispatcher.h>
#include <util/delay.h>

void ports_init0() {
    // всі порти як input
    DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
    DDRE = 0x00;

    // вимкнути pull-up (якщо треба "чисті" входи)
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;
    DDRB |= (1 << PB4);
    PORTB &= ~(1 << PB4);
}

void ports_init() {
    // всі порти як input
    /*DDRA = 0x00;
    DDRB = 0x00;
    DDRC = 0x00;
    DDRD = 0x00;
    DDRE = 0x00;

    // вимкнути pull-up (якщо треба "чисті" входи)
    PORTA = 0x00;
    PORTB = 0x00;
    PORTC = 0x00;
    PORTD = 0x00;
    PORTE = 0x00;*/

    // 3 - PA7
    // Present 1, 2, 3, 4, 5... 8, 9, 10, 11, 12
    // Not present 6, 7

    // 4, 5 lamps
    DDRC |= (1 << PC6 | 1 << PC7);
    PORTC &= ~(1 << PC6 | 1 << PC7);

    // UNKNOWN
    // DDRC |= (1 << PC4 | 1 << PC5);
    // PORTC |= (1 << PC4 | 1 << PC5);

    // the 1st 3 lamps (from left ot right)
    DDRA |= (1 << PA5 | 1 << PA6 | 1 << PA7);
    PORTA &= ~(1 << PA5 | 1 << PA6 | 1 << PA7);
    // PORTA |= (1 << PA5 | 1 << PA6 | 1 << PA7);

    // UNKNOWN??? NOT NECESSARY !!!!!!!!!!!!!!!1
    // DDRA |= (1 << PA0);
    // PORTA &= ~(1 << PA0);

    // DDRE |= (1 << PE5 | 1 << PE6);
    // PORTE |= (1 << PE5 | 1 << PE6);

    // the last 12th lamp
    DDRE |= (1 << PE6);
    PORTE &= ~(1 << PE6);
    // PORTE |= (1 << PE6);

    // UNKNOWN NOT NECESSARY !!!!!!!!!!!!!!!1
    // DDRE |= (1 << PE5);
    // PORTE |= (1 << PE5);

    // the last 8, 9, 10, 11 lamps;
    DDRB |= (1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB3);
    PORTB &= ~(1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB3);
    // PORTB |= (1 << PB0 | 1 << PB1 | 1 << PB2 | 1 << PB3);

    // TEST LAMP
    DDRB |= (1 << PB4);
    PORTB &= ~(1 << PB4);
}

ISR(TIMER0_COMPA_vect) { Timer0::interrupt_handler(); }

ISR(TIMER0_COMPB_vect) {
    while(1) {
        PORTB ^= (1 << PB4);
        _delay_ms(500);
    }
}

ISR(TIMER0_OVF_vect) {
    while(1) {
        PORTB ^= (1 << PB4);
        _delay_ms(1000);
    }
}

ISR(BADISR_vect) {
    while(1) {
        PORTB ^= (1 << PB4);
        _delay_ms(5000);
    }
}

int main(void) {
    MCUSR = 0;
    wdt_disable();
    DDRB |= (1 << PB4);
    PORTB |= (1 << PB4);

    {
        TIMSK0 = 0;
        TIMSK1 = 0;
        TIMSK2 = 0;

        EIMSK = 0;
        PCICR = 0;

        TIFR0 = 0xFF;
        TIFR1 = 0xFF;
        TIFR2 = 0xFF;
        EIFR = 0xFF;
        PCIFR = 0xFF;
    }

    /*{
        TCCR0A = 0;
        TCCR0B = 0;
        TCNT0 = 0;

        TCCR0A = (1 << WGM01);
        OCR0A = 255;

        TCCR0B = (1 << CS02) | (1 << CS00);
        TIFR0 = 0xFF;
        TIMSK0 = (1 << OCIE0A);
    }*/
    Dispatcher dispatcher;
    Timer0::init(1000000);
    Timer0::get_instance().set_interrupt_callback(&dispatcher);

    sei();

    while(1) {
    }
}
