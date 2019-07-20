
//#include"manage_system_head.h" 
#include"func.h"
int main(void){
	int i;
	
	Student *head =NULL;//学生文件信息内存中存储为链表
	char ch;	//存储选择结果变量 
	FILE *fp;	//文件指针
	int s1, s2, s3;	//保存选择结果变量
	
	system("cls");	//清屏
	
	while(1){
		//开始界面有三个功能，可以管理学生成绩和课程记录以及退出界面
		system("cls");
		s1= print(); //调用开始管理界面,返回对登录、注册和退出的选择 
		if(s1==1){//判断返回的选项
			register2(); 
			login();//如果登录成功，就可以进入选择菜单 
			if(menu(5)){
				while(1){//如果选择了学生管理 	 
					system("cls");
					s2=menu(1);
				    if(s2==0){
						//若链表数据有修改且未进行存盘则将此标志为1
						printf("\n是否把修改后的记录保存到文件中?(y/n):");
						scanf("%c", &ch);
						if(ch=='y'||ch=='Y'){
							save_s(head); 
						}
						printf("学生管理系统退出.\n");
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
							s3=menu(2);
							//调用成绩管理菜单
							if(s3==0){
					
							break;
							} 
							//输入0表示输出
							
							switch(s3){
								//成绩处理菜单命令选择
								case 1:input_g(head, ch);
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
						break; 
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
				
			} 
			else{
				exit(1);
			} 
		}
		else {
			//输入0表示退出这个系统 
			system("cls");
			printf("\t按任意键就可以退出了\n\n");
			getchar();
			exit(0); 
			}
		}	
}
