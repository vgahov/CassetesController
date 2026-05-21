#ifndef CASSETE_DOWN_STATE_H
#define CASSETE_DOWN_STATE_H

#include "commonmovingstate.h"
#include "istate.h"

class IStateMachine;

class CasseteDownState final : public CommonMovingState {
public:
    CasseteDownState(IStateMachine* state_machine, bool with_control);
    ~CasseteDownState();

private:
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;
    void change_tables(bool state) override;
};

#endif  // CASSETE_DOWN_STATE_H