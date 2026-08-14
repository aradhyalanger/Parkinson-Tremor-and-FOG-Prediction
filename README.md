# Parkinson Tremor and Freezing of Gait Syndrome Prediction

An integrated Parkinson’s disease monitoring project combining **Freezing of Gait (FOG) prediction using machine learning** and **real-time hand tremor detection and suppression using embedded systems and signal processing**.

**GitHub Repository:**
https://github.com/aradhyalanger/Parkinson-Tremor-and-FOG-Prediction

---

# Abstract

Parkinson’s disease is a progressive neurodegenerative disorder that affects movement and motor control. Two major motor symptoms are **Freezing of Gait (FOG)** and **hand tremor**. This project addresses both symptoms through a dual-module architecture:

1. **FOG Prediction Module** – predicts FOG episodes using gait datasets and machine learning models.
2. **Tremor Detection Module** – detects hand tremor in real time using an ESP32 and MPU6050 sensor and provides vibration feedback.

The project demonstrates the integration of **machine learning, embedded systems, wireless communication, and MATLAB-based signal analysis** for Parkinson’s monitoring.

---

# Repository Structure

```text
Parkinson-Tremor-and-FOG-Prediction/
├── Parkinson_FOG/
│   ├── Parkinsons-fog.ipynb
│   └── README.md
│
└── Parkinson_Tremor/
    ├── Arduino_Code/
    │   └── tremor_detection_esp32.ino
    ├── MATLAB_Analysis/
    │   └── tremor_analysis.m
    ├── Data/
    │   └── sample_tremor_data.csv
    ├── Images/
    │   ├── block_diagram.png
    │   └── hardware.png
    ├── README.md
    └── components_list.txt
```

---

# Overall System Architecture

```text
                    Parkinson Monitoring System
                               │
        ┌──────────────────────┴──────────────────────┐
        │                                             │
        ▼                                             ▼
  FOG Prediction Module                        Tremor Detection Module
        │                                             │
  Gait Dataset (tdcsfog, defog)                MPU6050 IMU Sensor
        │                                             │
  Feature Extraction                            ESP32 Processing
        │                                             │
  Logistic Regression / LightGBM               RMS Tremor Detection
        │                                             │
  FOG Prediction Output                         Motor + OLED + Telegram
```

---

# Module 1: Freezing of Gait (FOG) Prediction

## Objective

Predict Freezing of Gait episodes in Parkinson’s patients using gait sensor data and machine learning techniques.

## Dataset

The implementation uses the **tdcsfog** and **defog** datasets, which contain gait measurements and FOG-related annotations such as walking, turning, and hesitation events.

## Machine Learning Models

* Logistic Regression
* LightGBM

## FOG Prediction Workflow

```text
START
  │
Load gait dataset
  │
Preprocess and clean data
  │
Feature extraction
  │
Train ML models
  │
Model evaluation
  │
FOG prediction
  │
END
```

## Working Principle

1. Gait sensor data is loaded.
2. Missing values and noise are handled.
3. Relevant gait features are extracted.
4. Machine learning models are trained.
5. The trained model predicts whether a gait segment corresponds to a FOG event.

## Main File

* `Parkinson_FOG/Parkinsons-fog.ipynb`

---

# Module 2: Tremor Detection and Suppression

## Objective

Detect Parkinsonian hand tremor in real time and provide vibration feedback when tremor is detected.

## Hardware Used

* ESP32 DevKit V1
* MPU6050 / MPU6500 IMU Sensor
* SSD1306 OLED Display
* Coin Vibration Motor
* BC547 NPN Transistor
* 1 kΩ Resistor
* 10 kΩ Resistor
* 1N4007 Diode
* 3.7 V Li-ion Battery
* Breadboard and jumper wires

## Software Used

* Arduino IDE
* MATLAB

---

# Tremor Detection Hardware Flowchart

```text
START
  │
Initialize ESP32
Initialize MPU6050
Initialize OLED
Connect Wi-Fi
  │
Read gyroscope data (100 Hz)
  │
Moving average filter
  │
RMS calculation (0.5 s window)
  │
Is RMS > Threshold?
  ├── No ──► Motor OFF
  │          OLED: NORMAL
  │
  └── Yes ─► Motor ON
             Telegram Alert
             OLED: TREMOR
  │
Store serial data
  │
Repeat continuously
```

---

# Real-Time Tremor Working

