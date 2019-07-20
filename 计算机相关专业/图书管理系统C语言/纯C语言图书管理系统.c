#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//图书结构体
struct Book{		//图书的结构体
	char isbn[10];	//图书的编号
	char name[20];	//图书的名字
	int type;		//图书的类型 1.编程类 2.小说类 3.杂志类
	int exist;		//图书是否被借出
}g_books[1000];

int g_count;	//当前图书的数量

//显示菜单，并返回选择的菜单号
int ShowMenu()
{
	int num;
	system("cls");
	printf("--------------------图书馆-----------------------\n");
	printf("\t\t1.添加图书\n");
	printf("\t\t2.查看图书\n");
	printf("\t\t3.借阅图书\n");
	printf("\t\t4.归还图书\n");
	printf("\t\t0.退出系统\n");
	printf("--------------------请选择-----------------------\n");
	while(scanf("%d", &num) != 1 || num < 0 || num > 4)
	{
		printf("你选择的菜单错误！按任意键重新选择。\n");
		system("pause");
		fflush(stdin);//清空输入缓冲区
	}
	return num;
}

//添加图书
void AddBook()
{
	printf("请输入图书的编号：");
	scanf(" %s", g_books[g_count].isbn);
	printf("请输入图书的名字：");
	scanf(" %s", g_books[g_count].name);
	printf("请输入图书的类型（1~3）：");
	while(scanf("%d", &g_books[g_count].type) != 1
		|| g_books[g_count].type < 1 || g_books[g_count].type > 3)
	{
		printf("对不起，你输入的图书类型不正确，请重新输入：");
		fflush(stdin);
	}
	g_books[g_count].exist = 1;
	++g_count;//把图书的数量增加一本
	printf("图书添加成功！\n");
}

//查看图书
void ShowBooks()
{
	int i;
	printf("\n本图书馆现有如下图书供你借阅。\n");
	for(i = 0; i < g_count; ++i)
	{
		printf("图书编号：%-10s, 图书名字：%-20s, 图书类型：%d\n", 
			g_books[i].isbn, g_books[i].name, g_books[i].type);
	}
}

int main()
{
	int quit = 0;
	while(quit == 0)
	{
		switch(ShowMenu())
		{
			case 0:
			quit = 1;
			break;
			case 1:
//			printf("添加图书！\n");
			AddBook();
			break;
			case 2:
//			printf("查看图书！\n");
			ShowBooks();
			break;
			case 3:
			printf("借阅图书！\n");
			break;
			case 4:
			printf("归还图书!\n");
			break;
		}
		system("pause");
	}
	
	return 0;
}
