#include "errorstate.h"

#include <avr/io.h>
#include <logic/statemachine/istatemachine.h>

#include "helpers/helpers.h"

void ErrorState::move_table_front(bool state) {
    if(!(m_state_machine && state)) {
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(input_states.uSTOP) {
        m_state_machine->change_state(ESTATE::TableFront);
    }
}
void ErrorState::move_table_back(bool state) {
    if(!(m_state_machine && state)) {
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(input_states.uSTOP) {
        if(input_states.sCassetteDownStairs) {
            m_state_machine->change_state(ESTATE::TableBackUp);
        }
        else if(input_states.sCassetteUpStairs) {
            m_state_machine->change_state(ESTATE::TableBackDown);
        }
    }
}
void ErrorState::change_tables(bool state) {
    if(!(m_state_machine && state)) {
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    if(input_states.uSTOP) {
        if(input_states.sCassetteDownStairs) {
            m_state_machine->change_state(ESTATE::CasseteUp);
        }
        else if(input_states.sCassetteUpStairs) {
            m_state_machine->change_state(ESTATE::CasseteDown);
        }
        else {
            m_state_machine->change_state(ESTATE::CasseteUp);
        }
    }
}
void ErrorState::on_cassete_up(bool state) { check_for_valid_state(); }
void ErrorState::on_cassete_down(bool state) { check_for_valid_state(); }
void ErrorState::on_table_front(bool state) { check_for_valid_state(); }
void ErrorState::on_table_back_up(bool state) { check_for_valid_state(); }
void ErrorState::on_table_back_down(bool state) { check_for_valid_state(); }

void ErrorState::update() {
    if(m_delay_for_blink < 100) {
        ++m_delay_for_blink;
        return;
    }
    m_delay_for_blink = 0;
    if(!m_state_machine) {
        return;
    }

    // m_blink_state = !m_blink_state;
    //  m_state_machine->set_output_state(eOutputRole::INDICATION_READY,
    //                                    m_blink_state);
}

void ErrorState::check_for_valid_state() {
    InputStates input_states = m_state_machine->get_input_states();

    if(m_state_machine && ::check_for_valid_state(input_states)) {
        m_state_machine->change_state(ESTATE::Wait);
    }
}