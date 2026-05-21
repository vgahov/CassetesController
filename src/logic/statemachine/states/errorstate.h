#ifndef ERROR_STATE_H
#define ERROR_STATE_H

#include <logic/statemachine/istatemachine.h>

#include "istate.h"

class IStateMachine;

class ErrorState final : public IState {
public:
    ErrorState(IStateMachine* state_machine) : IState(state_machine) {
        if(!m_state_machine) {
            return;
        }
        m_state_machine->clear_output_states();
        m_state_machine->set_output_state(eOutputRole::INDICATION_READY, false);
    }

private:
    /*void move_cassete_up_pressed() override;
    void move_cassete_up_released() override;
    void move_cassete_down_pressed() override;
    void move_cassete_down_released() override;
    void move_table_front_pressed() override;
    void move_table_front_released() override;
    void move_table_back_pressed() override;
    void move_table_back_released() override;*/
    // void stop_pressed() override;
    // void stop_released() override;
    /*
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
    */
    void on_cassete_up(bool state) override;
    void on_cassete_down(bool state) override;

    void on_table_front(bool state) override;
    void on_table_back_up(bool state) override;
    void on_table_back_down(bool state) override;

    void update() override;

    void check_for_valid_state();
};

#endif  // ERROR_STATE_H