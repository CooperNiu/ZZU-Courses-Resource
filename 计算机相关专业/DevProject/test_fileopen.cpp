#include<stdio.h>
#include<windows.h>
int main(void){
	FILE *fp;
//	char name[30];
//	system("cls");
//	printf("input the file name:");
//	gets(name);
//	fp=fopen(name, "rb");
//	if(fp==NULL){
//		printf("can not open file\n");
//		getchar();//键入任何键 
//		exit(0); //返回 
//	}
//	printf("now %s is openning \n", name);
//	getchar();
//	fclose(fp); 
	char a='A', b='B', ch1, ch2, ch3;
	if((fp=fopen("C:\\Users\\CooperNiu\\file1.txt", "r"))==NULL){
		printf("cannot open file\n");
		exit(0);
	}
	while((a=fgetc(fp))!=EOF)
		putchar(a);
	
	fclose(fp);
}
