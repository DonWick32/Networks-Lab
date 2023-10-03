#include<stdio.h>
#include<ctype.h>
int stack[10],top =-1;
int main(){
    char arr[20];
    int i,result;
    printf("enter the postfix");
    scanf("%s",arr);
    int pushin(int value){
    top= top +1;
    stack[top] = value;
    
    }
    int popout(){
    int temp = stack[top];
    top =top -1;
    return temp;
    }
    for (int i = 0;arr[i] != "\";i++){
        if((arr[i]>='1' && arr[i]<='9')||(arr[i] == '0')){
        pushin(arr[i]-'0');
        }
        if (arr[i] == '+'|| arr[i] =='*' || arr[i]== '-' ||arr[i] =='/'){
            int value1 = popout();
            int value2 = popout();
        switch(arr[i]){
        case '+':{
                result = value1 + value2;
        
        }break;
        case '-':{
                 result = value1 - value2;
        }break;
        case '/':{
                 result = value1 / value2;
        }break;
        case '*':{
                result = value1 * value2;
        }break;
        }
        pushin(result);
        }
    }
    printf("the final result are %d",stack[top]);
}