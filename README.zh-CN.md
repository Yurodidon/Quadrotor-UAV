# DIY-Aircraft

###  [English](README.md) | 中文

> 本项目由两位心血来潮的高中生创立

> 由于本项目还处在PPT阶段，所以接下来的内容可能会存在很大的错误，并且进行较大的改动。

本项目的目的不是创立一个多么高性能、先进的四旋翼无人机，只是为了记录自己的学习历程，并有可能的话，为有同样兴趣的人提供经验。因此，本项目中可能有很多令人啼笑皆非的错误，<del>虽然可能也没什么人看</del>，但希望大家能嘴下留情，我们会虚心听取大家的意见的。

# 总目录

- [整个系统的介绍](#整个系统的介绍)
- [想要实现的功能](#想要实现的功能)
- [不得不提的几点](#不得不提的几点)

# 整个系统的介绍

本项目计划将通过电脑作为遥控信号发送端，通过Arduino作为USB-TTL转换器，将串口信息通过SX1268-lora无线模块发送到处于无人机上的lora模块上。无人机上的lora模块将会将接收到的信息通过串口传输到机载的Arduino上，Arduino会同时接收此时的遥控、ATK-IMU901十轴角度传感器、光流传感器信号。通过自身的算法，输出PWM信号到四个电调上，控制电机XXD-A2212的转速，从而实现较为稳定的前进后退、左右旋转等基础动作。
  
# 想要实现的功能
  
* 稳定的悬停
* 较为稳定的前进后退、左右旋转等基础动作
* 视距内飞行的能力
  
# 不得不提的几点
  
* 由于本项目还处在PPT阶段，所以内容可能会存在很大的错误，并且进行较大的改动。
* 由于两位作者都是高中生，并且其中一位还是住宿生，所以项目的更新可能很不稳定。
* 由于没有经验，项目中的部分内容可能没有遵守转载或开源规定，若不小心触犯到您的权益，请主动联系我们，我们会进行修改。
* 本项目的名称仅是暂时性的，未来可能会进行更改。
