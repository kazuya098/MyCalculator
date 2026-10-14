#ifndef ListStack_H
#define ListStack_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Status.h"
#include "List.h"
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

#define MAX_EXPRESSION_LENGTH 100
#define MAX_NUMBER_LENGTH 32
typedef List Stack;
Node* MakeNode(Stack* pStack,void* pElem);
////为pStack指向的链式栈创建一个新节点，并把pElem存入新节点

void FreeNode(Node* pNode);
//释放pNode指向的节点，同时释放节点上的数据

Stack* StackConstruct(int sizeOfData);
//创建一个链表并初始化
//sizeOfData为链表内节点上数据的长度，单位为字节

Status StackClear(Stack* pStack);
//清空pStack指向的链表,成功返回OK,失败返回Error

Status StackDestruct(Stack* pStack);
//析构pStack指向的链表,成功返回OK,失败返回Error

bool StackIsEmpty(Stack* pStack);
//判断pStack指向的链表是否为空，成功返回OK,失败返回Error

Status StackPush(Stack* pStack,void* pElem);
//将元素压入栈,返回状态值指示函数是否正常执行,成功返回OK,失败返回Error
//pStack指向要压入元素的栈,要压入的元素复制给pElem

Status StackPop(Stack* pStack,void*pElem);
//将元素弹出栈,返回状态值指示函数是否正常执行,成功返回OK,失败返回Error
//pStack指向要弹出元素的栈,要弹出的元素复制给pElem

int StackLength(Stack* pStack);
//计算并返回链式栈pStack的长度

Status StackPeek(Stack* pStack,void *pElem);
//查看栈顶元素,复制给pElem

Status StackTraverse(Stack* pStack, Status (*visit)(void*,int));
//遍历栈内元素,返回状态值指示函数是否正常执行,OK为正常,ERROR为出错
//pStack指向目标栈,(*visit)(void*)指向一个函数作为一个操作
#endif