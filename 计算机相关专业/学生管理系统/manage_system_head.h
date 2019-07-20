#include<stdio.h>	/*标准输入输出*/
#include<stdlib.h>	/*屏幕操作函数，用system"cls"*/
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/
#include <time.h>

#define M 3	//定义课程数目 
#define TIME 50 //延时长短

#define FORMAT "|%10d|%15s|%.2f|%.2f|%.2f|%.2f|  %d |\n"	//输出学生信息的格式 
#define DATA p->snum, p->name, p->score[0].sc, p->score[1].sc, p->score[2].sc, p->sum, p->rank
//extern int menu(int m); 
//int flag=0;
int topsort[M];
//定义数组，存放拓扑排序以后课程在数组中的存储位置 

typedef struct cnode{ //定义选课的先决条件结点
	int num;	   	//选课前应先学习的课程顺序
	struct cnode *next;		//下一个结点
}Cnode;

FILE *result, *source, *recall;

char account[25]={0};
char password[25]={0};//存放输入的密码和账户名称

char rcode[5];
//验证码产生函数

typedef struct{		//定义课程项目
	int cnum;		//课程号
	char cname[20];	//课程名称
	int credit;		//学分
//	int indegree;	//
	Cnode *first;	//头结点
}Cour, Course[M];	//定义课程项目数据结构

//Course[0]={.cnum=1,
//	.cname="数学",
//	.credit=5
//}
//Course[1]={.cnum=2,
//	.cname="英语",
//	.credit=5
//}
//Course[2]={.cnum=3,
//	.cname="C语言",
//	.credit=5
//}
 Cour *hg, *hc;
typedef struct{	//定义成绩数据结构
	Cour *cp;	//指向课程的指针
	float sc;	//该课程的成绩
}Score; 		//成绩数据结构

typedef struct snode{	//定义表示学生结点
	int  snum;		//学号
	char name[20];		//姓名
	Score score[M];		//成绩
	float sum;			//总分
	float average;		//平均分
	int rank;			//名次
	struct snode *next;	//下一个结点地址
}Student; 				//学生成绩数据结构，Student相当于struct snode，  

//加密和解密 
void RandomCode(char Rcode[]); 
void encode();
void decode();/*解密*/
 
//输出菜单 
int menu(int m);
int print(); 

//注册和登录
void register2();
void login();
 
//成绩管理系统
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

