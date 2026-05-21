#ifndef CASSETE_COMMON_MOVING_STATE_H
#define CASSETE_COMMON_MOVING_STATE_H

#include "istate.h"
#include "statehelper.h"

class IStateMachine;

class CasseteCommonMovingState : public StateHelper {
public:
    CasseteCommonMovingState(IStateMachine* state_machine, bool with_control);

private:
    void on_table_front(bool state) final override;
    void on_table_back_up(bool state) final override;
    void on_table_back_down(bool state) final override;
    void stop(bool state) final override;
    void change_tables(bool state) final override;
    void transition_to_error_if_needed();

protected:
    const bool m_with_stop_control = true;
    bool m_triggered_by_opposite_signal = false;
};

#endif  // CASSETE_COMMON_MOVING_STATE_H