#include <stdio.h>

int main(int argc, char const *argv[])
{
	int* a;
	a[0] = 1;
	a[1] = 2;
	printf("%d %d", a[0], a[1]);
	return 0;
}