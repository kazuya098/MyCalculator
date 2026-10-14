#ifndef List_H
#define List_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
typedef struct Node{
    struct Node* pNextNode;
    void* pData;
}Node;

typedef struct {
    Node* pFirstNode;
    int length;
    int dataSize;
}List;
Node* MakeNode(List* pList,void* pElem);
//为pList创建一个新节点，并把pElem存入新节点

void FreeNode(Node* pNode);
//释放pNode指向的节点，同时释放节点上的数据

List* ListConstruct(int sizeOfData);
//创建一个链表并初始化
//sizeOfData为链表内节点上数据的长度，单位为字节

Status ListClear(List* pList);
//清空pList指向的链表,成功返回OK,失败返回Error

Status ListDestruct(List* pList);
//析构pList指向的链表,成功返回OK,失败返回Error

bool ListIsEmpty(List* pList);
////判断pList指向的链表是否为空，成功返回OK,失败返回Error

int ListLength(List* pList);
//计算并返回链表pList的长度

Status GetData(Node* pNode,void* pElem);
//将节点数据赋值给pElem，获取节点上的数据

Status InsertAtFront(List* pList,void* pElem);
//在pList指向的链式栈的顶部插入一个节点，节点上的数据为pElem

Status ListAppend(List* pList,void* pElem);
//在pList指向的链式栈的尾部追加一个节点，节点上的数据为pElem

Status ListDeleteFirstNode(List* pList);
//pList指向的链表中的第一个节点删除,成功返回OK；失败返回ERROR

Status ListDeleteLastNode(List* pList);
//pList指向的链表中的最后一个节点删除,成功返回OK；失败返回ERROR

Status ListTraverse(List* pList, Status (*visit)(void*,int));
//遍历链表内元素,返回状态值指示函数是否正常执行,OK为正常,ERROR为出错
//pList指向目标栈,(*visit)(void*)指向一个函数作为一个操作
#endif