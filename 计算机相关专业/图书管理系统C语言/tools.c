#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
#include <stdarg.h>
#include "tools.h" 

//获取文件大小（以字节计）
long getFileSize(FILE *fp){
	long fsize;
	fpos_t fpos;  //当前位置
	fgetpos(fp, &fpos);  //获取当前位置
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	fsetpos(fp,&fpos);  //恢复之前的位置

	return fsize;
}

/**
 * 文件复制函数
 * @param  fSource       要复制的原文件
 * @param  offsetSource  原文件的位置偏移（相对文件开头），也就是从哪里开始复制
 * @param  len           要复制的内容长度，小于0表示复制offsetSource后边的所有内容
 * @param  fTarget       目标文件，也就是将文件复制到哪里
 * @param  offsetTarget  目标文件的位置偏移，也就是复制到目标文件的什么位置
 * @return  成功复制的字节数
**/

long fcopy(FILE *fSource, long offsetSource, long len, FILE *fTarget, long offsetTarget){
	int bufferLen = 1024*4;  // 缓冲区长度
    char *buffer = (char*)malloc(bufferLen);  // 开辟缓存
    int readCount;  // 每次调用fread()读取的字节数
	long nBytes = 0;  //总共复制了多少个字节
	int n = 0;  //需要调用多少次fread()函数
	int i;  //循环控制变量

	fseek(fSource, offsetSource, SEEK_SET);
	fseek(fTarget, offsetTarget, SEEK_SET);

	if(len<0){  //复制所有内容
		while( (readCount=fread(buffer, 1, bufferLen, fSource)) > 0 ){
			nBytes += readCount;
			fwrite(buffer, readCount, 1, fTarget);
		}
	}else{  //复制len个字节的内容
		n = (int)ceil((double)((double)len/bufferLen));
		for(i=1; i<=n; i++){
			if(len-nBytes<bufferLen){ bufferLen = len-nBytes; }
			readCount=fread(buffer, 1, bufferLen, fSource);
			fwrite(buffer, readCount, 1, fTarget);
			nBytes += readCount;
		}
	}
	fflush(fTarget);
    free(buffer);
	return nBytes;
}

/**
 * 向文件中插入内容
 * @param  fp      要插入内容的文件
 * @param  buffer  缓冲区，也就是要插入的内容
 * @param  offset  偏移量（相对文件开头），也就是从哪里开始插入
 * @param  len     要插入的内容长度
 * @return  成功插入的字节数
**/
int finsert(FILE *fp, long offset, void *buffer, int len){
	long fileSize = getFileSize(fp);
	FILE *fpTemp;  //临时文件

	if(offset>fileSize || offset<0 || len<0){  //插入错误
		return -1;
	}

	if(offset == fileSize){  //在文件末尾插入
		fseek(fp, offset, SEEK_SET);
		if(!fwrite(buffer, len, 1, fp)){
			return -1;
		}
	}

	if(offset < fileSize){  //从开头或者中间位置插入
		fpTemp = tmpfile();
		fcopy(fp, 0, offset, fpTemp, 0);
		fwrite(buffer, len, 1, fpTemp);
		fcopy(fp, offset, -1, fpTemp, offset+len);
		freopen(FILENAME, "wb+", fp );
		fcopy(fpTemp, 0, -1, fp, 0);
		fclose(fpTemp);
	}
	
	return 0;
}

/**
 * 从文件中删除内容
 * @param  fp      要插入内容的文件
 * @param  buffer  缓冲区，也就是要插入的内容
 * @param  offset  偏移量（相对文件开头），也就是从哪里开始插入
 * @param  len     要插入的内容长度
 * @return  成功插入的字节数
**/
int fdelete(FILE *fp, long offset, int len){
	long fileSize = getFileSize(fp);
	FILE *fpTemp;

	if(offset>fileSize || offset<0 || len<0){  //错误
		return -1;
	}

	fpTemp = tmpfile();
	fcopy(fp, 0, offset, fpTemp, 0);
	fcopy(fp, offset+len, -1, fpTemp, offset);
	freopen(FILENAME, "wb+", fp );
	fcopy(fpTemp, 0, -1, fp, 0);

	fclose(fpTemp);
	return 0;
}

/**
 * 暂停程序
 * @param  str  程序暂停时显示的字符串，可以包含格式控制符
 * @param  ...  变长参数
**/
void pause(const char *str, ...){
	va_list vl;
	char buf[500] = {0};
	va_start(vl, str);
	vsnprintf(buf, 500, str, vl);
	va_end(vl);
	printf(buf);
	getch();
	printf("\n");
}
