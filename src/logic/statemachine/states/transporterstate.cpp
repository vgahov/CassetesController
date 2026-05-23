#include "transporterstate.h"

#include "../../outputhandler/outputhandler.h"
#include "../statemachine.h"

TransporterState::TransporterState(StateMachine* state_machine)
    : m_state_machine(state_machine) {
    m_phase = TransporterPhase::Idle;
    m_timer_ms = 0;
    m_blink_state = false;
}

void TransporterState::move_transporter(bool state) {
    if(m_period_usec == 0) {
        return;
    }
    if(state) {
        m_phase = TransporterPhase::Running;
        m_timer_ms = 0;
        set_outputs(true, true);  // Both outputs ON
    }
    else {
        // Optionally handle release
    }
}

void TransporterState::stop(bool state) {
    if(m_period_usec == 0) {
        return;
    }

    if(state) {
        m_phase = TransporterPhase::Idle;
        set_outputs(false, false);  // Both outputs OFF
        m_timer_ms = 0;
        m_blink_state = false;
    }
}

void TransporterState::update() {
    if(m_period_usec == 0) {
        return;
    }

    if(m_phase == TransporterPhase::Running ||
       m_phase == TransporterPhase::Blinking) {
        m_timer_ms += m_period_usec / 1000;
        if(m_timer_ms >= kTotalTimeMs) {
            m_phase = TransporterPhase::Finished;
            set_outputs(false, false);
            return;
        }
        if(m_timer_ms >= kBlinkStartMs) {
            m_phase = TransporterPhase::Blinking;
            // Blink every 1s
            if((m_timer_ms / kBlinkIntervalMs) % 2 == 0) {
                if(!m_blink_state) {
                    set_outputs(true, true);  // Indication ON
                    m_blink_state = true;
                }
            }
            else {
                if(m_blink_state) {
                    set_outputs(true, false);  // Indication OFF, Stop ON
                    m_blink_state = false;
                }
            }
        }
    }
}

void TransporterState::set_outputs(bool stop_on, bool indication_on) {
    m_state_machine->set_output_state(eOutputRole::TRANSPORTER_STOP, stop_on);
    m_state_machine->set_output_state(eOutputRole::TRANSPORTER_INDICATION,
                                      indication_on);
}
