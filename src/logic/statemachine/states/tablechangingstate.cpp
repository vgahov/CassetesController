#include "tablechangingstate.h"

#include <logic/statemachine/istatemachine.h>

#include "cassetedownstate.h"
#include "casseteupstate.h"
#include "tablebackdownstate.h"
#include "tablebackupstate.h"
#include "tablefrontstate.h"

void TableChangingState::change_state(ESTATE state) {
    if(m_state_machine) {
        switch(state) {
            case ESTATE::Wait:
                get_next_substate() != ETableChangingSubState::None
                    ? trigger_substate()
                    : m_state_machine->change_state(state);
                break;
            case ESTATE::Error:
                m_state_machine->change_state(state);
                break;

            default:
                // Should we do something with other states? For now, just
                // ignore them
                break;
        }
    }
}
InputStates TableChangingState::get_input_states() const {
    if(m_state_machine) {
        return m_state_machine->get_input_states();
    }
    return InputStates();
}
void TableChangingState::set_output_state(eOutputRole role, bool on) {
    if(m_state_machine) {
        m_state_machine->set_output_state(role, on);
    }
}

void TableChangingState::clear_output_states() {
    if(m_state_machine) {
        m_state_machine->clear_output_states();
    }
}

void TableChangingState::on_cassete_up(bool state) {
    if(m_current_substate) {
        m_current_substate->on_cassete_up(state);
    }
}
void TableChangingState::on_cassete_down(bool state) {
    if(m_current_substate) {
        m_current_substate->on_cassete_down(state);
    }
}
void TableChangingState::on_table_front(bool state) {
    if(m_current_substate) {
        m_current_substate->on_table_front(state);
    }
}
void TableChangingState::on_table_back_up(bool state) {
    if(m_current_substate) {
        m_current_substate->on_table_back_up(state);
    }
}
void TableChangingState::on_table_back_down(bool state) {
    if(m_current_substate) {
        m_current_substate->on_table_back_down(state);
    }
}
void TableChangingState::stop(bool state) {
    if(m_current_substate) {
        m_current_substate->stop(state);
    }
}
void TableChangingState::check_initial_conditions() {
    if(!m_state_machine) {
        return;
    }

    const auto input_states = m_state_machine->get_input_states();
    auto should_be_started = false;

    // Check if:
    // - cassete is in the upper position;
    // - tables are inside
    if(input_states.sCassetteUpStairs) {
        // Check if:
        // - both tables are inside cassete
        if(input_states.sTableBackDown && input_states.sTableBackUp &&
           !input_states.sTableFront) {
            put_substate(0, ETableChangingSubState::TableToFront);
            put_substate(1, ETableChangingSubState::None);
            put_substate(2, ETableChangingSubState::None);
            put_substate(3, ETableChangingSubState::None);
            put_substate(4, ETableChangingSubState::None);
            should_be_started = true;
        }

        // Check if:
        // - upper table is on front of the work surface, lower one is inside of
        // the cassete
        if(input_states.sTableBackDown && !input_states.sTableBackUp &&
           input_states.sTableFront) {
            put_substate(0, ETableChangingSubState::CasseteToDown);
            put_substate(1, ETableChangingSubState::TableToBackUp);
            put_substate(2, ETableChangingSubState::CasseteToUp);
            put_substate(3, ETableChangingSubState::TableToFront);
            put_substate(4, ETableChangingSubState::None);
            should_be_started = true;
        }

        // Check if:
        // - lower table is on front of the work surface, upper one is inside of
        // the cassete
        if(!input_states.sTableBackDown && input_states.sTableBackUp &&
           input_states.sTableFront) {
            put_substate(0, ETableChangingSubState::TableToBackDown);
            put_substate(1, ETableChangingSubState::CasseteToDown);
            put_substate(2, ETableChangingSubState::TableToFront);
            put_substate(3, ETableChangingSubState::None);
            put_substate(4, ETableChangingSubState::None);
            should_be_started = true;
        }
    }

    //===========================
    // Check if:
    // - cassete is raised;
    if(input_states.sCassetteDownStairs) {
        // Check if:
        // - both tables are inside cassete
        if(input_states.sTableBackDown && input_states.sTableBackUp &&
           !input_states.sTableFront) {
            put_substate(0, ETableChangingSubState::TableToFront);
            put_substate(1, ETableChangingSubState::None);
            put_substate(2, ETableChangingSubState::None);
            put_substate(3, ETableChangingSubState::None);
            put_substate(4, ETableChangingSubState::None);
            should_be_started = true;
        }

        // Check if:
        // - upper table is on front of the work surface, lower one is inside of
        // the cassete
        if(input_states.sTableBackDown && !input_states.sTableBackUp &&
           input_states.sTableFront) {
            put_substate(0, ETableChangingSubState::TableToBackUp);
            put_substate(1, ETableChangingSubState::CasseteToUp);
            put_substate(2, ETableChangingSubState::TableToFront);
            put_substate(3, ETableChangingSubState::None);
            put_substate(4, ETableChangingSubState::None);
            should_be_started = true;
        }

        // Check if:
        // - lower table is on front of the work surface, upper one is inside of
        // the cassete
        if(input_states.sTableBackDown && !input_states.sTableBackUp &&
           input_states.sTableFront) {
            put_substate(0, ETableChangingSubState::CasseteToUp);
            put_substate(1, ETableChangingSubState::TableToBackUp);
            put_substate(2, ETableChangingSubState::CasseteToDown);
            put_substate(3, ETableChangingSubState::TableToFront);
            put_substate(4, ETableChangingSubState::CasseteToUp);
            should_be_started = true;
        }
    }

    if(should_be_started) {
        trigger_substate();
    }
}

void TableChangingState::trigger_substate() {
    cleanup_current_substate();

    const auto current_substate = pop_next_substate();
    switch(current_substate) {
        case ETableChangingSubState::None:
            break;
        case ETableChangingSubState::CasseteToDown:
            m_current_substate = new CasseteDownState(this, false);
            break;
        case ETableChangingSubState::CasseteToUp:
            m_current_substate = new CasseteUpState(this, false);
            break;
        case ETableChangingSubState::TableToFront:
            m_current_substate = new TableFrontState(this);
            break;
        case ETableChangingSubState::TableToBackDown:
            m_current_substate = new TableBackDownState(this);
            break;
        case ETableChangingSubState::TableToBackUp:
            m_current_substate = new TableBackUpState(this);
            break;
        default:
            break;
    }
}

TableChangingState::ETableChangingSubState
TableChangingState::pop_next_substate() {
    for(size_t i = 0; i < static_cast<size_t>(ETableChangingSubState::COUNT);
        ++i) {
        if(m_sub_states[i] != ETableChangingSubState::None) {
            const auto sub_state = m_sub_states[i];
            m_sub_states[i] = ETableChangingSubState::None;
            return sub_state;
        }
    }
    return ETableChangingSubState::None;
}

TableChangingState::ETableChangingSubState
TableChangingState::get_next_substate() {
    for(size_t i = 0; i < static_cast<size_t>(ETableChangingSubState::COUNT);
        ++i) {
        if(m_sub_states[i] != ETableChangingSubState::None) {
            return m_sub_states[i];
        }
    }
    return ETableChangingSubState::None;
}
