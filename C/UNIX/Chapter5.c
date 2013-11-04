// 5-1 用getc和putc将标准输入复制到标准输出
#include <stdio.h>

int main(void)
{
	int c;

	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			printf("output error\n");

	if (ferror(stdin))
		printf("input error\n");
	return 0;
}

// 5-2 用fgets和fputs将标准输入复制到标准输出
#include <stdio.h>
#define MAXLINE 4096

int main(void)
{
	char buf[MAXLINE];

	while ((c = fgets(buf, MAXLINE, stdin)) != NULL)
		if (fputs(buf, stdout) == EOF)
			printf("output error\n");

	if (ferror(stdin))
		printf("input error\n");
	return 0;
}

// 5-3 对各个标准I/O流打印缓冲状态信息
#include <stdio.h>
void pr_stdio(const char*, FILE*);

int main(void)
{
	FILE *fp;
	fputs("enter any character\n", stdout);
	if (getchar() == EOF)
		printf("getchar error\n");
	fputs("one line to standard error\n", stderr);

	pr_stdio("stdin", stdin);
	pr_stdio("stdout", stdout);
	pr_stdio("stderr", stderr);

	if ((fp = fopen("/etc/motd", "r")) == NULL)
		printf("fopen error\n");
	if (getc(fp) == EOF)
		printf("getc error\n");
	pr_stdio("/etc/motd", fp);
	return 0;
}

void pr_stdio(const char* name, FILE* fp)
{
	printf("stream = %s\n", name);
	if (fp->_IO_file_flags & _IO_UNBUFFRED)
		printf("unbuffered\n");
	else if (fp->_IO_file_flags & _IO_LINE_BUF)
		printf("line buffered\n");
	else
		printf("fully buffered\n");
	printf(", buffer size = %d\n", fp->_IO_buf_end - fp->_IO_buf_base);
}

// 5-4 tmpnam和tmpfile函数实例
#include <stdio.h>
#define MAXLINE 4096

int main(void)
{
	char name[L_tmpnam], line[MAXLINE];
	FILE* fp;
	printf("%s\n", tmpnam(NULL));
	tmpnam(name);
	printf("%s\n", name);

	if ((fp = tmpfile()) == NULL)
		printf("tmpfile error");
	fputs("one line of output\n", fp);
	rewind(fp);
	if (fgets(line, sizeof(line), fp) == NULL)
		printf("fget error");
	fputs(line, stdout);
	return 0;
}

// 5-5 演示tempnam函数
#include <stdio.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
		printf("usage: a.out <directory> <prefix>");

	printf("%s\n", tempnam(argv[1][0] != ' ' ? argv[1] : NULL, argv[2][0] != ' ' ? argv[2] : NULL));
	return 0;
}