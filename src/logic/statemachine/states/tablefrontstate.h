#ifndef TABLE_FRONT_STATE_H
#define TABLE_FRONT_STATE_H

#include "commonmovingstate.h"
#include "istate.h"
#include "tablesmovementblinkerhandler.h"

class IStateMachine;

class TableFrontState final : public CommonMovingState {
public:
    TableFrontState(IStateMachine* state_machine, uint32_t blink_period_usec,
                    bool with_control, bool handle_blinking);
    ~TableFrontState() = default;

private:
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;
    void on_table_front(bool state) override;
    void move_table_front(bool state) override;
    void update() override;

private:
    TableMovementBlinkerHandler m_blinker_handler;
};

#endif  // TABLE_FRONT_STATE_H