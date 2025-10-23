1. What is the role of the `volatile` keyword, and what might happen if you 
removed it from the `system_ticks` declaration?
- The volatile keyword tells the compiler that a variable’s value can change at any time.
In this case, system_ticks is updated by an interrupt every 1ms. If volatile is removed, 
the compiler might assume the value doesn’t change and reuse an old copy, causing the program
to miss updates. As a result, the LED may not blink correctly because the timing data won’t 
reflect real-time changes.

2. Why is a `static` variable used for `last_toggle_time` inside `task_blink_status_led()`?
 What would happen if it were a regular local variable?
 - In this case, we used static so that the value of last_toggle_time is remembered between function calls,
even though the function runs in a loop. If we use a regular local variable instead, it would reset to zero 
every time the function runs, causing the LED to blink rapidly instead of every 500ms as intended.

3. This framework is "cooperative." What does that mean for how you must write your task functions? What is 
the main risk of this approach if one task takes too long to execute?
 - In a cooperative framework, task functions must be specifically designed to execute quickly without blocking. 
This means they should avoid long delays or waiting times and return control immediately. The main risk of this 
approach is that if one task takes too long to run, it can delay or block other tasks from executing at their
intended time. Since tasks share the CPU and there are no interrupts to enforce timing, a slow task can negatively 
affect the performance of the entire system
