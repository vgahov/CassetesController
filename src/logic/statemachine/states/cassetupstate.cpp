#include "casseteupstate.h"

void CasseteUpState::on_cassete_up(bool state) {
    transition_to_waiting_state();
}
void CasseteUpState::on_cassete_down(bool state) {
    transition_to_error_if_needed();
}
void CasseteUpState::on_table_front(bool state) {
    transition_to_error_if_needed();
}
void CasseteUpState::on_table_back_up(bool state) {
    transition_to_error_if_needed();
}
void CasseteUpState::on_table_back_down(bool state) {
    transition_to_error_if_needed();
}
void CasseteUpState::stop(bool state) { transition_to_waiting_state(); }
void CasseteUpState::transition_to_error_if_needed() {
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
