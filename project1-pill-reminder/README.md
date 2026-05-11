# Project 1: Smart Pill Reminder Box 💊

## Project Overview
A smart medicine reminder system for elderly care or medication management. Built entirely in simulation on Wokwi.

## Features
-  Set custom alarm times via Serial Monitor commands
-  Green LED + Buzzer when it's time to take medicine
-  Yellow LED warns when alarm is approaching (30/15/5 min intervals)
-  Red LED + escalated beeping if dose is missed (5+ min)
-  Acknowledge button to confirm medicine taken
-  Auto-rearms for next dose (12 hours later)
-  Status command to check current alarm

## Commands
| Command | Action |
|---------|--------|
| `SET 14:30` | Set alarm for 2:30 PM |
| `STATUS` | Show current alarm time |
| `CANCEL` | Cancel active alarm |
| `HELP` | Show menu |

## Circuit Components
| Component | ESP32 Pin |
|-----------|-----------|
| Green LED | GPIO13 |
| Yellow LED | GPIO12 |
| Red LED | GPIO14 |
| Acknowledge Button | GPIO27 |
| Buzzer | GPIO26 |

## How It Works
1. User sets alarm using `SET HH:MM` command
2. System shows time remaining until alarm
3. Yellow LED warns as time approaches:
   - 30+ minutes: No warning
   - 30-15 minutes: Solid yellow
   - 15-5 minutes: Slow blink
   - 5-0 minutes: Fast blink
4. At alarm time: Green LED + Buzzer activates
5. User presses button to acknowledge
6. System confirms "Medicine taken" and sets next alarm in 12 hours
7. If no acknowledgment in 5 minutes: Warning message
8. If no acknowledgment in 8 minutes: Escalation (Red LED + faster beep)

## Technologies Used
- C++ (Arduino framework)
- ESP32 microcontroller (simulated)
- Wokwi online simulator
- GPIO programming
- State machine design
- Non-blocking timing with `millis()`

## Future Improvements
- Add LCD display to show time without Serial Monitor
- Multiple medication schedules (morning/afternoon/evening)
- Mobile app integration via Blynk
- Data logging of missed doses
- Snooze functionality (remind again in 10 minutes)

## Simulation Link
[Paste your Wokwi share link here]


## Author
Anushka Dubey- ECE Student

## Date
[11-05-2026]
