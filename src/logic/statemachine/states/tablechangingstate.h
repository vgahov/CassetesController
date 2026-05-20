#ifndef TABLE_CHANGING_STATE_H
#define TABLE_CHANGING_STATE_H

#include <logic/statemachine/istatemachine.h>
#include <stdint-gcc.h>

#include "istate.h"

class TableChangingState final : public IState, public IStateMachine {
public:
    TableChangingState(IStateMachine* state_machine) : IState(state_machine) {
        for(size_t i = 0;
            i < static_cast<size_t>(ETableChangingSubState::COUNT); ++i) {
            m_sub_states[i] = ETableChangingSubState::None;
        }

        check_initial_conditions();
    }

    ~TableChangingState() { cleanup_current_substate(); }

private:
    void change_state(ESTATE state) override;
    InputStates get_input_states() const override;
    void set_output_state(eOutputRole role, bool on) override;
    void clear_output_states() override;

    enum class ETableChangingSubState {
        None,
        CasseteToDown,
        CasseteToUp,
        TableToFront,
        TableToBackDown,
        TableToBackUp,
        COUNT,
    };
    // void move_cassete_up() override;
    // void move_cassete_down() override;
    void on_cassete_up() override;
    void on_cassete_down() override;
    void on_table_front() override;
    void on_table_back_up() override;
    void on_table_back_down() override;

    void stop_pressed() override;
    void stop_released() override;

    void check_initial_conditions();
    void put_substate(size_t index, ETableChangingSubState sub_state) {
        if(index >= static_cast<size_t>(ETableChangingSubState::COUNT)) {
            return;
        }
        m_sub_states[static_cast<size_t>(index)] = sub_state;
    }
    void trigger_substate();
    ETableChangingSubState pop_next_substate();
    ETableChangingSubState get_next_substate();
    void cleanup_current_substate() {
        if(m_current_substate) {
            m_current_substate->~IState();
            delete m_current_substate;
            m_current_substate = nullptr;
        }
    }

private:
    ETableChangingSubState
        m_sub_states[static_cast<size_t>(ETableChangingSubState::COUNT)];

    IState* m_current_substate = nullptr;
};

#endif  // TABLE_CHANGING_STATE_H