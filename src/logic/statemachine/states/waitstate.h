#ifndef WAIT_STATE_H
#define WAIT_STATE_H

#include "istate.h"

class IStateMachine;

class WaitState final : public IState {
public:
    WaitState(IStateMachine* state_machine) : IState(state_machine) {}

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
    void stop() override;
    void on_error() override;
    void update() override;
};

#endif  // WAIT_STATE_H