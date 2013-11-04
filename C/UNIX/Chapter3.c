//3-1 测试能否对标准输入设置偏移量
//如果文件描述符引用的是一个管道、FIFO或网络套接字，则lseek返回-1
#include "aque.h"

int main(void)
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK!\n");
	exit(0);
}

//3-2 创建一个具有空洞的文件

#include "aque.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
	int fd;

	if ((fd = create("file.hole", FILE_MODE)) < 0)
		err_sys("create error");

	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	// offset now = 10

	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	// offset now = 16384

	if (write(fd, buf2, 10) != 10)
		err_sys("buf2 write error")
	// offset now = 16394

	exit(0);
}

//3-3 将标准输入复制到标准输出

#include "aque.h"

#define BUFFSIZE 4096

int main(void)
{
	int n;
	char buf[BUFFSIZE];

	while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)
		if (write(STDOUT_FILENO, buf, n) != n)
			err_sys("write error");

	if (n < 0)
		err_sys("read error");

	exit(0);
}

//3-4 对于制定的描述符打印文件标志

#include "aque.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int val;

	if (argc != 2)
		err_sys("usage: a.out <descriptor#>");

	if ((val == fcntl(atoi(argv[1]), F_GETFL, 0)) < 0)
		err_sys("fcntl error for fd %d", atoi(argv[1]));

	switch (val & O_ACCMODE) {
	case O_RDONLY:
		printf("read only");
		break;

	case O_WRONLY:
		printf("write only");
		break;

	case O_RDWR:
		printf("read write");
		break;

	default:
		err_dump("unknown access mode");
	}

	if (val & O_APPEND)
		printf(", append");
	if (val & O_NONBLOCK)
		printf(", noblocking");
#if defined(O_SYNC)
	if (val & O_SYNC)
		printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if (val & O_FSYNC)
		printf(", synchronous writes");
#endif
	putchar('\n');
	exit(0);
}

//3-5 对一个文件描述符打开一个或多个文件状态标志

#include "aque.h"
#include <fcntl.h>

void set_fl(int fd, int flags)
{
	int val;

	if ((val = fcntl(fd, F_GETFL)) < 0)
		err_sys("fcntl F_GETFL error");

	val |= flags;

	if (fcntl(fd, F_SETFL) < 0)
		err_sys("fcntl F_SETFL error");
}

//习题3-2

int my_dup2(int filedes, int filedes2)
{
	int* tmp;
	int i = 0;
	if (filedes == filedes2)
		return filedes2;
	while ((tmp[i] = dup(filedes)) != filedes2)
		if (tmp[i++] < 0)
			err_sys("dup error!");
	while (i >= 0)
		if (close(tmp[i]) < 0)
			err_sys("close error!");
	return filedes2;
}