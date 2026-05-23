#include "tablefrontstate.h"

TableFrontState::TableFrontState(IStateMachine* state_machine,
                                 bool with_control)
    : CommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::TABLE_FORWARD, true);
        m_state_machine->set_output_state(
            eOutputRole::TABLE_CHANGING_INDICATION, true);
    }
}

TableFrontState::~TableFrontState() {
    clear_output_signals(StatesToStopList{
        {true, eOutputRole::TABLE_FORWARD},
        {true, eOutputRole::TABLE_CHANGING_INDICATION},
    });
}

void TableFrontState::on_table_back_up(bool state) {
    opposite_signal_triggered(state);
}

void TableFrontState::on_table_back_down(bool state) {
    opposite_signal_triggered(state);
}

void TableFrontState::on_table_front(bool state) {
    StatesToStopList states_to_stop = {
        {true, eOutputRole::TABLE_FORWARD},
        {true, eOutputRole::TABLE_CHANGING_INDICATION},
    };
    native_signal_triggered(state, states_to_stop);
}

void TableFrontState::move_table_front(bool state) {
    main_action_button(state);
}