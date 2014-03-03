#include <stdio.h>
#include <stdlib.h>

struct _node
{
    char data;
    struct _node *lchild;
    struct _node *rchild;
};
typedef struct _node node, *pnode;

pnode create_tree()
{
    pnode pt;
    char data;
    scanf("%c", &data);
    getchar();
    if (data == ' ')
        pt = NULL;
    else
    {
        pt = (pnode)malloc(sizeof(node));
        pt->data = data;
        pt->lchild = create_tree();
        pt->rchild = create_tree();
    }
    return pt;
}

void print_pretree(pnode ps)
{
    if (ps != NULL)
    {
        printf("%3c\n", ps->data);
        print_pretree(ps->lchild);
        print_pretree(ps->rchild);
    }
}

void main()
{
    pnode ps;
    ps = create_tree();
    print_pretree(ps);
    printf("\n");
}