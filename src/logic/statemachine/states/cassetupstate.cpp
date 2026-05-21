#include "casseteupstate.h"

CasseteUpState::CasseteUpState(IStateMachine* state_machine, bool with_control)
    : CasseteCommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::OIL_PUMP, true);
        m_state_machine->set_output_state(eOutputRole::CASSETTE_UP_STAIRS,
                                          true);
    }
}

void CasseteUpState::on_cassete_up(bool state) {
    m_state_machine->set_output_state(eOutputRole::OIL_PUMP, false);
    m_state_machine->set_output_state(eOutputRole::CASSETTE_UP_STAIRS, false);
    transition_to_waiting_state();
}
void CasseteUpState::on_cassete_down(bool state) {
    if(!(state || m_triggered_by_opposite_signal)) {
        m_triggered_by_opposite_signal = true;
        return;
    }
    transition_to_error_state();
}
