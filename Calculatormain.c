//更改第一行#include头文件可实现数组栈和链式栈的切换,注意数组栈的StackConstruct函数多一个参数
//该程序需要在与其他文件一同编译,终端输入gcc Calculatormain.c Stack.c Print.c -o Calculatormain -lm
//或gcc Calculatormain.c List.c ListStack.c Print.c -o Calculatormain -lm
#include "Stack.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define DEBUG 0
#define PI M_PI

typedef enum{SIN,COS,TAN,AMOUNT}TriangleFunc;

const char* TriangleNames[]={
    [SIN]="sin",
    [COS]="cos",
    [TAN]="tan",
};
bool IsNumber(char ch);
//判断(ch)字符是否为数字
//返回一个布尔值,是为1,否为0

bool IsOperator(char ch);
//判断(ch)字符是否为四则运算符
//返回一个布尔值,是为1,否为0

bool IsTriangle(char* str,int startpos);
//判断(*str)字符串是否为三角函数名,startpos是开始比较的字符串位置
//返回一个布尔值,是返回1,否返回0

bool IsPI(char* str,int startpos);
//判断(*str)字符串是否为常量PI,startpos是开始比较的字符串位置
//返回一个布尔值,是返回1,否返回0

double TriangleProcess(char* str, int startpos);
//处理三角函数名,计算并返回三角函数的数值
//str为整个带计算的表达式,startpos是三角函数名的开始位置

int Priority(char ch);
//设置四则运算符和左括号的优先级,返回整型数字指示优先级,(为0,+—为1,*/为2
//ch为要设置优先级的字符

Status Transform(char* inputString, char* outputString);
//将中缀表达式转换为后缀表达式,返回状态值指示函数是否正常执行,OK为正常,ERROR为出错
//inputString是中缀表达式的开始地址,outputString是后缀表达式的开始地址

double OperateNumber(double leftNumber, double rightNumber, char oper);
//进行左右数的操作运算,返回单个运算符的计算结果
//oper为要进行的运算符,leftNumber为运算符左侧数,rightNumber为运算符右侧数

