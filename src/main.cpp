#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <dispatcher/dispatcher.h>
#include <dispatcher/dispatcherlistener.h>
#include <logic/keyhandler/keysfabric.h>
#include <logic/statemachine/statemachine.h>
#include <util/delay.h>

static constexpr uint32_t TIMER_PERIOD_USEC = 1000;

int main(void) {
    wdt_disable();
    MCUCR |= (1 << JTD);
    MCUCR |= (1 << JTD);

    Dispatcher dispatcher;
    Timer0::init(TIMER_PERIOD_USEC);
    Timer0::get_instance().set_interrupt_callback(&dispatcher);

    auto& output_handler = OutputHandler::get_instance();
    StateMachine state_machine(output_handler);
    // KeyFabric::init(dispatcher, state_machine);
    dispatcher.add_listener(&state_machine, 10, ePeriodUnit::mSec);
    // dispatcher.set_timer_period(TIMER_PERIOD_USEC);

    sei();

    dispatcher.loop();
}
