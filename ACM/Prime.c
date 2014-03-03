#include <stdio.h>
#include <string.h>
#include <math.h>

int getPrime(int max, int* vec, int mode)
{
	int n = 2, num = 0;
	int i, tmp;

	if (mode == 1) //指定素数数量
	{
		memset(vec, 0, max * 4);
		vec[num++] = n;
		while (num < max)
		{
			tmp = ++n;
			for (i = 0; i < num; ++i)
				if (vec[i] <= ceil(sqrt(n)))
					if (tmp % vec[i] == 0)
						break;

			if (i == num)
				{
					vec[i] = n;
					++num;
				}
		}
	}
	else if (mode == 2) //指定最大数
	{
		memset(vec, 0, ((max > 100) ? (max / 3 * 4) : 120));
		vec[num++] = n;
		while (n < max)
		{
			tmp = ++n;
			for (i = 0; i < num; ++i)
				if (vec[i] <= ceil(sqrt(n)))
					if (tmp % vec[i] == 0)
						break;

			if (i == num)
				{
					vec[i] = n;
					++num;
				}
		}
	}

	return num;
}

// int main()
// {
// 	int v[1000];
// 	int i, j;
// 	j = getPrime(1000, v, 2);

// 	for (int i = 0; i < j; ++i)
// 	{
// 		printf("%d is %d in %d nums\n", v[i], i + 1, j);
// 	}
// }