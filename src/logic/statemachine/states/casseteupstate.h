#ifndef CASSETE_UP_STATE_H
#define CASSETE_UP_STATE_H

#include "istate.h"

class IStateMachine;

class CasseteUpState final : public IState {
public:
    CasseteUpState(IStateMachine* state_machine) : IState(state_machine) {}

private:
    // void move_cassete_up() override;
    // void move_cassete_down() override;
    void on_cassete_up() override;
    void on_cassete_down() override;
    void move_table_front_pressed() override;
    void move_table_back_pressed() override;
    void on_table_front() override;
    // void on_table_back() override;
    void pause() override;
    void stop_pressed() override;
    void stop_released() override;
    void on_error() override;
    void update() override;
};

#endif  // CASSETE_UP_STATE_H