#ifndef TABLE_BACKUP_STATE_H
#define TABLE_BACKUP_STATE_H

#include "commonmovingstate.h"
#include "istate.h"

class IStateMachine;

class TableBackUpState final : public CommonMovingState {
public:
    TableBackUpState(IStateMachine* state_machine, bool with_control);
    ~TableBackUpState();

private:
    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void move_table_back(bool state) override;
};

#endif  // TABLE_BACKUP_STATE_H