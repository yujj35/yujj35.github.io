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

## 游戏源码  
```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//宏定义区
#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define	NEXT_PLACE (map[snakePlace[0][0]+addY][snakePlace[1][0]+addX])	//下一个位置的字符
#define PLACE(X) (map[snakePlace[0][X]][snakePlace[1][X]])				//当前位置的字符

//地图
char map[12][12] = {
	"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"
};

//蛇的位置与长度
int snakePlace[2][SNAKE_MAX_LENGTH] = { {1,1,1,1,1},{5,4,3,2,1} };
int snakeLength = 5;

//移动与吞食,isFood==1则进行吞食
void snakeMove(int addX, int addY, int isFood);
//产生随机位置食物
void put_money(void);
//分支选择器,返回0则游戏结束，否则游戏继续
int judgeGameRun(int addX, int addY);
//显示
void output(void);
//游戏结束
void gameover(void);
//控制器
void operation(void);

int main() {
	put_money();
	output();
	operation();
	gameover();
	return 0;
}

//移动与吞食,isFood==1则进行吞食
void snakeMove(int addX, int addY, int isFood) {
	int temp1;

	//是否吞食
	if (!isFood)
		PLACE(snakeLength - 1) = ' ';
	else {
		snakeLength++;
	}

	//非头部移动与坐标变化
	PLACE(0) = SNAKE_BODY;
	for (temp1 = snakeLength - 1;temp1 > 0;temp1--) {
		snakePlace[0][temp1] = snakePlace[0][temp1 - 1];
		snakePlace[1][temp1] = snakePlace[1][temp1 - 1];
	}

	//头部移动与坐标变化
	snakePlace[0][0] += addY;
	snakePlace[1][0] += addX;
	PLACE(0) = SNAKE_HEAD;

}

//产生随机位置食物
void put_money(void) {
	int x, y;
	do {
		x = 1 + (int)(10.0*rand() / (RAND_MAX + 1.0));
		y = 1 + (int)(10.0*rand() / (RAND_MAX + 1.0));
	} while (map[y][x] != BLANK_CELL);
	map[y][x] = SNAKE_FOOD;
}

//分支选择器,返回0则游戏结束，否则游戏继续
int judgeGameRun(int addX, int addY) {
	//失败条件
	if ((NEXT_PLACE == WALL_CELL) || (NEXT_PLACE == SNAKE_BODY)) {
		printf("You fail!\n");
		return 0;
	}

	//移动与吞食
	if (NEXT_PLACE == SNAKE_FOOD) {
		//进行吞食

		//获胜条件
		if (snakeLength >= SNAKE_MAX_LENGTH) {
			printf("The snake is full.\nYou win!\n");
			return 0;
		}

		snakeMove(addX, addY, 1);
		put_money();
	}
	else //不进行吞食
		snakeMove(addX, addY, 0);

	return 1;
}

//显示
void output(void) {
	// system("clear"); linux
	system("cls");//windos
	printf("------------------------贪吃蛇-------------------------\n");
	int temp1, temp2;
	for (temp1 = 0;temp1 < 12;temp1++) {
		for (temp2 = 0;temp2 < 12;temp2++) {
			printf("%c", map[temp1][temp2]);
		}
		printf("\n");
	}
}

//游戏结束
void gameover(void) {
	printf("Game Over\n");
}

//控制器
void operation(void) {
	srand((int)time(0));
	char op;
	int addX, addY;
	addX = addY = 0;

	while (1) {
		//得到操作码
		printf("Please input the operation(WASD/wasd): ");
		scanf("%c", &op);
		setbuf(stdin, NULL);

		//解码
		switch (op)
		{
		case 'a':
		case 'A':
			addX = -1;
			addY = 0;
			break;
		case 'd':
		case 'D':
			addX = 1;
			addY = 0;
			break;
		case 'w':
		case 'W':
			addX = 0;
			addY = -1;
			break;
		case 's':
		case 'S':
			addX = 0;
			addY = 1;
			break;
		default:
			addX = addY = 0;
			break;
		}
		if (addX == 0 && addY == 0)
			continue;

		//进入分支
		if (!judgeGameRun(addX, addY)) {
			break;
		}
		output();
	}
}
```
[snake](extra\snake.c)
