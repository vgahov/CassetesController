#ifndef PORT_H
#define PORT_H

#ifndef IAR_PROJECT
#include <stdint-gcc.h>
#endif

#include <dispatcher/dispatcherlistener.h>

enum class ePORT {
    ePORTA,
    ePORTB,
    ePORTC,
    ePORTD,
#if defined(__AVR_ATmega328PB__) || defined(__AVR_ATmega324PB__)
    ePORTE,
#endif
};

class Pin final {
public:
    Pin();
    Pin(ePORT port, int pin, bool input);
    ~Pin();
    Pin &operator=(const Pin &);

    void set_as_output();
    void set_as_input();
    int read();
    void set();
    void toggle();
    void reset();
    bool is_input() const;
    bool is_valid() const { return m_is_valid; }

private:
    constexpr static bool OUTPUT = true;
    constexpr static bool INPUT = false;

    enum class eOutputAction { CLEAR, SET, TOGGLE };
    static inline uint8_t set_binary_value(uint8_t initial_value, uint8_t pin,
                                           eOutputAction action);
    static inline uint8_t get_binary_value(uint8_t initial_value, uint8_t pin);
    static inline void set_direction(ePORT port, uint8_t pin, bool direction);

    static inline bool get_direction(ePORT port, uint8_t pin);
    static inline void set_output(ePORT port, uint8_t pin);
    static inline void clr_output(ePORT port, uint8_t pin);
    static inline void toggle_output(ePORT port, uint8_t pin);
    static inline bool read_pin(ePORT port, uint8_t pin);

private:
    ePORT m_port;
    int m_pin;
    bool m_is_valid = false;
    uint32_t *m_reference_counter = 0;
};

#endif  // PORT_H