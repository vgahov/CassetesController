#ifndef ISTATE_H
#define ISTATE_H

class IStateMachine;

class IState {
public:
    IState(IStateMachine* state_machine);
    virtual ~IState() = default;

    virtual void move_cassete_up_pressed() {}
    virtual void move_cassete_up_released() {}
    virtual void move_cassete_down_pressed() {}
    virtual void move_cassete_down_released() {}
    virtual void on_cassete_up() {}
    virtual void on_cassete_down() {}

    virtual void change_tables() {}
    virtual void move_table_front_pressed() {}
    virtual void move_table_front_released() {}
    virtual void move_table_back_pressed() {}
    virtual void move_table_back_released() {}
    virtual void on_table_front() {}
    virtual void on_table_back_up() {}
    virtual void on_table_back_down() {}

    virtual void pause() {}
    virtual void stop_pressed() {}
    virtual void stop_released() {}
    virtual void on_error() {}

    virtual void update() {}

protected:
    IStateMachine* m_state_machine;
};

#endif  // ISTATE_H