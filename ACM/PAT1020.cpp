/*************************************************************************
	> File Name: PAT1020.cpp
	> Author: 
	> Mail: 
	> Created Time: 2014年08月04日 星期一 16时51分36秒
 ************************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;

const int N = 30;

struct Node
{
    int value;
    Node* lchild;
    Node* rchild;
};

int postOrder[N];
int inOrder[N];

void createTree(int b1, int e1, int b2, int e2, Node* &curNode)
{
    if (b1<0 || b2<0 || b1>e1 || b2>e2)
        return;
    if (curNode == NULL)
        curNode = new Node();
    curNode->lchild = NULL;
    curNode->rchild = NULL;
    curNode->value = postOrder[e1];

    int i = 0, j = 0;
    for (i=e2, j=e1; i>=b2; i--, j--)
        if (inOrder[i] == postOrder[e1])
            break;
    createTree(b1, j-1, b2, i-1, curNode->lchild);
    createTree(j, e1-1, i+1, e2, curNode->rchild);
}

void levelOrder(Node* root)
{
    if (root == NULL)
        return;
    queue<Node*> Q;
    Q.push(root);
    bool isFirst = true;
    while (!Q.empty())
    {
        Node* tmp = Q.front();
        Q.pop();
        if (tmp == NULL);
            return ;
        if (isFirst)
        {
            cout << tmp->value;
            isFirst = false;
        }
        else
            cout << " " << tmp->value;

        if (tmp->lchild)
            Q.push(tmp->lchild);
        if (tmp->rchild)
            Q.push(tmp->rchild);
    }
    cout << endl;
}

int main()
{
    freopen("PAT1020.input", "r", stdin);

    int N;
    cin >> N;
    
    for (int i=0; i<N; i++)
        cin >> postOrder[i];
    for (int i=0; i<N; i++)
        cin >> inOrder[i];

    Node *root = NULL;
    createTree(0, N-1, 0, N-1, root);
    levelOrder(root);
    return 0;
}
