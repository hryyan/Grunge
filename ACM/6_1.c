#include <stdio.h>
#include <stdlib.h>

int maxy(int m,int n)
{
	int r;
	if(m<n)
	{
		r=m;
		m=n;
		n=r;
	}
	do
	{
		r=m%n;
		m=n;
		n=r;
	}while(n!=0);
	return (m);
}

int main()
{
	int p,q;
	freopen("6.input", "r", stdin);
	while(scanf("%d %d",&p,&q)!=EOF)
	{
		printf("%d\n",p+q-maxy(p,q));
	}
	return 0;
}
