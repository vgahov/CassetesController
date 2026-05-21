#ifndef CASSETE_UP_STATE_H
#define CASSETE_UP_STATE_H

#include "commonmovingstate.h"
#include "istate.h"

class IStateMachine;

class CasseteUpState final : public CommonMovingState {
public:
    CasseteUpState(IStateMachine* state_machine, bool with_control);
    ~CasseteUpState();

private:
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;
    void change_tables(bool state) override;
};

#endif  // CASSETE_UP_STATE_H