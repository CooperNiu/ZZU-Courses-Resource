#include<stdio.h>	/*标准输入输出*/
#include<stdlib.h>	/*屏幕操作函数，用system"cls"*/
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/
#define M 3	//定义课程数目 
#define FORMAT "|%6d|%15s|%.2f|%.2f|%.2f|%.2f|%d|\n"	//输出学生信息的格式 
#define DATA p->snum, p->name, p->score[0].sc, p->score[1].sc, p->score[2].sc, p->sum, p->rank

int flag=0;
int topsort[M];
//定义数组，存放拓扑排序以后课程在数组中的存储位置 

typedef struct cnode{ //定义选课的先决条件结点
	int num;	   	//选课前应先学习的课程顺序
	struct cnode *next;		//下一个结点
}Cnode;

typedef struct{		//定义课程项目
	int cnum;		//课程号
	char cname[20];	//课程名称
	int credit;		//学分
	int indegree;	//
	Cnode *first;	//表结点的头结点
}Cour;				//定义课程项目数据结构

typedef Cour Course[M];

typedef struct{	//定义成绩数据结构
	Cour *cp;	//指向课程的指针
	float sc;	//该课程的成绩
}Score; 		//成绩数据结构

typedef struct snode{	//定义表示学生结点
	int snum;			//学号
	char name[20];		//姓名
	Score score[M];		//成绩
	float sum;			//总分
	float average;		//	平均分
	int rank;			//名次
	struct snode *next;	//下一个结点地址
}Student; 				//学生成绩数据结构

//课程管理实现
void init_c(Course *);	/*课程数据结构建立以及课程录入或打开，
						保存课程原始记录到文件*/
void sort_c(Course *);	/*所有课程的上课顺序*/
void plan_c(Course *); 	/*每学期上课安排*/

//成绩管理系统实现
void input_g(Student *, Cour *);	//成绩录入
void ave_g(Student*);		//成绩总和计算
void sort_g(Student*); 		//成绩排序，同时保存排序文件
void filt_g(Student*);		//成绩分类搜索
void print_g(Student*);	//成绩输出
void gotoxy(int x,int y);    //光标移动函数

//学生管理系统
Student *init_s();		//学生记录初始化，第一次建立保存，也可以打开
void manag_s();			//学生成绩管理
int sear_s(Student *);	//学生记录查询
Student *appe_s(Student *);//学生记录添加
Student *modi_s(Student*);//学生记录修改
Student *dele_s(Student*);//学生记录删除
void save_s(Student *);//学生记录保存


//#include<stdio.h>
//#include<string.h>
//#include<windows.h>
//#include<stdlib.h>
//#include<malloc.h>
//光标移动函数  参考网上资料 
//void gotoxy(int x,int y)   
//{
//    CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
//    HANDLE    hConsoleOut;
//    hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
//    GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
//    csbiInfo.dwCursorPosition.X = x;
//    csbiInfo.dwCursorPosition.Y = y;
//    SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition);
//}

