#ifndef HELPERS_H
#define HELPERS_H

#include <logic/statemachine/istatemachine.h>

bool is_cassete_valid(const InputStates& input_states);
bool are_tables_valid(const InputStates& input_states);

bool check_for_valid_state(const InputStates& input_states);

#endif  // HELPERS_H