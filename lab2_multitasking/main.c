/********************************************

*

*  Name:ANTONETTE DUMABOC

*  Section: A3

*  Assignment: lab 2: Cooperative Multitasking

*

********************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "gpio.h"

#define STATUS_LED_PORT GPIO_PORT_D
#define STATUS_LED_PIN 5
#define USER_BUTTON_PORT GPIO_PORT_D
#define USER_BUTTON_PIN 2

// 'volatile' is critical. It tells the compiler that this variable can change
// at any time (by the ISR), so it must always be read from memory.
volatile uint32_t system_ticks = 0;

// This is the Interrupt Service Routine for Timer1 Compare Match A.
// This function is automatically called by the hardware every 1ms.
ISR(TIMER1_COMPA_vect)
{
    system_ticks++;
}

void system_tick_init(void)
{
    // TODO: Configure Timer1 in CTC mode (WGM12 bit).
    TCCR1B |= (1 << WGM12);
    // TODO: Set the compare value in OCR1A to 249.
    OCR1A = 249;
    // TODO: Set the prescaler to 64 (CS11 and CS10 bits).
    TCCR1B |= (1 << CS11) | (1 << CS10);
    // TODO: Enable the Timer1 Compare A interrupt (OCIE1A bit).
    TIMSK1 |= (1 << OCIE1A);

    sei(); // Enable global interrupts. This must be called for any interrupt to work.
}

void task_blink_status_led(void)
{
    static uint32_t last_toggle_time = 0;
    if ((system_ticks - last_toggle_time) >= 500)
    { // 500ms interval
        // TODO: Toggle the LED using your gpio_write/gpio_read functions.
        GpioValue_t current_state = gpio_read(STATUS_LED_PORT, STATUS_LED_PIN);
        GpioValue_t new_state = (current_state == GPIO_PIN_HIGH) ? GPIO_PIN_LOW : GPIO_PIN_HIGH;
        gpio_write(STATUS_LED_PORT, STATUS_LED_PIN, new_state);
        last_toggle_time = system_ticks;
    }
}
void task_poll_button(void)
{
    static uint8_t last_button_state = GPIO_PIN_HIGH;
    uint8_t current_button_state = gpio_read(USER_BUTTON_PORT, USER_BUTTON_PIN);

    if (current_button_state == GPIO_PIN_LOW && last_button_state == GPIO_PIN_HIGH)
    {
        // Button was just pressed (falling edge). For now, we do nothing.
        // In a real app, you might set a flag here.
    }
    last_button_state = current_button_state;
}

int main(void)
{
    // --- INITIALIZATION ---
    gpio_set_direction(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_OUTPUT);
    gpio_set_direction(USER_BUTTON_PORT, USER_BUTTON_PIN, GPIO_PIN_INPUT);
    gpio_set_pullup(USER_BUTTON_PORT, USER_BUTTON_PIN, 1);

    system_tick_init();

    // --- SUPERLOOP ---
    while (1)
    {
        task_blink_status_led();
        task_poll_button();
    }
    return 0;
}