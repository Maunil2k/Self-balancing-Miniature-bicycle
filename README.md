# Self-balancing-Miniature-bicycle
SELF BALANCING MINIATURE BICYCLE

Hardware:
Computer running Windows and Ubuntu 
3D printer
Laser cutting machine
Medium Density Fibreboard (MDF) – 2mm and 5.5mm thick
Acrylic Sheets – 2mm thick
Sticking materials e.g. Mseal, Fevikwik and Gluegun
Hollow aluminium rod
Servo motor
DC motor
A conveyer belt
Software:
Toolchain to build the Application for ESP32
Solidworks software for designing chassis, gears, couplers and shafts.
ESP-IDF that essentially contains API (software libraries and source code) for ESP32 and scripts to operate the Toolchain
Text editor to write programs (Projects) in C, e.g., Sublime Text
Electronics:
An ESP32 board
USB cable - USB A / micro USB B
MPU6050
A development board/ bread board 
 
          
Implementation of solution: MPU6050 contains accelerometer, gyro sensor and temperature sensor. We will be using accelerometer and gyro sensor in our project. So, the MPU will first read the raw error (topple) along the roll axis. The readings will then be passed to the complementary filter. Next, the PID controller will calculate the feed angle for the servo motor. Simultaneously with all these there will be a motor driving the rear wheel whose speed can be controlled using PWM. There is a detailed explanation of some concepts in this module.
ESP32 
 
 


 
ESP 32 pin diagram:
 
 

 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
Algorithm of self balancing:
 

 
 
 
links:

1) I2C communication protocol:

> https://learn.sparkfun.com/tutorials/i2c/all

2) IMU, Gyro sensors, Accelerometers: 

> https://www.intorobotics.com/accelerometer-gyroscope-and-imu-sensors-tutorials/

> https://www.hillcrestlabs.com/posts/what-is-an-imu-sensor	

3) Complementary filter:

> https://sites.google.com/site/myimuestimationexperience/filters/complementary-filter

4) PID controller:

> https://www.elprocus.com/the-working-of-a-pid-controller/

> https://www.youtube.com/watch?v=wkfEZmsQqiA3

5) Solidworks:

> https://www.youtube.com/watch?v=pfzoyqMVNkQ&list=PLfP1GxQ1lPaRGk23H7PULcftZ3i-obn9C

> https://www.youtube.com/watch?v=xey6WL873-E

6) PWM:

> https://www.analogictips.com/pulse-width-modulation-pwm/

> https://www.youtube.com/watch?v=2XjqS1clY_E	

7) Programming for ESP32:

> MCPWM: https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/mcpwm.html

> GPIO: https://docs.espressif.com/projects/esp-idf/en/latest/api-reference/peripherals/gpio.html	


Github link: 

https://github.com/sanathmenon/Autobike
