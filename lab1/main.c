/********************************************

*

*  Name:ANTONETTE DUMABOC

*  Section: A3

*  Assignment: Activity 1.1: Morse Code Blinker

*

********************************************/
// main.c - Refactored with GPIO Driver
#define F_CPU 16000000UL
#include <util/delay.h>
#include "gpio.h"

// --- Pin Definitions for Clarity ---
#define LED_PORT GPIO_PORT_D
#define LED_PIN 2

#define M_BUTTON_PORT GPIO_PORT_B
#define M_BUTTON_PIN 3
// TODO: Define ports and pins for the 'S' and 'U' buttons
#define S_BUTTON_PORT GPIO_PORT_B
#define S_BUTTON_PIN 4
#define U_BUTTON_PORT GPIO_PORT_B
#define U_BUTTON_PIN 5

#define DOT_LENGTH_MS 250

// In the dot function, it allows the LED to turn ON with a delay of 250ms
void dot()
{
    gpio_write(LED_PORT, LED_PIN, GPIO_PIN_HIGH);
    _delay_ms(DOT_LENGTH_MS);
    gpio_write(LED_PORT, LED_PIN, GPIO_PIN_LOW);
    _delay_ms(DOT_LENGTH_MS);
}

// TODO: Rewrite the dash() function to use gpio_write()
// In the dash function, it allows the LED to turn ON with a delay 3 times the dot function
void dash()
{
    gpio_write(LED_PORT, LED_PIN, GPIO_PIN_HIGH);
    _delay_ms(DOT_LENGTH_MS * 3);
    gpio_write(LED_PORT, LED_PIN, GPIO_PIN_LOW);
    _delay_ms(DOT_LENGTH_MS);
}
int main(void)
{
    // --- PIN CONFIGURATION using the driver ---
    // In this section we were able to set the LED PIN as an OUTPUT,
    // also configuring buttons M, S, U, (PORTB PIN 3-5) as an INPUT,
    // as well as enabling the puul-ups to avoid floating
    gpio_set_direction(LED_PORT, LED_PIN, GPIO_PIN_OUTPUT); // Setting LED PIN in PORTD2 as an OUTPUT

    gpio_set_direction(M_BUTTON_PORT, M_BUTTON_PIN, GPIO_PIN_INPUT); // Setting M button, PORTB 3 as an INPUT
    gpio_set_pullup(M_BUTTON_PORT, M_BUTTON_PIN, 1);                 // Enabling the pull-up
    // TODO: Configure the 'S' and 'U' buttons
    gpio_set_direction(S_BUTTON_PORT, S_BUTTON_PIN, GPIO_PIN_INPUT); // Setting S button, PORTB 3 as an INPUT
    gpio_set_pullup(S_BUTTON_PORT, S_BUTTON_PIN, 1);                 // Enabling the pull-up

    gpio_set_direction(U_BUTTON_PORT, U_BUTTON_PIN, GPIO_PIN_INPUT); // Setting U button, PORTB 3 as an INPUT
    gpio_set_pullup(U_BUTTON_PORT, U_BUTTON_PIN, 1);                 // Enabling the pull-up

    // --- MAIN LOOP using the driver ---

    // Since the buttons are active-low, with the pull-up, it eads LOW (0) when pressed. Using the gipo_read, it will
    // continuously check if any of the button is LOW and will call the corresponding morse code dash() or dot().
    while (1)
    {
        if (gpio_read(M_BUTTON_PORT, M_BUTTON_PIN) == GPIO_PIN_LOW)
        {
            // Call dash(), dash() for 'M'
            dash();
            dash();
            _delay_ms(DOT_LENGTH_MS * 3);
        }
        // TODO: Add checks for the 'S' and 'U' buttons using gpio_read()
        if (gpio_read(S_BUTTON_PORT, S_BUTTON_PIN) == GPIO_PIN_LOW)
        {
            dot();
            dot();
            dot();
            _delay_ms(DOT_LENGTH_MS * 3);
        }
        if (gpio_read(U_BUTTON_PORT, U_BUTTON_PIN) == GPIO_PIN_LOW)
        {
            dot();
            dot();
            dash();
            _delay_ms(DOT_LENGTH_MS * 3);
        }
    }
}
