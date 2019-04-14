# 1903-DS-school-A-Hal



【邦普杯A题电控衡拉力系统】
主控：STM32F103c8t6

外设： 电源模块*1  
      直流无刷电机*1  ……  电调*1  
      应变片*1  ……  拉力AD解读芯片*1  
      矩阵按键*1  ……  LCD1602显示屏*1  

功能：	键盘可以输入一个制定的拉力目标值（中断）
      读取芯片实时回传数据（中断）
      电机迅速响应到该值并在结束时提示（PID、滤波算法）
      显示屏显示即时拉力值、目标值（同上）

设计步骤：
    1.框架整理好（main.c）
    2.驱动无刷电机（电调）（motor.c）
    3.速度环控制（PID参数）（pid.c）
    4.硬件I2C（i2c.c+dma.c）
    5.显示屏（lcd1602.c）


*【完成】即代表可用于底盘代码1.0；
*【可用】即代表尚且可以实现功能；




