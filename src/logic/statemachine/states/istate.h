#ifndef ISTATE_H
#define ISTATE_H

#include <port/port.h>

class IStateMachine;

class IState {
public:
    IState(IStateMachine* state_machine);
    virtual ~IState() = default;

    virtual void on_cassete_up(bool) {}
    virtual void on_cassete_down(bool) {}

    virtual void change_tables(bool) {}
    virtual void move_table_front(bool) {}
    virtual void move_table_back(bool) {}
    virtual void on_table_front(bool) {}
    virtual void on_table_back_up(bool) {}
    virtual void on_table_back_down(bool) {}

    virtual void pause() {}
    virtual void stop(bool) {}
    virtual void on_error() {}

    virtual void update() {}

protected:
    IStateMachine* m_state_machine;
};

#endif  // ISTATE_H