#ifndef _TOOLS_H
#define _TOOLS_H

#include "common.h"

extern long getFileSize(FILE *fp);  //获取文件大小
extern long fcopy(FILE *fSource, long offsetSource, long len, FILE *fTarget, long offsetTarget);  //文件内容复制
extern int finsert(FILE *fp, long offset, void *buffer, int len);  //向文件中插入数据
extern int fdelete(FILE *fp, long offset, int len);  //删除文件内容
extern void pause(const char *str, ...);  //暂停程序

#endif

