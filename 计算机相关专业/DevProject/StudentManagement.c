#include<stdio.h>	/*标准输入输出*/
#include<stdlib.h>	/*屏幕操作函数，用system"cls"*/
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/
#include"manage_system_head.h"
//学生记录文件建立 
Student *init_s(){
	Student *head, *p, *last;	//定义建立学生记录的工作指针
	Student s;
	char c; 		//定义变量c作为选择是否新建文件的提示变量 
	FILE *fp;
	char fname[20];		//定义打开文件名地址存储的字符数组 
	int i;
	system("cls");
	printf("do you creat new file(y/n)?");
	c=getchar();
	getchar();
	if(c=='Y'||c=='y'){	//如果是y，则新建文件 
		printf("input new student filename:");
		gets(fname);	//输入文件名
		if((fp=fopen(fname, "wb"))==NULL){	//文件打开失败
			printf("can not open file.\n");
			return NULL;	//返回主调函数
		}
		do{	//输入多个学生信息存入磁盘 ，当编号为1，结束录入
			printf("input the student number:");
			scanf("%d", &s.snum);
			getchar();
			if((s.snum != -1)){		//如果学号不是-1，那么输入姓名。 
				printf("input the name :");
				gets(s.name);
				getchar();	//get name
				for(i=0; i<M; i++){		//同时给出学生其他信息的初始化 
					s.score[i].cp=NULL;
					s.score[i].sc=0;
				}
				s.sum=0;	//总成绩清空
				s.rank=-1;
				s.next=NULL;
				fwrite(&s, sizeof(Student), 1, fp);	//把建立的记录写入文件
			}
			else{	//如果输入的提示为-1 ,建立结束 
				break;
			}
		}while(1);
		fclose(fp);
	}
	head=(Student*)malloc(sizeof(Student));
	//建立（初始化）单链表头结点
	head->next=NULL;
	last=head;
	printf("\n open the student file, input the filename:");
	gets(fname);
	fp=fopen(fname, "rb");  //打开学生文件 
	if(fp==NULL){
		printf("\n Can not open file!\n");
		return NULL;
	}
	while(!feof(fp)){
		p=(Student *)malloc(sizeof(Student));	//建立结点
		if(fread(p, sizeof(Student ), 1, fp)==1){
			//一次从文件中读取一条学生的记录
			p->next=NULL;	//尾插法建立链表
			last->next=p;
			last=p;
		}
	}
	fclose(fp);
	last->next=NULL;	//最后一个结点指为空
	return head;	//返回读出数据库文件的指针
}

//学生记录的保存 
void save_s(Student *head){
	FILE *fp;
	Student *p;
	char bname[30];
	printf("input the saving file name:");
	gets(bname);
	fp=fopen(bname, "wb");	//以只写方式打开二进制文件 
	if(fp==NULL){	//打开文件失败 
		printf("\n open file error!\n");
		return;
	}
	p=head->next;	//当前链表中所有数据写入内存 
	while(p){
		fwrite(p, sizeof(Student), 1, fp);
		//每次写一条记录或一个节点到文件 
		p=p->next;
	}
	fclose(fp);
} 

//学生记录查询
int sear_s(Student *head){
	int select;	//1:按照学号查，2：按照姓名查， 其他; 返回 
	Student *p;
	int num;
	char str[30];
	int f=0;	//表明记录是否找到，作为函数的返回值 
	if(!head->next ){	//若链表为空 
		system("cls");
		printf("\n The student don't exist!\n");
		getchar();
		return 0;
		//return NULL;
	}
	system("cls");
	printf("\n  1.Search by student number  2.Search by student name  \n");
	printf("   Please choose [1,2]  ");
	scanf("%d", &select);
	getchar();
	switch(select){
		case 1:
			printf("input the student number:");
			scanf("%d", &num);
			p=head->next;
			while(p){
				if(p->snum == num){	//若找到输入的学号地址 
					printf("\n");
					printf(FORMAT, DATA);	//输出信息 
					getchar();
					f=1;	//更改条件 ，表明记录是否找到 
					break;
				}
				p=p->next;
			}
			getchar();
			break;	//结束case 分支 
		case 2:
			printf("input the student name:");
			gets(str);
			p=head->next;
			while(p){
				if(strcmp(p->name, str) == 0){	//姓名比较 
					f=1;	//更改标志 
					printf(FORMAT, DATA);
				}
				p=p->next;
			}
			break;
	}
	getchar();
	return f;
} 

