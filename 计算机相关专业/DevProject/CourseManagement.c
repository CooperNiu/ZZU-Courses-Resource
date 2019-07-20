#include<stdio.h>	/*标准输入输出*/
#include<stdlib.h>	/*屏幕操作函数，用system"cls"*/
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/
#include"manage_system_head.h"
//课程信息表的建立 
void init_c(Course *g){
	//课程信息表结构的建立以及课程录入或者打开，保存原始记录文件
	FILE *fp;	//	设定指针保存课程信息文件地址 
	char fname[20]; 
	int i, j, k, n;
	Cnode *s=NULL;
	
	system("cls") ;
	
	printf("input the course information. \n");
	printf("|NO.  |Course | Credit|\n");
	
	for(i=0; i<M; i++){
		scanf("%d %s", &(g[i]->cnum), g[i]->cname);
		g[i]->indegree=0;
		g[i]->first=NULL; //清空顶点单链表指针 
		
	}
	
	printf("input number of course information :");
	scanf("%d", &n);
	getchar();
	//读入边数 
	printf("\n input information of course:\n");
	//建立每一个顶点的边的单链表 
	for(k=0; k<n; k++){
		scanf("%d%d", &i, &j);
		getchar();
		s=(Cnode *)malloc(sizeof(Cnode));
		//为单链表中结点分配空间
		s->num=j;
		//保存课程先决条件的下标 
		s->next=g[i]->first; 
		//头插法建立单链表
		g[i]->first=s;	
	} 
	printf("save the course to file, open the file.\n");
	gets(fname);
	getchar();
	if((fp=fopen(fname,"wb"))==NULL){
		//open the file
		printf("the file can not open.\n");
		exit(0);
	}
	for(i=0;i<M;i++){
		fwrite(g+i, sizeof(Cour), 1, fp);
		//save the record into the file
	}
	fclose(fp);
} 
	
//the order of all courses
void sort_c(Course *g){
	int ts=0;
	int i, j, top=1;
	//设定top描述栈顶元素的下标，即作为栈顶指针 
	Cnode *p;
	system("cls");
	for(i=0; i<M; i++){		
	//循环记录每个顶点的入度 
		p=g[i]->first;	//p指向每个顶点的单链表的头结点 
		while(p){
			//访问每个顶点的邻接链表，计算入度 
			g[p->num]->indegree++;
			p=p->next;
		} 
	} 
	for(i=0; i<M; i++){
		//如果某个顶点的入度为0， 那么把顶点的入度域更改为栈
		if(g[i]->indegree==0){
			g[i]->indegree=top;
			top=1;
		} 
	}
	
	printf("the course arrangement:\n");
	while(top!=-1){	
	//拓扑排序，条件是栈顶指针不是-1 
	//即栈顶元素不空
		j=top;
		top=g[top]->indegree; 
		printf("  %s \n", g[j]->cname);
		//访问入度为0的点
		topsort[ts++]=j;
		p=g[j]->first;
		while(p){
			//循环的作用是
			//减少以输出顶点为先决条件的结点的入度 
			i=p->num;
			g[i]->indegree==0;
			if(g[i]->indegree==0){
				//入度为0，继续进栈
				g[i]->indegree=top;
				top=i;
			}
			p=p->next;
		} 
		getchar();
		 
	} 
}

//每学期课程上课安排 
void plan_c(Course *g){
		int s=0;
		//定义变量计算总学分 
		char fname[20];
		FILE *fp;
		int i, j, k=0;
		system("cls");
		printf("open the course, input the filename \n");
		gets(fname);
		if((fp=fopen(fname,"rb"))==NULL){
			//打开文件，如果打开失败则返回 
			printf("the file can not open .\n");
			return;
		} 
		for(i=0; i<M; i++){
			fread(g+i, sizeof(Cour), 1, fp);
			//从文件中读出课程信息 
		}
		sort_c(g);
		//排序 
		for(i=0; i<M; i++){
			//计算学分和 
			s+=g[i]->credit; 
		} 
		s=s/4;
		j=1;
		for(i=0; i<M; i++){
			//平均分配各个学科 
			k+=g[topsort[i]]->credit;
			//计算读出课程的学分
			if(k<=s){
			//如果小于平均值，那么输出课程信息 
				printf("the %d term course:", j);
				//选中学期的课程
				printf("  %d  %s\n", g[topsort[i]]->cnum, g[topsort[i]]->cname); 
			} 
			else{
				//学分大于平均值
				j++;
				k=0; 
			}
		}
		getchar();
		getchar();
		fclose(fp);
	}

