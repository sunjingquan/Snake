#pragma once
void Menu();//�����������˵�
void CreatMap();//����������Ϸ��ͼ
void io_move(struct deltaxy**);//���ڿ����ƶ�
void game_info();//���ڻ�����Ϸ˵��
void draw_snake(struct snake* head);//���ڻ�������
struct snake* initsnake(struct snake** P_head);//���ڳ�ʼ����
struct snake* add_body(int x, int y);//�����������ڵ㣨�ڳ�ʼ���ߺͳԵ�ʳ����������ʱ�õ�)
void find_nail(struct snake* head, struct snake** prev, struct snake** current);//����Ѱ���ߵ����͵����ڶ����ڵ�ĵ�ַ
void delete_nail(struct snake** prev, struct snake** current);//��find_nail()һ��ʹ�ã�����ɾ���ߵ����һ���ڵ�
void dynamic_display();//���ڶ�̬��ʾ��
void add_newhead(struct snake** old_head);//��������ͷǰ����µĽڵ㣬��delete_nail()һ��ͬ�����ߵ��䶯
void random_food(struct food**);//����������ɲ��������غϵ�ʳ��
int CheckSnakeAlive();//���ڼ��С���Ƿ�ײǽ����ʳ�������ش����Ϣ//0����,1���
void GameOver();//������ʾ��Ϸ��������
void GameLoop();//������Ϸѭ��������ĵĴ��룬Ƕ�׶���Զ��庯��
void DeleteSnake(struct snake* head);//������Ϸʱɾ��֮ǰ��С��
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
//***************����ǰ�����Ŀ->����->�ַ�������Ϊ��ʹ�ö��ֽ��ַ��������Լ���Ŀ->����->C/C++->��������->��ȫ�������Ϊ�����ð�ȫ��飨GS-����*************
//***************����ǰ�Թ���Ա��ʽ��VS�����л���Ӣ�����뷨********************