#include "statemachine.h"

#include <avr/interrupt.h>

#include "states/cassetedownstate.h"
#include "states/casseteupstate.h"
#include "states/detectionstate.h"
#include "states/errorstate.h"
#include "states/helpers/helpers.h"
#include "states/istate.h"
#include "states/tablebackdownstate.h"
#include "states/tablebackupstate.h"
#include "states/tablechangingstate.h"
#include "states/tablefrontstate.h"
#include "states/waitstate.h"

StateMachine::StateMachine(OutputHandler& outputhandler)
    : m_state(nullptr), m_outputhandler(outputhandler) {
    m_state = nullptr;
}

StateMachine::~StateMachine() {}

// IDispatcherListener
void StateMachine::on_dispatcher_call() {
    if(m_state) {
        m_state->update();
        apply_state();
        detect_error();
    }
    handle_led();
}

void StateMachine::set_dispatcher_period(uint32_t period_usec) {
    m_period_usec = period_usec;
    m_current_state = ESTATE::Empty;
    m_new_state = ESTATE::Detection;
    apply_state();
}

// Don't call apply_state() here!!!
// the method is called from a state, the state will be replaced by another one
// but it's code is still running (UB)
void StateMachine::change_state(ESTATE state) { m_new_state = state; }

InputStates StateMachine::get_input_states() const { return m_input_states; }

void StateMachine::set_output_state(eOutputRole role, bool on) {
    m_outputhandler.set_role_state(role, on);
}

void StateMachine::clear_output_states() { m_outputhandler.clear_all(); }

// IKeyHandlerListener
void StateMachine::on_key_pressed(eKeyRole key_role, eKeyState key_state) {
    void (IState::*mptr)() = nullptr;

    const bool input_state = convert_input_state(key_state);

    switch(key_role) {
        case eKeyRole::uSTOP:
            if(input_state) {
                mptr = &IState::stop_pressed;
            }
            else {
                mptr = &IState::stop_released;
            }
            m_input_states.uSTOP = input_state;
            break;
        case eKeyRole::uTableChanging:
            mptr = &IState::change_tables;
            m_input_states.uTableChanging = input_state;
            break;
        case eKeyRole::uTableBack:
            mptr = &IState::move_table_back_pressed;
            m_input_states.uTableBack = input_state;
            break;
        case eKeyRole::uTableForward:
            mptr = &IState::move_table_front_pressed;
            m_input_states.uTableForward = input_state;
            break;
        case eKeyRole::sCassetteDownStairs:
            // mptr = &IState::move_cassete_down;
            mptr = &IState::on_cassete_down;
            m_input_states.sCassetteDownStairs = input_state;
            break;
        case eKeyRole::sCassetteUpStairs:
            // mptr = &IState::move_cassete_up;
            mptr = &IState::on_cassete_up;
            m_input_states.sCassetteUpStairs = input_state;
            break;
        case eKeyRole::sTableBackDown:
            mptr = &IState::on_table_back_down;
            m_input_states.sTableBackDown = input_state;
            break;
        case eKeyRole::sTableBackUp:
            mptr = &IState::on_table_back_up;
            m_input_states.sTableBackUp = input_state;
            break;
        case eKeyRole::sTableFront:
            mptr = &IState::on_table_front;
            m_input_states.sTableFront = input_state;
            break;
        default:
            break;
    }

    if(m_state && mptr) {
        (m_state->*mptr)();
    }

    apply_state();
}

bool StateMachine::convert_input_state(eKeyState key_state) {
    switch(key_state) {
        case eKeyState::PRESSED:
        case eKeyState::LONG_PRESSED:
        case eKeyState::CONTINUOUS_PRESSED:
            return true;

        case eKeyState::UNPRESSED:
        case eKeyState::LONG_UNPRESSED:
            return false;
    }
}

void StateMachine::apply_state() {
    if(m_current_state == m_new_state) {
        return;
    }

    if(m_state) {
        m_state->~IState();
        delete m_state;
        m_state = nullptr;
    }

    const bool has_control = check_for_control(m_new_state);

    switch(m_new_state) {
        case ESTATE::Empty:
            break;
        case ESTATE::CasseteDown:
            m_state = new CasseteDownState(this, has_control);
            break;
        case ESTATE::CasseteUp:
            m_state = new CasseteUpState(this, has_control);
            break;
        case ESTATE::Detection:
            m_state = new DetectionState(this, m_period_usec);
            break;
        case ESTATE::Error:
            m_state = new ErrorState(this);
            break;
        case ESTATE::TableBackDown:
            m_state = new TableBackDownState(this);
            break;
        case ESTATE::TableBackUp:
            m_state = new TableBackUpState(this);
            break;
        case ESTATE::TableChanging:
            m_state = new TableChangingState(this);
            break;
        case ESTATE::TableFront:
            m_state = new TableFrontState(this);
            break;
        case ESTATE::Wait:
            m_state = new WaitState(this);
            break;
    }

    if(m_state) {
        m_current_state = m_new_state;
    }
}

void StateMachine::detect_error() {
    if(!::check_for_valid_state(m_input_states) && m_state) {
        m_state->on_error();
    }
}

bool StateMachine::check_for_control(ESTATE state) const {
    switch(state) {
        case ESTATE::CasseteDown:
        case ESTATE::CasseteUp:
            return m_input_states.uSTOP && m_input_states.uTableChanging &&
                   ::check_for_valid_state(m_input_states);
        default:
            return false;
    }
}

void StateMachine::handle_led() {
    m_led_timer += m_period_usec;
    if(m_led_timer >= LED_PERIOD_MSEC * 1000) {
        m_led_timer = 0;
        m_led_pin.toggle();
    }
}