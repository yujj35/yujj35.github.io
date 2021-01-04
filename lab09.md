---
layout: default
title: 洗衣机算法设计
---
# 洗衣机算法设计
![](images\lab09_images\t0d.jpg)
## 什么是“自顶向下，逐步求精”的设计方法？
自顶向下就是在设计程序的过程中，先从高层次的问题上进行分析，再将高层次的问题分解为若干低层次问题进行解决，最终解决所有的问题。概括的说，就是将一个较大的任务，按照不同的层次逐步拆分，将解决一个大任务变为解决若干小任务。  
## 有什么用？
最明显的优点就是使得整个程序的结构变得清晰，利于编写者（或操作者）对程序进行使用和维护。
## 举例
例如下面是我最近编写的一个程序，这是最初的版本
![](images\lab09_images\eg1.png)  
虽然完整的实现了功能，但是看起来却是非常乱的，现在用Top-down简单拆分以后的版本如下
![](images\lab09_images\eg2.png)
虽然只进行了初步拆分但是可读性上升了不少，还可以继续往下，但是这里不进行了。  
## 洗衣机算法
接下来是有关洗衣机的程序设计，一般而言洗衣机分为“设定，注水，浸泡，漂洗，脱水，结束”几个过程，因此设计程序时也按照这个流程进行分解。  
1. READ    waterLine，timeLine1, timeLine2 //读取用户设定  
2. REPEAT //进行注水  
    water_in_switch(open)// open 打开上水开关，close关闭  
    UNTIL get_water_volume==waterLine//返回洗衣机内部水的高度  
    water_in_switch(close)  
3. REPEAT //进行浸泡  
    浸泡  
    UNTIL time_counter()==timeLine1  
4. SET nowTime = time_counter()  
REPEAT //进行漂洗  
    SET tempTime1 = time_counter()// 返回当前时间计数，以秒为单位  
    REPEAT  
        motor_run(left)// 电机转动。left左转，right右转，stop停  
    UNTIL time_counter()-tempTime1==3
    SET tempTime2 = time_counter()  
    REPEAT  
        motor_run(right)   
    UNTIL time_counter()-tempTime2==3  
     motor_run(stop)  
UNTIL time_counter()-nowTime==timeLine2  
5. REPEAT //进行脱水  
    water_out_switch(open)// open 打开排水开关，close关闭  
    UNTIL get_water_volume==0  
    water_out_switch(close)  
6. halt(0) //结束   
以上就是对洗衣机的程序的伪代码分解 

