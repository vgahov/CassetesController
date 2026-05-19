#ifndef ISTATE_H
#define ISTATE_H

class IStateMachine;

class IState {
public:
    IState(IStateMachine* state_machine) : m_state_machine(state_machine) {}
    virtual ~IState() = default;

    // virtual void move_cassete_up() {}
    // virtual void move_cassete_down() {}
    virtual void on_cassete_up() {}
    virtual void on_cassete_down() {}

    virtual void move_table_front() {}
    virtual void move_table_back() {}
    virtual void change_tables() {}
    virtual void on_table_front() {}
    virtual void on_table_back_up() {}
    virtual void on_table_back_down() {}

    virtual void pause() {}
    virtual void stop() {}
    virtual void on_error() {}

    virtual void update() {}

protected:
    IStateMachine* m_state_machine;
};

#endif  // ISTATE_H