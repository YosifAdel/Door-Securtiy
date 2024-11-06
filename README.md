# Door Locker Security System

## Overview

### This project implements a door locker security system using two ATmega32 microcontrollers.

### The system enables unlocking a door using a password, managed through a Human Machine Interface (HMI) and Control ECU.

### The HMI provides the interface with a 4x4 keypad and 2x16 LCD, while the Control ECU handles password verification, door unlocking, and alarm activation.

## Key Features:

### Password Protection:

User can set and change passwords using the keypad.

### Door Locking and Unlocking:

Rotates the motor to unlock or lock the door.

### Security Alarm:

Activates buzzer if the wrong password is entered multiple times.

### EEPROM Storage:

Stores the password securely in EEPROM.

### Communication:

Utilizes UART for communication between the two microcontrollers.

## Components

### 1. Microcontrollers: ATmega32 (2 units)

### 2. LCD: 2x16 LCD

### 3. Keypad: 4x4 Keypad

### 4. DC Motor: Used for door locking/unlocking

### 5. Buzzer: Used for security alarm

### 6. EEPROM: Stores the system password

## System Design

### Layered Architecture:

#### HMI_ECU:

Handles user input through keypad and displays information on LCD.

### Control_ECU:

Manages password validation, door control, and alarm functions.

### Steps:

#### 1. Create a Password: User sets a password by entering and confirming a 5-digit password.

#### 2. Open Door: User enters the password to unlock the door.

#### 3.Change Password: User can change the password by re-entering the current password and setting a new one.

#### 4. Security Mechanism: After 3 consecutive wrong password attempts, a buzzer sounds for 1 minute, and the system locks out.

### Driver Requirements

#### GPIO Driver

#### Used across both ECUs for input/output handling.

#### LCD Driver

#### 2x16 LCD used for displaying information.

#### Keypad Driver

#### 4x4 Keypad for user input.

#### Motor Driver

#### DC Motor for opening and closing the door.

#### EEPROM Driver

#### External EEPROM used to store the password.

#### UART Driver

#### UART used for communication between the two microcontrollers.

#### Timer Driver

#### Timer1 used for motor control and message display timing.

#### Buzzer Driver

#### Buzzer used for system alerts, like incorrect password entries.

### Installation

#### Hardware Setup:

Connect the microcontrollers, LCD, keypad, DC motor, EEPROM, buzzer, and other components according to the project specifications.

#### Software Setup:

##### Ensure that you have the necessary drivers for the UART, I2C, GPIO, and other components implemented.

##### Upload the code to the two ATmega32 microcontrollers.

#### Testing:

##### Set a password, and test the door unlocking, password changing, and security features.

#### Conclusion

The Door Locker Security System provides a secure and user-friendly solution for password-based door access. The system ensures safety with an alarm triggered after multiple incorrect attempts.
