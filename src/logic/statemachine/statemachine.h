#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <dispatcher/dispatcher.h>
#include <logic/keyhandler/keyhandler.h>
#include <logic/outputhandler/outputhandler.h>

#include "istatemachine.h"
#include "states/istate.h"
#include "states/transporterstate.h"

class StateMachine final : public IDispatcherListener,
                           public IKeyHandlerListener,
                           public IStateMachine {
public:
    StateMachine(OutputHandler& outputhandler);
    ~StateMachine();

    // IDispatcherListener
    void on_dispatcher_call() override;
    void set_dispatcher_period(uint32_t period_usec) override;

    // IKeyHandlerListener
    void on_key_pressed(eKeyRole, eKeyState) override;

    // IStateMachine
    void change_state(ESTATE) override;
    InputStates get_input_states() const override;
    void set_output_state(eOutputRole role, bool on) override;
    void clear_output_states() override;

private:
    void apply_state();
    static bool convert_input_state(eKeyState);

    void detect_error();
    bool check_for_stop_control(ESTATE) const;

    void handle_led();

private:
    ESTATE m_current_state = ESTATE::Empty;
    ESTATE m_new_state = ESTATE::Empty;
    IState* m_state = nullptr;
    uint32_t m_period_usec = 0;
    InputStates m_input_states;
    OutputHandler& m_outputhandler;
    TransporterState m_transport_state;
    bool m_transport_state_active = false;

    static constexpr uint32_t LED_PERIOD_MSEC = 2000;

    // Pin m_led_pin{ePORT::ePORTB, 4, false};
    uint32_t m_led_timer = 0;
};

#endif  // STATE_MACHINE_H