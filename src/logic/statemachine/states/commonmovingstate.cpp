#include "commonmovingstate.h"

#include <logic/statemachine/istatemachine.h>

CommonMovingState::CommonMovingState(IStateMachine* state_machine,
                                     bool with_control)
    : StateHelper(state_machine), m_with_stop_control(with_control) {}

void CommonMovingState::on_cassete_down(bool state) {
    transition_to_error_if_needed();
}

void CommonMovingState::on_cassete_up(bool state) {
    transition_to_error_if_needed();
}

void CommonMovingState::on_table_front(bool state) {
    transition_to_error_if_needed();
}
void CommonMovingState::on_table_back_up(bool state) {
    transition_to_error_if_needed();
}
void CommonMovingState::on_table_back_down(bool state) {
    transition_to_error_if_needed();
}

//+++
void CommonMovingState::stop(bool state) {
    if(m_with_stop_control) {
        transition_to_error_state();
        return;
    }
    else if(state) {
        transition_to_waiting_state();
    }
}

void CommonMovingState::transition_to_error_if_needed() {
    if(!m_state_machine) {
        return;
    }

    if(!m_with_stop_control) {
        transition_to_error_state();
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(!(input_states.uSTOP && input_states.uTableChanging)) {
        transition_to_error_state();
    }
}

void CommonMovingState::main_action_button(bool state) {
    if(m_with_stop_control && !state) {
        transition_to_error_state();
    }
}

void CommonMovingState::opposite_signal_triggered(bool state) {
    if(!(state || m_triggered_by_opposite_signal)) {
        m_triggered_by_opposite_signal = true;
        return;
    }
    transition_to_error_state();
}

void CommonMovingState::native_signal_triggered(
    bool state, const StatesToStopList& states_to_stop) {
    clear_output_signals(states_to_stop);
    if(m_state_machine && state) {
        transition_to_waiting_state();
    }
    else {
        transition_to_error_state();
    }
}

void CommonMovingState::clear_output_signals(
    const StatesToStopList& states_to_stop) {
    if(m_state_machine) {
        for(int i = 0; i < MAX_STATES_TO_STOP; ++i) {
            if(states_to_stop[i].stop &&
               states_to_stop[i].output_role != eOutputRole::KEY_ROLE_COUNT) {
                m_state_machine->set_output_state(states_to_stop[i].output_role,
                                                  false);
            }
        }
    }
}