#ifndef DISPATCHER_LISTENER_H
#define DISPATCHER_LISTENER_H

#ifndef IAR_PROJECT
#include <stdint-gcc.h>
#endif

class IDispatcherListener {
public:
    virtual ~IDispatcherListener() = default;
    virtual void on_dispatcher_call() {};
    virtual void set_dispatcher_period(uint32_t /*period_usec*/){};
};

enum class ePeriodUnit { uSec, mSec, Sec };
class IDispatcher {
public:
    virtual ~IDispatcher() = default;

    virtual void add_listener(IDispatcherListener* listener, uint32_t period,
                              ePeriodUnit unit) = 0;
};

#endif  // DISPATCHER_LISTENER_H