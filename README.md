# ESP32 BLE Gamepad 🎮

A DIY Bluetooth gamepad built using ESP32,
8 push buttons and 2 PS2 joysticks.
Works as a standard HID gamepad on Windows PC!

## Components
- 1x ESP32
- 8x Push Buttons
- 2x PS2 Joystick Module
- 1x Breadboard
- Jumper Wires (Male to Male + Female to Male)

## Pin Configuration
| Component            | GPIO |
|---------------------|------|
| Button 1 (UP)       | 27   |
| Button 2 (DOWN)     | 5    |
| Button 3 (LEFT)     | 13   |
| Button 4 (RIGHT)    | 14   |
| Button 5 (△)        | 18   |
| Button 6 (○)        | 19   |
| Button 7 (□)        | 22   |
| Button 8 (✕)        | 23   |
| Joystick 1 VRX      | 34   |
| Joystick 1 VRY      | 35   |
| Joystick 1 SW       | 32   |
| Joystick 2 VRX      | 25   |
| Joystick 2 VRY      | 26   |
| Joystick 2 SW       | 33   |

## Joystick Roles
| Joystick | Role | Used For |
|----------|------|----------|
| Joystick 1 (Left)    | Left Thumbstick  | Character movement, Car steering |
| Joystick 2 (Right)   | Right Thumbstick | Camera control, Aiming |
| JOY1 SW (press down) | L3 button        | Special actions in games |
| JOY2 SW (press down) | R3 button        | Special actions in games |

## Button Mapping
| Button               | Function               |
|---------------------|------------------------|
| Button 1            | D-pad UP ↑             |
| Button 2            | D-pad DOWN ↓           |
| Button 3            | D-pad LEFT ←           |
| Button 4            | D-pad RIGHT →          |
| Button 5            | Triangle △             |
| Button 6            | Circle ○               |
| Button 7            | Square □               |
| Button 8            | Cross ✕                |
| JOY1 SW (press down)| L3 - Left stick click  |
| JOY2 SW (press down)| R3 - Right stick click |
| JOY1 (X/Y axis)     | Left Stick - Movement  |
| JOY2 (X/Y axis)     | Right Stick - Camera   |

## Software Requirements
- Arduino IDE
- ESP32 Core 2.0.17 by Espressif
- ESP32-BLE-Gamepad by lemmingDev
- NimBLE-Arduino by h2zero

## Features
- 8 face buttons
- D-pad support
- 2 analog joysticks
- Left stick for movement, Right stick for camera
- Left stick click (L3) and Right stick click (R3)
- 4 analog axes
- Deadzone on joysticks (prevents drift)
- Bluetooth BLE connection
- Works as standard HID gamepad
- Print only on change (no spam in Serial Monitor)

## Games Tested
- HexGL (Browser)
- Chrome Dino (Browser)
- Trackmania (Epic Games)
- Forza Horizon 5

## How It Works
ESP32 reads button and joystick inputs
and sends them to PC via Bluetooth BLE
as a standard HID gamepad. No drivers
needed — plug and play!

## Wiring Rules
- All buttons: one leg to GPIO, other leg to GND
- Joysticks VCC: 3.3V 
- Joysticks GND: GND
- No external resistors needed (uses internal pullup)

## Author
Vaibhav Pachori
