/********************************************

*

*  Name:ANTONETTE DUMABOC

*  Section: A3

*  Assignment: lab 4: Motor Control and PWM

*

********************************************/

#include <util/delay.h>
#include "motor.h"

int main(void) {
    uint8_t i;
    motor_init();
    motor_forward(); // Set direction once
    while(1) {
        // Ramp speed up
        for (i = 0; i < 255; i++) {
            motor_set_speed(i);
            _delay_ms(30);
        }
        // Ramp speed down
        for (i = 255; i > 0; i--) {
            motor_set_speed(i);
            _delay_ms(30);
        }
    }
}


