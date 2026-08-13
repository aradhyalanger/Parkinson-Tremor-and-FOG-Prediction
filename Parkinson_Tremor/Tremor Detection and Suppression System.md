# Tremor Detection and Suppression System

## Objective
To detect Parkinsonian hand tremor in real time using an inertial sensor and provide vibration feedback when tremor is detected.

## Hardware Used
- ESP32 DevKit V1
- MPU6050 / MPU6500 IMU
- SSD1306 OLED Display
- Vibration motor
- BC547 transistor
- Li-ion battery

## Software Used
- Arduino IDE
- MATLAB

## Methodology
1. Acquire gyroscope data at 100 Hz.
2. Apply moving average filtering.
3. Compute RMS over a 0.5 s window.
4. Compare RMS with threshold.
5. Activate vibration motor if tremor is detected.
6. Send Telegram alert.
7. Display status on OLED.

## MATLAB Analysis
- Band-pass filter (3-8 Hz)
- RMS computation
- FFT analysis
- Peak frequency estimation

## Result
The prototype successfully detected tremor-like motion and activated the motor and Telegram alert during tremor events.

## Note
This project is intended for educational demonstration only and is not a medical diagnostic device.