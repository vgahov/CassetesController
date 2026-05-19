#ifndef WAIT_STATE_H
#define WAIT_STATE_H

#include "istate.h"

class IStateMachine;

class WaitState final : public IState {
public:
    WaitState(IStateMachine* state_machine) : IState(state_machine) {}

private:
    void on_cassete_up() override;
    void on_cassete_down() override;
    void move_table_front_pressed() override;
    void move_table_back_pressed() override;
    void change_tables() override;
    void stop_pressed() override;
    void stop_released() override;
    void on_error() override;
    void update() override;

private:
};

#endif  // WAIT_STATE_H