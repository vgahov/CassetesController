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
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;
    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;
    void stop(bool state) override;
};

#endif  // TABLE_BACKDOWN_STATE_H