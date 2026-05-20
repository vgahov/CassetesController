#ifndef STATE_HELPER_H
#define STATE_HELPER_H

#include <logic/statemachine/istatemachine.h>

class IStateMachine;

class StateHelper : public IState {
public:
    StateHelper(IStateMachine* state_machine) : IState(state_machine) {}
    virtual ~StateHelper() = default;

protected:
    void transition_to_error_state() {
        if(m_state_machine) {
            m_state_machine->change_state(ESTATE::Error);
        }
    }
    void transition_to_waiting_state() {
        if(m_state_machine) {
            m_state_machine->change_state(ESTATE::Wait);
        }
    }
};

#endif  // STATE_HELPER_H