#ifndef TABLE_BACKDOWN_STATE_H
#define TABLE_BACKDOWN_STATE_H

#include "istate.h"
#include "statehelper.h"

class IStateMachine;

class TableBackDownState final : public StateHelper {
public:
    TableBackDownState(IStateMachine* state_machine)
        : StateHelper(state_machine) {}

private:
    void on_cassete_up() override;
    void on_cassete_down() override;
    void on_table_front() override;
    void on_table_back_up() override;
    void on_table_back_down() override;
    void stop_pressed() override;
};

#endif  // TABLE_BACKDOWN_STATE_H