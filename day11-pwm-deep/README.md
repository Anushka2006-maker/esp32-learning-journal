# Day 11: PWM Deep Dive

## What I Learned Today

### What is PWM?
PWM (Pulse Width Modulation) is a technique to simulate analog output using digital signals. Instead of varying voltage, it varies **how long the signal is ON vs OFF**.

### Key Concepts

| Concept | Meaning | Example |
|---------|---------|---------|
| **Frequency** | How many cycles per second | 5000 Hz = 5000 ON/OFF cycles per second |
| **Duty Cycle** | Percentage of time signal is HIGH | 50% = ON half the time, OFF half the time |
| **Resolution** | Number of brightness steps | 8-bit = 256 steps (0 to 255) |


### How Duty Cycle Affects Brightness

| Duty Cycle | LED Looks Like |
|------------|----------------|
| 0% | OFF |
| 25% | Very Dim |
| 50% | Medium Bright |
| 75% | Bright |
| 100% | Maximum Bright |

### LEDC Functions (ESP32)

```cpp
// Setup PWM channel
ledcSetup(channel, frequency, resolution);

// Attach GPIO pin to channel
ledcAttachPin(pin, channel);

// Set brightness (0 to max based on resolution)
ledcWrite(channel, dutyCycle);
