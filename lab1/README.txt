----Review Questions-----
1. Suppose we relocated the three buttons from group B, bits 5-3 to group D, bits 5-3, 
noting that the LED is still attached to group D, bit 2. Assuming appropriate DDRD 
values, consider the following method of turning on the LED.

 PORTD = 0x04; // turn on the LED

Explain the problem with this approach and, in particular, what would stop working after executing 
that line of code.

ANS: If we relocate the three buttons, bits 5–3, to group D, and execute PORTD = 0x04 to turn on the LED,
    this will set PORTD to b00000100, setting PORTD2 = 1, which is mainly the LED alone. In that case,
    0x04 will overwrite the entire PORTD, and the relocated buttons on PORTD5–3 are set to 0. Now, the buttons will
    stop working because their pull-ups are turned off, leaving them floating, while the LED will stay in its 
    HIGH state.

----LAB REPORT QUESTIONS-----

1. Explain the purpose of the bitwise OR (`|=`) and bitwise AND with inversion (`&= ~`) 
for setting and clearing bits in a register. Why is this safer than writing a full value 
(e.g., `DDRD = 0b01000000;`)?

ANS: Using the bitwise operation is safer than writing a full value such as 0b01000000 because through this, we can
    specifically modify only the bit the we want to change without affecting the other bits. On the other hand, writing
    the full value can change or affect all the 8 bits.

2. Why is the button's logic "active low" (i.e., we check if the pin is `LOW` to detect a press)? 
What is the role of the internal pull-up resistor in this configuration?

ANS: The button’s logic is active low because the buttons are classified as momentary action, single-pole, normally open sbuttons. 
    When it is not pressed, the contacts are open, meaning the two terminals of the switch are not connected. The internal pull-up 
    resistor keeps its input pin HIGH. On the contrary, when the button is pressed, the contacts close, connecting the pin directly 
    to ground, which pulls the input LOW. Additionally, the role of the internal pull-up resistor is to prevent the input pin from 
    floating when the button is not pressed.


3. What is the major limitation of using `_delay_ms()` for timing in a more complex application 
where the robot needs to perform multiple tasks at once?

ANS: The major limitation of using _delay_ms() is that it blocks the CPU from doing other tasks during the delay period. 
    In that case, the program must wait before executing the next task, which does not allow multitasking.