# Automatic-Cat-Feeder
![image](https://github.com/user-attachments/assets/356bdb61-3e9a-473a-82d0-7b36fbde27ca)

# Project Overview
The purpose of this project is to create an automatic pet feeder for cats. The device is built using a 3D printer and controlled by an Arduino microcontroller.
It allows the scheduling of food distribution at specific time intervals, ensuring the cat is fed regularly even when the owner is not at home.

This project is inspired by [Electronoobs](http://electronoobs.com/eng_arduino_tut163.php). The main differences in my implementation are that instead of an OLED display, I used a 2x16 I2C LCD screen, so the code I used is different from the one in the original project. Additionally, I used a different buck converter, as I encountered issues with the one suggested in the original project.

# Components
* 1 x [MG995 Servo](https://www.robofun.ro/mecanice/servomotor-mg995.html)
* 1 x [Arduino NANO](https://store.arduino.cc/en-ro/products/arduino-nano?srsltid=AfmBOooZLFNVh-QeebxxlZAbhJjiAb6UiYyRmgVN_jURxY13lN-8jbhI)
* 1 x [DS3231 RTC Module](https://www.robofun.ro/ds3231-at24c32-iic-module-precision-rtc-module-with-cr2032-battery.html?gad_source=1&gclid=CjwKCAiAlPu9BhAjEiwA5NDSA9EO8z1ZhSsO7Z9mz9YH0nfmmMEbSWrl4xg6iNz1qRcp1VvrmFTIOBoCKOwQAvD_BwE)
* 1 x [I2C LCD 2 x 16](https://www.bitmi.ro/ecran-lcd1602-cu-modul-i2c-iic-10487.html?gad_source=1&gclid=CjwKCAiAlPu9BhAjEiwA5NDSAzAMmp3bmllEWw8EKrQmoRlt1wxjWHfQRoBsTwnhXWZT21BFgPU8QBoCAUkQAvD_BwE)
* 1 x [Buck Converter Module](https://www.sigmanortec.ro/Modul-coborator-tensiune-reglabil-cu-display-LM2596-p134561747?gad_source=1&gclid=CjwKCAiAlPu9BhAjEiwA5NDSA1tTPUx6nSX5OQMMyxlXF5Oy4z7pqTOBUvOZMe9UqCONQocX1JpGvxoCxb4QAvD_BwE)
* 1 x Buzzer
* 1 x 12V DC adapter
* 1 x DC jack
* 3 x Buttons
* M3 insertion nuts
* M3 threaded rod
* M3 nuts

# 3D Printed Parts
![image](https://github.com/user-attachments/assets/fb4fd157-a7c8-4c94-b133-330533d8080e)


# Schematic
![image](https://github.com/user-attachments/assets/320997e0-1239-4d9a-be81-126231bc5b23)

# Logical Code Diagram 
![image](https://github.com/user-attachments/assets/c7fe2ac7-7507-428b-8bd3-0481d96cac1b)

# !Important!
    //rtc.setDOW(THURSDAY);            
    //rtc.setTime(18, 03, 0);         
    //rtc.setDate(27, 02, 2024);      
The first time you upload the code, remove the comment from the lines above. Set the date and time to the correct values. After that, comment out those lines again and re-upload the code. This step is only needed once.

# Future Improvement Areas
There are several aspects that can be improved:
* Implementing a scale to adjust the desired amount of food
* Developing an application for monitoring from a phone
* Improving the physical appearance
* Enhancing the propeller that distributes the food to avoid possible situations where the food gets stuck



![image](https://github.com/user-attachments/assets/8db4eeb1-7b00-4333-a6cc-033c8526cac4)
