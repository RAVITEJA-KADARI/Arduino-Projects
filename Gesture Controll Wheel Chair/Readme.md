# Gesture-Controlled Wheelchair for Disabled People

## Project Overview

This project aims to provide a solution for physically disabled individuals by enabling them to control a wheelchair using hand gestures. Using **Arduino** and **Bluetooth** technology, this system allows the user to control the wheelchair’s movement, including forward, backward, left, right, and stop commands, all via Bluetooth.

The system uses:
- **Arduino Nano** for controlling the motors and processing commands
- **HC-05 Bluetooth module** for wireless communication
- **L298 Motor Driver** for motor control
- **DC Motors** to drive the wheelchair
- **Power Supply** for the system's operation

## Key Features

- **Prepaid Wheelchair Control**
- **Real-time Gesture Control**
- **Mobile App Control (Bluetooth connection)**
- **Wireless Communication with HC-05**
- **Motor Speed Control**
- **Multi-directional Movement** (Forward, Backward, Left, Right)
- **Local Status Display** (on Arduino)

## Hardware Components

| Component            | Description                                       |
|----------------------|---------------------------------------------------|
| **Arduino Nano**      | Main controller for motor and Bluetooth control   |
| **HC-05 Bluetooth Module** | For wireless communication and gesture command reception |
| **L298 Motor Driver** | Drives the wheelchair motors                      |
| **DC Motors**         | Motors for wheelchair movement                    |
| **Power Supply**      | Supplies power to the system                      |

## System Architecture

1. **Bluetooth Communication**: The **Arduino Nano** communicates with a Bluetooth-enabled device (e.g., a mobile phone).
2. **Motor Control**: The **L298 motor driver** takes commands from the Arduino and controls the movement of the DC motors.
3. **Wheelchair Movement**: The system moves the wheelchair based on Bluetooth input:
   - **Forward (F)**: Move forward
   - **Backward (B)**: Move backward
   - **Left (L)**: Turn left
   - **Right (R)**: Turn right
   - **Stop (S)**: Stop all movement

## Bluetooth Control Features

- **Live Gesture Control**: Send commands like 'F', 'B', 'L', 'R', and 'S' for movement.
- **Forward/Backward Movement**: Control the direction of the wheelchair.
- **Left/Right Turn**: Control the turning direction of the wheelchair.

## Implementation Steps

1. **Assemble Hardware**: Connect the **Arduino**, **Bluetooth module**, **motor driver**, and **motors** according to the wiring diagram.
2. **Upload Code**: Program the **Arduino** with the provided code using the **Arduino IDE**.
3. **Configure Bluetooth**: Pair the Bluetooth device with the **HC-05 module**.
4. **Test**:
   - Test the wheelchair’s movement in all directions.
   - Check the Bluetooth connection for real-time control.

## Experimental Results

- **Real-time Control**: Seamless movement control via Bluetooth.
- **Directional Accuracy**: Precise wheelchair movement in all directions.
- **Easy to Operate**: Simple Bluetooth communication for disabled users.

## Outputs

- **Bluetooth-controlled Movement**: The wheelchair moves based on Bluetooth signals received from a connected mobile device.
- **Arduino-controlled Motors**: The **L298 motor driver** controls the wheelchair motors based on the Arduino's logic.

## Future Enhancements

- **Gesture Recognition**: Implement hand gesture sensors (e.g., accelerometer) for more advanced control.
- **Voice Control**: Integrate voice recognition for easier control.
- **GPS Integration**: Add a GPS module to track the wheelchair's location.
- **GSM-based Emergency Alerts**: Implement a GSM module for sending SMS alerts in emergencies.

## Authors

- **K. Ravi Teja** – Graduate Student

## License

This project is for academic and educational purposes.  
Free to modify and reuse with proper acknowledgment.

---
