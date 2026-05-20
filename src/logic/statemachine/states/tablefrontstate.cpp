#include "tablefrontstate.h"

void TableFrontState::on_cassete_up() { transition_to_error_state(); }
void TableFrontState::on_cassete_down() { transition_to_error_state(); }
void TableFrontState::on_table_front() { transition_to_waiting_state(); }
void TableFrontState::on_table_back_up() { transition_to_error_state(); }
void TableFrontState::on_table_back_down() { transition_to_error_state(); }
void TableFrontState::stop_pressed() { transition_to_waiting_state(); }