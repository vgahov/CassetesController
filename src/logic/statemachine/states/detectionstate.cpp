#include "detectionstate.h"

#include <logic/statemachine/istatemachine.h>

#include "helpers/helpers.h"

void DetectionState::update() {
    const auto passed_period_usec = m_passed_period_usec;

    if(passed_period_usec < INIT_TIME_SEC * 1000000) {
        m_passed_period_usec += m_period_usec;
        return;
    }

    if(!m_state_machine) {
        return;
    }

    InputStates input_states = m_state_machine->get_input_states();

    if(!check_for_valid_state(input_states)) {
        m_state_machine->change_state(ESTATE::Error);
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, false);
        return;
    }

    m_state_machine->change_state(ESTATE::Wait);
    m_state_machine->set_output_state(eOutputRole::INDICATION_READY, true);
};
