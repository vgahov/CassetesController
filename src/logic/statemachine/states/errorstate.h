#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include <logic/statemachine/istatemachine.h>

#include "istate.h"

class IStateMachine;

class ErrorState final : public IState {
public:
    ErrorState(IStateMachine* state_machine, uint32_t period_usec);
    ~ErrorState();

private:
    void move_table_front(bool state) override;
    void move_table_back(bool state) override;
    void change_tables(bool state) override;
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;

    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;

    void update() override;

private:
    void check_for_valid_state();
    void handle_error_led_status_blinking();
    void handle_error_led_blinking();

private:
    const uint32_t m_period_usec;
    uint32_t m_delay_for_blink = 0;
    bool m_blink_state = false;

    struct ErrorBlinking {
        uint32_t blinking_number;
        uint32_t blinking_interval_ms;
        uint32_t blinking_duration_us;
    };

    ErrorBlinking m_error_blinking[2] = {
        {0, 0, 0},
        {0, 0, 0},
    };
    uint8_t m_current_blinking_position = 0;
    uint8_t m_current_sub_blinking_index = 0;
    uint8_t m_current_error_code = 0;
    bool m_eror_blink_state = true;
};

#endif  // ERROR_STATE_H