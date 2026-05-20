#ifndef CASSETE_UP_STATE_H
#define CASSETE_UP_STATE_H

#include "istate.h"
#include "statehelper.h"

class IStateMachine;

class CasseteUpState final : public StateHelper {
public:
    CasseteUpState(IStateMachine* state_machine, bool with_control)
        : StateHelper(state_machine), m_with_control(with_control) {}

private:
    void on_cassete_up() override;
    void on_cassete_down() override;
    void on_table_front() override;
    void on_table_back_up() override;
    void on_table_back_down() override;
    void stop_pressed() override;
    void stop_released() override;

    void transition_to_error_if_needed();

private:
    const bool m_with_control;
};

#endif  // CASSETE_UP_STATE_H