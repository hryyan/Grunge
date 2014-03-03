#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAXN=300;
char s[MAXN];

struct Node
{
	int have_value;
	int v;
	struct Node *left, *right;
};

Node *root;
int failed;

Node* newnode()
{
	Node* u = (Node*)malloc(sizeof(Node));
	if (u != NULL)
	{
		u->have_value = 0;
		u->left = u->right = NULL;
	}
	return u;
}

void addnode(int v, char *s)
{
	int n = strlen(s);
	Node* u = root;

}

int read_input()
{
	failed = 0;
	root = newnode();
	for (;;)
	{
		if (scanf("%s", s) != 1) return 0;
		if (!strcmp(s, "()")) break;
		int v;
		sscanf(&s[l], "%d", &v);
		addnode(v, strchr(s, ',')+1);
	}
	return 1;
}

int main()
{
	return 0;
}