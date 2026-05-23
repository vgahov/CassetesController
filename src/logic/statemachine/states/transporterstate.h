#ifndef TRANSPORTERSTATE_H
#define TRANSPORTERSTATE_H

#include <stdint.h>

class StateMachine;

class TransporterState {
public:
    TransporterState(StateMachine* state_machine);
    ~TransporterState() = default;

    void move_transporter(bool state);
    void stop(bool state);
    void update();
    void set_period(uint32_t period_usec) { m_period_usec = period_usec; }

private:
    StateMachine* m_state_machine;
    uint32_t m_period_usec = 0;
    enum class TransporterPhase {
        Idle,
        Running,
        Blinking,
        Finished
    } m_phase = TransporterPhase::Idle;

    uint32_t m_timer_ms = 0;
    static constexpr uint32_t kTotalTimeMs = 60000;  // 1 minute
    static constexpr uint32_t kBlinkStartMs =
        kTotalTimeMs - 10000;                           // Start blinking at 50s
    static constexpr uint32_t kBlinkIntervalMs = 1000;  // 1s
    bool m_blink_state = false;

    void set_outputs(bool stop_on, bool indication_on);
};

#endif  // TRANSPORTERSTATE_H
