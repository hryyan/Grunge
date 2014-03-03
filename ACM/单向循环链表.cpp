#include <stdio.h>
#include <stdlib.h>

struct _node
{
    int data;
    struct _node *next;
};
typedef struct _node node, *plist;
plist init_list()
{
    plist pl=(plist)malloc(sizeof(node));
    if(!pl)
    {
        printf("error malloc fail.../n");
        return NULL;
    }
    pl->data=-1;
    pl->next=pl;    /* pl->next=NULL */
    return pl;
}
void insert_item(plist pl, int pos, int data)
{
    int j=0;
    plist p,s;
    s=p=pl;
    while(p && j<pos-1)
    {
        p=p->next;
        j++;
    }
    if(!p || j>pos-1)
    {
        printf("Error insert fail.../n");
        return;
    }
    s=(plist)malloc(sizeof(node));
    if(!s)
    {
        printf("Error malloc fail.../n");
        return;
    }
    s->data=data;
    s->next=p->next;
    p->next=s;
}
int find_item(plist pl, int data)
{
    plist s,p;
    s=p=pl;
    p=p->next;
    while(s != p)
    {
        if(data==p->data)
            return 1;
        p=p->next;
    }
    return 0;
}
void delete_item(plist pl, int data)
{
    plist p,s;
    s=p=pl;
    if(data == p->data) /* first item is equal with data, then last item = second item */
    {
        s=p;
        while(s != p->next)
            p=p->next;
        p->next=s->next;
        return;
    }
    while(s != p->next) /* first item is not equal with data */
    {
        if(data == p->next->data)
        {
            p->next=p->next->next;
            return;
        }
        p=p->next;
    }
}
void display(plist pl)
{
    plist s,p;
    s=p=pl;
    printf("%5d", p->data); /* print first item */
    p=p->next;
    while(s != p)
    {
        printf("%5d", p->data);
        p=p->next;
    }
    printf("/n/n");
}
void main()
{
    int f;
    plist pl;
    pl=init_list();
    insert_item(pl, 1, 1);
    insert_item(pl, 2, 3);
    insert_item(pl, 3, 5);
    insert_item(pl, 4, 7);
    insert_item(pl, 5, 9);
    display(pl);
    printf("Finding 3.../n");
    f=find_item(pl, 3);
    if(f)
        printf("True find 3/n");
    else
        printf("False find 3.../n");
    printf("/nDeleting 1.../n");
    delete_item(pl->next, 1);
    display(pl->next);
    getch();
}