# Robot Floor Cleaner 2.0

## Project Overview

Cleaning large floor areas manually is time-consuming and tiring. This project presents an advanced **Robot Floor Cleaner 2.0** that can be controlled remotely using a smartphone application.

The robot uses **Bluetooth communication** to receive commands and can operate in **manual** or **autonomous mode**, making floor cleaning faster, easier, and more efficient.

## Scientific Principle

The working of this robot is based on:
- **Wireless communication** using Bluetooth.
- **Microcontroller-based motor control**.
- **Electromechanical cleaning mechanism**.
- **Automated power management**.

A mobile application sends control commands via Bluetooth, which are processed by the microcontroller to control movement and cleaning operations.

## Components Used

| Component          | Description                        |
|--------------------|------------------------------------|
| **Arduino Nano**    | Main controller                    |
| **L298N Motor Driver** | Controls DC motors                |
| **HC-05 Bluetooth Module** | Wireless communication            |
| **Relays**           | Power switching                    |
| **Lithium Battery** | Power supply                       |
| **DC Motors**       | Robot movement                     |
| **DC Water Pump**   | Water spraying for cleaning        |
| **Switches**        | Manual control                     |
| **Connecting Wires**| Electrical connections             |

## Working

### 1. Control via Smartphone
- The robot connects to a smartphone using the **HC-05 Bluetooth module**.
- A mobile app sends movement and cleaning commands.

### 2. Movement Control
- **DC motors** enable forward, backward, left, and right movement.
- Motors are controlled by the **Arduino Nano** through the **L298N motor driver**.

### 3. Cleaning Mechanism
- A cleaning motor scrubs the floor surface.
- A **DC water pump** sprays water to remove dirt and stains.

### 4. Power Control
- **Relays** and motor drivers regulate the power supply, preventing overheating and excessive power consumption.



## Advantages
- Convenient cleaning without physical presence.
- Cost-effective compared to commercial robot cleaners.
- Efficient cleaning of hard-to-reach areas.
- Simple and user-friendly operation.

## Applications
- Homes and apartments.
- Schools and offices.
- Hospitals and public spaces.
- Smart home automation systems.

## Future Enhancements
- Obstacle detection using sensors.
- Fully autonomous navigation.
- IoT and Wi-Fi control.
- Rechargeable docking station.

## License

This project is open for educational and learning purposes.  
Free to modify and reuse with proper acknowledgment.
