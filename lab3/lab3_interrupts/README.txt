1. Explain the complete sequence of events, from the physical button press to the LED changing state, 
mentioning the roles of the hardware (INT0), the ISR, the volatile flag, and the main loop tasks.
-    When the button connected to pin D2 is pressed, it triggers INT0, an external interrupt configured to 
respond to a falling edge (the button is pushed down). This causes the ISR to quickly set the 
g_button_pressed_flag, which is declared volatile to ensure the main loop detects changes made by the ISR. 
Timer1 is configured in CTC (Clear Timer on Compare Match) mode to generate a 1ms interrupt, incrementing the
system_ticks counter. In the main loop, task_process_button_press() checks the flag and applies debounce 
logic—ignoring presses that occur too close together to avoid false triggers. If valid, it toggles the LED 
blinking state and clears the flag to allow future presses. The task_blink_led() function uses system_ticks to
toggle the LED every 500ms when blinking is enabled. The sei() function enables global interrupts, allowing 
both INT0 and Timer1 ISRs to run; without it, interrupts would remain disabled.


2. Why is the debounce logic handled in the main loop task (`task_process_button_press`) instead of directly
inside the ISR with a `_delay_ms()`? Refer to the "Golden Rule of ISRs.
 - the debounce logic handled in the main loop task (`task_process_button_press`) instead of directly
inside the ISR because following the Golden Rule of ISRs,it is a must to keep ISRs short and fast. If it is 
impplemented inside an ISR, it would block other interrupts like Timer1, not following its time efficient goal.
Thus, simply setting a volatile flag in the ISR and handling debounce in the main loop is much effective.


3. The `EICRA` register can be configured to trigger on "any logical change." What is a potential disadvantage 
of this mode for a simple push-button compared to "falling edge"?
 - Configuring the EICRA register to "any logical change" mode allows interrupts to trigger on both rising and 
 falling edges, which can be useful for detecting any state transition. However, with since we are using push-buttons, 
 this mode often results in multiple interrupts due to bouncing during both press and release. On the other hand, 
 if we use "falling edge" mode, this will trigger only once when the signal transitions from high to low, meaning the
 button was really pressed.