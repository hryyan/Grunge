#include <stdio.h>

int gcd(int a, int b)
{
	int c;
	while (b)
	{
		c = b;
		b = a % b;
		a = c;
	}
	return a;
}

int main(void)
{
	int a, b, c, tmp;
	//freopen("6.input", "r", stdin);

	while(scanf("%d %d", &a, &b) != EOF)
	{
		if (b > a)
		{
			c = a;
			a = b;
			b = c;
		}
		if ((tmp = a % b) == 0)
			printf("%d\n", a);
		else
			printf("%d\n", a + b - gcd(a, b));
	}
	return 0;
}