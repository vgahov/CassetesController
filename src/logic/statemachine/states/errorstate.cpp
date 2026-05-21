#include "errorstate.h"

#include <logic/statemachine/istatemachine.h>

#include "helpers/helpers.h"

void ErrorState::on_cassete_up(bool state) {}
void ErrorState::on_cassete_down(bool state) {}

void ErrorState::on_table_front(bool state) {}
void ErrorState::on_table_back_up(bool state) {}
void ErrorState::on_table_back_down(bool state) {}

void ErrorState::update() {}

void ErrorState::check_for_valid_state() {
    InputStates input_states = m_state_machine->get_input_states();

    if(::check_for_valid_state(input_states) && m_state_machine) {
        m_state_machine->change_state(ESTATE::Wait);
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, true);
    }
}