double Calculate(char* afterTrans);
//计算整个后缀表达式的结果,返回最终计算结果
//afterTrans是后缀表达式的开始地址
bool IsNumber(char ch){
    if (ch >= '0' && ch <= '9' || ch == '.'){
        return true;
    }
    else{
        return false;
    }
}
bool IsOperator(char ch){
    if (ch == '+' || ch == '-' || ch == '*' || ch == '/'){
        return true;
    }
    else{
        return false;
    }
}
bool IsTriangle(char* str,int startpos){
    int i;
    for(i=0;i<AMOUNT;i++){
        if(strncmp(&str[startpos],TriangleNames[i],strlen(TriangleNames[i]))==0){
            return true;
        }
    }
    return false;
}
bool IsPI(char* str,int startpos){
    if(strncmp(&str[startpos],"PI",2)==0){
        return true;
    }
    return false;
}
double TriangleProcess(char* str, int startpos) {
    int i;
    double result;
    for(i=0;i<AMOUNT;i++){
        if(strncmp(&str[startpos],TriangleNames[i],strlen(TriangleNames[i]))==0){
            int numStart;
            numStart=startpos+strlen(TriangleNames[i]);
            while(str[numStart]==' '){
                numStart++;
            }
            if(str[numStart]=='('){
                int numEnd=numStart+1;
                int bracketcount=1;
                while(str[numEnd]!='\0'&&bracketcount>0){
                    if(str[numEnd]=='('){
                        bracketcount++;
                    }
                    else if(str[numEnd]==')'){
                        bracketcount--;
                    }
                    if(bracketcount>0){
                        numEnd++;
                    }
                }
                if(bracketcount==0){
                    char expression[MAX_NUMBER_LENGTH],transexpress[MAX_NUMBER_LENGTH];
                    double angle;
                    strncpy(expression, &str[numStart+1], numEnd-numStart-1);
                    expression[numEnd-numStart-1]='\0';
                    Transform(expression,transexpress);
                    angle=Calculate(transexpress);
                    switch(i) {
                        case SIN:
                            result = sin(angle); 
                            break;
                        case COS:
                            result = cos(angle);
                            break;
                        case TAN:
                            result = tan(angle);
                            break;
                    }
                    return result;
                }
            }
            return NAN;
        }
    }
    return NAN;
}
int Priority(char ch){
    switch(ch){
        case '(':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}
Status Transform(char* inputString, char* outputString){
#if DEBUG
    printf("Enter Transform\n");
#endif
    Stack* pOperatorStack = StackConstruct(INIT_STACK_SIZE,sizeof(char));
    if(pOperatorStack == nullptr){
        return ERROR;
    }
    int i,j=0;
    //建一个标识指示是不是正在处理数字
    bool isNumberProcess = false;
    for(i=0;inputString[i]!='\0';i++){
        char input = inputString[i];
        if(input==' '){
            continue;
        }
        if(IsNumber(input) ||
            (input=='-'&&
             (i==0||inputString[i-1]=='('||IsOperator(inputString[i-1])))){
            if(isNumberProcess){
                outputString[j++]=' ';
                isNumberProcess=false;
            }
            do {
                outputString[j++]=inputString[i++];
            } while(inputString[i]!='\0' && (IsNumber(inputString[i]) || inputString[i]=='.'));
            i--;
            isNumberProcess=true;
        }
        else{
            //数字处理结束,更新标识的值
            if(isNumberProcess){
                outputString[j++]=' ';
                isNumberProcess=false;
            }
            if(input == '('){
                StackPush(pOperatorStack,&input);
            }
            else if(input == ')'){
                char temp;
                while(!StackIsEmpty(pOperatorStack)){
                    StackPop(pOperatorStack, &temp);
                    if(temp == '('){
                        break;
                    }
                    outputString[j++] = temp;
                    outputString[j++]=' ';
                }
            }
            else if(IsOperator(input)){
                char top;
                while(!StackIsEmpty(pOperatorStack)&&
                        StackPeek(pOperatorStack, &top)==OK&&
                        Priority(input)<=Priority(top)){
                            StackPop(pOperatorStack,&top);
                            outputString[j++]=top;
                            outputString[j++]=' ';
                }
                StackPush(pOperatorStack, &input);
                outputString[j++]=' ';
            }
            else if(IsPI(inputString,i)){
                char piStr[MAX_NUMBER_LENGTH];
                sprintf(piStr,"%.6f",PI);
                int k=0;
                while(piStr[k]!='\0'){
                    outputString[j++]=piStr[k++];
                }
                outputString[j++]=' ';
                i++;
                isNumberProcess=true;
            }
            else if(IsTriangle(inputString,i)){
                double triangleResult=TriangleProcess(inputString,i);
                #if DEBUG
                    printf("Triangle result:%f\n",triangleResult);
                #endif
                if(isnan(triangleResult)){
                    StackDestruct(pOperatorStack);
                    return ERROR;
                }
                char triangleStr[MAX_NUMBER_LENGTH];
                sprintf(triangleStr,"%.6f",triangleResult);
                int k=0;
                while(triangleStr[k]!='\0'){
                    outputString[j++]=triangleStr[k++];
                }
                outputString[j++]=' ';
                //上面已经把三角函数部分解决了,下面要跳过三角部分
                int length=0,index;
                for(index=0;index<AMOUNT;index++){
                    int len=strlen(TriangleNames[index]);
                    if(strncmp(&inputString[i],TriangleNames[index],len)==0){
                        length=len;
                        break;
                    }
                }
                i+=length;
                if(inputString[i]=='('){
                    int bracketcount=1;
                    i++;
                    while(inputString[i]!='\0'&& bracketcount>0){
                        if(inputString[i]=='('){
                            bracketcount++;
                        }
                        else if(inputString[i]==')'){
                            bracketcount--;
                        }
                        if(bracketcount>0){
                            i++;
                        }
                    }
                }
                isNumberProcess=true;
            }
        }    
    }
    if(isNumberProcess){
        outputString[j++]=' ';
    }
    char temp;
    while(!StackIsEmpty(pOperatorStack)){
        StackPop(pOperatorStack, &temp);
        outputString[j++]=temp;
        outputString[j++]=' ';
    }
    outputString[j]='\0';
    #if DEBUG
        printf("after Transform:");
        PrintString(outputString);
        printf("\n");
    #endif
    StackDestruct(pOperatorStack);
    return OK;
#if DEBUG
    printf("Exit Transform\n");
#endif
}
double OperateNumber(double leftNumber, double rightNumber, char oper){
    switch(oper){
        case'+':
            return leftNumber+rightNumber;
        case'-':
            return leftNumber-rightNumber;
        case'*':
            return leftNumber*rightNumber;
        case'/':
            if(rightNumber==0){
                return NAN;
            }
            return leftNumber/rightNumber;
        default:
            break;
    }
    return NAN;
}
double Calculate(char* afterTrans){
#if DEBUG
    printf("Enter Calculate\n");
#endif
    Stack* pNumStack = StackConstruct(INIT_STACK_SIZE,sizeof(double));
    if (pNumStack==nullptr){
        return NAN;
    }
    int i = 0;
    while(afterTrans[i] != '\0'){
        char temp = afterTrans[i];
        if(temp == ' '){
            i++;
            continue;
        }
        if(IsNumber(temp)|| 
           (temp == '-' && afterTrans[i+1] != '\0' && (IsNumber(afterTrans[i+1])||afterTrans[i+1]=='.'))){
            int start = i;//创建数字的起始点
            if (temp == '-') {
                i++; //指向下一位,将负号保留下来
            }
            while(afterTrans[i] != '\0' && (IsNumber(afterTrans[i])||afterTrans[i]=='.')){
                i++;
            }
            char numString[MAX_NUMBER_LENGTH];//临时储存完整的数字字符串
            strncpy(numString, &afterTrans[start], i - start);
            numString[i - start] = '\0';
            
            double num = atof(numString);//将字符串转换为数字
            StackPush(pNumStack, &num);
        }
        else if(IsOperator(temp)){
            double right, left, result;
            if(StackPop(pNumStack,&right)==OK&&StackPop(pNumStack,&left)==OK){
                result = OperateNumber(left, right,temp);
                #if DEBUG
                    printf("middle step result:%f\n",result);
                #endif
                if(isnan(result)){  //检查运算结果
                    StackDestruct(pNumStack);
                    return NAN;
                }
                if(StackPush(pNumStack, &result) == ERROR){
                    StackDestruct(pNumStack);
                    return NAN;
                }
            }
            else {
                StackDestruct(pNumStack);
                return NAN;
            }
        }
        else {
            StackDestruct(pNumStack);
            return NAN;
        }
        i++;
    }
    double finalResult;
    if(StackPop(pNumStack, &finalResult) == OK && StackIsEmpty(pNumStack)){
        #if DEBUG
            printf("final result:%f\n",finalResult);
        #endif
        StackDestruct(pNumStack);
        return finalResult;
    } else {
        StackDestruct(pNumStack);
        return NAN;
    }
#if DEBUG
    printf("Exit Calculate\n");
#endif
}
int main(int argc,char* argv[]){
    if(argc==3){
        FILE* pinputfile=fopen(argv[1],"r");
        FILE* poutputfile=fopen(argv[2],"w");
        if(pinputfile==nullptr){
            printf("Failed to open the input file:%s",argv[1]);
            return 1;
        }
        if(poutputfile==nullptr){
            printf("Failed to open the output file:%s",argv[2]);
            return 1;
        }
        char expstrs[MAX_EXPRESSION_LENGTH];
        char transstrs[MAX_EXPRESSION_LENGTH*2];
        double result;
        while(fgets(expstrs,MAX_EXPRESSION_LENGTH,pinputfile)!=nullptr){
            expstrs[strcspn(expstrs,"\n")]=0;
            expstrs[strcspn(expstrs,"\r")]=0;
            if(strlen(expstrs) == 0){
                continue;
            }
            if(Transform(expstrs,transstrs)==OK){
                result=Calculate(transstrs);
                if(!isnan(result)){
                    fprintf(poutputfile,"%s=%.6f\n",expstrs,result);
                }
                else{
                    fprintf(poutputfile,"%s=nan\n",expstrs);
                }
            }
            else{
                fprintf(poutputfile,"%s=nan\n",expstrs);
            }
        }
        fclose(pinputfile);
        fclose(poutputfile);
        printf("Batch calculation has been completed,results has been saved to:%s\n",argv[2]);
        return 0;
    }
    else{
        printf("Please enter an expression:");
        char in[MAX_EXPRESSION_LENGTH],out[MAX_EXPRESSION_LENGTH*2];
        fgets(in, MAX_EXPRESSION_LENGTH, stdin);
        in[strcspn(in, "\n")] = 0;
        Transform(in, out);
        double result=Calculate(out);
        printf("The result is:%f",result);
        return 0;
    }
}