#ifndef Stack_H
#define Stack_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Status.h"
#include "Print.h"
#define C24_VERSION 202311L
#if __STDC_VERSION__ < C24_VERSION
    #define alignas _Alignas
    #define alignof _Alignof
    #define noreturn _Noreturn
    #define nullptr NULL
    #ifndef __cplusplus
        #ifndef bool
            typedef enum {false=0, true=1} bool;
        #endif
    #endif
#endif
#define INIT_STACK_SIZE 50
#define STACK_INCREASE 10
#define MAX_EXPRESSION_LENGTH 100
#define MAX_NUMBER_LENGTH 32
typedef struct {
    void *pBase;
    void *pTop;
    int elementSize;
    unsigned int StackSize;
}Stack;
Stack* StackConstruct(unsigned int sizeOfStack, int sizeOfElement);
//构造一个数组栈并且初始化,返回一个栈指针指向栈所在的位置
//sizeOfStack为栈的初始大小,size_of_elemet为元素所占字节数

void StackDestruct(Stack* pStack);
//析构一个栈,释放pStack指向的栈的内存

int StackLength(Stack* pStack);
//计算当前栈中的元素个数,返回整型数表示栈中元素数量
//pStack指向栈的位置

bool StackIsEmpty(Stack* pStack);
//判断栈是否为空,返回一个布尔值指示是否为空,是为1,否为0
//pStack指向要判断的栈

Status StackTraverse(Stack* pStack, Status (*visit)(void*,int));
//遍历栈内元素,返回状态值指示函数是否正常执行,OK为正常,ERROR为出错
//pStack指向目标栈,(*visit)(void*)指向一个函数作为一个操作

void StackClear(Stack* pStack);
//清空一个栈内的元素,pStack指向该栈

Status StackPush(Stack* pStack,void* pElem);
//将元素压入栈,返回状态值指示函数是否正常执行,OK为正常,ERROR为出错
//pStack指向要压入元素的栈,要压入的元素复制给pElem

Status StackPop(Stack* pStack,void* pElem);
//将元素弹出栈,返回状态值指示函数是否正常执行,OK为正常,ERROR为出错
//pStack指向要弹出元素的栈,要弹出的元素复制给pElem,

Status StackPeek(Stack* pStack,void* pElem);
//查看栈顶元素,返回一个状态值,空栈返回ERROR,栈顶有元素返回OK
//pStack指向要查看的栈,栈顶元素复制给pElem
#endif