//学生记录的追加，先判断，再添加 

//简单查询查找文件中是否有num学号相同的记录 
int check(Student *head, int num){	
	Student *p;
	p=head->next;
	while(p&&p->snum != num)	//如果结点不空，依次比较条件 
		p=p->next;	//指针后移 
	if(p)
		return 1;
	else 
		return 0;
} 

//学生记录添加 
Student *appe_s(Student *head){
	Student *p, *r;	//实现添加操作的临时结构体指针变量 
	int num;
	float x1, x2, x3;
	system("cls");
	r=head;
	while(r->next!=NULL){
		r=r->next;	//将指针移到链表末尾，准备添加记录 
	}
	while(1){
		/*一次可以输入多条记录，直到输入学号为-1时候结束记录结点添加操作；
		输入学号，保证该学号未被使用，若学号为-1，则退出添加记录操作		
		*/ 
		printf("input the student num(input -1 to finish):");
		p=(Student *) malloc(sizeof(Student));
		scanf("%d", &p->snum);
		getchar();
		
		while(check(head, p->snum)&& p->snum != -1){
			//学号不存在同时学号不为空，继续查询
			printf("input the student num:");
			scanf("%d", &p->snum);
			getchar() ;
		}
		
		if(p->snum==-1){	//输入为-1，则退出添加 
			printf("the insert is over, press any key ...\n");
			scanf("%d", &p->snum );
			getchar();
		}
		else{	//插入结点 
			printf("input the student name:");
			gets(p->name);
			printf("input the first term score:");
			scanf("%f%f%f", &x1, &x2, &x3);
			p->score[0].sc=x1;	//输入结点信息 
			p->score[1].sc=x2;
			p->score[2].sc=x3;
			p->sum=x1+x2+x3;
			p->next=NULL;
			r->next=p;		//插入单链表中 
			r=p; 
		}
	}
	flag=1;		//更改标记 
	system("cls");
	print_g(head);	//输出 
	save_s(head);
	return head;
}

Student *dele_s(Student *head){
	int select;
	Student *p, *r;
	char str[30];
	int num;
	if(head->next){		//如果链表无法打开 
		system("cls");
		printf("\n No student record!\n");
		return NULL;
	}
	system("cls");
	printf("\n   1. Delete by number   2. Delete by name\n");
	printf("     please choose [1, 2]:");
	scanf("%d", &select);
	if(select==1){	//按照学号查找 
		printf("input the student num:");
		scanf("%d", &num);
		r = head;
		p = head->next;		//r为中间变量，保存头结点 
		while(p && p->snum!=num){
			r=p;
			p=p->next;
		} 
		
		if(p){
			r->next=p->next;
			flag=1;
			free(p);
			printf("\n delete success!\n");
			getchar();
		}
		else{
			printf("\n Cannot find!\n");
			getchar();
		}
	}
	else if(select==2){		//先按姓名查询到该记录
		printf("input the student name:");
		gets(str);	//输入姓名信息 
		r=head;
		p=head->next;	//查找初始化 
		while(p&&strcmp(p->name, str)!=0){		 //循环比较查找记录 
			r=p;		//保存结点地址 
			p=p->next;	//结点指针后移 
		}
		if(p){
			r->next=p->next;	//将p所指结点从链表中去除 
			flag=1;
			free(p);	//释放内存空间 
			printf("\n delete success!\n");
			getchar();	
		}
		else
		printf("\n Cannot find.\n");
	}
	print_g(head);	//输出修改信息 
	getchar();
	return head; 
} 

//学生记录修改
Student *modi_s(Student *head){
	Student *p;
	float num;
	float x1, x2, x3;
	system("cls");
	printf("modify student recorder...\n");
	printf("input the student number that you want to modify:\n");
	scanf("%d", &num);
	getchar();
	p=head->next;
	while(p && p->snum!=num){	//查找是否存在 
		p=p->next;
	} 
	if(p){		//若p！=NULL表明已经找到结点 
		printf("input the student name:");
		gets(p->name);
		printf("input the first term score:");
		scanf("%f%f%f", x1, x2, x3);
		p->score[0].sc=x1;
		p->score[2].sc=x2;
		p->score[2].sc=x3;
		p->sum=x1+x2+x3;
		print_g(head);		//修改后的信息显示 
		flag=1;		//改变记录，更改标记 
		getchar(); 
	}
	else{
		printf("Cannot find record!\n");
		getchar();
	}
} 

