#include "keysfabric.h"

const KeyFabric::RolePin KeyFabric::role_pins[KeyFabric::KEY_ROLE_COUNT] = {
    {eKeyRole::uSTOP, Pin{ePORT::ePORTC, 2, true}},
    {eKeyRole::TransporterOn, Pin{ePORT::ePORTC, 1, true}},
    {eKeyRole::RollerDownStairs, Pin{ePORT::ePORTC, 0, true}},
    {eKeyRole::uTableChanging, Pin{ePORT::ePORTE, 3, true}},
    {eKeyRole::uTableBack, Pin{ePORT::ePORTE, 2, true}},
    {eKeyRole::uTableForward, Pin{ePORT::ePORTD, 7, true}},
    {eKeyRole::sCassetteDownStairs, Pin{ePORT::ePORTD, 6, true}},
    {eKeyRole::sCassetteUpStairs, Pin{ePORT::ePORTD, 5, true}},
    {eKeyRole::sTableBackDown, Pin{ePORT::ePORTD, 4, true}},
    {eKeyRole::sTableBackUp, Pin{ePORT::ePORTD, 3, true}},
    {eKeyRole::sTableFront, Pin{ePORT::ePORTD, 2, true}},
    {eKeyRole::RollerUpStairs, Pin{ePORT::ePORTD, 1, true}},
    {eKeyRole::Roller, Pin{ePORT::ePORTD, 0, true}},
};

uint8_t KeyFabric::storage[KeyFabric::KEY_ROLE_COUNT][sizeof(KeyHandler)];
// uint8_t KeyFabric::s_key_fabric_object[sizeof(KeyFabric)];