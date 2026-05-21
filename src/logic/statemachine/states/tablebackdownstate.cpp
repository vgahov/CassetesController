#include "tablebackdownstate.h"

TableBackDownState::TableBackDownState(IStateMachine* state_machine,
                                       bool with_control)
    : CommonMovingState(state_machine, with_control) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::TABLE_BACK, true);
        m_state_machine->set_output_state(
            eOutputRole::TABLE_CHANGING_INDICATION, true);
    }
}

TableBackDownState::~TableBackDownState() {
    native_signal_triggered(true,
                            StatesToStopList{
                                {true, eOutputRole::TABLE_BACK},
                                {true, eOutputRole::TABLE_CHANGING_INDICATION},
                            });
}

void TableBackDownState::on_table_front(bool state) {
    opposite_signal_triggered(state);
}

void TableBackDownState::on_table_back_down(bool state) {
    StatesToStopList states_to_stop = {
        {true, eOutputRole::TABLE_BACK},
        {true, eOutputRole::TABLE_CHANGING_INDICATION},
    };
    native_signal_triggered(state, states_to_stop);
}

void TableBackDownState::move_table_back(bool state) {
    main_action_button(state);
}
