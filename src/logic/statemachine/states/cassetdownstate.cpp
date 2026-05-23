#include <logic/statemachine/istatemachine.h>

#include "cassetedownstate.h"

CasseteDownState::CasseteDownState(IStateMachine* state_machine,
                                   bool with_control)
    : CommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::OIL_PUMP, true);
        m_state_machine->set_output_state(eOutputRole::CASSETTE_DOWN_STAIRS,
                                          true);
    }
}

CasseteDownState::~CasseteDownState() {
    clear_output_signals(StatesToStopList{
        {true, eOutputRole::OIL_PUMP},
        {true, eOutputRole::CASSETTE_DOWN_STAIRS},
    });
}

void CasseteDownState::on_cassete_up(bool state) {
    opposite_signal_triggered(state);
}

void CasseteDownState::on_cassete_down(bool state) {
    native_signal_triggered(state,
                            StatesToStopList{
                                {true, eOutputRole::OIL_PUMP},
                                {true, eOutputRole::CASSETTE_DOWN_STAIRS},
                            });
}

void CasseteDownState::change_tables(bool state) { main_action_button(state); }
