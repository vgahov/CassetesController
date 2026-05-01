#ifndef TIMER_H
#define TIMER_H

#include "timerlistener.h"

constexpr uint32_t FREQUENCY = F_CPU;

class Timer0 final {
public:
    static void interrupt_handler();
    // static void init( TimerReg timer, uint32_t period_usec );
    static void init(uint32_t period_usec);
    static void destroy();
    static Timer0& get_instance();

    void set_interrupt_callback(ITimerListener* callback);
    void run_callback();
    bool is_ready() const;

private:
    Timer0(const Timer0&) = default;
    Timer0& operator=(const Timer0&) = default;

    static Timer0* timer0_ptr;

    Timer0();
    // Timer0( TimerReg timer, uint32_t period_usec );
    Timer0(uint32_t period_usec);
    ~Timer0();

    bool is_registers_valid();

    static char s_timer_object[];

    void initialize_divider_logic(uint32_t necessary_period_usec,
                                  uint16_t divider);
    void initialize_skipper_logic(uint32_t necessary_period_usec,
                                  uint16_t divider);
    void set_divider(uint16_t divider);

    void handle_divider_logic();
    bool handle_skipper_logic();

    static const uint32_t PRECISION_COEF = 1000;
    // result is bigger than real in 100times (to avoid float)
    static uint32_t get_one_tick_duration(uint16_t divider) {
        return (divider * 1000000) / (FREQUENCY / PRECISION_COEF);
    }

    static uint32_t get_number_of_ticks(uint32_t necessary_period_usec,
                                        uint16_t divider) {
        const auto one_tick_duration = get_one_tick_duration(divider);
        return (necessary_period_usec * PRECISION_COEF) / one_tick_duration;
    }

    static uint32_t get_timer_period(uint32_t necessary_period_usec,
                                     uint16_t divider) {
        const auto one_tick_duration = get_one_tick_duration(divider);
        const auto number_of_ticks =
            get_number_of_ticks(necessary_period_usec, divider);
        return (number_of_ticks * one_tick_duration) / PRECISION_COEF;
    }

private:
    // TimerReg m_timer;
    ITimerListener* m_timer_callback;

    uint32_t m_skip_timer_value = 0;
    uint32_t m_skip_timer_curr_value = 0;
    uint32_t m_timer_period = 0;
    bool m_is_ready = false;

    uint32_t m_skip_interrupt = 0;
    uint32_t m_skip_interrupt_counter = 0;
    uint8_t m_reload_timer_value = 0;

    struct SkipLogic {
        uint32_t skip_interrupt_number = 0;
        uint32_t skip_interrupt_counter = 0;
        uint8_t reload_timer_value = 0;
        bool m_is_valid = false;
        bool is_tail = false;
        bool is_valid() { return m_is_valid; }

        SkipLogic() = default;

        SkipLogic(uint32_t skip_number, uint32_t skip_counter,
                  uint8_t reload_value)
            : skip_interrupt_number(skip_number),
              skip_interrupt_counter(skip_counter),
              reload_timer_value(reload_value),
              m_is_valid(true) {}
    };

    SkipLogic m_skip_logic;
};

#endif  // TIMER_H
