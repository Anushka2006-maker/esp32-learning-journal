# Day 9: Interrupts – Instant Reaction

## What I Learned

### New Concepts
- **Interrupts** – Pause main code for urgent tasks
- **ISR (Interrupt Service Routine)** – Function that runs on interrupt
- **volatile keyword** – Prevents compiler optimization
- **Edge triggering** – FALLING, RISING, CHANGE

### Key Insight
Interrupts allow ESP32 to react INSTANTLY, even while sleeping or doing other tasks.

## My Experiments
- [ ] Single button interrupt
- [ ] Button counter (no missed presses)
- [ ] Two buttons with different functions
- [ ] Panic button with buzzer
- [ ] Speed control via interrupt

## Important Rules
1. Keep ISR very short (just set flags)
2. Use `volatile` for shared variables
3. No `delay()` in ISR
4. No `Serial.print()` in ISR

## Simulation Link
[https://wokwi.com/projects/464094412286777345]

## Real-World Applications
- Emergency stop buttons
- Encoder reading (volume knobs)
- Motion detection triggers
- Fire alarm systems
