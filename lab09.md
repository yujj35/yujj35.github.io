---
layout: default
title: 洗衣机算法设计
---
# 洗衣机算法设计
一般而言洗衣机分为“设定，注水，浸泡，漂洗，脱水，结束”几个过程，因此设计程序时也按照这个流程进行分解。  
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

