#include "tablebackdownstate.h"

void TableBackDownState::on_cassete_up() { transition_to_error_state(); }
void TableBackDownState::on_cassete_down() { transition_to_error_state(); }
void TableBackDownState::on_table_front() { transition_to_error_state(); }
void TableBackDownState::on_table_back_up() { transition_to_error_state(); }
void TableBackDownState::on_table_back_down() { transition_to_waiting_state(); }
void TableBackDownState::stop_pressed() { transition_to_waiting_state(); }