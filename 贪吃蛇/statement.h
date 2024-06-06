#pragma once
void Menu();//用于生成主菜单
void CreatMap();//用于生成游戏地图
void io_move(struct deltaxy**);//用于控制移动
void game_info();//用于绘制游戏说明
void draw_snake(struct snake* head);//用于绘制蛇身
struct snake* initsnake(struct snake** P_head);//用于初始化蛇
struct snake* add_body(int x, int y);//用于添加蛇身节点（在初始化蛇和吃到食物增长蛇身时用到)
void find_nail(struct snake* head, struct snake** prev, struct snake** current);//用于寻找蛇的最后和倒数第二个节点的地址
void delete_nail(struct snake** prev, struct snake** current);//与find_nail()一起使用，用于删除蛇的最后一个节点
void dynamic_display();//用于动态显示，
void add_newhead(struct snake** old_head);//用于在蛇头前添加新的节点，与delete_nail()一起共同用于蛇的蠕动
void random_food(struct food**);//用于随机生成不与蛇身重合的食物
int CheckSnakeAlive();//用于检测小蛇是否撞墙和自食其身并返回存活信息//0死亡,1存活
void GameOver();//用于显示游戏结束画面
void GameLoop();//用于游戏循环，最核心的代码，嵌套多个自定义函数
void DeleteSnake(struct snake* head);//重新游戏时删除之前的小蛇
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
//***************运行前请把项目->属性->字符集设置为“使用多字节字符集”，以及项目->属性->C/C++->代码生成->安全检查设置为“禁用安全检查（GS-）”*************
//***************运行前以管理员方式打开VS，并切换至英文输入法********************