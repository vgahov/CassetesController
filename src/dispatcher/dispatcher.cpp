#include "dispatcher.h"

#include <avr/interrupt.h>

void Dispatcher::on_timer_call() { m_tick = true; }

void Dispatcher::set_timer_period(uint32_t period_usec) {
    m_period_usec = period_usec;
}

void Dispatcher::add_listener(IDispatcherListener* listener, uint32_t period,
                              ePeriodUnit unit) {
    if(m_current_listener_pos >= LISTENERS_NUMBER) {
        return;
    }

    uint32_t period_usec = 0;
    switch(unit) {
        case ePeriodUnit::uSec:
            period_usec = period;
            break;
        case ePeriodUnit::mSec:
            period_usec = period * 1000;
            break;
        case ePeriodUnit::Sec:
            period_usec = period * 1000000;
            break;
    }

    m_listeners[m_current_listener_pos].listener = listener;
    m_listeners[m_current_listener_pos].period_usec = period_usec;
    m_listeners[m_current_listener_pos].current_period = 0;
    ++m_current_listener_pos;
    listener->set_dispatcher_period(period_usec);
}

void Dispatcher::loop() {
    while(!m_stop) {
        cli();
        const auto tick = m_tick;
        m_tick = false;
        sei();

        if(!tick) {
            continue;
        }

        if(!m_period_usec) {
            continue;
        }

        // PORTB |= (1 << PB4);
        for(auto& listener : m_listeners) {
            if(listener.listener) {
                listener.current_period += m_period_usec;
                if((listener.current_period + 30) >= listener.period_usec) {
                    listener.listener->on_dispatcher_call();
                    listener.current_period = 0;
                }
            }
        }
    }
}