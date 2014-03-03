#include <stdio.h>
#include <string.h>
const int MAXD = 20;
int s[1<<MAXD];

int main()
{
	int D, I;
	while (scanf("%d%d", &D, &I) == 2)
	{
		memset(s, 0, sizeof(s));
		int k, n = (1<<D)-1;
		for (int i = 0; i < I; i++)
		{
			k = 1;
			for (;;)
			{
				s[k] = !s[k];
				k = s[k] ? k*2 : k*2+1;
				if (k > n) break;
			}
		}
		printf("%d\n", k/2);
	}
	return 0;
}

{
	while (scanf("%d%d", &D, &I) == 2)
		if (I%2) { k = k*2; I = (I+1)/2;}
		else { k = k*2+1; I /= 2;}
	printf("%d\n", k);
}