#include <stdio.h>
#include <stdlib.h>

typedef char DataType;
struct _node
{
    DataType data;
    struct _node *next;
};
typedef struct _node node, *pstack;

pstack init_stack()
{
    pstack ps;
    ps = (pstack)malloc(sizeof(node));
    if (ps == NULL)
    {
        printf("Error, malloc failed...\n");
        return NULL;
    }
    ps->data = -1;
    ps->next = NULL;
    return ps;
}

pstack push(pstack ps, DataType data)
{
    pstack ptop;
    ptop = (pstack)malloc(sizeof(node));
    if (ptop == NULL)
    {
        printf("Error, malloc failed...\n");
        return NULL;
    }
    ptop->next = ps;
    ptop->data = data;
    ps = ptop;
    return ps;
}

pstack pop(pstack ps, DataType *data)
{
    if (ps->next == NULL)
    {
        printf("Stack is empty\n");
        *data = -1;
        return NULL;
    }
    pstack ptop;
    ptop = ps;
    *data = ptop->data;
    ps = ps->next;
    return ps;
}

DataType top_stack(pstack ps)
{
    if (ps-> == NULL)
    {
        printf("Stack is empty\n");
        return -1;
    }
    return ps->data;
}

int len_stack(pstack ps)
{
    int len = 0;
    pstack p = ps;
    while (p != NULL)
    {
        p = p->next;
        len++;
    }
    return len;
}

void display(pstack ps)
{
    pstack p = ps;
    while (p != NULL)
    {
        printf("%4c ", p->data);
        p = p->next;
    }
    printf("\n\n");
}

void main()  
{  
    pstack ps;  
    DataType *data=(DataType *)malloc(sizeof(DataType));  
    ps=init_stack();  
    ps=push(ps, 'a');  
    ps=push(ps, 'b');  
    ps=push(ps, 'c');  
    ps=push(ps, 'd');  
    ps=push(ps, 'e');  
    display(ps);  
    printf("len of stack is: %d\n\n", len_stack(ps));  
    printf("top of stack is: %c\n\n", top_stack(ps));  
    ps=pop(ps, data);  
    printf("pop %c\n",*data);  
    display(ps);  
    ps=pop(ps, data);  
    printf("pop %c\n",*data);  
    display(ps);
    ps=pop(ps, data);  
    printf("pop %c\n",*data);  
    display(ps);  
    ps=pop(ps, data);  
    printf("pop %c\n",*data);  
    display(ps);  
    ps=pop(ps, data);  
    printf("pop %c\n",*data);  
    display(ps);  
    ps=pop(ps, data);  
    printf("pop %c\n",*data);  
    display(ps);  
    getch();  
}  