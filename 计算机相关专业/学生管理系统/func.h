#include"manage_system_head.h" 
//登录和注册账户 
void RandomCode(char Rcode[]){
    int i;
    srand((unsigned int)time(NULL));

    for(i=0; i<3; ++i){
        Rcode[i]=rand()%10+'0';
    }
    Rcode[i]='\0';
}


void register2(void){
	 result = fopen("result.txt", "r");
	 recall = fopen("recall.txt", "r");
    if((recall)!=NULL && (result)!=NULL){       
       	printf("\t\t已注册，请登录:\n"); 
       	 fclose(recall);
       	  fclose(result);
		return;
    }
    else{
    	 result = fopen("result.txt", "w");
    	 recall = fopen("recall.txt", "w");
        printf("请输入账号(20个字母或者数字):____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s", account);
        fprintf(recall,"%s\n",account); //将输入字符输出至recall文件中
        printf("\n请输入密码(20个字母或者数字):____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
        scanf("%s", password);
        fprintf(result,"%s",password); //将输入字符输出至result文件中
        
		 fclose(recall);
          fclose(result);
        return;
    }
}


void login(){
	char rc[5]; //随机码
    int count=0, i=0; //count来记录输入密码的次数
    char RealAccount[20];
    char RealPassword[20];

//    decode();

    FILE *recall=fopen("recall.txt", "r");
    FILE *result=fopen("result.txt", "r");

    fscanf(recall,"%s",RealAccount);
    printf("%s\n", RealAccount);
    fscanf(result,"%s",RealPassword);//读取真实的账户和密码，用以验证
    printf("%s\n", RealPassword);
    fclose(recall);
    fclose(result);
//   remove("recall.txt"); 
//	 remove("recall.txt");
//	//清空文件，保证账户和密码的安全

    printf("请输入账号(20个字母或者数字):____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
    scanf("%s", account);
    do
    {
        if((strcmp(account, RealAccount))==0){
            printf("\n账户名称正确！\n");
            printf("\n请输入密码(20个字母或者数字):____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
            scanf("%s", password);
            do
            {
                count++;
               if((strcmp(password, RealPassword))==0){
               		printf("\n密码正确！\n");
              	    RandomCode (rc);
		            printf ("验证码: %s\n", rc);
		            printf("请输入验证码："); 
		            scanf("%s", rcode);
		           do{
		           		if(strcmp(rcode, rc)==0)
						{
								system("cls");
						 	  	printf("\t登录成功！\n");
//								 printf("================================================\r");
//					      	  for(i=0;i<TIME;i++)//动态界面设计 
//					      	  {
//					       		     printf("<");
//					       		     Sleep(TIME);//延迟TIME毫秒
//					        	}
//					      	  printf("\n");
							return; 
						}
						else{
							
		           			  printf("\n输入错误，请重新输入！\n");
		               	 	  printf("请输入验证码：");
		                      scanf("%s", rcode);
		            
						}
		              
		            }while(strcmp(rc, rcode)!=0); 
			   }
           	
               else{
              	 
               		 printf("\n密码错误，请重新输入\n");
               		 scanf("%s", password);
                	if(sizeof(password)>(20* sizeof(char))){
                   		 printf("\n提示：输入的密码长度超过20了\n");
               		 }
			   }
			   
            }while (((strcmp(password, RealPassword))!=0)&& count<=3 );
         	printf("输入次数过多，请稍后再试！");
        }
		else{
			 printf("\n账户名称错误，请重新输入\n");
        	scanf("%s", account);	
		}	
           
    }while ((strcmp(account, RealAccount))!=0);
}


//开始界面设计 
int print(){
	int n;
	system("cls");	//代替clrscr()
	system("color F0");//color F是亮白色，0是黑色 
	
	printf("\n\n");
	printf("\t*******************************************\n");
	printf("\t*                                         *\n");
	printf("\t*      ---------------------------        *\n");
	printf("\t*-----|   欢迎使用学生管理系统    |-------*\n");
	printf("\t*      ---------------------------        *\n");
	printf("\t*                                         *\n");
	printf("\t*              1.注册/登录                *\n");
	printf("\t*              0.退出                     *\n");
	printf("\t*                                         *\n");
	printf("\t*                              ——牛岩制作 *\n");
	printf("\t*******************************************\n");	
	printf("\t\t请选择1 or 0:");
	scanf("%d", &n);
//	getchar();
	return n;
}

int menu(int m){
	int select;	
	if(m==1){
		system("cls");	
		
		printf("\t*******************************************\n");
		printf("\t*                                         *\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*-----|   欢迎使用学生管理系统    |-------*\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*                                         *\n");
		printf("\t*              1.新建文件                 *\n");
		printf("\t*              2.成绩管理                 *\n");
		printf("\t*              3.搜索记录                 *\n");
		printf("\t*              4.追加记录                 *\n");
		printf("\t*              5.修改记录                 *\n");
		printf("\t*              6.删除记录                 *\n");
		printf("\t*              7.保存文件                 *\n");
		printf("\t*              0.退出                     *\n");
		printf("\t*                                         *\n");
		printf("\t*******************************************\n");	
		
		do{
			printf("\n\t\t请选择(0~7)...");
			scanf("%d", &select);
			getchar();//输入选择项
		}while(select<0||select>13);//选择项不在0~13之间重输
		return select; //返回选择项，主函数根据该函数调用相应的函数
	}
	else if(m==2){
		system("cls");
		printf("\t*******************************************\n");
		printf("\t*                                         *\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*-----|   欢迎使用成绩管理系统    |-------*\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*                                         *\n");
		printf("\t*              1.新建文件                 *\n");
		printf("\t*              2.显示均分                 *\n");
		printf("\t*              3.显示排序                 *\n");
		printf("\t*              4.分类浏览                 *\n");
		printf("\t*              5.显示成绩                 *\n");
		printf("\t*              0.返回                     *\n");
		printf("\t*                                         *\n");
		printf("\t*******************************************\n");	
		
		do{
			printf("\n\t\t 请选择(0~5)...");
			scanf("%d", &select);
			getchar();//输入选择项
		}while(select<0||select>5);
		return select; //返回选择项，主函数根据该函数调用相应的函数
	}
	else if(m==3){
		system("cls");
		printf("\t*******************************************\n");
		printf("\t*                                         *\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*-----|   欢迎使用课程管理系统    |-------*\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*                                         *\n");
		printf("\t*              1.新建文件                 *\n");
		printf("\t*              2.上课顺序                 *\n");
		printf("\t*              3.课程安排                 *\n");
		printf("\t*              0.返回                     *\n");
		printf("\t*                                         *\n");
		printf("\t*******************************************\n");	
			
		do{
			printf("\n\t\t 请选择(0~3)...");
			scanf("%d", &select);
			getchar();//输入选择项
		}while(select<0||select>3);
		return select; //返回选择项，主函数根据该函数调用相应的函数
	}	
	else if(m==4){
		system("cls");
		printf("\t*******************************************\n");
		printf("\t*                                         *\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*-----|   欢迎使用成绩管理系统    |-------*\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*     ********** 显示成绩**********       *\n");
		printf("\t*      1.80<=成绩<=100                    *\n");
		printf("\t*      2.60<=成绩<80                      *\n");
		printf("\t*      3.挂科                             *\n");
		printf("\t*      0.返回                             *\n");
		printf("\t*                                         *\n");
		printf("\t*******************************************\n");	
			
		do{
			printf("\n\t\t 请选择(0~3)...");
			scanf("%d", &select);
			getchar();//输入选择项
		}while(select<0||select>3);
		return select; //返回选择项，主函数根据该函数调用相应的函数
	} 
	else if(m==5){
		printf("\n\n");
		printf("\t*******************************************\n");
		printf("\t*                                         *\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*-----|   欢迎使用学生管理系统    |-------*\n");
		printf("\t*      ---------------------------        *\n");
		printf("\t*                                         *\n");
		printf("\t*              1.学生管理                 *\n");
		printf("\t*              0.退出                     *\n");
		printf("\t*                                         *\n");
		printf("\t*                              ——牛岩制作 *\n");
		printf("\t*******************************************\n");	
		do{
			printf("\n\t\t 请选择(0~1)...");
			scanf("%d", &select);
			getchar();//输入选择项
		}while(select<0||select>1);
		return select; //返回选择项，主函数根据该函数调用相应的函数
		
	}
}
 		
//学生记录文件建立 
Student *init_s(){
	Student *head, *p, *last, *R;	//定义建立学生记录的工作指针
	Student s;
	char c; 		//定义变量c作为选择是否新建文件的提示变量 
	FILE *fp;
	char fname[20];		//定义打开文件名地址存储的字符数组 
	int i;
	system("cls");
	printf("是否新建文件来保存学生记录(y/n)?_\b");
	c=getchar();
	getchar(); 
	if(c=='Y'||c=='y'){	//如果是y，则新建文件 
		printf("输入文件名称(不超过20个字符):____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
		scanf("%s", fname);	//输入文件名
		if((fp=fopen(fname, "w"))==NULL){	//文件打开失败
			printf("无法打开文件\n");
			return NULL;	//返回主调函数
		}
		do{	//输入多个学生信息存入磁盘 ，当编号为1，结束录入
			printf("输入学号(不超过10个数字，输入0结束):__________\b\b\b\b\b\b\b\b\b\b");
			
			scanf("%d", &s.snum);
			while(sizeof(s.snum)>10*sizeof(int)){
				printf("输入错误，请重新输入！\n");
				printf("输入学号(不超过10个数字，输入0结束):__________\b\b\b\b\b\b\b\b\b\b");
			
				scanf("%d", &s.snum); 
			} 
			getchar();//消除回车符，以便输入下一个内容 
			if((s.snum != 0)){		//如果学号不是0，那么输入姓名。 
				printf("输入名字(不超过20个字母):__________\b\b\b\b\b\b\b\b\b\b");
				scanf("%s", s.name);
				
				while(sizeof(s.name)>20*sizeof(char)){
					printf("输入错误，请重新输入！\n");
					printf("输入名字(不超过20个字母):__________\b\b\b\b\b\b\b\b\b\b");
			
					scanf("%s", s.name);
				} 
				
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
			else{	//如果输入为0 ,建立结束 
				break;
			}
		}while(1);
		fclose(fp);
	}
	head=(Student*)malloc(sizeof(Student));
	//建立（初始化）单链表头结点
	head->next=NULL;
	last=head;
	printf("\n请输入文件名称以打开文件:____________________\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	scanf("%s", fname);
	fp=fopen(fname, "r");  //打开学生文件 
	if(fp==NULL){
		printf("\n 无法打开文件\n");
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
	return head;	//返回读出文件的指针
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
}

//成绩管理系统实现
void input_g(Student *head , Cour *hg){ // 成绩录入 
	Student *p, *R;
	float x1, x2, x3;
	p=head->next;	//指向首元结点
	system("cls");
	while(p){
		printf("输入第一学期的三门成绩（以空格分隔）:");
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
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
} 

//计算每一科目的平均成绩
void ave_g(Student *head){	 
	Student *p, *q, *R;	
	int i, n=0;		//定义变量n统计每门课程参考的人数 
	float sa=0;		//定义变量sa计算课程的平均值 
	system("cls");
	q=head->next;
	char *ch[3]={"数学","英语","C语言"}; 
	//保存首元结点的信息 
	//设定指针变量保存链表中某个结点的地址可以访问课程信息 
	for(i=0; i<M; i++){	//访问M门课程 
		sa=0;	//每一门课程计算前变量初始化 
		n=0;	 
		p=head->next;	//p指向首元结点
		while(p){		//访问每个学生的该门课程  
			n++;	//统计 
			sa+=p->score[i].sc;	//课程值累加 
			
			printf("%f", sa ); 
			
			p=p->next;
		}
		sa=sa/n;	//计算平均值 
		printf("%s的平均分是 %.2f\n", ch[i], sa);
		//输出课程平均值 
		//q->score[i]访问成绩域数组中第i 个元素，
		//q->score[i].cp则访问成绩记录中的指针域
		//q->score[i].cp->cname 访问顶点中的cname成员信息。 
	}
	getchar();
	
		while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
		while(q){//释放所有结点的空间 
		R=q;
		q=q->next;
		free(R);
	}
}


//成绩排序 
void sort_g(Student *head){
	Student *p, *q, *r, *u , *R;	//定义排序的工作指针 
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
//	flag=1;
	save_s(head);
	getchar();
	
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
		while(q){//释放所有结点的空间 
		R=q;
		q=q->next;
		free(R);
	}
		while(r){//释放所有结点的空间 
		R=r;
		r=r->next;
		free(R);
	}
		while(u){//释放所有结点的空间 
		R=u;
		u=u->next;
		free(R);
	}
}

//分类统计成绩分布情况 
//把统计的各个分数段设计成函数，利用菜单管理各个函数 
void class_1(Student *h){	//大于等于80分的记录 
	Student *p, *R;	//定义工作指针 
	int i;
	p=h->next;	//指向首元结点 
	system("cls");
	printf("|--学号--|--姓名--|----科目----|----成绩----|\n");
	//输出界面头
	 
	while(p!=NULL){	//结点访问不为空 
		for(i=0; i<M; i++){	//访问每一个学生每门课的成绩 
			if(p->score[i].sc>=80){	//成绩大于等于80 
				printf("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
			p=p->next;	//指向下一个记录 
		}
		printf("\n\n输入任意键继续...");
		getchar();
	}
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
}

void class_2(Student *h){
	Student *p, *R;
	int i;
	p=h->next;
	system("cls");
	printf("|--学号--|--姓名--|----科目----|----学分----|\n");
	
	while(p!=NULL){
		for(i=0; i<M; i++){
			if(p->score[i].sc>=60&&p->score[i].sc<=79){
				printf("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
			p=p->next;	//指向下一个记录
		}
		printf("\n\n输入任意键继续 ...");
		getchar();
	}
	
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
}

void class_3(Student *h){
	Student *p, *R;
	int i;
	p=h->next;
	system("cls");
	printf("|--学号--|--姓名--|----科目----|----学分----|\n");

	while(p!=NULL){
		for(i=0; i<M; i++){
			if(p->score[i].sc<60){
				printf("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
			p=p->next;	//指向下一个记录
		}
		printf("\n\n输入任意键继续 ...");
		getchar();
	}
	
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
} 

//成绩分类搜索 
void filt_g(Student *head){
	int select;

	while(1){	//进入分类筛选界面 
		system("cls");
		select=menu(4);	//调用分类筛选菜单 
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
	Student *p, *R;
	system("cls");
	p=head->next;	//指向首元结点 
	printf("\n\n*****************************************************\n");
	//输出标题头 
	printf("|   学号   |    姓   名    |课程1|课程2|课程3|总 分|等级|\n\n");
	while(p!=NULL){	//链表中的结点不为空 
		printf(FORMAT, DATA);	//输出相应的信息 
		p=p->next;		//指针后移 
	}
	printf("\n\n*****************************************************");
	getchar();
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
}

//学生记录的保存 
void save_s(Student *head){
	FILE *fp;
	Student *p, *R;
	char bname[30];
//	printf("输入保存记录的文件名:");
//	scanf("%s", bname);
	fp=fopen("student.txt", "wt");	//以只写方式打开文件 
	if(fp==NULL){	//打开文件失败 
		printf("\n 打开文件错误!\n");
		return;
	}
	p=head->next;	//当前链表中所有数据写入内存 
	while(p){
		fwrite(p, sizeof(Student), 1, fp);
		//每次写一条记录或一个节点到文件 
		p=p->next;
	}
	fclose(fp);
	while(p){//释放所有结点的空间 
		R=p;
		p=p->next;
		free(R);
	}
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
		printf("\n 该学生不存在!\n");
		getchar();
		return NULL; 
	}
	system("cls");
	printf("\n  1.通过学号查找  2.通过姓名查找 \n");
	printf("  请选择[1,2]  ");
	scanf("%d", &select);
	getchar();
	switch(select){
		case 1:
			printf("输入学号:");
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
			printf("输入学生姓名:");
			scanf("%s", str);
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
		printf("输入学号(输入0结束):");
		p=(Student *) malloc(sizeof(Student));
		scanf("%d", &p->snum);
		getchar();
		
		while(check(head, p->snum)&& p->snum != 0){
			//学号不存在同时学号不为空，继续查询
			printf("输入学号:");
			scanf("%d", &p->snum);
			getchar() ;
		}
		
		if(p->snum==0){	//输入为0，则退出添加 
			printf("输入结束，按任意键继续...\n");
			break;
//			scanf("%d", &p->snum );
//			getchar(); 
		}
		else{	//插入结点 
			printf("输入学生姓名:");
			scanf("%s", p->name);
			printf("输入第一学期的成绩:");
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
//	flag=1;		//更改标记 
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
		printf("\n 没有学生记录!\n");
		return NULL;
	}
	system("cls");
	printf("\n   1. 通过学号删除   2. 通过名字删除\n");
	printf("请选择[1, 2]:");
	scanf("%d", &select);
	if(select==1){	//按照学号查找 
		printf("输入学号\n"); 
		scanf("%d", &num);
		r = head;
		p = head->next;		//r为中间变量，保存头结点 
		while(p && p->snum!=num){
			r=p;
			p=p->next;
		} 
		
		if(p){
			r->next=p->next;
//			flag=1;
			free(p);
			printf("\n 删除成功!\n");
			getchar();
		}
		else{
			printf("\n 无法找到!\n");
			getchar();
		}
	}
	else if(select==2){		//先按姓名查询到该记录
		printf("输入学生姓名:");
		scanf("%s", str);	//输入姓名信息 
		r=head;
		p=head->next;	//查找初始化 
		while(p&&strcmp(p->name, str)!=0){		 //循环比较查找记录 
			r=p;		//保存结点地址 
			p=p->next;	//结点指针后移 
		}
		if(p){
			r->next=p->next;	//将p所指结点从链表中去除 
//			flag=1;
			free(p);	//释放内存空间 
			printf("\n 删除成功!\n");
			getchar();	
		}
		else
		printf("\n 无法找到.\n");
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
	printf("修改学生记录...\n");
	printf("输入你想修改信息的学生的学号:\n");
	scanf("%d", &num);
	getchar();
	p=head->next;
	while(p && p->snum!=num){	//查找是否存在 
		p=p->next;
	} 
	if(p){		//若p！=NULL表明已经找到结点 
		printf("输入学生姓名:");
		scanf("%s", p->name);
		printf("输入第一学期成绩:");
		scanf("%f%f%f", x1, x2, x3);
		p->score[0].sc=x1;
		p->score[2].sc=x2;
		p->score[2].sc=x3;
		p->sum=x1+x2+x3;
		print_g(head);		//修改后的信息显示 
//		flag=1;		//改变记录，更改标记 
		getchar(); 
	}
	else{
		printf("无法找到文件!\n");
		getchar();
	}
} 
	

//课程信息表的建立 
void init_c(Course *g){
	//课程信息表结构的建立以及课程录入或者打开，保存原始记录文件
	FILE *fp;	//	设定指针保存课程信息文件地址 
	char fname[20]; 
	int i, j, k, n;
	Cnode *s=NULL;
	
	system("cls") ;
	
	printf("输入课程信息 \n");
	printf("|NO.  |Course | Credit|\n");
	
	for(i=0; i<M; i++){
		scanf("%d %s", &(g[i]->cnum), g[i]->cname);
//		g[i]->indegree=0;
		g[i]->first=NULL; //清空顶点单链表指针 
		
	}
	
	printf("输入课程数量:");
	scanf("%d", &n);
	getchar();
	//读入边数 
	printf("\n输入课程信息:\n");
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
	printf("把课程信息保存到文件，然后打开\n");
	gets(fname);
	getchar();
	if((fp=fopen(fname,"wb"))==NULL){
		//open the file
		printf("文件无法打开\n");
		exit(0);
	}
	for(i=0;i<M;i++){
		fwrite(g+i, sizeof(Cour), 1, fp);
		//save the record into the file
	}
	fclose(fp);
} 
