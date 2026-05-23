#include "casseteupstate.h"

CasseteUpState::CasseteUpState(IStateMachine* state_machine, bool with_control)
    : CommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::OIL_PUMP, true);
        m_state_machine->set_output_state(eOutputRole::CASSETTE_UP_STAIRS,
                                          true);
    }
}

CasseteUpState::~CasseteUpState() {
    clear_output_signals(StatesToStopList{
        {true, eOutputRole::OIL_PUMP},
        {true, eOutputRole::CASSETTE_UP_STAIRS},
    });
}

void CasseteUpState::on_cassete_down(bool state) {
    opposite_signal_triggered(state);
}

void CasseteUpState::on_cassete_up(bool state) {
    native_signal_triggered(state, StatesToStopList{
                                       {true, eOutputRole::OIL_PUMP},
                                       {true, eOutputRole::CASSETTE_UP_STAIRS},
                                   });
}

void CasseteUpState::change_tables(bool state) { main_action_button(state); }