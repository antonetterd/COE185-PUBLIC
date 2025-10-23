// motor.c - Implementation
#include "motor.h"
#include "gpio.h"
#include <avr/io.h>

// Define all the motor pin connections using #define
#define IN1 3  // PD3 
#define IN2  4  // PD4 
#define IN3  7  // PD7 
#define IN4  0  // PB0
void motor_init(void) {
    // TODO: Use gpio_set_direction to configure all motor pins as outputs.
    gpio_set_direction(GPIO_PORT_D, IN1, GPIO_PIN_OUTPUT);  // IN1 - PD3
    gpio_set_direction(GPIO_PORT_D, IN2, GPIO_PIN_OUTPUT);  // IN2 - PD4
    gpio_set_direction(GPIO_PORT_D, IN3, GPIO_PIN_OUTPUT);  // IN3 - PD7
    gpio_set_direction(GPIO_PORT_B, IN4, GPIO_PIN_OUTPUT);  // IN4 - PB0
    
     // Also set PWM pins as outputs
    gpio_set_direction(GPIO_PORT_D, 6, GPIO_PIN_OUTPUT);  // ENA - PD6 (OC0A)
    gpio_set_direction(GPIO_PORT_D, 5, GPIO_PIN_OUTPUT);  // ENB - PD5 (OC0B)

    // Configure Timer0 for Fast PWM mode
    // TODO: Set WGM01 and WGM00 for Fast PWM.
    TCCR0A |= (1 << WGM01) | (1 << WGM00);
    
    // TODO: Set COM0A1 and COM0B1 for non-inverting output on OC0A and OC0B
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
    
   // TODO: Set prescaler (e.g., 64) using CS01 and CS00 bits in TCCR0B.
    TCCR0B |= (1 << CS01) | (1 << CS00);

    // Set initial speed (duty cycle) to 0. OCR0A/B can be 0-255.
    OCR0A = 0; // Left motor speed
    OCR0B = 0; // Right motor speed
    
    // Start with motors stopped
    motor_stop();
}

void motor_set_speed(uint8_t speed) {
    OCR0A = speed;  
    OCR0B = speed; 
}

void motor_forward(void) {
   // TODO: Use gpio_write to set IN1=H, IN2=L, IN3=H, IN4=L
    gpio_write(GPIO_PORT_D, IN1, GPIO_PIN_HIGH);  // IN1 HIGH - Left forward
    gpio_write(GPIO_PORT_D, IN2, GPIO_PIN_LOW);   // IN2 LOW
    gpio_write(GPIO_PORT_D, IN3, GPIO_PIN_HIGH);  // IN3 HIGH - Right forward
    gpio_write(GPIO_PORT_B, IN4, GPIO_PIN_LOW);   // IN4 LOW
}
// TODO: Implement the rest of the functions (backward, left, right, stop).
void motor_backward(void) {
    // Set IN1=L, IN2=H, IN3=L, IN4=H
    gpio_write(GPIO_PORT_D, IN1, GPIO_PIN_LOW);   // IN1 LOW
    gpio_write(GPIO_PORT_D, IN2, GPIO_PIN_HIGH);  // IN2 HIGH - Left backward
    gpio_write(GPIO_PORT_D, IN3, GPIO_PIN_LOW);   // IN3 LOW
    gpio_write(GPIO_PORT_B, IN4, GPIO_PIN_HIGH);  // IN4 HIGH - Right backward
}

void motor_turn_left(void) {
    // Set IN1=L, IN2=H (left backward), IN3=H, IN4=L (right forward)
    gpio_write(GPIO_PORT_D, IN1, GPIO_PIN_LOW);   // IN1 LOW
    gpio_write(GPIO_PORT_D, IN2, GPIO_PIN_HIGH);  // IN2 HIGH - Left backward
    gpio_write(GPIO_PORT_D, IN3, GPIO_PIN_HIGH);  // IN3 HIGH - Right forward
    gpio_write(GPIO_PORT_B, IN4, GPIO_PIN_LOW);   // IN4 LOW
}

void motor_turn_right(void) {
    // Set IN1=H, IN2=L (left forward), IN3=L, IN4=H (right backward)
    gpio_write(GPIO_PORT_D, IN1, GPIO_PIN_HIGH);  // IN1 HIGH - Left forward
    gpio_write(GPIO_PORT_D, IN2, GPIO_PIN_LOW);   // IN2 LOW
    gpio_write(GPIO_PORT_D, IN3, GPIO_PIN_LOW);   // IN3 LOW
    gpio_write(GPIO_PORT_B, IN4, GPIO_PIN_HIGH);  // IN4 HIGH - Right backward
}

void motor_stop(void) {
    // Set all pins LOW to stop both motors
    gpio_write(GPIO_PORT_D, IN1, GPIO_PIN_LOW);  // IN1 LOW
    gpio_write(GPIO_PORT_D, IN2, GPIO_PIN_LOW);  // IN2 LOW
    gpio_write(GPIO_PORT_D, IN3, GPIO_PIN_LOW);  // IN3 LOW
    gpio_write(GPIO_PORT_B, IN4, GPIO_PIN_LOW);  // IN4 LOW
}