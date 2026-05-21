#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <dispatcher/dispatcher.h>
#include <dispatcher/dispatcherlistener.h>
#include <logic/keyhandler/keysfabric.h>
#include <logic/statemachine/statemachine.h>
#include <util/delay.h>

static constexpr uint32_t TIMER_PERIOD_USEC = 5000;

Pin m_led_pin{ePORT::ePORTB, 4, false};
// extern Pin m_led_pin;

int main(void) {
    wdt_disable();
    MCUCR |= (1 << JTD);
    MCUCR |= (1 << JTD);

    Dispatcher dispatcher;
    Timer0::init(TIMER_PERIOD_USEC);
    Timer0::get_instance().set_interrupt_callback(&dispatcher);

    auto& output_handler = OutputHandler::get_instance();
    StateMachine state_machine(output_handler);
    KeyFabric::init(dispatcher, state_machine);
    dispatcher.add_listener(&state_machine, 10, ePeriodUnit::mSec);

    sei();

    dispatcher.loop();
}
