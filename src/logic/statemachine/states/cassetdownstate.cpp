#include <logic/statemachine/istatemachine.h>

#include "cassetedownstate.h"

void CasseteDownState::on_cassete_up() { transition_to_error_state(); }
void CasseteDownState::on_cassete_down() { transition_to_waiting_state(); }
void CasseteDownState::on_table_front() { transition_to_error_if_needed(); }
void CasseteDownState::on_table_back_up() { transition_to_error_if_needed(); }
void CasseteDownState::on_table_back_down() { transition_to_error_if_needed(); }
void CasseteDownState::stop_pressed() { transition_to_waiting_state(); }
void CasseteDownState::stop_released() { transition_to_waiting_state(); }
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
