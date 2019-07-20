#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "common.h"
#include "stu.h"

//初始化
void init(){
	//打开文件
	if( (fp=fopen(FILENAME, "rb+")) == NULL && (fp=fopen(FILENAME, "wb+")) == NULL ){
		pause("Error on open %s file!", FILENAME);
		exit(EXIT_FAILURE);
	}

	stuSize = sizeof(STU);
	fileSize = getFileSize(fp);
	stuIndex = NULL;

	updateIndex();
}

//添加学生信息
void addStuInfo(){
	STU stu;
	int i, nPreEleCount = 0;

	getStuID(&stu.id);
	getStuName(stu.name);
	getStuSex(stu.sex);
	getStuAge(&stu.age);
	getStuMath(&stu.math);
	getStuCN(&stu.cn);
	getStuEN(&stu.en);

	for(i=0; i<stuCount; i++){
		if(stu.id == stuIndex[i]){
			pause("错误：该学生信息已存在，无需重复添加！按任意键返回...");
			return;
		}else if(stu.id > stuIndex[i]){
			nPreEleCount++;
		}else{
			break;
		}
	}

	finsert(fp, nPreEleCount*stuSize, &stu, stuSize);
	updateIndex();
	pause("提示：添加成功！按任意键返回...");
}

//删除学生信息
void deleteStuInfo(){
	STU stu;
	int i, index = -1;

	getStuID(&stu.id);
	for(i=0; i<stuCount; i++){
		if(stu.id == stuIndex[i]){
			index = i;
		}else if(stu.id < stuIndex[i]){
			break;
		}
	}

	if(index<0){
		pause("错误：该学生信息不存在，删除失败！按任意键返回...");
		return;
	}else{
		fdelete(fp, index*stuSize, stuSize);
	}

	updateIndex();
	pause("提示：删除成功，按任意键返回...");
}

//修改学生信息
void alterStuInfo(){
	STU stu;
	int i, index = -1;

	getStuID(&stu.id);
	for(i=0; i<stuCount; i++){
		if(stu.id == stuIndex[i]){
			index = i;
		}else if(stu.id < stuIndex[i]){
			break;
		}
	}

	if(index<0){
		pause("错误：该学生信息不存在，修改失败！按任意键返回...");
		return;
	}else{
		getStuName(stu.name);
		getStuSex(stu.sex);
		getStuAge(&stu.age);
		getStuMath(&stu.math);
		getStuCN(&stu.cn);
		getStuEN(&stu.en);
		fseek(fp, index*stuSize, SEEK_SET);
		fwrite(&stu, stuSize, 1, fp);
	}
	pause("提示：修改成功，按任意键返回...");
}

//根据ID查询学生信息
void findStuByID(){
	STU stu;
	int i, index = -1;
	float total;

	getStuID(&stu.id);
	for(i=0; i<stuCount; i++){
		if(stu.id == stuIndex[i]){
			index = i;
		}else if(stu.id < stuIndex[i]){
			break;
		}
	}
	if(index<0){
		pause("错误：该学生信息不存在，查询失败！按任意键返回...");
		return;
	}else{
		fseek(fp, stuSize*index, SEEK_SET);
		fread(&stu, stuSize, 1, fp);
		total = stu.math + stu.cn + stu.en;
		printf("-----------------------------------------------------------------------\n");
		printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
		printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
		printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, total);
		printf("-----------------------------------------------------------------------\n");
		pause("\n按任意键返回...");
	}
}

//根据姓名查询学生信息
void findStuByName(){
	STU stu;
	int n = 0;  //匹配到几条学生记录
	float total;
	char name[20];

	getStuName(name);
	fseek(fp, 0, SEEK_SET);
	while(fread(&stu, stuSize, 1, fp)){
		if(strstr(stu.name, name)){
			n++;
			total = stu.math + stu.cn + stu.en;
			if(n==1){
				printf("-----------------------------------------------------------------------\n");
				printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
				printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
			}
			printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, total);
		}
	}

	if(n>0){
		printf("-----------------------------------------------------------------------\n");
		pause("\n共查询到%d条记录。按任意键返回...", n);
	}else if(n==0){
		pause("错误：没有查询到相关记录！按任意键返回...");
	}
}

