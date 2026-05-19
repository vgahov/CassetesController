#include "statemachine.h"

#include "states/cassetedownstate.h"
#include "states/casseteupstate.h"
#include "states/detectionstate.h"
#include "states/errorstate.h"
#include "states/istate.h"
#include "states/tablebackstate.h"
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
    }
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

// IKeyHandlerListener
void StateMachine::on_key_pressed(eKeyRole key_role, eKeyState key_state) {
    void (IState::*mptr)() = nullptr;

    const bool input_state = convert_input_state(key_state);

    switch(key_role) {
        case eKeyRole::uSTOP:
            mptr = &IState::stop;
            m_input_states.uSTOP = input_state;
            break;
        case eKeyRole::uTableChanging:
            mptr = &IState::change_tables;
            m_input_states.uTableChanging = input_state;
            break;
        case eKeyRole::uTableBack:
            mptr = &IState::move_table_back;
            m_input_states.uTableBack = input_state;
            break;
        case eKeyRole::uTableForward:
            mptr = &IState::move_table_front;
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
    m_state->~IState();
    delete m_state;
    m_state = nullptr;

    switch(m_new_state) {
        case ESTATE::Empty:
            break;
        case ESTATE::CasseteDown:
            m_state = new CasseteDownState(this);
            break;
        case ESTATE::CasseteUp:
            m_state = new CasseteUpState(this);
            break;
        case ESTATE::Detection:
            m_state = new DetectionState(this, m_period_usec);
            break;
        case ESTATE::Error:
            m_state = new ErrorState(this);
            break;
        case ESTATE::TableBack:
            m_state = new TableBackState(this);
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