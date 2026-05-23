#ifndef COMMON_MOVING_STATE_H
#define COMMON_MOVING_STATE_H

#include "istate.h"
#include "statehelper.h"

class IStateMachine;

class CommonMovingState : public StateHelper {
public:
    CommonMovingState(IStateMachine* state_machine, bool with_control);

private:
    void on_cassete_down(bool state) override;
    void on_cassete_up(bool state) override;
    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;
    void stop(bool state) final override;

protected:
    void transition_to_error_if_needed();
    void main_action_button(bool state);
    void opposite_signal_triggered(bool state);

    static constexpr size_t MAX_STATES_TO_STOP = 2;
    struct StatesToStop {
        bool stop;
        eOutputRole output_role;
    };
    using StatesToStopList = StatesToStop[MAX_STATES_TO_STOP];
    void native_signal_triggered(bool state,
                                 const StatesToStopList& states_to_stop);

    void clear_output_signals(const StatesToStopList& states_to_stop);
    // void native_signal_triggered(bool state, StatesToStop
    // (&states_to_stop)[2]);

protected:
    const bool m_with_stop_control = true;
    bool m_triggered_by_opposite_signal = false;
};

#endif  // COMMON_MOVING_STATE_H