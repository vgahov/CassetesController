#ifndef TABLE_FRONT_STATE_H
#define TABLE_FRONT_STATE_H

#include "istate.h"

class IStateMachine;

class TableFrontState final : public IState {
public:
    TableFrontState(IStateMachine* state_machine) : IState(state_machine) {}

private:
    // void move_cassete_up() override;
    // void move_cassete_down() override;
    void on_cassete_up() override;
    void on_cassete_down() override;
    void move_table_front() override;
    void move_table_back() override;
    void on_table_front() override;
    // void on_table_back() override;
    void pause() override;
    void on_stop_pressed() override;
    void on_stop_released() override;
    void on_error() override;
    void update() override;
};

#endif  // TABLE_FRONT_STATE_H