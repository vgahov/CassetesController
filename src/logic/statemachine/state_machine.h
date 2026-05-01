#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <dispatcher/dispatcher.h>

class StateMachine : public IDispatcherListener {
public:
    StateMachine(/* args */);
    ~StateMachine();

    void on_dispatcher_call() override;

private:
    /* data */
};

StateMachine::StateMachine(/* args */) {}

StateMachine::~StateMachine() {}

#endif  // STATE_MACHINE_H