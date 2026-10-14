#include "List.h"
#include "Status.h"
Node* MakeNode(List* pList,void* pElem){
    Node* pNewNode;
    pNewNode=(Node*)malloc(sizeof(Node));
    if(pNewNode==nullptr){
        return nullptr;
    }
    pNewNode->pData=malloc(pList->dataSize);
    if(pNewNode->pData==nullptr){
        return nullptr;
    }
    memcpy(pNewNode->pData,pElem,pList->dataSize);
    pNewNode->pNextNode=nullptr;
    return pNewNode;
}
void FreeNode(Node* pNode){
    if(pNode==nullptr){
        return;
    }
    free(pNode->pData);
    free(pNode);
}
List* ListConstruct(int sizeOfData){
    List* pList;
    pList=(List*)malloc(sizeof(List));
    if(pList==nullptr){
        free(pList);
        pList=nullptr;
    }
    pList->pFirstNode=nullptr;
    pList->length=0;
    pList->dataSize=sizeOfData;
    return pList;
}
Status ListClear(List* pList){
    Node *pCurrentNode,*pNextNode;
    pCurrentNode=pList->pFirstNode;
    while(pCurrentNode!=nullptr){
        pNextNode=pCurrentNode->pNextNode;
        FreeNode(pCurrentNode);
        pCurrentNode=pNextNode;
        }
    pList->pFirstNode=nullptr; 
    pList->length=0;
    return OK;
}

Status ListDestruct(List* pList){
    ListClear(pList);
    free(pList);
    return OK;
}
bool ListIsEmpty(List* pList){
    if(pList==nullptr||pList->length==0){
        return true;
    }
    return false;
}
int ListLength(List* pList){
    if(pList==nullptr){
        return 0;
    }
    return pList->length;
}
Status GetData(Node* pNode,void* pElem){
    if(pNode==nullptr){
        return ERROR;
    }
    memcpy(pElem, pNode->pData, sizeof(pNode->pData));
    return OK;
}
Status InsertAtFront(List* pList,void* pElem){
    Node* pNewNode;
    pNewNode=MakeNode(pList,pElem);
    if(pNewNode==nullptr){
        return ERROR;
    }
    pNewNode->pNextNode=pList->pFirstNode;
    pList->pFirstNode=pNewNode;
    pList->length++;
    return OK;
}
Status ListAppend(List* pList,void* pElem){
    Node *pNewNode,*pTail;
    pNewNode=MakeNode(pList,pElem);
    if(pNewNode==nullptr){
        return ERROR;
    }
    
    if(pList->pFirstNode==nullptr){
        pList->pFirstNode=pNewNode;
    }
    else{
        pTail=pList->pFirstNode;
        while(pTail->pNextNode!=nullptr){
            pTail=pTail->pNextNode;
        }
        pTail->pNextNode=pNewNode;
    }
    pList->length++;
    return OK;
}
Status ListDeleteFirstNode(List* pList){
    Node *pTempNode;
    if(pList->length==0){
        return ERROR;
    }
    pTempNode=pList->pFirstNode;
    pList->pFirstNode=pTempNode->pNextNode;
    FreeNode(pTempNode);
    pList->length--;
    return OK; 
}
Status ListDeleteLastNode(List* pList){
    Node *p,*q;
    if(pList->length==0){
        return ERROR;
    }
    q=pList->pFirstNode;
    if(q->pNextNode==nullptr){
        return ListDeleteFirstNode(pList);
    }
    while(q->pNextNode!=nullptr){
        p=q;
        q=q->pNextNode;
    }
    p->pNextNode=nullptr;
    FreeNode(q);
    pList->length--; 
    return OK; 
}
Status ListTraverse(List* pList, Status (*visit)(void*,int)){
    if(pList==nullptr){
        return ERROR;
    }
    Node* pNode;
    pNode=pList->pFirstNode;
    while(pNode!=nullptr){
        if(visit(pNode->pData,pList->dataSize)==ERROR){
            return ERROR;
        }
        pNode=pNode->pNextNode;
    }
    return OK;
}