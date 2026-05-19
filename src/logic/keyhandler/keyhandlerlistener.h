#ifndef KEY_HANDLER_LISTENER_H
#define KEY_HANDLER_LISTENER_H

enum class eKeyState {
    PRESSED,
    LONG_PRESSED,
    UNPRESSED,
    LONG_UNPRESSED,
    CONTINUOUS_PRESSED
};

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

class IKeyHandlerListener {
public:
    virtual ~IKeyHandlerListener() = default;
    virtual void on_key_pressed(eKeyRole, eKeyState) = 0;
};

#endif  // KEY_HANDLER_LISTENER_H