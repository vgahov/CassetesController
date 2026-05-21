#include <logic/statemachine/istatemachine.h>

#include "cassetedownstate.h"

void CasseteDownState::on_cassete_up(bool state) {
    transition_to_error_state();
}
void CasseteDownState::on_cassete_down(bool state) {
    transition_to_waiting_state();
}
void CasseteDownState::on_table_front(bool state) {
    transition_to_error_if_needed();
}
void CasseteDownState::on_table_back_up(bool state) {
    transition_to_error_if_needed();
}
void CasseteDownState::on_table_back_down(bool state) {
    transition_to_error_if_needed();
}
void CasseteDownState::stop(bool state) { transition_to_waiting_state(); }
void CasseteDownState::on_error() {
    if(!m_state_machine) {
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(!(input_states.uSTOP && input_states.uTableChanging)) {
        transition_to_error_state();
    }
}

void CasseteDownState::transition_to_error_if_needed() {
    if(!m_state_machine) {
        return;
    }

    if(!m_with_control) {
        transition_to_error_state();
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(!(input_states.uSTOP && input_states.uTableChanging)) {
        transition_to_error_state();
    }
}
