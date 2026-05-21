#ifndef TABLE_BACKDOWN_STATE_H
#define TABLE_BACKDOWN_STATE_H

#include "commonmovingstate.h"
#include "istate.h"

class IStateMachine;

class TableBackDownState final : public CommonMovingState {
public:
    TableBackDownState(IStateMachine* state_machine, bool with_control);
    ~TableBackDownState();

private:
    void on_table_front(bool state) override;
    void on_table_back_down(bool state) override;
    void move_table_back(bool state) override;
};

#endif  // TABLE_BACKDOWN_STATE_H