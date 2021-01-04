//main.c
//snake
//
//����ɽ��ѧ17������������ٺ����
//������ʱ��2018-12-1/16:57


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//�궨����
#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'
#define	NEXT_PLACE (map[snakePlace[0][0]+addY][snakePlace[1][0]+addX])	//��һ��λ�õ��ַ�
#define PLACE(X) (map[snakePlace[0][X]][snakePlace[1][X]])				//��ǰλ�õ��ַ�

//��ͼ
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

//�ߵ�λ���볤��
int snakePlace[2][SNAKE_MAX_LENGTH] = { {1,1,1,1,1},{5,4,3,2,1} };
int snakeLength = 5;

//�ƶ�����ʳ,isFood==1�������ʳ
void snakeMove(int addX, int addY, int isFood);
//�������λ��ʳ��
void put_money(void);
//��֧ѡ����,����0����Ϸ������������Ϸ����
int judgeGameRun(int addX, int addY);
//��ʾ
void output(void);
//��Ϸ����
void gameover(void);
//������
void operation(void);

int main() {
	put_money();
	output();
	operation();
	gameover();
	return 0;
}

//�ƶ�����ʳ,isFood==1�������ʳ
void snakeMove(int addX, int addY, int isFood) {
	int temp1;

	//�Ƿ���ʳ
	if (!isFood)
		PLACE(snakeLength - 1) = ' ';
	else {
		snakeLength++;
	}

	//��ͷ���ƶ�������仯
	PLACE(0) = SNAKE_BODY;
	for (temp1 = snakeLength - 1;temp1 > 0;temp1--) {
		snakePlace[0][temp1] = snakePlace[0][temp1 - 1];
		snakePlace[1][temp1] = snakePlace[1][temp1 - 1];
	}

	//ͷ���ƶ�������仯
	snakePlace[0][0] += addY;
	snakePlace[1][0] += addX;
	PLACE(0) = SNAKE_HEAD;

}

//�������λ��ʳ��
void put_money(void) {
	int x, y;
	do {
		x = 1 + (int)(10.0*rand() / (RAND_MAX + 1.0));
		y = 1 + (int)(10.0*rand() / (RAND_MAX + 1.0));
	} while (map[y][x] != BLANK_CELL);
	map[y][x] = SNAKE_FOOD;
}

//��֧ѡ����,����0����Ϸ������������Ϸ����
int judgeGameRun(int addX, int addY) {
	//ʧ������
	if ((NEXT_PLACE == WALL_CELL) || (NEXT_PLACE == SNAKE_BODY)) {
		printf("You fail!\n");
		return 0;
	}

	//�ƶ�����ʳ
	if (NEXT_PLACE == SNAKE_FOOD) {
		//������ʳ

		//��ʤ����
		if (snakeLength >= SNAKE_MAX_LENGTH) {
			printf("The snake is full.\nYou win!\n");
			return 0;
		}

		snakeMove(addX, addY, 1);
		put_money();
	}
	else //��������ʳ
		snakeMove(addX, addY, 0);

	return 1;
}

//��ʾ
void output(void) {
	// system("clear"); linux
	system("cls");//windos
	printf("------------------------̰����-------------------------\n");
	int temp1, temp2;
	for (temp1 = 0;temp1 < 12;temp1++) {
		for (temp2 = 0;temp2 < 12;temp2++) {
			printf("%c", map[temp1][temp2]);
		}
		printf("\n");
	}
}

//��Ϸ����
void gameover(void) {
	printf("Game Over\n");
}

//������
void operation(void) {
	srand((int)time(0));
	char op;
	int addX, addY;
	addX = addY = 0;

	while (1) {
		//�õ�������
		printf("Please input the operation(WASD/wasd): ");
		scanf("%c", &op);
		setbuf(stdin, NULL);

		//����
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

		//�����֧
		if (!judgeGameRun(addX, addY)) {
			break;
		}
		output();
	}
}
