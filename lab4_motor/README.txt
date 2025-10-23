1. Draw a truth table for the L298N's IN1 and IN2 pins and the resulting motor action 
(Forward, Backward, Coast, Brake).


            |     IN1     |      IN2      |
Forward     |      1      |       0       |
            |             |               |
Backward    |      0      |       1       |
            |             |               |
Coast       |      0      |       0       |
            |             |               |
Break       |      1      |       1       |

2. In `motor_init()`, we configured Timer0 for "non-inverting" Fast PWM mode. What is the 
difference between inverting and non-inverting mode? How would the motor's behavior change 
if you used inverting mode (`COM0A1` and `COM0A0` both set)?

- In non-inverting mode, when you set the speed to 0, it means 0% duty cycle (motor stopped), 
and when you set it to 255, it means 100% duty cycle (motor full speed). This means the speed 
setting directly matches the actual motor behavior. On the other hand, in inverting mode, the 
relationship is reversed, setting the speed to 0 results in 100% duty cycle (motor full speed),
while setting it to 255 results in 0% duty cycle (motor stopped). This reversed behavior is not
intuitive and could cause errors if forgotten. Therefore, if both COM0A1 and COM0A0 are set
(inverting mode), instead of the motor starting slowly when set to 0, it would run at full speed.

3. With a 16MHz clock and a prescaler of 64, what is the frequency of the PWM signal generated 
by Timer0? Is this frequency audible to humans? Why is it generally better to use a frequency 
above the range of human hearing?

-Timer0 generates a 976.56 Hz PWM signal, which is audible to human hearing as observed in the 
laboratory. When trying different prescaler values, either lower(8 or 1) or higher than 64, the 
noise becomes inaudible. Therefore, to eliminate the audible beeping noise, using prescaler values 
that produce frequencies outside the human hearing range is better.