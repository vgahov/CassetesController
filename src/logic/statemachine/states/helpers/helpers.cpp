#include "helpers.h"

// Check the cassete state/position
bool is_cassete_valid(const InputStates& input_states) {
    return input_states.sCassetteDownStairs || input_states.sCassetteUpStairs;
}

// Check the tables states
// if the tables:
// - both are inside cassete
// - one of them in cassete, another one is on front of the work surface
// In general - 2 of 3 should be true
bool are_tables_valid(const InputStates& input_states) {
    return (input_states.sTableBackDown + input_states.sTableBackUp +
                input_states.sTableFront >=
            2);
}

bool check_for_valid_state(const InputStates& input_states) {
    return is_cassete_valid(input_states) && are_tables_valid(input_states);
}