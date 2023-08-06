# Fire_System 
is a system which determine the state of the system (based on Atmega32)--> 
-the first state is fine
-the second is Heat
-the third is fire according to sensors (Temp, Smoke) reading.

then print the state on LCD, if heat state achieved, set the heat led.
if state 3 achieved and the system detect a fire, it opens alarm, water pump and can't return to normal state until fix it and enter password to the system to reset.

#Reading Temp and Smoke sensors, while system ON,

#Normal State if (temp <50 & smoke<50):
-The system prints Fine and Temp on LCD.
-LCD prints option for editing password, click 2.

#Heat State if (temp >50 & smoke<50):
-The system prints Heat and Temp on LCD.
-yellow led will light up to indicate Heat state. -LCD prints option for editing password, click 2.
-if Temp decreased under 50 the system return to Fine state.

#Fire State if (temp >50 & smoke>50):
-The system prints Fire on LCD.
-red led will light up to indicate Fire state. -LCD prints option for reset system, click 1.
-to reset system will click 1, then LCD will print Enter Password, LCD will print wrong password if you enterd a wrong password and give you option to try again.
-if the system is reseted, the system will read the current state.
-if Temp and Smoke decreased under 50, so the system can't return to previous state untile fix the problem.

#in case of changing the password of the system: the new password will store in NVM data (EEPROM), so the new password remains on the system.
