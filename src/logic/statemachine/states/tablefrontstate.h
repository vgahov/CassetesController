#ifndef TABLE_FRONT_STATE_H
#define TABLE_FRONT_STATE_H

#include "commonmovingstate.h"
#include "istate.h"

class IStateMachine;

class TableFrontState final : public CommonMovingState {
public:
    TableFrontState(IStateMachine* state_machine, bool with_control);
    ~TableFrontState();

private:
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;
    void on_table_front(bool state) override;
    void move_table_front(bool state) override;
};

#endif  // TABLE_FRONT_STATE_H