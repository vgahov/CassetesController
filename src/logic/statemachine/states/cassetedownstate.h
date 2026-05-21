#ifndef CASSETE_DOWN_STATE_H
#define CASSETE_DOWN_STATE_H

#include "cassetecommonmovingstate.h"
#include "istate.h"

class IStateMachine;

class CasseteDownState final : public CasseteCommonMovingState {
public:
    CasseteDownState(IStateMachine* state_machine, bool with_control);

private:
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;
};

#endif  // CASSETE_DOWN_STATE_H