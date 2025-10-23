/********************************************

*

*  Name:ANTONETTE DUMABOC

*  Section: A3

*  Assignment: lab 3: Reactivity with Interrupts

*

********************************************/

#define F_CPU 16000000UL 
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include "gpio.h" 


// ... (Includes, system_ticks, Timer1 ISR, INT0 ISR from previous sections) ...


volatile uint32_t system_ticks = 0;

// Timer 1 Compare Match A ISR to increment the tick counter
ISR(TIMER1_COMPA_vect) {
    system_ticks++; 
}

// Function to initialize Timer 1 for a 1ms tick 
void system_tick_init(void) { 
    // Set up Timer 1 for CTC 
    TCCR1B |= (1 << WGM12); 
    
    // Set Compare Value (OCR1A)
    OCR1A = 249; 
    
    // Enable Timer 1 Output Compare Match A Interrupt
    TIMSK1 |= (1 << OCIE1A); 
    
    // Start Timer 1 with Prescaler of 64
    TCCR1B |= (1 << CS11) | (1 << CS10); 
}

// --- Global Volatile Flag ---
// This flag is our communication channel between the ISR and main loop.
volatile uint8_t g_button_pressed_flag = 0;

// --- NEW: ISR for External Interrupt 0 (INT0) ---
ISR(INT0_vect) {
    // Set the flag. That's it. Keep it fast!
    g_button_pressed_flag = 1;
}

// --- NEW: Initialization for External Interrupt 0 ---
void external_interrupt_init(void) {
    // Use our GPIO driver to configure the button pin.
    gpio_set_direction(GPIO_PORT_D, 2, GPIO_PIN_INPUT);
    gpio_set_pullup(GPIO_PORT_D, 2, 1);

    // TODO: Configure EICRA to trigger INT0 on a falling edge.
    // HINT: You need to set ISC01 and clear ISC00.
    EICRA |= (1 << ISC01);  
    EICRA &= ~(1 << ISC00); 
    
    // TODO: Enable the external interrupt for INT0 in the EIMSK register.
     EIMSK |= (1 << INT0);
}


#define STATUS_LED_PORT GPIO_PORT_D
#define STATUS_LED_PIN 5
#define USER_BUTTON_PORT GPIO_PORT_D
#define USER_BUTTON_PIN 2

volatile uint8_t g_led_is_blinking = 1;

void task_process_button_press(void) {
    static uint32_t last_debounce_time = 0;
    const uint16_t DEBOUNCE_DELAY_MS = 50;
    
    // Check if the ISR has set our flag AND we are outside the debounce window
    if (g_button_pressed_flag && (system_ticks - last_debounce_time) > DEBOUNCE_DELAY_MS) {
        g_led_is_blinking = !g_led_is_blinking; // Toggle the application state
        g_button_pressed_flag = 0; // Clear the flag now that we've handled it
        last_debounce_time = system_ticks; // Start the debounce timer
    }
}

void task_blink_led(void) {
    static uint32_t last_toggle_time = 0;
    if (!g_led_is_blinking) {
        gpio_write(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_LOW);
        return;
    }
    if ((system_ticks - last_toggle_time) >= 500) {
        // TODO: Toggle the LED using your GPIO driver
         if (gpio_read(STATUS_LED_PORT, STATUS_LED_PIN) == GPIO_PIN_HIGH) {
            gpio_write(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_LOW);
        } else {
            gpio_write(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_HIGH);
        }
        last_toggle_time = system_ticks;
    }
}

int main(void) {
    // --- INITIALIZATION ---
    gpio_set_direction(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_OUTPUT);
    external_interrupt_init(); // Sets up button pin as well
    system_tick_init();
    
    sei(); // Enable global interrupts

    // --- SUPERLOOP ---
    while (1) {
        task_process_button_press(); // Check for and handle events
        task_blink_led(); // Update state based on events
    }
    return 0;
}
