#include "errorstate.h"

#include <avr/io.h>
#include <logic/statemachine/istatemachine.h>

#include "helpers/helpers.h"

ErrorState::ErrorState(IStateMachine* state_machine, uint32_t period_usec)
    : IState(state_machine), m_period_usec(period_usec) {}

ErrorState::~ErrorState() {
    if(m_state_machine) {
        m_state_machine->set_output_state(
            eOutputRole::TABLE_CHANGING_INDICATION, false);
        m_state_machine->set_output_state(eOutputRole::TABLE_INDICATION, false);
    }
}

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
void ErrorState::on_cassete_up(bool) { check_for_valid_state(); }
void ErrorState::on_cassete_down(bool) { check_for_valid_state(); }
void ErrorState::on_table_front(bool) { check_for_valid_state(); }
void ErrorState::on_table_back_up(bool) { check_for_valid_state(); }
void ErrorState::on_table_back_down(bool) { check_for_valid_state(); }

void ErrorState::update() {
    handle_error_led_blinking();
    handle_error_led_status_blinking();
}

void ErrorState::check_for_valid_state() {
    InputStates input_states = m_state_machine->get_input_states();

    if(m_state_machine && ::check_for_valid_state(input_states)) {
        m_state_machine->change_state(ESTATE::Wait);
    }
}

void ErrorState::handle_error_led_blinking() {
    if(m_delay_for_blink < 100) {
        ++m_delay_for_blink;
        return;
    }
    m_delay_for_blink = 0;
    if(!m_state_machine) {
        return;
    }

    m_blink_state = !m_blink_state;
    m_state_machine->set_output_state(eOutputRole::TABLE_CHANGING_INDICATION,
                                      m_blink_state);
    m_state_machine->set_output_state(eOutputRole::TABLE_INDICATION,
                                      !m_blink_state);
}
void ErrorState::handle_error_led_status_blinking() {
    if(!m_state_machine) {
        return;
    }

    // 2 cassetes are off - 1
    // 2 cassetes are on - 2
    // cassete is empty or tables are in undefined position - 3
    // low table is in undefined position - 4
    // upper table is in undefined position - 5
    // tables are absent - 6
    const auto input_states = m_state_machine->get_input_states();

    uint8_t error_code = 0;

    if(!input_states.sCassetteDownStairs && !input_states.sCassetteUpStairs) {
        error_code = 1;
    }
    else if(input_states.sCassetteDownStairs &&
            input_states.sCassetteUpStairs) {
        error_code = 2;
    }
    else if(!input_states.sTableBackDown && !input_states.sTableBackUp &&
            input_states.sTableFront) {
        error_code = 3;
    }
    else if(input_states.sTableBackUp && !input_states.sTableBackDown &&
            !input_states.sTableFront) {
        error_code = 4;
    }
    else if(input_states.sTableBackDown && !input_states.sTableBackUp &&
            !input_states.sTableFront) {
        error_code = 5;
    }
    else if(!input_states.sTableBackDown && !input_states.sTableBackUp &&
            !input_states.sTableFront) {
        error_code = 6;
    }

    if(m_current_error_code != error_code) {
        m_current_error_code = error_code;

        m_current_blinking_position = 0;
        m_current_sub_blinking_index = 0;

        m_error_blinking[0].blinking_duration_us = 0;
        m_error_blinking[1].blinking_duration_us = 0;

        m_eror_blink_state = false;

        m_state_machine->set_output_state(eOutputRole::CONTROL_LED, false);

        if(error_code == 0) {
            m_error_blinking[0].blinking_number = 0;
            m_error_blinking[0].blinking_interval_ms = 0;

            m_error_blinking[1].blinking_number = 0;
            m_error_blinking[1].blinking_interval_ms = 0;
        }
        else {
            // pause
            m_error_blinking[0].blinking_number = 2;
            m_error_blinking[0].blinking_interval_ms = 3000;

            // error blinks
            m_error_blinking[1].blinking_number = error_code * 2;
            m_error_blinking[1].blinking_interval_ms = 500;
        }

        return;
    }

    auto& current_blinking = m_error_blinking[m_current_blinking_position];

    if(current_blinking.blinking_number == 0) {
        return;
    }

    current_blinking.blinking_duration_us += m_period_usec;

    if(current_blinking.blinking_duration_us <
       static_cast<uint32_t>(current_blinking.blinking_interval_ms) * 1000UL) {
        return;
    }

    current_blinking.blinking_duration_us = 0;

    m_eror_blink_state = !m_eror_blink_state;

    m_state_machine->set_output_state(eOutputRole::CONTROL_LED,
                                      m_eror_blink_state);

    ++m_current_sub_blinking_index;

    if(m_current_sub_blinking_index >= current_blinking.blinking_number) {
        m_current_sub_blinking_index = 0;

        m_current_blinking_position =
            (m_current_blinking_position + 1) %
            (sizeof(m_error_blinking) / sizeof(m_error_blinking[0]));
    }
}
