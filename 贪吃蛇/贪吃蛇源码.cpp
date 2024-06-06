#include<stdio.h>//����sprintf()��������int���ͷ�����������
#include<graphics.h>//���ڳ�ʼ�����ڣ�������Ϸ
#include"statement.h"//�Լ������ͷ�ļ��������и����Զ��庯����������һЩ��
#include<conio.h>//����_getch()��������ʱ���ռ������벢���������Ҫ���»س����Ҳ��Ὣ������Ϣ��ʾ�ڿ���̨��
#include <ctime>//����ʹ��time()��������ȡʱ����Ϣ�����������������
#include<windows.h>//��������������Sleep()�����������Ͷ���,���ƺ����������ͷ�ļ�Ҳ������
struct snake
{
	int x;
	int y;
	struct snake* next;//��¼С�ߵ���һ�ڵ���Ϣ
};//��¼С��������Ϣ�Ľṹ��
struct deltaxy
{
	int dx;
	int dy;
};//��¼С��ÿ���ƶ��ľ���Ľṹ��
struct food
{
	int x;
	int y;
};//��¼ʳ���������Ϣ
struct snake* head = NULL;//��������ʼ��ͷ�ڵ�
struct deltaxy* deltaxy = (struct deltaxy*)malloc(sizeof(struct deltaxy));//�Ӷ����Ҹ�λ�ô�deltaxy�ƶ�������Ϣ
struct food* food = (struct food*)malloc(sizeof(struct food));//�Ӷ����Ҹ�λ�ô�food������Ϣ
struct snake* prev = NULL;//��β�����ڶ����ڵ�
struct snake* current = NULL;//��β�ڵ�
int score_value = 0;//��������ʼ������
int direction = RIGHT;//��¼������Ϣ
int main()
{
	int GameRunning = 1;//��Ϸ״̬��1��Ϸ���̴�0Ϊ�˳���Ϸ
	while (GameRunning)
	{
		deltaxy->dx = 10;//*****�˴���ʼ������*****
		deltaxy->dy = 0;//*****�˴���ʼ������*****
		Menu();
		int input = _getch();
		while (1)//����û�û�1��2ʱ�����µȴ������û�
		{
			if (input == '1')//��1��ʼ��Ϸ
			{
				GameLoop();
				break;//���ڻص����˵�
			}
			if (input == '2')//��2�˳���Ϸ
			{
				GameRunning = 0;
				break;
			}
			input = _getch();
		}
	}
	closegraph();
	return 0;
}
void Menu() //������
{
	initgraph(800, 600, NULL);
	setbkcolor(RGB(245, 245, 220));//���ñ�����ɫ
	cleardevice();
	settextcolor(100);
	settextstyle(50, 25, "");//�������ֽڿ��
	outtextxy(325, 100, "̰����");
	outtextxy(275, 250, "1.��ʼ��Ϸ");
	outtextxy(275, 350, "2.�˳���Ϸ");
}
void CreatMap()
{
	cleardevice();
	setcolor(0);
	rectangle(50, 550, 550, 50);
	line(600, 0, 600, 600);
}

void game_info()
{
	char score[10];
	sprintf(score, "%d", score_value);
	outtextxy(650, 100, "˵����");
	settextstyle(20, 10, "");
	outtextxy(640, 200, "��ʹ��W,A,S,D");
	outtextxy(620, 250, "����С�ߣ�Ŭ����");
	outtextxy(620, 300, "�ø��ߵķ����ɣ�");
	settextstyle(30, 15, "");
	outtextxy(50, 20, "�÷֣�");
	outtextxy(120, 20, score);
}


void draw_snake(struct snake* head)//��һ��С�ߵ�ͷ�����ܸ��㻭��������
{
	struct snake* p;
	p = head;
	setfillcolor(WHITE);
	while (NULL != p)//���������ӡС��
	{
		fillrectangle(p->x, p->y, p->x + 10, p->y + 10);
		p = p->next;
	}
}
struct snake* initsnake(struct snake** P_head)//���ڳ�ʼ����
{
	*P_head = add_body(260, 250);
	struct snake* body_1 = add_body(250, 250);
	struct snake* body_2 = add_body(240, 250);
	(*P_head)->next = body_1;
	body_1->next = body_2;
	return *P_head;

}
struct snake* add_body(int x, int y)//��������С�ߵ�һ������
{
	struct snake* newbody = (struct snake*)malloc(sizeof(struct snake));
	newbody->x = x;
	newbody->y = y;
	newbody->next = NULL;
	return newbody;
}

