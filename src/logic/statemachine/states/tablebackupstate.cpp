#include "tablebackupstate.h"

TableBackUpState::TableBackUpState(IStateMachine* state_machine,
                                   bool with_control)
    : CommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::TABLE_BACK, true);
        m_state_machine->set_output_state(
            eOutputRole::TABLE_CHANGING_INDICATION, true);
    }
}

TableBackUpState::~TableBackUpState() {
    clear_output_signals(StatesToStopList{
        {true, eOutputRole::TABLE_BACK},
        {true, eOutputRole::TABLE_CHANGING_INDICATION},
    });
}

void TableBackUpState::on_table_front(bool state) {
    opposite_signal_triggered(state);
}

void TableBackUpState::on_table_back_up(bool state) {
    StatesToStopList states_to_stop = {
        {true, eOutputRole::TABLE_BACK},
        {false, eOutputRole::KEY_ROLE_COUNT},
    };
    native_signal_triggered(state, states_to_stop);
}

void TableBackUpState::move_table_back(bool state) {
    main_action_button(state);
}