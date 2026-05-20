#ifndef KEY_FABRIC_H
#define KEY_FABRIC_H

#include <port/port.h>
#include <system/systemfunc.h>

#include "keyhandler.h"
#include "keyhandlerlistener.h"

class KeyFabric {
private:
    struct RolePin {
        eKeyRole key_role;
        Pin pin;
    };

    static constexpr uint8_t KEY_ROLE_COUNT =
        static_cast<uint8_t>(eKeyRole::KEY_ROLE_COUNT);
    static const RolePin role_pins[KEY_ROLE_COUNT];

    static uint8_t storage[KEY_ROLE_COUNT][sizeof(KeyHandler)];

    static void init_key_handler(IDispatcher& dispatcher,
                                 IKeyHandlerListener& key_handler_listener) {
        for(size_t i = 0; i < KEY_ROLE_COUNT; ++i) {
            const auto& role_pin = role_pins[i];

            KeyHandler* key_handler = new(storage[i])
                KeyHandler(&dispatcher, role_pin.pin, role_pin.key_role,
                           &key_handler_listener);
        }
    }

public:
    static void init(IDispatcher& dispatcher, IKeyHandlerListener& listener) {
        init_key_handler(dispatcher, listener);
    }
};

#endif  // KEY_FABRIC_H
