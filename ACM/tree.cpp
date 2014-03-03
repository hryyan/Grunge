#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
using namespace std;

struct Node
{
	Node *left, *right;
	int value;
	bool haveValue;
};

Node* newNode()
{
	Node *u = (Node*)malloc(sizeof(Node));
	if (u != NULL)
	{
		u->left = u->right = NULL;
		u->haveValue = false;
		u->value = 0;
	}
	return u;
}

bool addNode(Node *n, Node *where, int value, bool insertLeft)
{
	if (insertLeft)
		if (where->left)
			return false;
		else
		{
			where->left = n;
			where->left->haveValue = true;
			where->left->value = value;
		}
	else
		if (where->right)
			return false;
		else
		{
			where->right = n;
			where->right->haveValue = true;
			where->left->value = value;
		}
}

void bfs(Node* root)
{
	if (!root)
		return;
	queue<Node*> nodeQ;
	Node *tmp;
	nodeQ.push(root);
	while (!nodeQ.empty())
	{
		tmp = nodeQ.front();
		nodeQ.pop();
		printf("%d\n", tmp->value);
		if (tmp->left != NULL)
			nodeQ.push(tmp->left);
		if (tmp->right != NULL)
			nodeQ.push(tmp->right);
	}
}

int main()
{
	int num;
	bool which;
	scanf("%d", &num);
	queue<Node*> nodeQ;
	Node *root, *tmp;
	root = newNode();
	nodeQ.push(root);
	for (int i = 0; i < num; ++i)
	{
		tmp = nodeQ.front();
		if (!tmp->left)
		{
			Node *n = newNode();
			addNode(n, tmp, i, true);
			nodeQ.push(n);
			continue;
		}
		else if (!tmp->right)
		{
			Node *n = newNode();
			addNode(n, tmp, i, false);			
			nodeQ.push(n);
			continue;
		}
		nodeQ.pop();
	}
	bfs(root);
	return 0;
}