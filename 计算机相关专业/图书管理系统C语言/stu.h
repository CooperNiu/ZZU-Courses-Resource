#ifndef _STU_H
#define _STU_H

#include "common.h"

#define FIND_BY_MATH 1
#define FIND_BY_CN 2
#define FIND_BY_EN 3
#define FIND_BY_TOTAL 4

FILE *fp;  //文件指针
int stuSize;  //一条学生信息的长度（字节数）
int stuCount;  //总共有多少条学生信息
long fileSize;  //文件长度（占用的字节数）
int *stuIndex;  //学生信息索引

//学生信息结构体
typedef struct _STU{
	int id;  //学号
	char name[20];  //姓名
	char sex[4];  //性别
	int age;  //年龄
	float math;  //数学成绩
	float cn;  //语文成绩
	float en;  //英语成绩
}STU;

//初始化
extern void init();

//学生信息增删改查
extern void addStuInfo();
extern void deleteStuInfo();
extern void alterStuInfo();
extern void findStuByID();
extern void findStuByName();
extern void findStuByScores(int flag);
extern void showAllStu();

//更新索引
extern void updateIndex();

//校验学生信息
extern int checkStuID(int stuID);
extern int checkStuName(char name[]);
extern int checkStuSex(char sex[]);
extern int checkStuAge(int age);
extern int checkStuMath(float math);
extern int checkStuCN(float cn);
extern int checkStuEN(float en);

//输入学生信息
extern void getStuID(int *id);
extern void getStuName(char name[]);
extern void getStuSex(char sex[]);
extern void getStuAge(int *age);
extern void getStuMath(float *math);
extern void getStuCN(float *cn);
extern void getStuEN(float *en);

#endif