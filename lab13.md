---
layout: default
title: 贪吃蛇实验报告
---

#贪吃蛇实验报告

## 设计思想
首先根据程序的大致逻辑  
![](images\lab13_images\construction.png)  
可以大致将整个程序的主结构分为开始、操作、结束  
![](images\lab13_images\main.png)  
再对操作项进行分析，可以将其拆分为得码（输入），解码（case），操作三部分。  
![](images\lab13_images\op.png)  
得码项使用scanf，解码则用switch函数完成，为了应对不同的操作，因此设置一个分支函数进行封装。  
![](images\lab13_images\select.png)  
显然根据游戏规则可知，蛇移动共分为三种情况，一是撞墙或吃自己导致失败，二是单纯移动，三是遇到食物进行吞食同时移动（同时设置获胜条件)。因此在remove函数中加入一个参数来区分移动与吞食移动。
![](images\lab13_images\move.png)  
在移动时将身体与头部移动分离，再根据传入的参数判断是否吞食，移动操作完成。  
同时还有随机产生事物，显示画面等功能也一一拆分成函数，最后将所有函数整合即可完成本次实验。  
因为我在代码中将移动与吞食稍微修改整合成一个函数的原因，因此我认为将文件再分成移动和吞食的话显得没有必要，所以附件只添加了一个完整的snake.c文件。  
## 实验结果
![](images\lab13_images\result.png)  
游戏运行正常，且无BUG产生。  

## 游戏文件  
请参考extra目录  
[snake](extra\snake.c)