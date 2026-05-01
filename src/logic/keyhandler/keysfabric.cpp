#include "keysfabric.h"

const RolePin KeyFabric::role_pins[KeyFabric::KEY_ROLE_COUNT] = {
    {eKeyRole::STOP, Pin{ePORT::ePORTC, 2, true}},
    {eKeyRole::TransportOn, Pin{ePORT::ePORTC, 1, true}},
    {eKeyRole::RollerDownStairs, Pin{ePORT::ePORTC, 0, true}},
    {eKeyRole::TableChanging, Pin{ePORT::ePORTE, 3, true}},
    {eKeyRole::TableBack, Pin{ePORT::ePORTE, 2, true}},
    {eKeyRole::TableForward, Pin{ePORT::ePORTD, 7, true}},
    {eKeyRole::CassetteDownStairs, Pin{ePORT::ePORTD, 6, true}},
    {eKeyRole::CassetteUpStairs, Pin{ePORT::ePORTD, 5, true}},
    {eKeyRole::TableBackDown, Pin{ePORT::ePORTD, 4, true}},
    {eKeyRole::TableBackUp, Pin{ePORT::ePORTD, 3, true}},
    {eKeyRole::TableFront, Pin{ePORT::ePORTD, 2, true}},
    {eKeyRole::RollerUpStairs, Pin{ePORT::ePORTD, 1, true}},
    {eKeyRole::Roller, Pin{ePORT::ePORTD, 0, true}},
};

uint8_t KeyFabric::storage[KeyFabric::KEY_ROLE_COUNT][sizeof(KeyHandler)];