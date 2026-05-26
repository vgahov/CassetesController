#ifndef OUTPUTHANDLER_H
#define OUTPUTHANDLER_H

#include <logic/keyhandler/keyhandler.h>

enum class eOutputRole {
    TABLE_BACK,
    TABLE_FORWARD,
    TABLE_INDICATION,
    TABLE_CHANGING_INDICATION,
    TRANSPORTER_STOP,
    TRANSPORTER_INDICATION,
    INDICATION_READY,
    CASSETTE_DOWN_STAIRS,
    CASSETTE_UP_STAIRS,
    OIL_PUMP,
    ROLLER_DOWN_STAIRS,
    ROLLER_UP_STAIRS,
    CONTROL_LED,
    KEY_ROLE_COUNT
};

class OutputHandler final {
private:
    struct RolePin {
        eOutputRole key_role;
        Pin pin;
    };

    static constexpr uint8_t OUTPUT_ROLE_COUNT =
        static_cast<uint8_t>(eOutputRole::KEY_ROLE_COUNT);
    static RolePin role_pins[OUTPUT_ROLE_COUNT];

public:
    static OutputHandler& get_instance() {
        static OutputHandler instance;
        return instance;
    }

    void set_role_state(eOutputRole role, bool on);

    void set_table_forward(bool on = true);
    void set_table_back(bool on = true);
    void set_table_indication(bool on = true);
    void set_table_changing_indication(bool on = true);
    void set_transporter_stop(bool on = true);
    void set_transporter_indication(bool on = true);
    void set_indication_ready(bool on = true);
    void set_cassette_down_stairs(bool on = true);
    void set_cassette_up_stairs(bool on = true);
    void set_oil_pump(bool on = true);
    void set_roller_down_stairs(bool on = true);
    void set_roller_up_stairs(bool on = true);
    void set_control_led(bool on = true);
    void clear_all();
};
#endif  // OUTPUTHANDLER_H