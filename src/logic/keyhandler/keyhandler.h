#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

#include <dispatcher/dispatcherlistener.h>
#include <logic/keyhandler/keyhandlerlistener.h>
#include <port/port.h>
#include <stdint-gcc.h>

class KeyHandler : public IDispatcherListener {
public:
    KeyHandler(IDispatcher* dispatcher, Pin pin, eKeyRole key_role,
               IKeyHandlerListener* listener);

    void on_dispatcher_call() override;
    void set_dispatcher_period(uint32_t period_usec) override;

private:
    int32_t is_key_pressed();
    void call_listener(eKeyState action);
    bool is_ready() const;
    uint32_t get_period_increment_value_msec() const;
    void recalculate_increment_value_msec();

private:
    struct KeyStateDetector {
        static constexpr uint32_t CONTACT_BOUNCE_FILTER_MS = 50;

        uint32_t current_state_duration_msec = 0;
        bool filter_state = false;
    };

    struct KeyActionDetector {
        static constexpr uint32_t LONG_PRESSED_DELAY_MS = 3000;
        static constexpr uint32_t CONTINUOUS_PRESSED_DELAY_MS = 1500;

        uint32_t pressed_state_duration_msec = 0;
        eKeyState key_state = eKeyState::LONG_UNPRESSED;
        bool is_pressed = false;
    };

    Pin m_pin;
    KeyStateDetector m_key_state_detector;
    KeyActionDetector m_key_action_detector;
    IKeyHandlerListener* m_listener = nullptr;
    eKeyRole m_key_role;
    uint32_t m_dispatcher_period_usec = 0;
    uint32_t m_usec_period_counter = 0;
    uint32_t m_increment_value_msec = 0;
};

#endif  // KEY_HANDLER_H