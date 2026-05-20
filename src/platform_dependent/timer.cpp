
#ifndef IAR_PROJECT
#include <avr/io.h>
#endif

// #include "Port.h"
#include <system/systemfunc.h>

#include "timer.h"

namespace
{
    constexpr uint32_t TIMER_COUNTER_MAX_VALUE = 255;
    constexpr uint32_t TIMER_COUNTER_MAX_TICKS = TIMER_COUNTER_MAX_VALUE + 1;

    struct PrescalerOption {
        uint16_t divisor;
        uint8_t cs_bits;
    };
};  // namespace

Timer0* Timer0::timer0_ptr = nullptr;
char Timer0::s_timer_object[sizeof(Timer0)];

Timer0::Timer0() : m_timer_callback(nullptr) {}

Timer0::Timer0(uint32_t necessary_period_usec) : m_timer_callback(nullptr) {
    if(necessary_period_usec == 0) {
        return;
    }

    static const PrescalerOption options[] = {
        {1, (1 << CS00)},
        {8, (1 << CS01)},
        {64, (1 << CS01) | (1 << CS00)},
        {256, (1 << CS02)},
        {1024, (1 << CS02) | (1 << CS00)},
    };

    const auto fclk = get_fclk();
    const double cpu_period_usec = (1. / fclk) * 1000000;

    uint8_t best_ocr = 0;
    uint8_t best_cs = 0;
    for(const auto& option : options) {
        const double divider_tick_usec = option.divisor * cpu_period_usec;
        const auto necessary_ticks_number =
            static_cast<uint32_t>(necessary_period_usec / divider_tick_usec);

        if(necessary_ticks_number > 0 &&
           necessary_ticks_number <= TIMER_COUNTER_MAX_TICKS) {
            best_cs = option.cs_bits;
            best_ocr = static_cast<uint8_t>(necessary_ticks_number - 1);
            m_is_ready = true;
            break;
        }
    }

    // Stop the timer
    TCCR0A = 0;
    TCCR0B = 0;
    TCNT0 = 0;
    // CTC mode: TOP = OCR0A
    TCCR0A |= (1 << WGM01);

    if(!is_ready()) {
        const auto divider_idx = sizeof(options) / sizeof(options[0]) - 1;
        const auto divider = options[divider_idx];

        const double divider_tick_usec = divider.divisor * cpu_period_usec;
        const auto necessary_ticks_number =
            static_cast<uint32_t>(necessary_period_usec / divider_tick_usec);

        m_skip_logic =
            SkipLogic((necessary_ticks_number - 1) / 256, 0u,
                      static_cast<uint8_t>((necessary_ticks_number - 1) % 256));

        best_ocr = TIMER_COUNTER_MAX_VALUE;
        best_cs = divider.cs_bits;
        m_is_ready = true;
    }
    TIFR0 |= (1 << OCF0A);
    TIMSK0 |= (1 << OCIE0A);

    // Period
    OCR0A = best_ocr;
    // Prescaler
    TCCR0B |= best_cs;

    m_timer_period = necessary_period_usec;
}

Timer0::~Timer0() {
    if(is_ready()) {
        // Disable interrupt
        TIMSK0 = 0;
        // Stop counter
        TCCR0B = 0b00000000;
    }
}

void Timer0::interrupt_handler() { get_instance().run_callback(); }

void Timer0::init(uint32_t period_usec) {
    if(!timer0_ptr) {
        timer0_ptr = new((void*)Timer0::s_timer_object) Timer0(period_usec);
    }
}

void Timer0::destroy() {
    if(timer0_ptr) {
        timer0_ptr->~Timer0();
        timer0_ptr = nullptr;
    }
}

Timer0& Timer0::get_instance() {
    static Timer0 invalid_timer;
    return timer0_ptr ? *timer0_ptr : invalid_timer;
}

bool Timer0::is_registers_valid() { return true; }

void Timer0::set_interrupt_callback(ITimerListener* callback) {
    if(is_ready() && callback) {
        m_timer_callback = callback;
        m_timer_callback->set_timer_period(m_timer_period);
    }
}

void Timer0::run_callback() {
    bool run_callback = false;

    if(!m_skip_logic.is_valid()) {
        run_callback = true;
    }
    else {
        if(!m_skip_logic.is_tail) {
            ++m_skip_logic.skip_interrupt_counter;

            if(m_skip_logic.skip_interrupt_counter >=
               m_skip_logic.skip_interrupt_number) {
                if(m_skip_logic.reload_timer_value > 0) {
                    OCR0A = m_skip_logic.reload_timer_value - 1;
                    m_skip_logic.is_tail = true;
                }
                else {
                    m_skip_logic.skip_interrupt_counter = 0;
                    run_callback = true;
                }
            }
        }
        else {
            m_skip_logic.skip_interrupt_counter = 0;
            m_skip_logic.is_tail = false;
            OCR0A = TIMER_COUNTER_MAX_VALUE;
            run_callback = true;
        }
    }

    if(run_callback) {
        // It can be checked if the callback is called
    }

    if(m_timer_callback && run_callback) {
        m_timer_callback->on_timer_call();
    }
}

bool Timer0::is_ready() const { return m_is_ready; }
