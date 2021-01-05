---
layout: default
title: 智能蛇实验报告
---
# 智能蛇实验报告


## 算法  
主要根据伪代码进行编写。最终达到预定目的。  
![](images\lab15_images\auto1.png)  
![](images\lab15_images\auto2.png)  
可以实现自动寻路
![](images\lab15_images\auto_snake.png)  
## 源码
``
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}

//将你的 snake 代码放在这里

#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define	NEXT_PLACE (map[snakePlace[0][0]+addY][snakePlace[1][0]+addX])	
#define PLACE(X) (map[snakePlace[0][X]][snakePlace[1][X]])			

char map[12][12] = {
	"************",
	"*XXXXH     *",
	"*          *",
	"*    *     *",
	"* *  *  *  *",
	"*    *     *",
	"* **   **  *",
	"*    *     *",
	"* *  *  *  *",
	"*    *     *",
	"*          *",
	"************"
};

int snakePlace[2][SNAKE_MAX_LENGTH] = { {1,1,1,1,1},{5,4,3,2,1} };
int snakeLength = 5;
int foodPlace[2] = {0,0};
void snakeMove(int addX, int addY, int isFood) {
	int temp1;

	if (!isFood)
		PLACE(snakeLength - 1) = ' ';
	else {
		snakeLength++;
	}

	PLACE(0) = SNAKE_BODY;
	for (temp1 = snakeLength - 1;temp1 > 0;temp1--) {
		snakePlace[0][temp1] = snakePlace[0][temp1 - 1];
		snakePlace[1][temp1] = snakePlace[1][temp1 - 1];
	}

	snakePlace[0][0] += addY;
	snakePlace[1][0] += addX;
	PLACE(0) = SNAKE_HEAD;

}

void put_money() {
	int x, y;
	do {
		x = 1 + (int)(10.0*rand() / (RAND_MAX + 1.0));
		y = 1 + (int)(10.0*rand() / (RAND_MAX + 1.0));
	} while (map[y][x] != BLANK_CELL);
	map[y][x] = SNAKE_FOOD;
	foodPlace[0] = y;
	foodPlace[1] = x;
}


char whereGoNext(int Hx,int Hy,int Fx,int Fy) {
	// 用数组movable[3]={“a”,”d”,”w”,”s”} 记录可走的方向
	char movable[4]={'a','d','w','s'};
	int distance[4]={0,0,0,0};
	// 用数组distance[3]={0,0,0,0} 记录离食物的距离
	// 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
	//     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
	//           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
	// 选择distance中存最小距离的下标p，注意最小距离不能是9999
	int minum = 9999;
	int p = 0;
	distance[0] = fabs(Fx - (Hx-1)) + fabs(Fy - Hy);
	if(map[Hy][Hx-1] == WALL_CELL||map[Hy][Hx-1]==SNAKE_BODY)
		distance[0] = 9999;
	if(minum>distance[0]){
		minum = distance[0];
		p = 0;
	}
	distance[1] = fabs(Fx - (Hx+1)) + fabs(Fy - Hy);
	if(map[Hy][Hx+1] == WALL_CELL||map[Hy][Hx+1]==SNAKE_BODY)
		distance[1] = 9999;
	if(minum>distance[1]){
		minum = distance[1];
		p = 1;
	}
	distance[2] = fabs(Fx - (Hx)) + fabs(Fy - (Hy-1));
	if(map[Hy-1][Hx] == WALL_CELL||map[Hy-1][Hx]==SNAKE_BODY)
		distance[2] = 9999;
	if(minum>distance[2]){
		minum = distance[2];
		p = 2;
	}
	distance[3] = fabs(Fx - (Hx)) + fabs(Fy - (Hy+1));
	if(map[Hy+1][Hx] == WALL_CELL||map[Hy+1][Hx]==SNAKE_BODY)
		distance[3] = 9999;
	if(minum>distance[3]){
		minum = distance[3];
		 p = 3;
	}
	return movable[p];
	// 返回 movable[p]
	}

int judgeGameRun(int addX, int addY) {
	if ((NEXT_PLACE == WALL_CELL) || (NEXT_PLACE == SNAKE_BODY)) {
		printf("You fail!\n");
		return 0;
	}

	if (NEXT_PLACE == SNAKE_FOOD) {
		if (snakeLength >= SNAKE_MAX_LENGTH) {
			printf("The snake is full.\nYou win!\n");
			return 0;
		}

		snakeMove(addX, addY, 1);
		put_money();
	}
	else 
		snakeMove(addX, addY, 0);

	return 1;
}

void output(void) {
	system("clear"); //linux
	//system("cls");//windos
	printf("------------------------Snake-------------------------\n");
	int temp1, temp2;
	for (temp1 = 0;temp1 < 12;temp1++) {
		for (temp2 = 0;temp2 < 12;temp2++) {
			printf("%c", map[temp1][temp2]);
		}
		printf("\n");
	}
}

void gameover(void) {
	printf("Game Over\n");
}

void operation(void) {
	srand((int)time(0));
	char op;
	int addX, addY;
	addX = addY = 0;

	while (1) {
		//printf("Please input the operation(WASD/wasd): ");
		//do{
			//op = getchar();
		//}while(op=='\n');
		//setbuf(stdin, NULL);
		//fflush(stdin);
		long t=time(NULL);
		     
	        while(t==time(NULL))
			;//等待1秒
		op = whereGoNext(snakePlace[1][0],snakePlace[0][0],foodPlace[1],foodPlace[0]);
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

		if (!judgeGameRun(addX, addY)) {
			break;
		}
		output();
	}
}



int main()
{
        //设置终端进入非缓冲状态
        int tty_set_flag;
        tty_set_flag = tty_set();

        //将你的 snake 代码放在这里
	put_money();
	output();
	operation();
	gameover();

        printf("pressed `q` to quit!\n");
        while(1) {

                if( kbhit() ) {
                        const int key = getchar();
                        printf("%c pressed\n", key);
                        if(key == 'q')
                                break;
                } else {
                       ;// fprintf(stderr, "<no key detected>\n");
                }
        }

        //恢复终端设置
        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
}
``
