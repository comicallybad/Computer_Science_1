//this code illustrate a simple array based stack which is globally declared
#include <stdio.h>
#define size 6
int stack[size];
int top;
void PUSH(int element)
{
    if (top >= size-1)
        printf("STACK FULL !!!");
    else
    stack[++top] = element;
}
int POP()
{
    if(top<0)
    {
        printf("STACK IS EMPTY!!!");
        return 0;
    }
    return stack[top--];
}

void display()
{
    printf("\nPrinting the Current stack...");
    for(int i=0; i<=top; i++)
        printf("%d ", stack[i]);
}

int main(void)
{
    int ele;
    char ch;
    top = -1;
    while(1)
    {
        printf("\npress e for Push, press p for POP, press d for displaying, press x for Exit\nEnter your choice: ");
        scanf("%c",&ch);
        if(ch=='x')
        {
            printf("<<EXIT>>");
            break;
        }
        else if (ch=='e')
        {
            printf("Enter an element to PUSH in the stack: ");
            scanf("%d",&ele);
            PUSH(ele);
        }
        else if (ch=='p')
        {
            ele = POP();
            if(ele!=0 )
            {
                printf(" ITEM POPED :%d ",ele);
            }
        }
        else if(ch=='d')
        {
            display();
        }
        char c;
        //the following line is the flush the enter key from the above input, so that the next %c scanf does not skip taking input
        while((c=getchar())!= '\n' && c !=EOF);
    }
	return 0;
}