//根据成绩查询学生信息
void findStuByScores(int flag){
	STU stu;
	int n = 0;  //匹配到几条学生记录
	float *scores = NULL;  //当前学生的成绩
	float min = 0, max = 0;  //用户输入的最高分和最低分
	int MAX = 0;  //common.h 中指定的成绩最高分
	char *courseName = NULL;  //科目名称
	float total = 0;  //当前学生总分

	if(flag == FIND_BY_MATH){
		courseName = "数学成绩";
		MAX = MAX_STU_MATH;
		scores = &stu.math;
	}else if(flag == FIND_BY_CN){
		courseName = "语文成绩";
		MAX = MAX_STU_CN;
		scores = &stu.cn;
	}else if(flag == FIND_BY_EN){
		courseName = "英语成绩";
		MAX = MAX_STU_EN;
		scores = &stu.en;
	}else if(flag == FIND_BY_TOTAL){
		courseName = "总成绩";
		MAX = MAX_STU_MATH + MAX_STU_CN + MAX_STU_EN;
		scores = &total;
	}else{
		return;
	}

	while(1){
		printf("要查询的%s的范围：", courseName);
		fflush(stdin);
		scanf("%f %f", &min, &max);
		if(min<0 || min>MAX || max<0 || max>MAX){
			pause("错误：%s的取值范围为0~%d！按任意键重新输入...", courseName, MAX);
			continue;
		}
		if(min>max){
			pause("错误：最高分要高于最低分！按任意键重新输入...");
			continue;
		}
		break;
	}

	fseek(fp, 0, SEEK_SET);
	while(fread(&stu, stuSize, 1, fp)){
		total = stu.math + stu.cn + stu.en;

		if(min <= *scores && *scores <= max){
			n++;
			if(n==1){
				printf("-----------------------------------------------------------------------\n");
				printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
				printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
			}
			printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, total);
		}
	}

	if(n>0){
		printf("-----------------------------------------------------------------------\n");
		pause("\n共查询到%d条记录。按任意键返回...", n);
	}else if(n==0){
		pause("错误：没有查询到相关记录！按任意键返回...");
	}
}

//显示所有学生信息
void showAllStu(){
	STU stu;
	//stuCount = getStuCount();
	float mathTotal = 0, cnTotal = 0, enTotal = 0, ageTotal = 0, totalStu = 0, allTotal = 0;
	int manTotal = 0, womanTotal = 0, n = 0;

	if(!stuCount){
		pause("还未添加任何学生信息，按任意键返回...");
		return;
	}
	fseek(fp, 0, SEEK_SET);
	system("cls");
	printf("-----------------------------------------------------------------------\n");
	printf("  学号  |  姓名  |  性别  |  年龄  |  数学  |  语文  |  英语  | 总成绩\n");
	printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
	while( fread(&stu, stuSize, 1, fp) ){
		totalStu = stu.math + stu.cn + stu.en;
		allTotal += totalStu;
		mathTotal += stu.math;
		cnTotal += stu.cn;
		enTotal += stu.en;
		ageTotal += stu.age;
		n++;
		if(strcmp(stu.sex, "男")){
			womanTotal++;
		}else{
			manTotal++;
		}
		printf("   %.2d   | %-6s |   %-3s  |   %-3d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", stu.id, stu.name, stu.sex, stu.age, stu.math, stu.cn, stu.en, totalStu);
	}
	printf("--------+--------+--------+--------+--------+--------+--------+--------\n");
	printf("   --   |   --   | %2d/%-2d  | %-6.2f | %-6.2f | %-6.2f | %-6.2f | %-6.2f\n", manTotal, womanTotal, ageTotal/stuCount, mathTotal/stuCount, cnTotal/stuCount, enTotal/stuCount, allTotal/stuCount);
	printf("-----------------------------------------------------------------------\n");
	pause("\n共有%d条学生信息，按任意键返回...", n);
}

