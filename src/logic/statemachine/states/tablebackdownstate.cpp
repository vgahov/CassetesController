#include "tablebackdownstate.h"

void TableBackDownState::on_cassete_up(bool state) {
    transition_to_error_state();
}
void TableBackDownState::on_cassete_down(bool state) {
    transition_to_error_state();
}
void TableBackDownState::on_table_front(bool state) {
    transition_to_error_state();
}
void TableBackDownState::on_table_back_up(bool state) {
    transition_to_error_state();
}
void TableBackDownState::on_table_back_down(bool state) {
    transition_to_waiting_state();
}
void TableBackDownState::stop(bool state) { transition_to_waiting_state(); }