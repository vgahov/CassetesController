#ifndef TABLE_BACKUP_STATE_H
#define TABLE_BACKUP_STATE_H

#include "istate.h"
#include "statehelper.h"

class IStateMachine;

class TableBackUpState final : public StateHelper {
public:
    TableBackUpState(IStateMachine* state_machine)
        : StateHelper(state_machine) {}

private:
    void on_cassete_up() override;
    void on_cassete_down() override;
    void on_table_front() override;
    void on_table_back_up() override;
    void on_table_back_down() override;
    void stop_pressed() override;
};

#endif  // TABLE_BACKUP_STATE_H