#include <stdio.h>
#include <string.h>

int cmp(char* a, char* b);

int main(int argc, char*argv[])
{
	int i;
	FILE* fp;
	FILE* tmp;
	char b[4096] = "#! /usr/bin/perl\n";
	char c[4096] = "#! /bin/perl\n";
	char buf[4096];

	for (i = 1; i < argc; ++i)
	{
		fp = fopen(argv[i], "r+");
		fgets(buf, 4096, fp);
		if (cmp(buf, b) == 1)
		{
			printf("2");
			tmp = tmpfile();
			memset(buf, 0, sizeof(char) * 4096);
			strcpy(buf, c);
			fputs(buf, tmp);
			while (fgets(buf, 4096, fp) != NULL)
				fputs(buf, tmp);
			rewind(tmp);
			rewind(fp);
			while (fgets(buf, 4096, tmp) != NULL)
				fputs(buf, fp);
		}
	}
}

int cmp(char* a, char* b)
{
	int i;
	printf("cmp");
	for (i = 0; i < sizeof(a); ++i)
	{
		if (a[i] != b[i])
			return 0;
	}
	return 1;
}
