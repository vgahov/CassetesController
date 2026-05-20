#ifndef DISPATCHER_H
#define DISPATCHER_H

#ifndef IAR_PROJECT
#include <stdint-gcc.h>
#endif

#include <platform_dependent/timer.h>
#include <port/port.h>

#include "dispatcherlistener.h"

class Dispatcher : public ITimerListener, public IDispatcher {
    static constexpr uint32_t LISTENERS_NUMBER = 20;

public:
    // ITimerListener
    void on_timer_call() override;
    void set_timer_period(uint32_t period_usec) override;

    // IDispatcher
    void add_listener(IDispatcherListener *listener, uint32_t period,
                      ePeriodUnit unit) override;

    void loop();

private:
    struct ListenerHandler {
        uint32_t period_usec;
        uint32_t current_period;
        IDispatcherListener *listener;
    };

    bool m_stop = false;
    volatile bool m_tick = false;
    bool m_is_ready = false;
    uint32_t m_period_usec = 0;
    ;

    ListenerHandler m_listeners[LISTENERS_NUMBER] = {{0, 0, nullptr}};
    uint32_t m_current_listener_pos = 0;
};

#endif  // DISPATCHER_H