#include "cassetecommonmovingstate.h"

#include <logic/statemachine/istatemachine.h>

CasseteCommonMovingState::CasseteCommonMovingState(IStateMachine* state_machine,
                                                   bool with_control)
    : StateHelper(state_machine), m_with_stop_control(with_control) {}

void CasseteCommonMovingState::on_table_front(bool state) {
    transition_to_error_if_needed();
}
void CasseteCommonMovingState::on_table_back_up(bool state) {
    transition_to_error_if_needed();
}
void CasseteCommonMovingState::on_table_back_down(bool state) {
    transition_to_error_if_needed();
}
void CasseteCommonMovingState::stop(bool state) {
    if(m_with_stop_control) {
        transition_to_error_state();
        return;
    }
    else if(state) {
        transition_to_waiting_state();
    }
}

void CasseteCommonMovingState::change_tables(bool state) {
    if(m_with_stop_control && !state) {
        transition_to_error_state();
    }
}

void CasseteCommonMovingState::transition_to_error_if_needed() {
    if(!m_state_machine) {
        return;
    }

    if(!m_with_stop_control) {
        transition_to_error_state();
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(!(input_states.uSTOP && input_states.uTableChanging)) {
        transition_to_error_state();
    }
}
