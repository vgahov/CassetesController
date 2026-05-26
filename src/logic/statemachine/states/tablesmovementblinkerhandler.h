#ifndef TABLE_MOVEMENT_BLINKER_HANDLER_H
#define TABLE_MOVEMENT_BLINKER_HANDLER_H

#include <stdint.h>

#include "../../outputhandler/outputhandler.h"
#include "../istatemachine.h"

class TableMovementBlinkerHandler {
public:
    TableMovementBlinkerHandler(IStateMachine* state_machine,
                                uint32_t period_usec, bool handle_blinking)
        : m_state_machine(state_machine),
          m_period_usec(period_usec),
          m_handle_blinking(handle_blinking) {
        if(m_state_machine && m_handle_blinking) {
            m_state_machine->set_output_state(
                eOutputRole::TABLE_CHANGING_INDICATION, true);
            m_state_machine->set_output_state(eOutputRole::TABLE_INDICATION,
                                              true);
        }
    }

    ~TableMovementBlinkerHandler() {
        if(m_state_machine && m_handle_blinking) {
            m_state_machine->set_output_state(
                eOutputRole::TABLE_CHANGING_INDICATION, false);
            m_state_machine->set_output_state(eOutputRole::TABLE_INDICATION,
                                              false);
        }
    }

    void handle_blinking() {
        if(m_period_usec == 0 || m_handle_blinking == false) {
            return;
        }
        if(m_blink_delay >= BLINK_DELAY_S * 1000000) {
            m_blink_delay = 0;
            m_blink_state = !m_blink_state;
            if(m_state_machine) {
                m_state_machine->set_output_state(
                    eOutputRole::TABLE_CHANGING_INDICATION, m_blink_state);
                m_state_machine->set_output_state(eOutputRole::TABLE_INDICATION,
                                                  m_blink_state);
            }
        }
        else {
            m_blink_delay += m_period_usec;
        }
    }

private:
    IStateMachine* m_state_machine;
    uint32_t m_period_usec;
    uint32_t m_blink_delay = 0;
    bool m_blink_state = true;
    const bool m_handle_blinking;
    static constexpr uint32_t BLINK_DELAY_S = 1;
};

#endif  // TABLE_MOVEMENT_BLINKER_HANDLER_H