1. MPU6050 senses hand angular motion.
2. ESP32 samples gyroscope data at **100 Hz**.
3. A moving-average filter reduces noise.
4. RMS is computed over **50 samples (0.5 s)**.
5. If RMS exceeds a threshold, tremor is detected.
6. The vibration motor is activated.
7. OLED displays the status.
8. A Telegram alert is sent through Wi-Fi.

---

# MATLAB Analysis

MATLAB is used for **offline validation** of the sensor data recorded from the ESP32.

## MATLAB Flowchart

```text
START
  │
Load CSV data
  │
Remove DC offset
  │
Band-pass filter (3–8 Hz)
  │
RMS computation
  │
FFT analysis
  │
Peak frequency estimation
  │
Generate plots
  │
Save processed data
  │
END
```

## MATLAB Functions Performed

* Band-pass filtering
* RMS calculation
* FFT spectrum analysis
* Peak tremor frequency estimation
* Time-domain and frequency-domain visualization

---

# Integrated Data Flow

```text
Hand Motion
     │
     ▼
MPU6050 Sensor
     │
     ▼
ESP32 Acquisition
     │
     ▼
Moving Average Filter
     │
     ▼
RMS Calculation
     │
     ▼
Threshold Decision
 ┌───────────────┴───────────────┐
 │                               │
 ▼                               ▼
Normal                        Tremor
 │                               │
OLED NORMAL                Motor ON
                            Telegram Alert
                            OLED TREMOR
     │
     ▼
Serial Data Logging
     │
     ▼
MATLAB Analysis
(Filter + FFT + Validation)
```

---

# Circuit Connections

| Component          | ESP32 Pin |
| ------------------ | --------- |
| MPU6050 SDA        | GPIO21    |
| MPU6050 SCL        | GPIO22    |
| OLED SDA           | GPIO21    |
| OLED SCL           | GPIO22    |
| Motor Driver Input | GPIO25    |
| Battery ADC        | GPIO34    |
| VCC                | 3.3V      |
| GND                | GND       |

---

# How to Run

## FOG Prediction

1. Open `Parkinson_FOG/Parkinsons-fog.ipynb`.
2. Install required Python packages.
3. Run notebook cells sequentially.

## Tremor Detection

1. Open the Arduino sketch in `Parkinson_Tremor/Arduino_Code/`.
2. Install ESP32 board support in Arduino IDE.
3. Upload the code to ESP32.
4. Open Serial Monitor at **115200 baud**.

## MATLAB Analysis

1. Open MATLAB.
2. Navigate to `Parkinson_Tremor/MATLAB_Analysis/`.
3. Run:

```matlab
tremor_analysis
```

---

# Key Features

* Combined FOG and tremor monitoring system
* Machine learning based FOG prediction
* Real-time embedded tremor detection
* OLED status display
* Battery monitoring
* Wi-Fi and Telegram alert support
* MATLAB signal analysis and visualization
* Academic mini-project ready

---

# Results

## FOG Module

* Demonstrates prediction of FOG episodes using gait data and machine learning models.

## Tremor Module

* Successfully detects tremor-like motion.
* Activates vibration feedback during tremor events.
* Sends Telegram alerts and displays status on OLED.
* MATLAB analysis shows tremor frequency components around the Parkinsonian range.

---

# Advantages

* Low-cost implementation
* Portable and wearable prototype
* Real-time monitoring capability
* Wireless alert system
* Easy data visualization using MATLAB

---

# Limitations

* Intended for educational and research demonstration only.
* Clinical validation with patient data is not included.
* Real-time MATLAB integration is not implemented; MATLAB is used for offline analysis.

---

# Future Scope

* Real-time cloud data logging
* Mobile application integration
* Deep learning based FOG prediction
* Wearable compact PCB design
* Adaptive tremor thresholding
* Multi-axis tremor analysis
* Integration with healthcare monitoring systems

---

# Viva Summary

**FOG:** Gait data is processed, features are extracted, machine learning models are trained, and FOG events are predicted.

**Tremor:** MPU6050 senses hand motion, ESP32 processes the signal in real time, RMS is computed, tremor is detected, and motor/OLED/Telegram actions are triggered. MATLAB validates the recorded signal using filtering and FFT.

---

# Educational Note

This repository is developed for **academic and educational purposes only**. It is **not a medical diagnostic device** and should not be used for clinical decision making.

---

# Author

* **Aradhya Langer**

---

# Acknowledgement

Developed as part of an **Electronics and Communication Engineering mini project** exploring Parkinson’s disease monitoring through machine learning, embedded systems, wireless communication, and signal processing.
