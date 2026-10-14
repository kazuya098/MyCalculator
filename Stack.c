#include "Stack.h"
#include "Status.h"
//数组栈部分
Stack* StackConstruct(unsigned int sizeOfStack, int sizeOfElement){
    Stack* pStack;
    pStack=(Stack*)malloc(sizeof(Stack));
    if(pStack==nullptr){
        return nullptr;
    }
    pStack->pBase=malloc(sizeOfStack*sizeOfElement);
    if(pStack->pBase==nullptr){
        free(pStack);
        return nullptr;
    }
    pStack->pTop=pStack->pBase;
    pStack->elementSize=sizeOfElement;
    pStack->StackSize=sizeOfStack;
    return pStack;
}
void StackDestruct(Stack* pStack){
    free(pStack->pBase);
    free(pStack);
}
int StackLength(Stack* pStack){
    return((char*)pStack->pTop-(char*)pStack->pBase)/pStack->elementSize;
}
bool StackIsEmpty(Stack* pStack){
    if(pStack->pTop==pStack->pBase){
        return true;
    }
    else{
        return false;
    }
}
Status StackTraverse(Stack* pStack, Status (*visit)(void*,int)){
    int i,n;
    n=StackLength(pStack);
    for(i=0;i<n;i++){
        if(visit((char*)pStack->pBase+i*pStack->elementSize,pStack->elementSize)==ERROR){
            return ERROR;
        }
    }
    return OK;
}
void StackClear(Stack* pStack) {
    pStack->pTop = pStack->pBase;
}
Status StackPush(Stack* pStack,void* pElem){
    if(StackLength(pStack)==pStack->StackSize){
        int newSize;
        void *pTemp;
        newSize=pStack->StackSize+STACK_INCREASE;
        #if DEBUG
            printf("Stack size after realloc:%d",newSize);
        #endif
        pTemp=(void*)realloc(pStack->pBase,newSize*pStack->elementSize);
        if(pTemp==nullptr){
            return ERROR;
        }
        pStack->pBase=pTemp;
        pStack->pTop=(char*)pStack->pBase + pStack->StackSize * pStack->elementSize;
        pStack->StackSize=newSize;
    }
    memcpy(pStack->pTop, pElem, pStack->elementSize);
    pStack->pTop = (char*)pStack->pTop + pStack->elementSize;
    #if DEBUG
        printf("after push:\n");
    StackTraverse(pStack,PrintElem);
    #endif
    return OK;
}
Status StackPop(Stack* pStack,void* pElem){
    if(StackIsEmpty(pStack)){
        return ERROR;
    }
    pStack->pTop=(char*)pStack->pTop-pStack->elementSize;
    memcpy(pElem, pStack->pTop, pStack->elementSize);
    #if DEBUG
        printf("after pop:\n");
    StackTraverse(pStack,PrintElem);
    #endif
    return OK;
}
Status StackPeek(Stack* pStack,void* pElem){
    if(StackIsEmpty(pStack)){
        return ERROR;
    }
    memcpy(pElem, (char*)pStack->pTop - pStack->elementSize, pStack->elementSize);
    #if DEBUG
        PrintElem(pElem,pStack->elementSize);
    #endif
    return OK;
}