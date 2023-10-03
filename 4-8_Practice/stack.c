#include<stdio.h>
top=-1;
int stack[16];

void push()
{
int a;
printf("enter value");
scanf("%d",&a);
if(top==(15))
{
    printf("overflow");
}
else{
    top++;
    stack[top]=a;
}
}

void pop()
{
    
   if(top==-1)
   {
    printf("overflow");
   }
   else{
    int a=stack[top];
    top--;
    printf("popped element is %d",a);
   }
}

int main()
{
    int w[10];
    int count=0;
    for(int i=0;i<10;i++)
    {printf("give 1 for push,2 for pop ,if you want to see the top element enter 3,and if you want to see the element of stack enter 4");
    scanf("%d",&w[i]);

    if(w[i]==2)
    {
        pop();
        count--;

    }
    if(w[i]==1)
    {
        push();
        count++;
    }
    if(w[i]==3)
    {
        int a;
        a=stack[top];
        printf("the top element is %d",a);
    }
    if(w[i]==4)
    {
        for(int j=0;j<count;j++)
        {
            printf("%d\n",stack[j]);
        }
    }
    
}
}