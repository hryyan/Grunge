// 7-2 终止处理程序实例
#include <stdio.h>

static void my_exit1(void);
static void my_exit2(void);

int main(void)
{
	if (atexit(my_exit2) != 0)
		printf("can't register my_exit2\n");
	if (atexit(my_exit1) != 0)
		printf("can't register my_exit1\n");
	if (atexit(my_exit2) != 0)
		printf("can't register my_exit2\n");

	printf("main is done\n");
	return 0;
}

static void my_exit1(void)
{
	printf("first exit handler\n");
}

static void my_exit2(void)
{
	printf("second exit handler\n");
}

// 7-3 将所有命令行参数回送到标准输出上
#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i;

	for (i = 0; i< argc; ++i)
		printf("argv[%d]: %s\n", i, argv[i]);
	return 0;
}