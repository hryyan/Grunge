#include <stdio.h>

__int64 gcd(__int64 a, __int64 b)
{
	__int64 c;
	if (a < b)
	{
		c = a;
		a = b;
		b = c;
	}
	;;
	while(b)
	{
		c = b;
		b = a % b;
		a = c;
	}
	// printf("%I64d\n", a);
	return a;
}

__int64 common_multiple(__int64 a, __int64 b)
{
	__int64 c = gcd(a, b);
	return a * b / c;
}

int main(int argc, char const *argv[])
{
	int n;
	__int64 af, an, bf, bn, tmpf, tmpn, tmp1, tmp2;
	tmp1 = tmp2 = 0;
	//freopen("5.input", "r", stdin);

	scanf("%d", &n);

	while(n--)
	{
		scanf("%I64d/%I64d %I64d/%I64d", &af, &an, &bf, &bn);
		tmpn = an * bn;
		tmpf = common_multiple(af * bn, bf * an);
		// printf("%I64d/%I64d\n", tmpf, tmpn);
		while ((tmp1 = gcd(tmpf, tmpn)) != tmp2)
		{
			tmpf = tmpf / tmp1;
			tmpn = tmpn / tmp1;
			tmp2 = tmp1;
		}
		if (tmpn == 1)
			printf("%I64d\n", tmpf);
		else
			printf("%I64d/%I64d\n", tmpf, tmpn);
	}
	return 0;
}