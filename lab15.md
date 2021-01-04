---
layout: default
title: 智能蛇实验报告
---
# 智能蛇实验报告
废了好大劲才把Ubuntu和VMware弄好，不多说了，进入正题
## 1. VT 100 终端标准
emmm,这项的代码我运行失败了，未知BUG，后面清屏函数使用system("clear")代替。

## 2. 实现 kbhit()
将代码黏贴即可  
![](images\lab15_images\kit.png)  
可以实现类似getc的功能。

## 3. 智能算法  
主要根据伪代码进行编写。最终达到预定目的。  
![](images\lab15_images\auto1.png)  
![](images\lab15_images\auto2.png)  
可以实现自动寻路，不过在特殊情况下仍会导致游戏结束（食物的玄学放置）  
![](images\lab15_images\auto_snake.png)  
详细代码请见附件  
[new_snake](extra\new_snake.c)