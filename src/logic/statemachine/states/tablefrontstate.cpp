#include "tablefrontstate.h"

TableFrontState::TableFrontState(IStateMachine* state_machine,
                                 uint32_t blink_period_usec, bool with_control,
                                 bool handle_blinking)
    : CommonMovingState(state_machine, with_control),
      m_blinker_handler(state_machine, blink_period_usec, handle_blinking) {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::TABLE_FORWARD, true);
    }
}

void TableFrontState::on_table_back_up(bool state) {
    if(!m_state_machine) {
        return;
    }
    const auto input_states = m_state_machine->get_input_states();
    if(input_states.sCassetteDownStairs) {
        opposite_signal_triggered(state);
    }
    else {
        transition_to_error_state();
    }
}

void TableFrontState::on_table_back_down(bool state) {
    if(!m_state_machine) {
        return;
    }
    const auto input_states = m_state_machine->get_input_states();
    if(input_states.sCassetteUpStairs) {
        opposite_signal_triggered(state);
    }
    else {
        transition_to_error_state();
    }
}

void TableFrontState::on_table_front(bool state) {
    StatesToStopList states_to_stop = {
        {true, eOutputRole::TABLE_FORWARD},
        {false, eOutputRole::KEY_ROLE_COUNT},
    };
    native_signal_triggered(state, states_to_stop);
}

void TableFrontState::move_table_front(bool state) {
    main_action_button(state);
}

void TableFrontState::update() { m_blinker_handler.handle_blinking(); }