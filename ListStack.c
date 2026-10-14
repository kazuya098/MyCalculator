#include "ListStack.h"
#include "Status.h"
#include <string.h>
#include <stdlib.h>
Stack* StackConstruct(int sizeOfData){
    return ListConstruct(sizeOfData);
}
Status StackClear(Stack* pStack){
    return ListClear(pStack);
}
Status StackDestruct(Stack* pStack){
    return ListDestruct(pStack);
}
bool StackIsEmpty(Stack* pStack){
    return ListIsEmpty(pStack);
}
Status StackPush(Stack* pStack,void* pElem){
    return InsertAtFront(pStack,pElem);
}
Status StackPop(Stack* pStack,void*pElem){
    if(StackIsEmpty(pStack)){
        return ERROR;
    }
    Node* pTempNode;
    pTempNode=pStack->pFirstNode;
    pStack->pFirstNode=pTempNode->pNextNode;
    memcpy(pElem,pTempNode->pData,pStack->dataSize);
    FreeNode(pTempNode);
    pTempNode=nullptr;
    pStack->length--;
    return OK;
}
int StackLength(Stack* pStack){
    return ListLength(pStack);
}
Status StackPeek(Stack* pStack,void *pElem){
    if(pStack==nullptr){
        return ERROR;
    }
    Node* pTempNode;
    pTempNode=pStack->pFirstNode;
    memcpy(pElem,pTempNode->pData,pStack->dataSize);
    return OK;
}
Status StackTraverse(Stack* pStack, Status (*visit)(void*,int)){
    return ListTraverse(pStack,visit);
}