#ifndef TABLE_BACKUP_STATE_H
#define TABLE_BACKUP_STATE_H

#include "commonmovingstate.h"
#include "istate.h"
#include "tablesmovementblinkerhandler.h"

class IStateMachine;

class TableBackUpState final : public CommonMovingState {
public:
    TableBackUpState(IStateMachine* state_machine, uint32_t blink_period_usec,
                     bool with_control, bool handle_blinking);
    ~TableBackUpState();

private:
    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void move_table_back(bool state) override;
    void update() override;

private:
    TableMovementBlinkerHandler m_blinker_handler;
};

#endif  // TABLE_BACKUP_STATE_H