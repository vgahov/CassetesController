#ifndef ISTATE_MACHINE_H
#define ISTATE_MACHINE_H

#include <logic/outputhandler/outputhandler.h>
#include <stdint.h>
#include <stdlib.h>

enum class ESTATE {
    Empty,
    CasseteDown,
    CasseteUp,
    Detection,
    Error,
    TableBackDown,
    TableBackUp,
    TableChanging,
    TableFront,
    Wait,
};

/*
enum class eKeyRole {
    uSTOP,
    TransporterOn,
    RollerDownStairs,
    uTableChanging,
    uTableBack,
    uTableForward,
    sCassetteDownStairs,  // «кассета низ» (нижнее положение кассеты)
    sCassetteUpStairs,  // «кассета верх» (верхнее положение кассеты);
    sTableBackDown,  // «стол зад низ» (датчик припаркованного положения нижнего
                     // стола в кассете);
    sTableBackUp,  // «стол зад верх» (датчик припаркованного положения
                   // верхнего стола в кассете);
    sTableFront,  // «стол спереди» (датчик припаркованного положения стола к
                  // краю рабочей зоны);
    RollerUpStairs,
    Roller,
    KEY_ROLE_COUNT
};
*/

struct InputStates {
    union {
        struct {
            uint16_t uSTOP : 1;
            uint16_t TransporterOn : 1;
            uint16_t RollerDownStairs : 1;
            uint16_t uTableChanging : 1;
            uint16_t uTableBack : 1;
            uint16_t uTableForward : 1;
            uint16_t sCassetteDownStairs : 1;
            uint16_t sCassetteUpStairs : 1;
            uint16_t sTableBackDown : 1;
            uint16_t sTableBackUp : 1;
            uint16_t sTableFront : 1;
            uint16_t RollerUpStairs : 1;
            uint16_t Roller : 1;
        };
        uint16_t all;
    };

    InputStates() : all(0) {}
};

class IStateMachine {
public:
    virtual ~IStateMachine() = default;

    virtual void change_state(ESTATE state);
    virtual InputStates get_input_states() const;
    virtual void set_output_state(eOutputRole role, bool on);
    virtual void clear_output_states();
};

#endif  // ISTATE_MACHINE_H