#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "common.h"
#include "stu.h"

char printMainMenu();
char printSubMain();

int main(){
	int menuID;
	init();
	while(1){
		menuID = printMainMenu();
		switch(menuID){
			case '1': addStuInfo(); break;
			case '2': deleteStuInfo(); break;
			case '3': alterStuInfo(); break;
			case '4': 
				while(1){
					menuID = printSubMain();
					switch(menuID){
						case '1': findStuByID(); break;
						case '2': findStuByName(); break;
						case '3': findStuByScores(FIND_BY_MATH); break;
						case '4': findStuByScores(FIND_BY_CN); break;
						case '5': findStuByScores(FIND_BY_EN); break;
						case '6': findStuByScores(FIND_BY_TOTAL); break;
					}
					if(menuID=='0') break;
				}
				break;
			case '5': showAllStu(); break;
			case '0': exit(EXIT_SUCCESS);
		}
	}
	fclose(fp);
	free(stuIndex);
    return 0;
}

//打印主菜单
char printMainMenu(){
	char menuID;
	system("cls");
	printf("***********欢迎使用学生信息管理系统（当前共有%02d名学生）***********\n", stuCount);
	printf("*                                                                *\n");
	printf("*                ---------------------------------               *\n");
	printf("*                |   Powered By c.biancheng.net  |               *\n");
	printf("*                ---------------------------------               *\n");
	printf("*                                                                *\n");
	printf("*                1)添加学生信息                                  *\n");
	printf("*                2)删除学生信息(根据学号)                        *\n");
	printf("*                3)修改学生信息(根据学号)                        *\n");
	printf("*                4)查询学生信息                                  *\n");
	printf("*                5)显示所有学生信息以及统计信息                  *\n");
	printf("*                0)退出软件                                      *\n");
	printf("*                                                                *\n");
	printf("******************************************************************\n");
	fflush(stdin);
	menuID = getch();
	return menuID;
}

//打印子菜单
char printSubMain(){
	char menuID;
	system("cls");
	printf("*****************查询学生信息（当前共有%02d名学生）*****************\n", stuCount);
	printf("*                                                                *\n");
	printf("*                1)根据学号查询                                  *\n");
	printf("*                2)根据姓名查询                                  *\n");
	printf("*                3)根据数学成绩查询                              *\n");
	printf("*                4)根据语文成绩查询                              *\n");
	printf("*                5)根据英语成绩查询                              *\n");
	printf("*                6)根据总成绩查询                                *\n");
	printf("*                0)返回主菜单                                    *\n");
	printf("*                                                                *\n");
	printf("******************************************************************\n");
	fflush(stdin);
	menuID = getch();
	return menuID;
}