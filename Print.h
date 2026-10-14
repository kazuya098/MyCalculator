#ifndef Print_H
#define Print_H
#include<stdio.h>
#include "Status.h"
Status PrintElem(void* pElem,int sizeOfElement);
//打印某个元素,pElem是要打印的元素地址

Status PrintString(char* inputString);
//打印一个字符串,inputString是要打印的字符串开始地址
#endif