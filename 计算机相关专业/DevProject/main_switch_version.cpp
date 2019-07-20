#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>	/*动态地址分配函数*/
#include<string.h>	/*字符串函数*/
#include<windows.h> /*包含gotoxy(x, y)函数*/
#include"manage_system_head.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int i;
	char *m1[]={
		"*****Student Management System*****\n",
		//定义菜单字符串数组
		"1.Init list\n",
		//初始化，从学生文件中打开学生记录
		"2.Score management\n",
		//学生成绩管理 
		"3.Search record(s)\n",
		//按照姓名查找记录
		"4.Append a record to list\n",
		//在文件中追加记录
		"5.Modify a record to list\n"
		//修改记录
		"6.Delete a record from list\n",
		//从表中删除记录
		"7.Save the file\n",
		//将单链表中的记录保存到文件中
		"0.Exit\n",
		//返回主界面 
	};
	
	char *m2[]={"*****Score Manegement System*****\n",
		//定义成绩管理菜单字符串数组 
		"1.Init list\n",
		//初始化，录入学生成绩到成绩文件 
		"2.Average of each subject\n",
		//每个学生总成绩排序 
		"3.Sort and order\n",
		//按照总成绩排序 
		"4.Filter score\n",
		//按照分数段分类浏览 
		"5.Display number and score\n",
		//浏览学生成绩 
		"0.Return \n"
		//返回学生管理菜单 
	};
	
	char *m3[]={"*****Course Manegement System*****\n",
		//定义课程管理菜单字符串数组 
		"1.Init list\n",
		//初始化，建立或读出所学课程表单
		"2.Sort of course\n",
		//所有课程上课顺序 
		"3.Plan\n",
		//每个学期课程安排 
		"0.Return\n"
		//返回主界面 
	} ;
	
	Student *head =NULL;
	//学生文件信息内存中存储为链表
	Course hc;
	//课程信息存储为图
	FILE *fp, fpc;
	//文件指针
	int s1, s2, s3;
	//保存选择结果变量
	char ch;
	//保存（y, Y, n, N）
	system("cls");
	//清屏
	
	//进度条,输入密码登录界面，第一次可以设置密码，之后就要输入密码才可以登录
	//而保存密码的文件需要加密！！！！！ 
	//忘记密码得有重设密码的功能
	int i,password=123456;
	printf("================================================\r");	
	for(i=0;i<50;i++)
	{
		printf("<");
		Sleep(50);//延迟500毫秒==0.5秒
	}
	printf("\n请输入操作系统密码:\n");
	do
	{
		scanf("%d",&password);
		if(password!=123456)
			printf("\n密码错误，请重新输入\n");
		else
			printf("\n密码正确，请等待...\n");
		
	}while(password!=123456);
	printf("================================================\r");	
	for(i=0;i<50;i++)
	{
		printf("<");
		Sleep(50);//延迟500毫秒==0.5秒
	}

	while(1){
		//开始界面有三个功能，可以管理学生成绩和课程记录以及退出界面
		system("cls");
		//清屏 
		s1=print(); 
		//调用开始管理界面
		switch (s1){
			case 1:{
				while(1){
				system("cls");
				s2=menu(m1, 9);
				if(s2==0){
					//若链表数据有修改且未进行存盘则将此标志为1
					printf("\n Whether save the modified record to file?(y/n):");
					scanf("%c", &ch);
					if(ch=='y'||ch=='Y'){
						save_s(head); 
					}
					printf("the student system qiut.\n");
					break;
				}
				switch(s2){
					//菜单选择命令 
					case 1:head=init_s();
					break;
					//可以新建或者打开文件内容到内存 
					case 2:
						while(1){
							//循环的功能是进入成绩管理界面 
							system("cls");
							s3=menu(m2, 7);
							//调用成绩管理菜单
							if(s3==0){
								break;
							} 
							//输入0表示输出
							
							switch(s3){
								//成绩处理菜单命令选择
								case 1:input_g(head, hc);
								break;
								//录入每门课的成绩和课程信息
								case 2:ave_g(head);
								break;
								//计算各科平均分
								case 3:sort_g(head);
								break;
								//为成绩排序
								case 4:filt_g(head);
								break;
								//分类成绩筛选
								case 5:print_g(head);
								break;
								//输出成绩 
							} 
						}
						break;
					case 3:
						sear_s(head);
						//查找某个学生的成绩
					case 4:
						head=appe_s(head);
						break;
						//追加记录
					case 5:
						head=modi_s(head);
						break;
						//修改记录
					case 6:
						head=dele_s(head);
						break;
						//删除记录
					case 7:
						save_s(head);
						break;
						//保存到文件 
					}
				}
			}break;
			
			case 2:{
				//选择2进入课程管理界面
				{
					while(1){
						//循环管理课程 
						system("cls");
						s2=menu(m3, 5);
						//调用课程管理菜单
						if(s2==0){
							system("cls");
							break;
						} 
						
						witch(s2){
						case 1:
							init_c(&hc);
							break;
						//录入课程记录
						
						case 2:
							sort_c(&hc);
							break;
						//课程进度安排
						case 3:
							plan_c(&hc);
							break; 
						//每个学期课程信息 
						}
					}
				} break;
			}
			
			case 3:{
				{
					//输入0表示退出这个系统 
					system("cls");
					printf("Press any key to exit.");
					getchar();
					exit(0); 
				}break;
			}
			
		  }
		} 
	};
	return 0;
}
