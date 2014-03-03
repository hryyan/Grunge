#include <stdio.h>
#include <stdlib.h>

#define DataType char

/* 树的结构定义 */
struct _tree
{
    DataType data;
    struct _tree *lchild;
    struct _tree *rchild;
};
typedef struct _tree tree, *ptree;

/* 栈的结构定义 */
struct _node
{
    ptree pt;
    struct _node *next;
};
typedef struct _node node, *pnode;

struct _stack
{
    int size;
    pnode ptop;
};
typedef struct _stack stack, *pstack;

/* 堆的结构定义 */
struct _queue
{
    pnode front;
    pnode rear;
};
typedef struct _queue queue, *pqueue;

/* 栈的数据操作 */
pstack init_stack()
{
    pnode pn = NULL;
    pstack ps = NULL;
    pn = (pnode)malloc(sizeof(node));
    ps = (pstack)malloc(sizeof(stack));
    pn->pt = NULL;
    pn->next = NULL;
    ps->ptop=pn;
    return ps;
}

int isEmpty_stack(pstack ps)
{
    if (ps->ptop == NULL)
        return 1;
    else
        return 0;
}

void push_stack(pstack ps, ptree pt)
{
    pnode pn = NULL;
    pn = (pnode)malloc(sizeof(node));
    pn->pt = pt;
    pn->next = ps->ptop;
    ps->ptop = pn;
}

ptree pop_stack(pstack ps)
{
    ptree pt = NULL;
    pnode pn = NULL;
    if (!isEmpty_stack(ps))
    {
        pn = ps->ptop;
        ps->ptop = ps->ptop->next;
        pt = pn->pt;
        free(pn);
    }
    return pt;
}

ptree gettop_stack(pstack ps)  
{  
    if(!empty_stack(ps))  
        return ps->ptop->pt;
}

/* 堆的数据操作 */
queue init_queue()
{
    pnode pn = NULL;
    queue qu;
    pn = (pnode)malloc(sizeof(node));
    pn->pt = NULL;
    pn->next = NULL;
    qu.front = qu.rear = pn;
    return qu;
}

int isEmpty_queue(queue qu)
{
    if (qu.front == qu.rear)
        return 1;
    else
        return 0;
}

void en_queue(queue qu, ptree pt)
{
    pnode pn = NULL;
    pn = (pnode)malloc(sizeof(node));
    pn->pt = pt;
    pn->next = qu.rear->next;
    qu.rear = pn;
}

ptree de_queue(queue qu)
{
    ptree pt = NULL;
    pnode pn = NULL;
    if (!isEmpty_queue(qu))
    {
        pn = qu.front;
        qu.front = qu.front->next;
        pt = pn->pt;
        free(pn);
    }
    return pt;
}

/* 树的数据操作 */
ptree init_tree()
{
    ptree pt = NULL;
    pt = (ptree)malloc(sizeof(tree));
    pt->data = '0';
    pt->lchild = NULL;
    pt->rchild = NULL;
    return pt;
}

ptree create_tree()  
{  
    char ch;  
    ptree pt=NULL;  
      
    scanf("%c", &ch);  
    getchar();    
    if(ch==' ')  
        return NULL;  
    else  
    {  
        pt=(ptree)malloc(sizeof(tree));  
        pt->data=ch;  
        pt->lchild=create_tree();  
        pt->rchild=create_tree();  
    }  
    return pt;  
}

void print_pretree(ptree pt)  
{  
    if(pt!=NULL)  
    {  
        printf("%3c", pt->data);  
        print_pretree(pt->lchild);  
        print_pretree(pt->rchild);  
    }  
}

void print_pretree2(ptree pt)
{
    pstack ps = NULL;
    ptree p = NULL;
    ps = init_stack();
    p = pt;
    while (p != NULL || !isEmpty_stack(ps))
    {
        while (p! = NULL)
        {
            printf("%3c\n", p->data);
            push_stack(ps, p);
            p = p->lchild;
        }
        if (!isEmpty_stack(ps))
        {
            p = pop_stack(ps);
            p = p->rchild;
        }
    }
}

void print_midtree(ptree pt)
{
    if (pt != NULL)
    {
        print_midtree(pt->lchild);
        printf("%3c\n", pt->data);
        print_midtree(pt->rchild);
    }
}

void print_midtree2(ptree pt)
{
    pstack ps = NULL;
    ptree p = NULL;
    ps = init_stack();
    p = pt;
    while (p != NULL || !isEmpty_stack(ps))
    {
        while (p != NULL)
        {
            push_stack(ps, p);
            p = p->lchild;
        }
        if (!isEmpty_stack(ps))
        {
            p = pop_stack(ps);
            printf("%3c\n", p->data);
            p = p->rchild;
        }
    }
}

void print_posttree(ptree pt)
{
    if (pt != NULL)
    {
        print_posttree(pt->lchild);
        print_posttree(pt->rchild);
        printf("%3c\n", pt->data);
    }
}

void print_posttree2(ptree pt)
{
    pstack ps = NULL;
    ptree p = NULL;
    ptree p2 = NULL;
    ptree lastvisit = NULL;
    ps = init_stack();
    p = pt;
    while (p != NULL || !isEmpty_stack(ps))
    {
        while (p != NULL)
        {
            push_stack(ps, p);
            p = p->lchild;
        }
        p2 = gettop_stack(ps);
        if (p2->rchild==NULL || p2->rchild==lastvisit)
        {
            printf("%3c\n", p2->data);
            lastvisit = pop_stack(ps);
        }
        else
            p = p2->rchild;
    }
}