#include "outputhandler.h"

OutputHandler::RolePin
    OutputHandler::role_pins[OutputHandler::OUTPUT_ROLE_COUNT] = {
        {eOutputRole::TABLE_BACK, Pin{ePORT::ePORTA, 5, false}},
        {eOutputRole::TABLE_FORWARD, Pin{ePORT::ePORTA, 6, false}},
        {eOutputRole::TABLE_INDICATION, Pin{ePORT::ePORTA, 7, false}},
        {eOutputRole::TABLE_CHANGING_INDICATION, Pin{ePORT::ePORTC, 7, false}},
        {eOutputRole::TRANSPORTER_STOP, Pin{ePORT::ePORTC, 6, false}},
        {eOutputRole::TRANSPORTER_INDICATION, Pin{ePORT::ePORTC, 5, false}},
        {eOutputRole::INDICATION_READY, Pin{ePORT::ePORTC, 4, false}},
        {eOutputRole::CASSETTE_DOWN_STAIRS, Pin{ePORT::ePORTB, 3, false}},
        {eOutputRole::CASSETTE_UP_STAIRS, Pin{ePORT::ePORTB, 2, false}},
        {eOutputRole::OIL_PUMP, Pin{ePORT::ePORTB, 1, false}},
        {eOutputRole::ROLLER_DOWN_STAIRS, Pin{ePORT::ePORTB, 0, false}},
        {eOutputRole::ROLLER_UP_STAIRS, Pin{ePORT::ePORTE, 6, false}},
};

void OutputHandler::set_table_forward(bool on) {
    set_role_state(eOutputRole::TABLE_FORWARD, on);
}
void OutputHandler::set_table_back(bool on) {
    set_role_state(eOutputRole::TABLE_BACK, on);
}
void OutputHandler::set_table_indication(bool on) {
    set_role_state(eOutputRole::TABLE_INDICATION, on);
}
void OutputHandler::set_table_changing_indication(bool on) {
    set_role_state(eOutputRole::TABLE_CHANGING_INDICATION, on);
}

void OutputHandler::set_transporter_stop(bool on) {
    set_role_state(eOutputRole::TRANSPORTER_STOP, on);
}

void OutputHandler::set_transporter_indication(bool on) {
    set_role_state(eOutputRole::TRANSPORTER_INDICATION, on);
}

void OutputHandler::set_indication_ready(bool on) {
    set_role_state(eOutputRole::INDICATION_READY, on);
}

void OutputHandler::set_cassette_down_stairs(bool on) {
    set_role_state(eOutputRole::CASSETTE_DOWN_STAIRS, on);
}

void OutputHandler::set_cassette_up_stairs(bool on) {
    set_role_state(eOutputRole::CASSETTE_UP_STAIRS, on);
}

void OutputHandler::set_oil_pump(bool on) {
    set_role_state(eOutputRole::OIL_PUMP, on);
}

void OutputHandler::set_roller_down_stairs(bool on) {
    set_role_state(eOutputRole::ROLLER_DOWN_STAIRS, on);
}

void OutputHandler::set_roller_up_stairs(bool on) {
    set_role_state(eOutputRole::ROLLER_UP_STAIRS, on);
}

void OutputHandler::clear_all() {
    for(uint8_t i = 0; i < OUTPUT_ROLE_COUNT; ++i) {
        role_pins[i].pin.reset();
    }
}

void OutputHandler::set_role_state(eOutputRole role, bool on) {
    const auto role_index = static_cast<uint8_t>(role);
    if(on) {
        role_pins[role_index].pin.set();
    }
    else {
        role_pins[role_index].pin.reset();
    }
}