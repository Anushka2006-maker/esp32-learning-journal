# Day 10: Hardware Timers

## What I Learned

### New Concepts
- **Hardware Timers** – Built-in counters independent of main code
- **Timer Interrupts** – Trigger functions at exact intervals
- **Prescaler** – Divides clock speed for timing
- **Non-blocking timing** – No delays, no freezing

### Key Insight
Timers allow precise scheduling WITHOUT blocking code. Multiple timers can run independently!
###Simulation Link
https://wokwi.com/projects/464371725907108865


## Timer Configuration
```cpp
timer = timerBegin(0, 80, true);      // Timer 0, prescaler 80
timerAttachInterrupt(timer, &callback, true);
timerAlarmWrite(timer, 1000000, true);  // 1 second
timerAlarmEnable(timer);
