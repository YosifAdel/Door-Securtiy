# Door Locker Security System
Door Locker Security System
⚙️🖥️ Hardware Setup:
For this project, I utilized the mighty ATmega32 MCU, operating at a clock frequency of 8 MHz .

- Microcontroller 1 (MC1):
1. It acts as the Human Machine Interface (HMI_ECU) , It is responsible for user interaction, handling input from the keypad, and displaying messages on the LCD.

2. Drivers:
a) HAL drivers for MC1: includes LCD and Keypad b) MCAL drivers for MC1:
includes GPIO, UART,Timer 1

- Microcontroller 2 (MC2):
1. It acts as the (Control_ECU) and manages all processing and decisions, including password verification, door operation, and system alarm activation.

2. Drivers:
a) HAL drivers for MC2: includes Buzzer, EEPROM, and DC-motor
b) MCAL drivers for MC2: include GPIO, I2C, UART, PWM mode of Timer0 and Timer1.

⚙️ System Sequence :
1. Create New Password 🔐:
To create a new password, use the keypad to input a 5-digit password, then re-enter it for confirmation. If both passwords are identical, save them in EEPROM. If not, repeat step 1.

2. Display the main options:
a) LCD displays "choose option + or -"
🚪 '+' for open the Door
🔐 '-' for change the password

b) Using Keypad, enter your option
🚪IF YOU CHOOSE '+' Open Door Sequence
- if you choose + this means that you want to open the door.
- LCD displays "please enter passwod"
- Using Keypad, enters 5-digits password each character display as '*'
,after finishing your password enter '=' to enter the password
- compare the two passwords [password entered , password save in
EEPROM]
if identical, Open the door Sequence:
1. LCD displays "Unlocking the door" for 15 seconds and Motor rotates
with speed 100 in Clockwise for 15 seconds
2. LCD displays "Door is open" for 3 seconds and Motor stops for 3 seconds
3. LCD displays "Door is Locking" for 15 seconds and Motor rotates with speed 100 in Anti-Clockwise for 15 seconds

If password is incorrect, enter it twice before the buzzer turns on. The buzzer will open for 60 seconds, and the LCD will display "ERROR 3 times Wait 60 sec."

🚪IF YOU CHOOSE '-' Change the password
if you choose - this means that you want to change the password.
LCD displays "please enter passwod"
Using Keypad, enters 5-digits password each character display as '*' ,after
finishing your password enter '=' to enter the password

compare the two passwords [password entered , password saved in EEPROM], if correct, change the password, repeat step 1

If password is incorrect, enter it twice before the buzzer turns on. The buzzer will open for 60 seconds, and the LCD will display "ERROR 3 times Wait 60 sec."
