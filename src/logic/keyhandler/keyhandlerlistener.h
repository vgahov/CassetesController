#ifndef KEY_HANDLER_LISTENER_H
#define KEY_HANDLER_LISTENER_H

enum class eKeyState {
    PRESSED,
    LONG_PRESSED,
    LONG_UNPRESSED,
    CONTINUOUS_PRESSED
};

enum class eKeyRole {
    STOP,
    TransportOn,
    RollerDownStairs,
    TableChanging,
    TableBack,
    TableForward,
    CassetteDownStairs,
    CassetteUpStairs,
    TableBackDown,
    TableBackUp,
    TableFront,  //???
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