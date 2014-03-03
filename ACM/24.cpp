#include <stdio.h>

#define MAXN 15+5
int matrix[MAXN][MAXN];
int verifyMatrix[MAXN+2][MAXN+2];

bool verify(int n)
{
	for (int i = 1; i < n+1; ++i)
		for (int j = 1; j < n+1; ++j)
		{
			int sum = verifyMatrix[i][j-1]+verifyMatrix[i][j+1]+verifyMatrix[i-1][j]+verifyMatrix[i+1][j];
			if (sum % 2 == 1)
				return false;
		}
	return true;
}

void generate(int n)
{
	for (int i = 2; i < n+1; ++i)
		for (int j = 1; j < n+1; ++j)
		{
			if (verifyMatrix[i-1][j-1]+verifyMatrix[i-2][j]+verifyMatrix[i-1][j+1] == 1)
				verifyMatrix[i][j] == 1;
			else
				verifyMatrix[i][j] == 0;
		}
	return;
}

int main()
{
	int m, n, tmp;
	scanf("%d", &m);
	while (m--)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; ++i)
			for (int j = 0; j < n; ++j)
			{
				scanf("%d", &tmp);
				matrix[i][j] = tmp;
			}
		for (int i = 1; i < n+1; ++i)
			for (int j = 1; i < n+1; ++i)
				verifyMatrix[i][j] = matrix[i-1][j-1];
		
	}
}