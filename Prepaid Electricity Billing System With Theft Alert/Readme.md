# IoT-Based Prepaid Electricity Billing System with Theft Alert

## Project Overview

This project implements an IoT-based prepaid electricity billing system with theft detection and alert features. The system allows consumers and utility providers to monitor and control electricity usage efficiently. It integrates real-time energy monitoring, prepaid billing, remote control, and theft detection, using mobile applications and GSM alerts.

### Features
- **Prepaid Energy Billing**: Consumers can top up their account and pay for electricity usage in advance.
- **Real-time Energy Monitoring**: Track energy consumption and balance in real-time.
- **Mobile App Control (Blynk IoT)**: Easily monitor and control the system via a mobile app.
- **Electricity Theft Detection**: Detect and alert on any attempts at electricity theft.
- **SMS Alerts via GSM**: Receive notifications on low balance, power cut, or theft.
- **Remote Power ON/OFF**: Control power remotely through a relay module.
- **Local Status Display**: Use an LCD display to show energy units and balance.
- **Audible Alerts**: Alerts via a buzzer when required.

## Hardware Components
- **ESP32**: Main IoT controller for Wi-Fi communication.
- **Arduino Uno**: Peripheral interfacing and sensor control.
- **SIM800 GSM Module**: For sending SMS alerts.
- **Relay Module**: To control the power based on the balance.
- **Micro Limit Switch**: For tamper detection.
- **Buzzer**: To trigger audible alerts.
- **LCD I2C Display**: To show energy and balance information.
- **4N35 Optocoupler**: For electrical isolation between components.
- **10k Resistor**: For voltage division in the system.

## System Architecture
- **ESP32** communicates with the **Blynk App** over Wi-Fi.
- **Arduino Uno** manages sensors, relay, LCD, and buzzer operations.
- **GSM Module** sends SMS alerts for low balance, power cut, and theft detection.
- **Relay** disconnects the power when the balance reaches zero.
- **Micro Limit Switch** detects tampering or theft.
- **LCD Display** shows units consumed, balance, and system status.

## Blynk App Features
- Display live energy units.
- Monitor balance in real-time.
- Recharge system through the app.
- View energy usage trends with graphs.
- Receive theft and low-balance notifications.

## Implementation Steps
1. **Hardware Setup**: Assemble the components as per the circuit diagram.
2. **Software Configuration**: Program the ESP32 and Arduino Uno using the Arduino IDE.
3. **Blynk App Setup**:
   - Create a project in the Blynk App.
   - Add necessary widgets.
   - Generate an authentication token.
4. **GSM Configuration**: Set up the SIM800 GSM module for SMS alerts.
5. **Testing**: Verify the system works with power cutoff, theft detection, SMS notifications, and app communication.

## Experimental Results
- Accurate real-time energy monitoring.
- Immediate theft detection and alerts.
- Stable prepaid billing mechanism.
- Reliable GSM-based SMS communication.

## Outputs
- **LCD** displays live energy usage and balance.
- **Blynk App** shows live energy consumption, balance, and trends.
- **SMS Alerts** are sent for theft detection and low balance.

## Future Enhancements
- Integration with cloud databases.
- AI-based theft prediction.
- Scalability for smart meters in larger grids.
- Dashboard for utility providers.
- Integration with renewable energy sources.

## Authors
- **K. Ravi Teja** – Graduate Student

## License
This project is for academic and educational purposes. You may modify and reuse it with proper credits.