//更新索引
void updateIndex(){
	int i;
	free(stuIndex);
	stuCount = getFileSize(fp)/stuSize;
	stuIndex = (int*)malloc(stuCount*sizeof(int));
	for(i=0; i<stuCount; i++){
		fseek(fp, stuSize*i, SEEK_SET);
		fread(&stuIndex[i], sizeof(int), 1, fp);
	}
}

//输入学生ID
void getStuID(int *id){
	while(1){
		printf("输入学号：");
		fflush(stdin);
		scanf("%d", id);
		if(checkStuID(*id)){
			break;
		}
	}
}

//输入学生姓名
void getStuName(char name[]){
	while(1){
		printf("输入姓名：");
		fflush(stdin);
		scanf("%s", name);
		if(checkStuName(name)){
			break;
		}
	}
}

//输入学生性别
void getStuSex(char sex[]){
	while(1){
		printf("输入性别：");
		fflush(stdin);
		scanf("%s", sex);
		if(checkStuSex(sex)){
			break;
		}
	}
}

//输入学生年龄
void getStuAge(int *age){
	while(1){
		printf("输入年龄：");
		fflush(stdin);
		scanf("%d", age);
		if(checkStuAge(*age)){
			break;
		}
	}
}

//输入数学成绩
void getStuMath(float *math){
	while(1){
		printf("数学成绩：");
		fflush(stdin);
		scanf("%f", math);
		if(checkStuMath(*math)){
			break;
		}
	}
}

//输入语文成绩
void getStuCN(float *cn){
	while(1){
		printf("语文成绩：");
		fflush(stdin);
		scanf("%f", cn);
		if(checkStuCN(*cn)){
			break;
		}
	}
}

//输入英语成绩
void getStuEN(float *en){
	while(1){
		printf("英语成绩：");
		fflush(stdin);
		scanf("%f", en);
		if(checkStuEN(*en)){
			break;
		}
	}
}

//检查学生ID是否正确
int checkStuID(int stuID){
	if(stuID <= 0 || stuID > MAX_STU_ID){
		printf("错误：学号必须是大于0且小于等于%d的整数！\n", MAX_STU_ID);
		return 0;
	}
	return 1;
}

//检查学生姓名是否正确
int checkStuName(char name[]){
	if(strlen(name) > MAX_STU_NAME){
		printf("错误：名字的最大长度不超过%d个字节！\n", MAX_STU_NAME);
		return 0;
	}
	return 1;
}

//检查学生性别是否正确
int checkStuSex(char sex[]){
	if(strcmp(sex, "男") && strcmp(sex, "女")){
		printf("错误：性别只能是男或女！\n");
		return 0;
	}else{
		return 1;
	}
}

//检查学生年龄是否正确
int checkStuAge(int age){
	if(age <=0 || age > MAX_STU_AGE){
		printf("错误：年龄的取值范围为1~%d！\n", MAX_STU_AGE);
		return 0;
	}
	return 1;
}

//检查数学成绩是否正确
int checkStuMath(float math){
	if(math < 0 || math > MAX_STU_MATH){
		printf("错误：数学成绩的取值范围为0~%d！\n", MAX_STU_MATH);
		return 0;
	}
	return 1;
}

//检查语文成绩是否正确
int checkStuCN(float cn){
	if(cn < 0 || cn > MAX_STU_CN){
		printf("错误：语文成绩的取值范围为0~%d！\n", MAX_STU_CN);
		return 0;
	}
	return 1;
}

//检查英语成绩是否正确
int checkStuEN(float en){
	if(en < 0 || en > MAX_STU_EN){
		printf("错误：英语成绩的取值范围为0~%d！\n", MAX_STU_EN);
		return 0;
	}
	return 1;
}