#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include <logic/statemachine/istatemachine.h>

#include "istate.h"

class IStateMachine;

class ErrorState final : public IState {
public:
    ErrorState(IStateMachine* state_machine) : IState(state_machine) {
        if(!m_state_machine) {
            return;
        }
        m_state_machine->clear_output_states();
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, false);
        m_blink_state = false;
    }

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

    void check_for_valid_state();

private:
    uint32_t m_delay_for_blink = 0;
    bool m_blink_state = false;
};

#endif  // ERROR_STATE_H