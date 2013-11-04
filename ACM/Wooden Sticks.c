#include <stdio.h>
#define NUM 1024

int main(int argc, char const *argv[])
{
	FILE* pFile;
	char mystring[NUM];
	pFile = fopen("Wooden Sticks.txt", "r");
	int a;
	while(!feof(pFile))
	{
		fscanf(pFile, "%d", &a);
	}
	printf ("d", a)
	fclose(pFile);
	return 0;
}