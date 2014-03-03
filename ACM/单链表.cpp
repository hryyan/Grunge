#include <stdio.h>
#include <stdlib.h>

struct _node
{
    int data;
    struct _node *next;
};
typedef struct _node list;

void display(list *l)
{
    list *p;
    p = l;
    while (p->next)
    {
        printf("%d", p->next->next);
        p = p->next;
    }
}

void main()
{
    int i, n;
    list *h, *p, *s;
    printf("Enter num n:");
    scanf("%d", &n);
    h = (list*)malloc(sizeof(list));
    h->data = -1;
    h->next = NULL;
    s = p = h;
    for (i=n;i>0;i--)
    {
        p = (list*)malloc(sizeof(list));
        scanf("%d", &(p->data));
        p->next = h->next;
        h->next = p;
        h = h->next;
    }
    display();
    getch();
}