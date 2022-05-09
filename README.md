
   
# DIY-Aircraft

> This project was created by two high school students on a whim

> Since this project is still in the PPT stage, the rest of the content may be very buggy and subject to major changes.

The purpose of this project is not to create a high performance, advanced quadcopter drone, but simply to document their own learning journey and, if possible, provide experience for others with similar interests. As a result, there may be a lot of ludicrous mistakes in this project, even though I don't think many people will check out our project, we will be kind enough to listen to your comments.

# General Contents

- [Introduction to the whole system](#Introduction to the whole system)
- [Features we want to achieve](#Features we want to achieve)
- [Points that must be mentioned](#Points that must be mentioned)

# Introduction of the whole system

This project plans to send the serial information to the lora module on the UAV through the SX1268-lora wireless module by using the computer as the remote control signal transmitter and the Arduino as the USB-TTL converter. The lora module on the drone will transmit the received information to the on-board Arduino through the serial port, and the Arduino will receive the remote control, ATK-IMU901 ten-axis angle sensor and optical flow sensor signals at the same time. Through its own algorithm, it will output PWM signals to the four ESCs to control the speed of motor XXD-A2212, so as to achieve more stable forward and backward, left and right rotation and other basic actions.
  
# The functions we want to achieve
  
* Stable hovering
* Stable basic movements such as forward and backward, left and right rotation
* Ability to fly within visual range
  
# Points that must be mentioned
  
* Since this project is still in the PPT stage, the content may have big mistakes and make big changes.
* Since both authors are high school students, and one of them is a residential student, updates of the project may be very unstable.
* Due to inexperience, some contents in the project may not follow the reproduction or open source regulations. If you accidentally violate your rights, please contact us voluntarily and we will make changes.
* The name of this project is only temporary and may be changed in the future.
