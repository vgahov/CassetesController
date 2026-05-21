#ifndef WAIT_STATE_H
#define WAIT_STATE_H

#include <logic/statemachine/istatemachine.h>

#include "istate.h"

class IStateMachine;

class WaitState final : public IState {
public:
    WaitState(IStateMachine* state_machine) : IState(state_machine) {
        m_state_machine->clear_output_states();
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, true);
    }

private:
    void move_table_front(bool state) override;
    void move_table_back(bool state) override;
    void change_tables(bool state) override;
    void stop(bool state) override;
    void on_error() override;
    void update() override;

private:
};

#endif  // WAIT_STATE_H