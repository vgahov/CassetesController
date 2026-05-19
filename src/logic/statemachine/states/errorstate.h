#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include "istate.h"

class IStateMachine;

class ErrorState final : public IState {
public:
    ErrorState(IStateMachine* state_machine) : IState(state_machine) {}

private:
    void on_cassete_up() override;
    void on_cassete_down() override;

    void on_table_front() override;
    void on_table_back_up() override;
    void on_table_back_down() override;

    void update() override;

    void check_for_valid_state();
};

#endif  // ERROR_STATE_H