void find_nail(struct snake* head, struct snake** prev, struct snake** current)
{
	*current = head;
	while ((*current)->next != NULL)//"->"�����ȼ�����"*"
	{
		*prev = *current;
		*current = (*current)->next;
	}
}
void delete_nail(struct snake** prev, struct snake** current)
{
	(*prev)->next = NULL;
	free(*current);
}
void dynamic_display()
{
	if (head->x != food->x || head->y != food->y)//��ͷ����ʳ���غ���ɾȥβ�ڵ�
	{
		find_nail(head, &prev, &current);//�ҵ�����������͵����ڶ����ڵ�
		delete_nail(&prev, &current);//ɾ���ߵ����һ���ڵ�
	}
	else
	{
		random_food(&food);
		score_value += 10;
	}
	CreatMap();//ע����Ƕclear(),��game_info�ȵ÷���������
	game_info();
	add_newhead(&head);//�ߵ��䶯֮��ͷ��ǰ�ƶ�
	draw_snake(head);
	setfillcolor(RED);
	fillrectangle(food->x, food->y, food->x + 10, food->y + 10);
	Sleep(100);
}
void add_newhead(struct snake** old_head)
{
	struct snake* new_head = add_body((*old_head)->x + deltaxy->dx, (*old_head)->y + deltaxy->dy);
	new_head->next = *old_head;//��ͷnextָ����ͷ
	*old_head = new_head;//��ͷ�ĵ�ַ��ֵ����ͷλ��
}
void io_move(struct deltaxy** deltaxy)//���Ʒ���Ĵ���
{
	if (_kbhit())
	{
		int x = _getch();
		switch (x)
		{
		case UP:if (direction != DOWN)
		{
			(*deltaxy)->dx = 0; (*deltaxy)->dy = -10; direction = UP; break;
		}
		case DOWN:if (direction != UP)
		{
			(*deltaxy)->dx = 0; (*deltaxy)->dy = 10; direction = DOWN; break;
		}
		case LEFT:if (direction != RIGHT)
		{
			(*deltaxy)->dx = -10; (*deltaxy)->dy = 0; direction = LEFT; break;
		}
		case RIGHT:if (direction != LEFT)
		{
			(*deltaxy)->dx = 10; (*deltaxy)->dy = 0; direction = RIGHT; break;
		}
		}

	}
}
void random_food(struct food** P_food)
{
	struct snake* CheckFoodSnake = head;
	srand((unsigned)time(NULL));
	(*P_food)->x = rand() % 30 * 10 + 50;
	(*P_food)->y = rand() % 30 * 10 + 50;
	while (CheckFoodSnake != NULL)//���ڼ��ʳ���Ƿ�������������
	{
		if (CheckFoodSnake->x == (*P_food)->x && CheckFoodSnake->y == (*P_food)->y)
		{
			(*P_food)->x = rand() % 30 * 10 + 50;
			(*P_food)->y = rand() % 30 * 10 + 50;
			CheckFoodSnake = head;
		}
		CheckFoodSnake = CheckFoodSnake->next;
	}
	setfillcolor(RED);
	fillrectangle((*P_food)->x, (*P_food)->y, (*P_food)->x + 10, (*P_food)->y + 10);
}

int CheckSnakeAlive()
{
	if (head->x < 50 || head->y < 50 || head->x >= 550 || head->y >= 550)
		return 1;//��ζ����ײǽ��
	struct snake* check = head->next;//С�ߵ����ӽڵ�
	while (check != NULL)
	{
		if (head->x == check->x && head->y == check->y)
			return 2;//��ζ���߳Ե��Լ���
		else check = check->next;//��ʼ������Ƿ�Ե��ߵ���һ������
	}
	return 0;//���·���
}
void GameOver()
{
	cleardevice();
	settextstyle(50, 25, NULL);
	outtextxy(300, 100, "��Ϸ����");
}
void GameLoop()
{
	int LoopRunning = 1;
	while (LoopRunning)
	{
		deltaxy->dx = 10;//��ʼ������
		deltaxy->dy = 0;
		direction = RIGHT;
		CreatMap();//������Ϸ��ͼ
		game_info();//��Ϸ˵��
		draw_snake(initsnake(&head));//��ʼ����������
		random_food(&food);//��ʼ��ʳ��
		char score[10];//�洢����
		int SnakeAlive = 1;//С�ߴ��״̬��״̬0Ϊ������1Ϊ���
		while (SnakeAlive)//��ͼ�������̸��·����ж������ĺ���ѭ��
		{
			dynamic_display();//�ƹ��ߵ��䶯�ͽ������
			io_move(&deltaxy);//������
			switch (CheckSnakeAlive())//������Ⲣ������������
			{
			case 0:break;
			case 1:GameOver();  settextstyle(50, 20, ""); outtextxy(270, 200, "����ԭ��:ײǽ"); SnakeAlive = 0; break;//ײǽ
			case 2:GameOver();  settextstyle(50, 20, ""); outtextxy(240, 200, "����ԭ��:��ʳ����"); SnakeAlive = 0; break;//��ʳ����
			}
		}
		sprintf(score, "%d", score_value);//�ѷ������������printf("here");

		outtextxy(320, 300, "�÷֣�");
		outtextxy(420, 300, score);
		outtextxy(290, 400, "��1��������");
		outtextxy(270, 500, "��2�������˵�");
		char input = _getch();
		while (1)//����û�û�1��2ʱ�����µȴ������û�
		{
			if (input == '1')//��1���½�����Ϸ
			{
				DeleteSnake(head);//������Ϸʱɾ��֮ǰ��С��
				score_value = 0;
				break;
			}
			if (input == '2')//��2�ص��˵�
			{
				DeleteSnake(head);
				score_value = 0;
				LoopRunning = 0;
				break;
			}
			input = _getch();
		}
	}
}
void DeleteSnake(struct snake* head)//������Ϸʱɾ��֮ǰ��С��
{
	struct snake* p = head;//һ����ΪNULL���м����
	while (p != NULL)
	{
		p = head->next;
		free(head);
		head = p;
	}
}