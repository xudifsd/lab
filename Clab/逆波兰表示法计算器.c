#include<stdio.h>
#define MAX 100
#define NUMBER '0'
float opnum;//由get()产生
float shed[MAX];//定义栈，push(),pop()调用，main()打印
int p=0;//push(),pop()使用，类似于指向shed[]的指针

char get()
{
char c;
int decimal=0;		//小数
float deep=0.1;		//小数位数
int num=0;			//是否是数
opnum=0;			//全局变量
while((c=getchar()) != EOF ){
     if( c<='9' && c>='0'){//是数
         num=1;
         if(decimal){//是小数
             opnum+=deep*(c-'0');
             deep*=0.1;
             }
         else{	//不是小数
			 opnum=opnum*10.0+(c-'0');
	 }}
     else if(c=='.')
        decimal=1;
     else if(c=='+'||c=='-'||c=='*'||c=='/')
        return c;
     else if(c==' '){
         if(num){
            return NUMBER;}
         }
     else if(c=='\n')
        return c;
     }//不处理错误
}
    
void push(float num)
{
	shed[p++]=num;
}

float pop(){
    float num;
    num=shed[--p];
    return num;
    }

void main()
{
char c;float op;
while((c=get())!='\n'){
    switch(c){
        case NUMBER:
            push(opnum);
            break;
        case '+':
            push(pop()+pop());
            break;
        case '*':
            push(pop()*pop());
            break;
        case '-':
            op=pop();
            push(pop()-op);
            break;
        case '/':
            op=pop();
            if(op==0){
                printf("Zero disivor!\n");
                break;
                }
            else{
                push(pop()/op);
                break;
                }
        default:
            printf("There are some errors!\n");
        }
    }
printf("The result is %.2f!\n",shed[0]);
}