#include "keyhandler.h"

#include <avr/interrupt.h>

KeyHandler::KeyHandler(IDispatcher* dispatcher, Pin pin, eKeyRole key_role,
                       IKeyHandlerListener* listener)
    : m_pin(pin), m_listener(listener), m_key_role(key_role) {
    if(dispatcher) {
        dispatcher->add_listener(this, 20, ePeriodUnit::mSec);
    }
}

void KeyHandler::on_dispatcher_call() {
    if(!is_ready()) {
        return;
    }

    const auto is_pressed = is_key_pressed();
    if(is_pressed == 0) {
        return;
    }
    else if(is_pressed > 0) {
        if(!m_key_action_detector.is_pressed) {
            m_key_action_detector.is_pressed = true;
            call_listener(eKeyState::PRESSED);
        }
    }
    else {
        if(m_key_action_detector.is_pressed) {
            call_listener(eKeyState::UNPRESSED);
            m_key_action_detector.is_pressed = false;
        }
    }

    /*else if(is_pressed > 0) {
        m_key_action_detector.is_pressed = true;

        if(m_key_action_detector.pressed_state_duration_msec >
           KeyActionDetector::CONTINUOUS_PRESSED_DELAY_MS) {
            call_listener(eKeyState::CONTINUOUS_PRESSED);
        }

        if(m_key_action_detector.pressed_state_duration_msec >
           KeyActionDetector::LONG_PRESSED_DELAY_MS) {
            return;
        }

        m_key_action_detector.pressed_state_duration_msec +=
            get_period_increment_value_msec();
        if(m_key_action_detector.pressed_state_duration_msec >
           KeyActionDetector::LONG_PRESSED_DELAY_MS) {
            call_listener(eKeyState::LONG_PRESSED);
        }
    }
    else {
        if(m_key_action_detector.pressed_state_duration_msec >
           KeyActionDetector::LONG_PRESSED_DELAY_MS) {
            call_listener(eKeyState::LONG_UNPRESSED);
        }
        else {
            if(m_key_action_detector.is_pressed) {
                // if a key pressed but not in CONTINOUS_PRESSED_STATE
                if(m_key_action_detector.pressed_state_duration_msec <
                   KeyActionDetector::CONTINUOUS_PRESSED_DELAY_MS) {
                    call_listener(eKeyState::PRESSED);
                }
                else {
                    call_listener(eKeyState::UNPRESSED);
                }
            }
        }
        m_key_action_detector.is_pressed = false;
        m_key_action_detector.pressed_state_duration_msec = 0;
    }*/
}

void KeyHandler::set_dispatcher_period(uint32_t period_usec) {
    m_dispatcher_period_usec = period_usec;
    // Pay attention !!!!!!!
    m_increment_value_msec = m_dispatcher_period_usec / 1000;
}

int32_t KeyHandler::is_key_pressed() {
    int32_t result = 0;
    const uint32_t state = m_pin.read();

    if(state != m_key_state_detector.filter_state) {
        m_key_state_detector.filter_state = state;
        m_key_state_detector.current_state_duration_msec = 0;
    }
    else {
        if(m_key_state_detector.current_state_duration_msec <
           KeyStateDetector::CONTACT_BOUNCE_FILTER_MS) {
            m_key_state_detector.current_state_duration_msec +=
                get_period_increment_value_msec();
        }
        else {
            result = state > 0 ? 1 : -1;
        }
    }
    // 1 - pressed
    // 0 - undefined
    // -1 - unpressed
    return result;
}

void KeyHandler::call_listener(eKeyState action) {
    if(m_listener) {
        m_listener->on_key_pressed(m_key_role, action);
    }
}

bool KeyHandler::is_ready() const { return m_dispatcher_period_usec > 0; }

uint32_t KeyHandler::get_period_increment_value_msec() const {
    return m_increment_value_msec;
}

uint32_t KeyHandler::get_period_increment_value_usec() const {
    return m_increment_value_msec;
}