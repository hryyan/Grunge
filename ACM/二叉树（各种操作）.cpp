#include <stdio.h>
#include <stdlib.h>

struct _node
{
    char data;
    struct _node lchild;
    struct _node rchild;
};
typedef struct _node node, *Pnode;

int count_l = 0;
int count_n = 0;

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

void print_midtree(pnode ps)  
{  
    if(ps != NULL)  
    {  
        print_midtree(ps->lchild);  
      
        printf("%3c", ps->data);  
        print_midtree(ps->rchild);     
    }  
}

void print_posttree(pnode ps)  
{  
    if(ps != NULL)  
    {  
        print_posttree(ps->lchild);  
        print_posttree(ps->rchild);  
        printf("%3c", ps->data);  
    }  
}

int count_leaf(pnode ps)
{
    if (ps != NULL)
    {
        if (ps->lchild == NULL && ps->rchild == NULL)
            count_l++;
        count_leaf(ps->lchild);
        count_leaf(ps->rchild);
    }
    return count_l;
}

int count_node(pnode ps)
{
    if (ps != NULL)
    {
        count_n++;
        count_node(ps->lchild);
        count_node(ps->rchild);
    }
    return count_n;
}

int count_depth(pnode ps)
{
    int ldep, rdep;
    if (ps == NULL)
        return 0;
    else 
    {
        ldep = count_depth(ps->lchild);
        rdep = count_depth(ps->rchild);

        return ldep > rdep ? (ldep+1) : (rdep+1);
    }
}

void main()  
{  
    pnode ps;  
    ps=create_tree();  
      
    printf("pre order.../n");  
    print_pretree(ps);  
    printf("/n");  
    printf("mid order.../n");  
    print_midtree(ps);  
    printf("/n");  
    printf("post order.../n");  
    print_posttree(ps);  
    printf("/n");  
    printf("number of leaf is: %d/n", count_leaf(ps));  
    printf("number of node is: %d/n", count_node(ps));  
    printf("max  of  depth is: %d/n", count_depth(ps));  
}  