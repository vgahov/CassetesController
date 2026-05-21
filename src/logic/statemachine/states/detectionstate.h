#ifndef DETECTION_STATE_H
#define DETECTION_STATE_H

#include <stdint-gcc.h>

#include "istate.h"

class IStateMachine;

class DetectionState final : public IState {
public:
    DetectionState(IStateMachine* state_machine, uint32_t period_usec)
        : IState(state_machine),
          m_period_usec(period_usec),
          m_passed_period_usec(0) {}

private:
    void update() override;

private:
    static constexpr uint32_t INIT_TIME_SEC = 5;
    uint32_t m_period_usec;
    uint32_t m_passed_period_usec;
};

#endif  // DETECTION_STATE_H