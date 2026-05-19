#include "waitstate.h"

#include <logic/statemachine/istatemachine.h>

// void WaitState::move_cassete_up() {}
// void WaitState::move_cassete_down() {};
void WaitState::on_cassete_up() {}
void WaitState::on_cassete_down() {}

void WaitState::move_table_front() {
    if(!m_state_machine) {
        return;
    }
    const auto input_states = m_state_machine->get_input_states();
    if(input_states.uSTOP) {
        m_state_machine->change_state(ESTATE::TableFront);
    }
}

void WaitState::move_table_back() {
    if(!m_state_machine) {
        return;
    }
    const auto input_states = m_state_machine->get_input_states();
    if(input_states.uSTOP) {
        m_state_machine->change_state(ESTATE::TableBack);
    }
}

void WaitState::change_tables() {
    if(!m_state_machine) {
        return;
    }

    m_state_machine->change_state(ESTATE::TableChanging);
}

void WaitState::on_stop_pressed() {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, false);
    }
}

void WaitState::on_stop_released() {
    if(m_state_machine) {
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, true);
    }
}

void WaitState::on_error() {
    if(m_state_machine) {
        m_state_machine->change_state(ESTATE::Error);
    }
}
void WaitState::update() {};
