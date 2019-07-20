#include<stdio.h>	/*标准输入输出*/
#include<stdlib.h>	/*屏幕操作函数，用system"cls"*/
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/
#include"manage_system_head.h"

//成绩管理系统实现
void input_g(Student *head , Cour *hg){ // 成绩录入 
	Student *p;
	float x1, x2, x3;
	p=head->next;	//指向首元结点
	system("cls");
	while(p){
		printf("input the first term score:");
		scanf("%f%f%f", &x1, &x2, &x3);  //录入每个学生的学期成绩
		p->score[0].sc=x1;
		p->score[1].sc=x2;
		p->score[2].sc=x3;
		p->sum=x1+x2+x3;	//计算成绩和 
		p->score[0].cp=hg;	//该课程的课程信息 
		p->score[0].cp=hg+1;
		p->score[0].cp=hg+2;
		p=p->next;		//指针后移 
	} 
	save_s(head);
	getchar(); 
} 

//计算每一科目的平均成绩
void ave_g(Student *head){	 
	Student *p, *q;	
	int i, n=0;		//定义变量n统计每门课程参考的人数 
	float sa=0;		//定义变量sa计算课程的平均值 
	system("cls");
	q=head->next;	//设定指针变量保存链表中某个结点的地址可以访问课程信息 
	for(i=0; i<M; i++){	//访问M门课程 
		sa=0;	//每一门课程计算前变量初始化 
		n=0;	 
		p=head->next;	//p指向首元结点
		while(p){		//访问每个学生的该门课程  
			n++;	//统计 
			sa+=p->score[i].sc;	//课程值累加 
			p=p->next;
		}
		sa=sa/n;	//计算平均值 
		printf("%6s average %.2f\n", q->score[i].cp->cname, sa);
		//输出课程平均值 ，其中表达式q->score[i].cp->cname中 q->score[i]访问成绩域数组中第i 个元素，
		//而 q->score[i].cp则访问成绩记录中的指针域，q->score[i].cp->cname 访问顶点中的cname成员信息。 
	}
	getchar();
}

//成绩排序 
void sort_g(Student *head){
	Student *p, *q, *r, *u;	//定义排序的工作指针 
	int re = 1;		//定义变量表示名次计算 
	p=head->next ;	//指向首元结点 
	head->next=NULL;	//置空链表 
	while(p){	//当链表尚未到尾，p为工作指针 
		r=head;	//保存头结点地址 
		q=head->next;
		while(q&&q->sum >= p->sum){	//查p结点在链表 
			r=q;
			q=q->next;
		}
		u=p->next;
		p->next=r->next;	//将p结点接入链表中 
		r->next=p;	//r是q的前缀， u是下个待插入结点的指针 
		p=u;
	}
	p=head->next;	//指向首元结点 
	while(p){	//访问链表中的每个结点 
		p->rank=re++;	//给出学生记录的名次 
		p=p->next;
	}
	print_g(head);		//输出信息 
	flag=1;
	save_s(head);
	getchar();
}

//分类统计成绩分布情况 
//把统计的各个分数段设计成函数，利用菜单管理各个函数 
void class_1(Student *h){	//大于等于80分的记录 
	Student *p;	//定义工作指针 
	int i;
	p=h->next;	//指向首元结点 
	system("cls");
	printf("|--nubmber--|--name--|----subject----|----score----|\n");
	//输出界面头
	 
	while(p!=NULL){	//结点访问不为空 
		for(i=0; i<M; i++){	//访问每一个学生每门课的成绩 
			if(p->score[i].sc>=80){	//成绩大于等于80 
				printf("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
			p=p->next;	//指向下一个记录 
		}
		printf("\n\npress any key ...");
		getchar();
	}
}

void class_2(Student *h){
	Student *p;
	int i;
	p=h->next;
	system("cls");
	printf("|--nubmber--|--name--|----subject----|----score----|\n");
	while(p!=NULL){
		for(i=0; i<M; i++){
			if(p->score[i].sc>=60&&p->score[i].sc<=79){
				printf("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
			p=p->next;	//指向下一个记录
		}
		printf("\n\npress any key ...");
		getchar();
	}
}

void class_3(Student *h){
	Student *p;
	int i;
	p=h->next;
	system("cls");
	printf("|--nubmber--|--name--|----subject----|----score----|\n");
	while(p!=NULL){
		for(i=0; i<M; i++){
			if(p->score[i].sc<60){
				printf("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
			p=p->next;	//指向下一个记录
		}
		printf("\n\npress any key ...");
		getchar();
	}
} 

//成绩分类搜索 
void filt_g(Student *head){
	int select;
	char *m[5]={
		"*********** Display **********",	//定义菜单字符串数组 
		"1. .....80<= Record <= 100....",
		"2. .....60<= Record <  80.....",
		"3. .....No pass...............",
		"0. .....return................"};
	while(1){	//进入分类筛选界面 
		system("cls");
		select=menu(m, 5);	//调用分类筛选菜单 
		if(select==0)
			break;
		switch(select){	//调用子菜单函数 
			case 1:class_1(head); break;
			case 2:class_2(head); break;
			case 3:class_3(head); break; 
		}
	}
}

//成绩输出 
void print_g(Student *head){
	Student *p;
	system("cls");
	p=head->next;	//指向首元结点 
	printf("\n\n******************Student*******************\n");
	//输出标题头 
	printf("|No    |     name     |sc1|sc2|sc3|  sum  |rank|\n\n");
	while(p!=NULL){	//链表中的结点不为空 
		printf(FORMAT, DATA);	//输出相应的信息 
		p=p->next;		//指针后移 
	}
	printf("\n\n******************END*******************");
	getchar();
}

