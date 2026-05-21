#ifndef CASSETE_UP_STATE_H
#define CASSETE_UP_STATE_H

#include "cassetecommonmovingstate.h"
#include "istate.h"

class IStateMachine;

class CasseteUpState final : public CasseteCommonMovingState {
public:
    CasseteUpState(IStateMachine* state_machine, bool with_control);

private:
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;
};

#endif  // CASSETE_UP_STATE_H