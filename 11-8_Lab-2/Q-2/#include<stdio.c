#include<stdio.h>
#include<ctype.h>
char stack[100];
int top =-1;
void push(char x)
{
    stack[++top]= x;
}
char pop()
{
    if(top==-1)
      return-1;
    else
      return stack[top--];
}
int priority(char x)
{
  if(x=='(')
  return 0;
  if(x==1 '+'||x=='-')
    return 1;
  if(x=='*'||x=='/')
  return 2;
   return 0;

}
int main()
{
    char exp[100];
    char*e,x;
    printf("Enter the expression:");
    scanf("%s",exp);
    printf("\n");
    e = exp;
    while(*e!=)
}
