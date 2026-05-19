
#include "istate.h"

#include <logic/statemachine/istatemachine.h>

IState::IState(IStateMachine* state_machine) : m_state_machine(state_machine) {}