#ifndef TIMER_LISTENER_H
#define TIMER_LISTENER_H

class ITimerListener {
public:
    virtual void on_timer_call() = 0;
    virtual void set_timer_period(uint32_t period_usec) = 0;
};

#endif  // TIMER_LISTENER_H