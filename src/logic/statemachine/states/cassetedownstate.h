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
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;
    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;
    void stop(bool state) override;
    void on_error() override;

    void transition_to_error_if_needed();

private:
    const bool m_with_control = true;
};

#endif  // CASSETE_DOWN_STATE_H