# 🌡️ EMB546 MOA Water Heater Control System

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)
[![Microcontroller: ATmega](https://img.shields.io/badge/MCU-ATmega-green.svg)]()
[![RTOS: FreeRTOS](https://img.shields.io/badge/RTOS-FreeRTOS-orange.svg)]()

> **Advanced Water Heater Temperature Control System** - A sophisticated embedded systems graduation project implementing intelligent temperature control with real-time monitoring and user-friendly interface.

## 📋 Table of Contents

- [🎯 Project Overview](#-project-overview)
- [✨ Features](#-features)
- [🔧 Hardware Requirements](#-hardware-requirements)
- [🏗️ Software Architecture](#️-software-architecture)
- [📁 Project Structure](#-project-structure)
- [🚀 Getting Started](#-getting-started)
- [💡 Usage](#-usage)
- [🔄 System Operation](#-system-operation)
- [🛠️ Development](#️-development)
- [📸 Screenshots](#-screenshots)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👥 Authors](#-authors)

## 🎯 Project Overview

The EMB546 MOA Water Heater Control System is an advanced embedded systems project that provides intelligent temperature control for water heating applications. Built on the ATmega microcontroller platform with FreeRTOS, this system offers precise temperature monitoring, user-configurable setpoints, and automated heating/cooling control.

### Key Highlights

- **Real-time Temperature Monitoring** with LM35 sensor
- **RTOS-based Multitasking** using FreeRTOS
- **Non-volatile Settings Storage** via EEPROM
- **Intuitive User Interface** with seven-segment displays
- **Automated Control Logic** for heating and cooling
- **Safety Features** with temperature limits and indicators

## ✨ Features

### 🎛️ **Temperature Control**
- Precise temperature sensing using LM35 analog sensor
- Configurable temperature setpoints (35°C - 75°C)
- Automatic heating and cooling control
- Temperature averaging over 10 readings for stability

### 🖥️ **User Interface**
- Dual seven-segment display for temperature readout
- Push-button controls for temperature adjustment
- Visual indicators with LED status lights
- Blinking display during configuration mode

### 💾 **Settings Management**
- EEPROM storage for temperature presets
- Non-volatile memory ensures settings persist
- Default temperature setting of 60°C

### ⚡ **System Control**
- FreeRTOS-based task management
- Real-time multitasking with proper task synchronization
- Semaphore-controlled display access
- Queue-based inter-task communication

### 🔄 **Hardware Control**
- Relay control for heating elements
- PWM-controlled cooling fan
- LED status indicators
- Button debouncing and input handling

## 🔧 Hardware Requirements

### **Core Components**
- **Microcontroller**: ATmega series (ATmega328P/ATmega32 recommended)
- **Crystal Oscillator**: 16 MHz
- **Temperature Sensor**: LM35 precision analog sensor
- **Display**: Dual seven-segment displays (common cathode/anode)
- **Memory**: External EEPROM for settings storage

### **Control Interface**
- **Push Buttons**: 
  - Power ON/OFF button
  - Temperature UP button  
  - Temperature DOWN button
- **LEDs**:
  - Power status indicator (Green)
  - Heating status indicator (Red)

### **Power & Control**
- **Relays**: For heater and cooling fan control
- **Power Supply**: 5V regulated supply
- **Connectors**: Standard pin headers for modular connections

### **Communication**
- **TWI/I2C**: For EEPROM communication
- **SPI**: Available for future expansions
- **UART**: For debugging and monitoring

## 🏗️ Software Architecture

### **Real-Time Operating System**
The project utilizes **FreeRTOS** for efficient task management and real-time operation:

- **Task 1**: Temperature setting and configuration mode
- **Task 2**: Display management and temperature readout  
- **Task 3**: Control logic for heating/cooling decisions
- **Task 4**: Power management and system ON/OFF control

### **Layered Architecture**

```
┌─────────────────────────────────────┐
│           Application Layer         │
├─────────────────────────────────────┤
│     Hardware Abstraction Layer     │
│              (HAL)                  │
├─────────────────────────────────────┤
│   Microcontroller Abstraction      │
│         Layer (MCAL)                │
├─────────────────────────────────────┤
│          Hardware Layer             │
└─────────────────────────────────────┘
```

### **Key Modules**
- **DIO**: Digital Input/Output management
- **ADC**: Analog-to-Digital conversion for temperature sensing
- **TWI**: Two-Wire Interface for EEPROM communication
- **Timer**: PWM generation and timing functions
- **RTOS**: Task scheduling and synchronization

## 📁 Project Structure

```
EM_MAADI546 Water Heater Grad. Project/
├── APP/
│   └── main.c                 # Main application logic
├── FreeRTOS/                  # FreeRTOS kernel files
├── HAL/                       # Hardware Abstraction Layer
│   ├── EEPROM/               # EEPROM interface
│   ├── SSD/                  # Seven Segment Display
│   ├── LCD/                  # LCD display (optional)
│   └── LED/                  # LED control
├── MCAL/                     # Microcontroller Abstraction Layer
│   ├── DIO/                  # Digital I/O
│   ├── ADC/                  # Analog to Digital Converter
│   ├── TWI/                  # Two Wire Interface (I2C)
│   ├── TIM0/                 # Timer 0
│   ├── TIM2/                 # Timer 2
│   └── GI/                   # Global Interrupt
├── LIB/                      # Common libraries and definitions
└── Debug/                    # Build output files
```

## 🚀 Getting Started

### **Prerequisites**
- Atmel Studio 7 or compatible AVR development environment
- AVR-GCC compiler toolchain
- AVRDUDE for programming
- Hardware setup with required components

### **Installation**

1. **Clone the Repository**
   ```bash
   git clone https://github.com/yourusername/emb546-moa-water-heater.git
   cd emb546-moa-water-heater
   ```

2. **Open in Development Environment**
   - Launch Atmel Studio 7
   - Open the project file: `EM_MAADI546.cproj`

3. **Configure Hardware**
   - Set up the microcontroller connections as per the pin configuration
   - Connect temperature sensor, displays, and control relays
   - Verify power supply connections

4. **Build and Program**
   ```bash
   # Build the project
   make clean && make

   # Program the microcontroller
   avrdude -p atmega328p -c usbasp -U flash:w:EM_MAADI546.hex
   ```

## 💡 Usage

### **Initial Setup**
1. Power on the system using the ON/OFF button
2. The green power LED will illuminate
3. The display will show the current temperature
4. Default setpoint is 60°C (stored in EEPROM)

### **Temperature Configuration**
1. Press and hold the **UP** or **DOWN** button to enter configuration mode
2. The display will start blinking to indicate configuration mode
3. Use **UP** button to increase temperature setpoint (+5°C increments)
4. Use **DOWN** button to decrease temperature setpoint (-5°C increments)
5. Temperature range: 35°C to 75°C
6. Configuration mode automatically exits after 5 seconds of inactivity
7. New setpoint is automatically saved to EEPROM

### **System Operation**
- **Heating Mode**: When temperature is 5°C below setpoint, heater activates
- **Cooling Mode**: When temperature is 5°C above setpoint, cooling fan activates
- **Standby Mode**: When temperature is within ±4°C of setpoint
- **Status LEDs**: Red LED blinks during heating, stays solid during cooling

## 🔄 System Operation

### **Temperature Control Logic**

```
Temperature ≤ (Setpoint - 5°C)  →  Heater ON
Temperature ≥ (Setpoint + 5°C)  →  Cooling Fan ON
(Setpoint - 4°C) ≤ Temp ≤ (Setpoint + 4°C)  →  Standby
```

### **Display Behavior**
- **Normal Operation**: Steady display of current temperature
- **Configuration Mode**: Blinking display showing setpoint value
- **Power Off**: Display disabled, all controls inactive

### **Safety Features**
- Temperature limits prevent overheating
- Automatic timeout for configuration mode
- EEPROM backup ensures settings are not lost
- Debounced button inputs prevent accidental changes

## 🛠️ Development

### **Pin Configuration**

| Component | Port | Pin | Function |
|-----------|------|-----|----------|
| ON/OFF Button | PORTB | PIN0 | System power control |
| UP Button | PORTD | PIN2 | Temperature increase |
| DOWN Button | PORTD | PIN6 | Temperature decrease |
| SSD Enable 1 | PORTB | PIN1 | Display control |
| SSD Enable 2 | PORTB | PIN2 | Display control |
| Heater Relay | PORTC | PIN2 | Heating element |
| Fan Relay | PORTC | PIN7 | Cooling fan |
| Status LED | PORTC | PIN5 | Heating indicator |
| Power LED | PORTD | PIN3 | System status |
| LM35 Sensor | ADC | CH0 | Temperature input |

### **Build Configuration**
- **CPU Frequency**: 16 MHz
- **Compiler**: AVR-GCC
- **Optimization**: -Os (size optimization)
- **FreeRTOS Version**: Compatible with AVR architecture

### **Customization**
The system can be easily customized by modifying:
- Temperature ranges in `main.c`
- Display update intervals
- Control logic parameters
- Additional sensor inputs

## 📸 Screenshots

*[Add screenshots of your hardware setup, display readings, and system in operation]*

## 🤝 Contributing

We welcome contributions to improve this project! Here's how you can help:

1. **Fork** the repository
2. **Create** a new feature branch (`git checkout -b feature/AmazingFeature`)
3. **Commit** your changes (`git commit -m 'Add some AmazingFeature'`)
4. **Push** to the branch (`git push origin feature/AmazingFeature`)
5. **Open** a Pull Request

### **Areas for Improvement**
- Additional sensor support (humidity, pressure)
- Wireless connectivity (WiFi/Bluetooth)
- Mobile app integration
- Data logging capabilities
- Enhanced safety features

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 👥 Authors

- **Mahmoud Hisham** - *Lead Developer* - [@mahmoud](https://github.com/Mahmoud-Hisham-94/)
- **MOA Team** - *Project Contributors*

### **Acknowledgments**
- Thanks to the embedded systems community
- FreeRTOS development team
- Course instructors and mentors
- Fellow students and collaborators

---

<div align="center">

**⭐ Star this repository if you found it helpful!**

[Report Bug](https://github.com/Mahmoud-Hisham-94//emb546-moa-water-heater/issues) • [Request Feature](https://github.com/yourusername/emb546-moa-water-heater/issues) • [Documentation](https://github.com/Mahmoud-Hisham-94//emb546-moa-water-heater/wiki)

</div>
