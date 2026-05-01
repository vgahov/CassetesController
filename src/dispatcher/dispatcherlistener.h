#ifndef DISPATCHER_LISTENER_H
#define DISPATCHER_LISTENER_H

#ifndef IAR_PROJECT
#include <stdint-gcc.h>
#endif

class IDispatcher;

class IDispatcherListener {
public:
    virtual ~IDispatcherListener() = default;
    virtual void on_dispatcher_call() = 0;
    virtual void set_dispatcher_period(uint32_t period_usec) = 0;
};

inline void IDispatcherListener::on_dispatcher_call() {}
inline void IDispatcherListener::set_dispatcher_period(uint32_t) {}

/*class IDispatcher {
   public:
    // virtual ~IDispatcher( ) = default;

    virtual uint32_t get_period(IDispatcherListener*) = 0;
};*/

#endif  // DISPATCHER_LISTENER_H