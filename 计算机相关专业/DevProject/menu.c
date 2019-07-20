#include<stdio.h>	/*标准输入输出*/
#include<stdlib.h>	/*屏幕操作函数，用system"cls"*/
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/

#include"manage_system_head.h"	 
//开始界面设计 
int print(){
	int n;
	system("cls");	//代替clrscr()
	printf("\n\n");
	printf("\t*******************************************\n");
	printf("\t*                                         *\n");
	printf("\t*                                         *\n");
	printf("\t*------Welcome To Academic System---------*\n");
	printf("\t*                                         *\n");
	printf("\t*         1.Student Management            *\n");
	printf("\t*         2.Course Management             *\n");
	printf("\t*         0.Exit Management               *\n");
	printf("\t*                                         *\n");
	printf("\t*                                         *\n");
	printf("\t*******************************************\n");	
	printf("\t\tNow please select 1,2 or 0:");
	scanf("%d", &n);
	getchar();
	return n;
}

int menu(char **m, int n){
	int i;
	int select;
	system("cls");		//clear screen
//	gotoxy(1,1); 	//move cursor
	//textcolor();	//TC only
//	gotoxy(19,2); 	//move cursor
//	putchar(0xc9);	//print 左上角边框
//	for(i=1; i<44; i++)
//		putchar(0xcd); //输出上边框水平线
//	putchar(0xbb);//输出右上角边框
//	for(i=3;i<20;i++){
//		gotoxy(19,i);
//		putchar(0xba);//输出左垂直线
//		gotoxy(63,i);
//		putchar(0xba); //输出右垂直线
//	}
//	gotoxy(19,20);
//	putchar(0xc8);// 输出左下角边框
//	for(i=1;i<44;i++)
//		putchar(0xcd);//输出下边框水平线
//	putchar(0xbc);//输出右下角边框
//	window(20,3,62,19);//制作显示菜单窗口，大小根据菜单条数设计
	system("cls");//clear screen
	for(i=0;i<n;i++){	//	输出主菜单数组
//		gotoxy(8, i+4);
		printf("%s", m[i]);
	}
	//window(1,1,80,25);//恢复原窗口大小
//	gotoxy(10,21);	//移动光标
	do{
		printf("\n\t\t  Enter your choice(0~%d) to continue...", n-2);
		scanf("%d", &select);
		getchar();//输入选择项
	}while(select<0||select>n);//选择项不在0~13之间重输
	return select; //返回选择项，主函数根据该函数调用相应的函数
}


