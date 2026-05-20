#ifndef CASSETE_DOWN_STATE_H
#define CASSETE_DOWN_STATE_H

#include "istate.h"
#include "statehelper.h"

class IStateMachine;

class CasseteDownState final : public StateHelper {
public:
    CasseteDownState(IStateMachine* state_machine, bool with_control)
        : StateHelper(state_machine), m_with_control(with_control) {}

private:
    void on_cassete_up() override;
    void on_cassete_down() override;
    void on_table_front() override;
    void on_table_back_up() override;
    void on_table_back_down() override;
    void stop_pressed() override;
    void stop_released() override;
    void on_error() override;

    void transition_to_error_if_needed();

private:
    const bool m_with_control = true;
};

#endif  // CASSETE_DOWN_STATE_H