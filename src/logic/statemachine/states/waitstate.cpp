#include "waitstate.h"

#include <logic/statemachine/istatemachine.h>

void WaitState::move_table_front(bool state) {
    if(!state) {
        return;
    }
    if(!m_state_machine) {
        return;
    }
    const auto input_states = m_state_machine->get_input_states();
    if(input_states.uSTOP) {
        return;
    }
    if(input_states.sTableBackDown && input_states.sTableBackUp) {
        m_state_machine->change_state(ESTATE::TableFront);
    }
}

void WaitState::move_table_back(bool state) {
    if(!state) {
        return;
    }
    if(!m_state_machine) {
        return;
    }
    const auto input_states = m_state_machine->get_input_states();

    if(input_states.uSTOP) {
        return;
    }

    if(input_states.sTableFront) {
        if(!input_states.sTableBackDown && input_states.sCassetteUpStairs) {
            m_state_machine->change_state(ESTATE::TableBackDown);
            return;
        }

        if(!input_states.sTableBackUp && input_states.sCassetteDownStairs) {
            m_state_machine->change_state(ESTATE::TableBackUp);
            return;
        }
    }
}

void WaitState::change_tables(bool state) {
    if(!state) {
        return;
    }
    if(!m_state_machine) {
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
        return;
    }

    m_state_machine->change_state(ESTATE::TableChanging);
}

void WaitState::on_error() {
    if(m_state_machine) {
        m_state_machine->change_state(ESTATE::Error);
    }
}
void WaitState::update() {};
