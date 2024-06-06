#include<stdio.h>//用于sprintf()函数：把int类型分数存入数组
#include<graphics.h>//用于初始化窗口，绘制游戏
#include"statement.h"//自己定义的头文件，里面有各种自定义函数的声明和一些宏
#include<conio.h>//用于_getch()函数，即时接收键盘输入并输出，不需要按下回车，且不会将接收信息显示在控制台上
#include <ctime>//用于使用time()函数，获取时间信息用于生成随机数种子
#include<windows.h>//理论上这里面有Sleep()函数的声明和定义,但似乎不引入这个头文件也能运行
struct snake
{
	int x;
	int y;
	struct snake* next;//记录小蛇的下一节点信息
};//记录小蛇坐标信息的结构体
struct deltaxy
{
	int dx;
	int dy;
};//记录小蛇每次移动的距离的结构体
struct food
{
	int x;
	int y;
};//记录食物的坐标信息
struct snake* head = NULL;//声明并初始化头节点
struct deltaxy* deltaxy = (struct deltaxy*)malloc(sizeof(struct deltaxy));//从堆里找个位置存deltaxy移动距离信息
struct food* food = (struct food*)malloc(sizeof(struct food));//从堆里找个位置存food坐标信息
struct snake* prev = NULL;//蛇尾倒数第二个节点
struct snake* current = NULL;//蛇尾节点
int score_value = 0;//声明并初始化分数
int direction = RIGHT;//记录方向信息
int main()
{
	int GameRunning = 1;//游戏状态，1游戏进程存活，0为退出游戏
	while (GameRunning)
	{
		deltaxy->dx = 10;//*****此处初始化方向*****
		deltaxy->dy = 0;//*****此处初始化方向*****
		Menu();
		int input = _getch();
		while (1)//键盘没敲击1或2时，重新等待键盘敲击
		{
			if (input == '1')//扣1开始游戏
			{
				GameLoop();
				break;//用于回到主菜单
			}
			if (input == '2')//扣2退出游戏
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
void Menu() //主界面
{
	initgraph(800, 600, NULL);
	setbkcolor(RGB(245, 245, 220));//设置背景颜色
	cleardevice();
	settextcolor(100);
	settextstyle(50, 25, "");//中文两字节宽度
	outtextxy(325, 100, "贪吃蛇");
	outtextxy(275, 250, "1.开始游戏");
	outtextxy(275, 350, "2.退出游戏");
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
	outtextxy(650, 100, "说明：");
	settextstyle(20, 10, "");
	outtextxy(640, 200, "请使用W,A,S,D");
	outtextxy(620, 250, "操作小蛇，努力获");
	outtextxy(620, 300, "得更高的分数吧！");
	settextstyle(30, 15, "");
	outtextxy(50, 20, "得分：");
	outtextxy(120, 20, score);
}


void draw_snake(struct snake* head)//给一个小蛇的头，他能给你画出整条蛇
{
	struct snake* p;
	p = head;
	setfillcolor(WHITE);
	while (NULL != p)//遍历链表打印小蛇
	{
		fillrectangle(p->x, p->y, p->x + 10, p->y + 10);
		p = p->next;
	}
}
struct snake* initsnake(struct snake** P_head)//用于初始化蛇
{
	*P_head = add_body(260, 250);
	struct snake* body_1 = add_body(250, 250);
	struct snake* body_2 = add_body(240, 250);
	(*P_head)->next = body_1;
	body_1->next = body_2;
	return *P_head;

}
struct snake* add_body(int x, int y)//用于增加小蛇的一节身体
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
	while ((*current)->next != NULL)//"->"的优先级大于"*"
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
	if (head->x != food->x || head->y != food->y)//蛇头不与食物重合则删去尾节点
	{
		find_nail(head, &prev, &current);//找到蛇链表的最后和倒数第二个节点
		delete_nail(&prev, &current);//删掉蛇的最后一个节点
	}
	else
	{
		random_food(&food);
		score_value += 10;
	}
	CreatMap();//注意内嵌clear(),故game_info等得放在她后面
	game_info();
	add_newhead(&head);//蛇的蠕动之蛇头向前移动
	draw_snake(head);
	setfillcolor(RED);
	fillrectangle(food->x, food->y, food->x + 10, food->y + 10);
	Sleep(100);
}
void add_newhead(struct snake** old_head)
{
	struct snake* new_head = add_body((*old_head)->x + deltaxy->dx, (*old_head)->y + deltaxy->dy);
	new_head->next = *old_head;//新头next指向老头
	*old_head = new_head;//将头的地址赋值到新头位置
}
void io_move(struct deltaxy** deltaxy)//控制方向的代码
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
	while (CheckFoodSnake != NULL)//用于检测食物是否生成在蛇体内
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
		return 1;//意味着蛇撞墙了
	struct snake* check = head->next;//小蛇的身子节点
	while (check != NULL)
	{
		if (head->x == check->x && head->y == check->y)
			return 2;//意味着蛇吃到自己了
		else check = check->next;//开始检测蛇是否吃到蛇的下一节身体
	}
	return 0;//无事发生
}
void GameOver()
{
	cleardevice();
	settextstyle(50, 25, NULL);
	outtextxy(300, 100, "游戏结束");
}
void GameLoop()
{
	int LoopRunning = 1;
	while (LoopRunning)
	{
		deltaxy->dx = 10;//初始化方向
		deltaxy->dy = 0;
		direction = RIGHT;
		CreatMap();//建立游戏地图
		game_info();//游戏说明
		draw_snake(initsnake(&head));//初始化并画出蛇
		random_food(&food);//初始化食物
		char score[10];//存储分数
		int SnakeAlive = 1;//小蛇存货状态：状态0为死亡，1为存活
		while (SnakeAlive)//绘图，检测键盘更新方向，判断死亡的核心循环
		{
			dynamic_display();//掌管蛇的蠕动和界面更新
			io_move(&deltaxy);//检测键盘
			switch (CheckSnakeAlive())//死亡检测并区分死亡类型
			{
			case 0:break;
			case 1:GameOver();  settextstyle(50, 20, ""); outtextxy(270, 200, "死亡原因:撞墙"); SnakeAlive = 0; break;//撞墙
			case 2:GameOver();  settextstyle(50, 20, ""); outtextxy(240, 200, "死亡原因:自食其身"); SnakeAlive = 0; break;//自食其身
			}
		}
		sprintf(score, "%d", score_value);//把分数存进数组里printf("here");

		outtextxy(320, 300, "得分：");
		outtextxy(420, 300, score);
		outtextxy(290, 400, "按1重新来过");
		outtextxy(270, 500, "按2返回主菜单");
		char input = _getch();
		while (1)//键盘没敲击1或2时，重新等待键盘敲击
		{
			if (input == '1')//扣1重新进行游戏
			{
				DeleteSnake(head);//重新游戏时删除之前的小蛇
				score_value = 0;
				break;
			}
			if (input == '2')//扣2回到菜单
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
void DeleteSnake(struct snake* head)//重新游戏时删除之前的小蛇
{
	struct snake* p = head;//一个不为NULL的中间变量
	while (p != NULL)
	{
		p = head->next;
		free(head);
		head = p;
	}
}