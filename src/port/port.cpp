

#ifndef IAR_PROJECT
#include <avr/io.h>
#else
#endif  // ifndef IAR_PROJECT

#include <system/systemfunc.h>

#include "port.h"

Pin::Pin() {}

Pin::Pin(ePORT port, int pin, bool input)
    : m_port(port), m_pin(pin), m_is_valid(true) {
    if(input) {
        set_as_input();
    }
    else {
        set_as_output();
    }
    m_reference_counter = new uint32_t(1);
}

Pin::~Pin() {
    if(m_reference_counter && --m_reference_counter == 0) {
        set_as_input();
        delete m_reference_counter;
        m_reference_counter = nullptr;
    }
}

Pin &Pin::operator=(const Pin &other) {
    if(this == &other) {
        return *this;
    }

    this->~Pin();
    m_reference_counter = other.m_reference_counter;
    if(m_reference_counter) {
        ++m_reference_counter;
    }
    m_port = other.m_port;
    m_pin = other.m_pin;
    m_is_valid = other.m_is_valid;
}

void Pin::set_as_output() {
    if(is_input()) {
        set_direction(m_port, m_pin, true);
    }
}

void Pin::set_as_input() {
    if(!is_input()) {
        set_direction(m_port, m_pin, false);
    }
    // PULL UP
    set_output(m_port, m_pin);
}

int Pin::read() { return read_pin(m_port, m_pin); }

void Pin::set() { set_output(m_port, m_pin); }

void Pin::toggle() { toggle_output(m_port, m_pin); }

void Pin::reset() { clr_output(m_port, m_pin); }

bool Pin::is_input() const { return !get_direction(m_port, m_pin); }

uint8_t Pin::set_binary_value(uint8_t initial_value, uint8_t pin,
                              eOutputAction action) {
    uint8_t result = 0;
    switch(action) {
        case eOutputAction::CLEAR:
            result = initial_value & (~(1 << pin));
            break;
        case eOutputAction::SET:
            result = initial_value | (1 << pin);
            break;
        case eOutputAction::TOGGLE:
            result = initial_value ^ (1 << pin);
            break;
    }
    return result;
}

uint8_t Pin::get_binary_value(uint8_t initial_value, uint8_t pin) {
    return initial_value & (1 << pin);
}

void Pin::set_direction(ePORT port, uint8_t pin, bool direction) {
    eOutputAction action =
        direction ? eOutputAction::SET : eOutputAction::CLEAR;
    switch(port) {
        case ePORT::ePORTA:
            break;
        case ePORT::ePORTB:
            DDRB = set_binary_value(DDRB, pin, action);
            break;
        case ePORT::ePORTC:
            DDRC = set_binary_value(DDRC, pin, action);
            break;
        case ePORT::ePORTD:
            DDRD = set_binary_value(DDRD, pin, action);
            break;
#if defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega324PB__)
        case ePORT::ePORTE:
            DDRE = set_binary_value(DDRE, pin, action);
            break;
#endif
    }
}

bool Pin::get_direction(ePORT port, uint8_t pin) {
    bool result = false;
    switch(port) {
        case ePORT::ePORTA:
            break;
        case ePORT::ePORTB:
            result = get_binary_value(DDRB, pin);
            break;
        case ePORT::ePORTC:
            result = get_binary_value(DDRC, pin);
            break;
        case ePORT::ePORTD:
            result = get_binary_value(DDRD, pin);
            break;
#if(ATMEGA328PB)
        case ePORT::ePORTE:
            result = get_binary_value(DDRE, pin);
            break;
#endif
    }

    return result;
}

bool Pin::read_pin(ePORT port, uint8_t pin) {
    bool result = false;
    switch(port) {
        case ePORT::ePORTA:
            break;
        case ePORT::ePORTB:
            result = get_binary_value(PINB, pin);
            break;
        case ePORT::ePORTC:
            result = get_binary_value(PINC, pin);
            break;
        case ePORT::ePORTD:
            result = get_binary_value(PIND, pin);
            break;
#if(ATMEGA328PB)
        case ePORT::ePORTE:
            result = get_binary_value(PINE, pin);
            break;
#endif
    }

    return result;
}

void Pin::set_output(ePORT port, uint8_t pin) {
    switch(port) {
        case ePORT::ePORTA:
            break;
        case ePORT::ePORTB:
            PORTB = set_binary_value(PORTB, pin, eOutputAction::SET);
            break;
        case ePORT::ePORTC:
            PORTC = set_binary_value(PORTC, pin, eOutputAction::SET);
            break;
        case ePORT::ePORTD:
            PORTD = set_binary_value(PORTD, pin, eOutputAction::SET);
            break;
#if(ATMEGA328PB)
        case ePORT::ePORTE:
            PORTE = set_binary_value(PORTE, pin, eOutputAction::SET);
            break;
#endif
    }
}

void Pin::clr_output(ePORT port, uint8_t pin) {
    switch(port) {
        case ePORT::ePORTA:
            break;
        case ePORT::ePORTB:
            PORTB = set_binary_value(PORTB, pin, eOutputAction::CLEAR);
            break;
        case ePORT::ePORTC:
            PORTC = set_binary_value(PORTC, pin, eOutputAction::CLEAR);
            break;
        case ePORT::ePORTD:
            PORTD = set_binary_value(PORTD, pin, eOutputAction::CLEAR);
            break;
#if(ATMEGA328PB)
        case ePORT::ePORTE:
            PORTE = set_binary_value(PORTE, pin, eOutputAction::CLEAR);
            break;
#endif
    }
}

void Pin::toggle_output(ePORT port, uint8_t pin) {
    switch(port) {
        case ePORT::ePORTA:
            break;
        case ePORT::ePORTB:
            PORTB = set_binary_value(PORTB, pin, eOutputAction::TOGGLE);
            break;
        case ePORT::ePORTC:
            PORTC = set_binary_value(PORTC, pin, eOutputAction::TOGGLE);
            break;
        case ePORT::ePORTD:
            PORTD = set_binary_value(PORTD, pin, eOutputAction::TOGGLE);
            break;
#if(ATMEGA328PB)
        case ePORT::ePORTE:
            PORTE = set_binary_value(PORTE, pin, eOutputAction::TOGGLE);
            break;
#endif
    }
}
