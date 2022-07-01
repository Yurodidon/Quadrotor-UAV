
   
# DIY-Aircraft

###  English | [中文](README.zh-CN.md)

> This project was created by two high school students on a whim

> Since this project is still in the early stage, the rest of the content may be very buggy and subject to major changes.

The purpose of this project is **not** to create a high performance, advanced quadcopter UAV, but simply to document our own learning journey and, if possible, provide available reference for those with similar interests. As a result, there may be a number of ludicrous mistakes in this project, even though I don't think many people will check out our project(lol), we will be willing to listen to your comments.

# General Contents

- [Introduction to the whole system](#introduction-to-the-whole-system)
- [Features we want to achieve](#the-features-we-want-to-achieve)
- [Points that must be mentioned](#points-that-should-be-mentioned)

# Introduction to the whole system

This project plans to send the serial information to the lora module on the UAV through the SX1268-lora wireless module, with the computer as the remote control signal transmitter and the Arduino as the USB-TTL converter. The lora module on the drone will transmit the received control signals to the on-board Arduino through the serial port. The Arduino will receive the remote control, ATK-IMU901 ten-axis angle sensor and optical flow sensor signals at the same time, for operating its own algorithm. Based on the flight control system, PWM signals will be generated and sent to the four ESCs to adjust the speed of motor XXD-A2212, so as to achieve more stable forward and backward, left and right rotation and other basic actions.
  
# The features we want to achieve
  
* Stable hovering
* Stable basic movements such as forward and backward, left and right rotation
* Ability to fly within visual range
  
# Points that should be mentioned
  
* Since this project is still in the early stage, the content may have unavoidable mistakes. But we will correct them as the project goes.
* Since both authors are high school students, and one of them is a residential student, the intervals between updates of the project may be very long.
* Due to inexperience, some contents in the project may not follow the reproduction or open source regulations. If we accidentally violate your rights, please contact us voluntarily and we will make changes as soon as possible.
* The name of this project is only temporary and may be changed in the future.
