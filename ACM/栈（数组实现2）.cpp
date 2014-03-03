#include <stdio.h>
#include <stdlib.h>
/* typedef DataType int */
#define DataType int
#define MAX 1024
typedef struct
{
    DataType data[MAX];
    int top;
}stack, *pstack;

pstack *init_stack()
{
    pstack ps;
    ps = (pstack)malloc(sizeof(stack));
    if (!ps)
    {
        printf("Error, malloc failed\n");
        return NULL;
    }
    ps->top = -1;
    return ps;
}

int isEmpty_stack(pstack ps)
{
    if (ps->top == -1)
        return 1;
    else
        return 0;
}

int push(pstack ps, DataType data)
{
    if (ps->top == MAX-1)
    {
        printf("Stack is full...\n");
        return 0;
    }
    ps->top++;
    ps->data[ps->top] = data;
    return 1;
}

int pop(pstack ps, DataType *data)
{
    if (isEmpty_stack(ps))
    {
        printf("Stack is empty...\n");
        return 0;
    }
    *data = ps->data[ps->top];
    ps->top--;
    return 1;
}

DataType top_stack(pstack ps)
{
    if (isEmpty_stack(ps))
    {
        printf("Stack is empty...\n");
        return 0;
    }
    return ps->data[ps->top];
}

void display(pstack ps)
{
    int i;
    if(empty_stack(ps))
    {
        printf("Stack is empty.../n");
        return;
    }
    printf("printf the items of stack.../n");
    for(i=ps->top;i>-1;i--)
        printf("%4d", ps->data[i]);
    printf("/n/n");
}

void main()
{
    int i, num, data, *pdata;
    pstack ps;
    ps=init_stack();
    printf("Enter stack num:");
    scanf("%d", &num);
    for(i=0;i<num;i++)
    {
        scanf("%d", &data);
        push(ps, data);
    }
    display(ps);
    printf("Top is %d/n/n", top_stack(ps));
    for(i=0;i<num;i++)
    {
        pop(ps, pdata);
        printf("%3d", *pdata);
    }
    printf("/n/n");
    display(ps);
    getch();
}
