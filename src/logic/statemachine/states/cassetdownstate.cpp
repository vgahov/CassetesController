#include <logic/statemachine/istatemachine.h>

#include "cassetedownstate.h"

CasseteDownState::CasseteDownState(IStateMachine* state_machine,
                                   bool with_control)
    : CasseteCommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::OIL_PUMP, true);
        m_state_machine->set_output_state(eOutputRole::CASSETTE_DOWN_STAIRS,
                                          true);
    }
}

void CasseteDownState::on_cassete_up(bool state) {
    if(!(state || m_triggered_by_opposite_signal)) {
        m_triggered_by_opposite_signal = true;
        return;
    }
    transition_to_error_state();
}

void CasseteDownState::on_cassete_down(bool state) {
    m_state_machine->set_output_state(eOutputRole::OIL_PUMP, false);
    m_state_machine->set_output_state(eOutputRole::CASSETTE_DOWN_STAIRS, false);
    transition_to_waiting_state();
}
