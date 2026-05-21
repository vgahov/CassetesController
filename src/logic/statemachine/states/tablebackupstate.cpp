#include "tablebackupstate.h"

void TableBackUpState::on_cassete_up(bool state) {
    transition_to_error_state();
}
void TableBackUpState::on_cassete_down(bool state) {
    transition_to_error_state();
}
void TableBackUpState::on_table_front(bool state) {
    transition_to_error_state();
}
void TableBackUpState::on_table_back_up(bool state) {
    transition_to_waiting_state();
}
void TableBackUpState::on_table_back_down(bool state) {
    transition_to_error_state();
}
void TableBackUpState::stop(bool state) { transition_to_waiting_state(); }