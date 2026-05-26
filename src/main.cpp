#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <dispatcher/dispatcher.h>
#include <dispatcher/dispatcherlistener.h>
#include <logic/keyhandler/keysfabric.h>
#include <logic/statemachine/statemachine.h>
#include <util/delay.h>

static constexpr uint32_t TIMER_PERIOD_USEC = 5000;

void watchdog_handler() {
    uint8_t reset_reason = MCUSR;

    MCUSR = 0;
    wdt_disable();
    DDRB |= (1 << PB4);
    if(reset_reason & (1 << WDRF)) {
        Pin ready_pin = Pin{ePORT::ePORTC, 4, false};
        ready_pin.reset();
        Pin controller_pin = {ePORT::ePORTB, 4, false};
        while(1) {
            controller_pin.toggle();
            _delay_ms(100);
        }
    }
}

int main(void) {
    MCUCR |= (1 << JTD);
    MCUCR |= (1 << JTD);
    /*{
        auto& output_handler = OutputHandler::get_instance();
        StateMachine state_machine(output_handler);
        state_machine.set_dispatcher_period(TIMER_PERIOD_USEC);
        state_machine.change_state(ESTATE::Wait);
        state_machine.on_key_pressed(eKeyRole::KEY_ROLE_COUNT,
                                     eKeyState::PRESSED);
        state_machine.on_key_pressed(eKeyRole::uTableChanging,
                                     eKeyState::PRESSED);

        state_machine.on_key_pressed(eKeyRole::sTableBackUp,
                                     eKeyState::PRESSED);
    }*/

    watchdog_handler();

    auto& output_handler = OutputHandler::get_instance();
    output_handler.set_control_led(true);
    _delay_ms(1000);
    output_handler.set_control_led(false);
    _delay_ms(1000);
    output_handler.set_control_led(true);
    _delay_ms(1000);
    output_handler.set_control_led(false);
    _delay_ms(1000);
    output_handler.set_control_led(true);

    wdt_enable(WDTO_250MS);

    Dispatcher dispatcher;
    Timer0::init(TIMER_PERIOD_USEC);
    Timer0::get_instance().set_interrupt_callback(&dispatcher);

    StateMachine state_machine(output_handler);
    KeyFabric::init(dispatcher, state_machine);
    dispatcher.add_listener(&state_machine, 10, ePeriodUnit::mSec);
    sei();
    dispatcher.loop();
}
