#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <dispatcher/dispatcher.h>
#include <logic/keyhandler/keyhandler.h>
#include <logic/outputhandler/outputhandler.h>

#include "istatemachine.h"
#include "states/istate.h"

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

private:
    void apply_state();
    static bool convert_input_state(eKeyState);

    void detect_error();

private:
    ESTATE m_current_state = ESTATE::Empty;
    ESTATE m_new_state = ESTATE::Empty;
    IState* m_state = nullptr;
    uint32_t m_period_usec = 0;
    InputStates m_input_states;
    OutputHandler& m_outputhandler;
};

#endif  // STATE_MACHINE_H