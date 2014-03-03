#include <stdio.h>
#include <stdlib.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -2

typedef int status;
typedef struct BiNode
{
    char data;
    struct BiNode* lChild;
    struct BiNode* rChild;
}BiNode, *pBiNode;

status CreateTree(BiNode** pTree);
status PreOrderTraval(BiNode* pTree);
status InOrderTraval(BiNode* pTree);
status PostOrderTraval(BiNode* pTree);
status Visit(char Data);
status ShowLeaves(BiNode* pTree);
status ShowDepth(BiNode* pTree);
status DelTree(BiNode* pTree);
status Display(BiNode* pTree, int level);
status Clear(BiNode* pTree);
BiNode *pRoot = NULL;

int main()
{
    freopen("test.input", "r", stdin);
    CreateTree(&pRoot);
    printf("\nPreOrder:");
    PreOrderTraval(pRoot);
    printf("\nInOrder:");
    InOrderTraval(pRoot);
    printf("\nPostOrder:");
    PostOrderTraval(pRoot);
    printf("\nShowLeaves:");
    ShowLeaves(pRoot);
    printf("\nShowDepth:%d", ShowDepth(pRoot));
    printf("\n------------------\n");
    Display(pRoot, 0);
    printf("\n");
    printf("\nDeleting Tree:\n");
    DelTree(pRoot);
    printf("BiTree Deleted\n");
}

status CreateTree(BiNode** pTree)
{
    char ch;
    scanf("%c", &ch);

    if (ch == '\n')
        (*pTree) = NULL;
    else
    {
        if (!((*pTree)=(BiNode*)malloc(sizeof(BiNode))))
            exit(OVERFLOW);
        (*pTree)->data = ch;
        CreateTree(&((*pTree)->lChild));
        CreateTree(&((*pTree)->rChild));
    }
    return OK;
}

status PreOrderTraval(BiNode* pTree)
{
    if (pTree)
    {
        Visit(pTree->data);
        PreOrderTraval(pTree->lChild);
        PreOrderTraval(pTree->rChild);
    }
    return OK;
}

status InOrderTraval(BiNode* pTree)
{
    if (pTree)
    {
        InOrderTraval(pTree->lChild);
        Visit(pTree->data);
        InOrderTraval(pTree->rChild);
    }
    return OK;
}

status PostOrderTraval(BiNode* pTree)
{
    if (pTree)
    {
        PostOrderTraval(pTree->lChild);
        PostOrderTraval(pTree->rChild);
        Visit(pTree->data);
    }
    return OK;
}

status Visit(char Data)
{
    printf("%c", Data);
    return OK;
}

status Display(BiNode* pTree, int level)
{
    int i;
    if (pTree == NULL)
        return FALSE;
    Display(pTree->lChild, level+1);
    for (int i = 0; i < level-1; ++i)
    {
        printf(" ");
    }
    if (level >= 1)
    {
        printf("--");
    }
    printf("%c\n", pTree->data);
    Display(pTree->rChild, level+1);
    return TRUE;
}

status ShowLeaves(BiNode* pTree)
{
    if (pTree)
    {
        ShowLeaves(pTree->lChild);
        ShowLeaves(pTree->rChild);
        if ((pTree->lChild==NULL)&&(pTree->rChild==NULL))
            Visit(pTree->data);
    }
    return OK;
}

status ShowDepth(BiNode* pTree)
{
    int ldep = 0, rdep = 0;

    if (!pTree)
        return 0;
    else
    {
        ldep = ShowDepth(pTree->lChild);
        rdep = ShowDepth(pTree->rChild);
        return ldep > rdep ? (ldep+1) : (rdep+1);
    }
}

status DelTree(BiNode* pTree)
{
    if (pTree)
    {
        DelTree(pTree->lChild);
        DelTree(pTree->rChild);
        printf("Deleting %c\n", pTree->data);
        free((void*)pTree);
    }
    return OK;
}