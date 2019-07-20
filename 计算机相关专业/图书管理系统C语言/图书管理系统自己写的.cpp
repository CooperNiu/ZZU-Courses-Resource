#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>

#define Maxn

void Add();
void Find();
void Delete();

int main(void)
{
	
	
	return 0;
}

void Add(){
	LIST *p1=NULL, *p2=NULL;
	p1=(LIST*)malloc(sizeof(LIST));
	printf("输入书名：\n");
	scanf("%s", p1->bookname);
	printf("输入编号：\n");
	scanf("%s", p1->num);
	printf("输入单价：\n");
	scanf("%s", p1->price);
	printf("输入ISBN：\n");
	scanf("%s", p1->ISBN);
	printf("输入出版社：\n");
	scanf("%s", p1->press);
	
	p1->next = NULL;
	
	if(head==NULL){
		head  (LIST*)malloc(sizeof(LIST));
		head ->next=p1;
	}
	else{
		for(p2=head; p2 ->next=NULL;p2=p2->next);
		p2->next=p1;
	}
	printf("此记录以及成功添加！\n"); 
}

void Find(){
	LIST *p;
	char bookname[30],num[15];
	int i;
	printf("请输入查找方式：1.按照书名；2.按照编号\n");
	scanf("%d", &i);
	if(i==1){
		printf("请输入要查找的书籍名称：\n");
		scanf("%s", bookname);
		printf("书名\t\t编号\t\tISBN\t\t出版社\n");
		for(p=head->next; p!=NULL; p=p->next) {
			if(strcmp(p->num, num)==0)
				printf("%s\t%s\t%s\t%s\n",p->bookname,p->num,p->jprice,p->ISBN,p->press);
			else
				printf("请选择1和2两个数字\n");
					
		}
	} 
}
