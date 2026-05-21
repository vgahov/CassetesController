#ifndef ISTATE_H
#define ISTATE_H

#include <port/port.h>
extern Pin m_led_pin;

class IStateMachine;

class IState {
public:
    IState(IStateMachine* state_machine);
    virtual ~IState() = default;

    // virtual void move_cassete_up(bool state) {}
    // virtual void move_cassete_down(bool state) {}
    virtual void on_cassete_up(bool state) {}
    virtual void on_cassete_down(bool state) {}

    virtual void change_tables(bool state) {}
    virtual void move_table_front(bool state) {}
    virtual void move_table_back(bool state) {}
    virtual void on_table_front(bool state) {}
    virtual void on_table_back_up(bool state) {}
    virtual void on_table_back_down(bool state) {}

    virtual void pause() {}
    virtual void stop(bool state) {}
    virtual void on_error() {}

    virtual void update() {}

protected:
    IStateMachine* m_state_machine;
};

#endif  // ISTATE_H