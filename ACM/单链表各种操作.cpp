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
    plist pl;
    pl = (plist)malloc(sizeof(node));
    if (pl == NULL)
    {
        printf("init list, malloc is failed\n");
        return NULL;
    }
    pl->data = -1;
    pl->next = NULL;
    return pl;
}

int isEmpty_list(plist pl)
{
    if (pl == NULL || pl->next == NULL)
        return 1;
    else
        return 0;
}

plist clear_list(plist pl)
{
    pl = NULL;
    return pl;
}

void destroy_list(plist pl)
{
    plist p, s;

    p = pl->next;
    while (p)
    {
        s = p;
        p = p->next;
        free(s);
    }

    pl = NULL;
}

void insert_item(plist pl, int i, int e)
{
    int j = 1;
    plist p, s;
    p = pl;
    while (p && j<i)
    {
        p = p->next;
        j++;
    }
    if (!p || j>i) /* >len or <1 */
        printf("Insert failed...\n");
    s = (plist)malloc(sizeof(node));
    s->data = e;
    s->next = p->next;
    p->next = s;
}

void display(plist pl)
{
    plist p;
    p = pl->next;
    while (p)
    {
        printf("%d\n", p->next);
        p = p->next;
    }
    printf("\n\n");
}

int getbyid_item(plist pl, int i)
{
    plist p;
    p = pl->next;
    int j = 1;
    while (p && i>j)
    {
        p = p->next;
        j++;
    }
    if (!p || j>i)
    {
        printf("filed\n");
        exit(1);
    }
    return p->data;
}

int locate_item(plist pl, int e)
{
    plist p;
    p = pl->list;
    int j = 1;
    while (p->data != e && p->next)
    {
        p = next;
        j++;
    }
    if (p->data == e)
        return j;
    else
    {
        printf("There is n %d in list\n", e);
        return -1;
    }
}

void delete_item(plist pl, int i, int *e)
{
    plist p, q;
    p = pl;
    int j = 1;
    while (p->next && j<i)
    {
        p = p->next;
        j++;
    }
    if (!(p->next) || j>i) /* >len or <1 */
    {
        printf("failed\n");
        return;
    }
    q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
}

int len_item(plist pl)
{
    int j = 0;
    plist p = pl;
    while (pl && p->next)
    {
        j++;
        p = p->next;
    }
    return j;
}

plist traverse_list(plist pl)
{
    plist h, p, s;

    if (!pl || !pl->next)
        return pl;
    h = pl->next;
    s = h;
    p = s->next;
    h->next = NULL;
    while (p)
    {
        s = p;
        p = p->next;
        s->next = h;
        h = s;
    }
    pl->next = h;

    return pl;
}

void main()
{
    int len, pos, *del;
    plist pl = NULL;
    del = (int*)malloc(sizeof(int));
    pl = init_list();
    isEmpty_list(pl);
    insert_item(pl, 1, 1);
    insert_item(pl, 2, 3);
    insert_item(pl, 3, 5);
    insert_item(pl, 4, 7);
    insert_item(pl, 5, 9);
    insert_item(pl, 6, 11);
    display(pl);
    len = len_list(pl);
    printf("link list len: %d\n", len);
    pos = locate_item(pl, 7);
    printf("num 7 pos: %d\n", pos);
    delete_item(pl, 3, del);
    printf("delete pos 3 num: %d\n", *del);
    display(pl);
    printf("link list traverse...\n");
    pl = traverse_list(pl);
    display(pl);
    destroy_list(pl);
    getch();
}