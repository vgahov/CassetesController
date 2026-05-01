#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <dispatcher/dispatcher.h>
#include <logic/keyhandler/keyhandler.h>

class StateMachine : public IDispatcherListener, public IKeyHandlerListener {
public:
    StateMachine(/* args */);
    ~StateMachine();

    // IDispatcherListener
    void on_dispatcher_call() override {
        IDispatcherListener::on_dispatcher_call();
    };
    void set_dispatcher_period(uint32_t period_usec) override {
        IDispatcherListener::set_dispatcher_period(period_usec);
    }

    // IKeyHandlerListener
    void on_key_pressed(eKeyRole, eKeyState) override{};

private:
    /* data */
};

StateMachine::StateMachine(/* args */) {}

StateMachine::~StateMachine() {}

#endif  // STATE_MACHINE_H