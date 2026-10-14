#include "Print.h"
#include <stdio.h>
#include "Status.h"
Status PrintElem(void* pElem,int sizeOfElement){
    switch(sizeOfElement){
        case 1:
            printf("%c\n",*(char*)pElem);
            break;
        case 4:
            printf("%d\n",*(int*)pElem);
            break;
        case 8:
            printf("%f\n",*(double*)pElem);
            break;
    }
}
Status PrintString(char* inputString){
    int i;
    for(i=0;inputString[i]!=0;i++){
        printf("%c",inputString[i]);
    }
    return OK;
}