#include "errorstate.h"

#include <logic/statemachine/istatemachine.h>

#include "helpers/helpers.h"

void ErrorState::on_cassete_up() {}
void ErrorState::on_cassete_down() {}

void ErrorState::on_table_front() {}
void ErrorState::on_table_back_up() {}
void ErrorState::on_table_back_down() {}

void ErrorState::update() {}

void ErrorState::check_for_valid_state() {
    InputStates input_states = m_state_machine->get_input_states();

    if(::check_for_valid_state(input_states) && m_state_machine) {
        m_state_machine->change_state(ESTATE::Wait);
    }
}