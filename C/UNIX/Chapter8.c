// 8-1 fork函数实例
#include <stdio.h>

int glob = 6;
char buf[] = "a writer to stdout\n";

int main(void)
{
	int var;
	pid_t pid;

	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1)
		printf("write error\n");
	printf("before fork\n");

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		glob++;
		var++;
	}
	else
		sleep(2);

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	return 0;
}

// 8-2 vfork函数实例
#include <unistd.h>
#include <sys/types.h>

int glob = 6;

int main(void)
{
	int var;
	pid_t pid;

	var = 88;
	printf("before vfork\n");
	if ((pid = vfork() < 0))
	{
		printf("vfork error\n");
	}
	else if (pid == 0)
	{
		++glob;
		++var;
		_exit(0);
	}
	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}

// 8-3 打印exit状态的说明
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void pr_exit(int status)
{
	if (WIFEXITED(status))
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("abnormal termination, signal number = %d%s\n", WTERMSIG(status),
	#ifdef WCOREDUMP
		WCOREDUMP(status) ? " (core file generated)" : "");
	#else 
		"");
	#endif
		else if (WIFSTOPPED(status))
			printf("child stopped, signal number = %d\n", WSTOPSIG(status));
}

// 8-4 演示不同的exit值
#include <sys/wait.h>
#include <time.h>

int main(void)
{
	pid_t pid;
	int status;

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		sleep(1);
		exit(7);		
	}

	if (wait(&status) != pid)
		printf("wait error\n");
	pr_exit(status);

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		sleep(1);
		abort();
	}

	if (wait(&status) != pid)
		printf("wait error\n");
	pr_exit(status);

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		sleep(1);
		status /= 0;
	}

	if (wait(&status) != pid)
		printf("wait error\n");
	pr_exit(status);

	return 0;
}

// 8-5 调用fork两次以避免僵尸进程
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		if ((pid = fork()) < 0)
			printf("fork error\n");
		else if (pid > 0)
			exit(0);

		sleep(2);
		printf("second child, parent pid = %d\n", getppid());
		exit(0);
	}

	if (waitpid(pid, NULL, 0) != pid)
		printf("waitpid error\n");
	exit(0);
}

// 8-6 具有竞争条件的程序
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static void charatatime(char*);

int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
		charatatime("output from child\n");
	else
		charatatime("output from parent\n");

	exit(0);
}

static void charatatime(char *str)
{
	char* ptr;
	int c;
	setbuf(stdout, NULL);
	for(ptr = str; (c = *ptr++) != 0;)
		putc(c, stdout);
}

// 8-8 exec函数实例
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

char* env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
		if (execle("/home/sar/bin/echoall", "echoall", "myarg1", "MY ARG2", (char*)0, env_init) < 0)
			printf("execle error\n");

	if (waitpid(pid, NULL, 0) < 0)
		printf("wait error\n");

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
		if (execlp("echoall", "echoall", "only 1 arg", (char*)0) < 0)
			printf("execlp error\n");

	return 0;
}

// 8-9 回送所有命令行参数和所有环境字符串
#include <stdio.h>

int main(int argc, char* argv[])
{
	int i;
	char **ptr;
	extern char **environ;

	for (i = 0; i < argc; ++i)
		printf("argv[%d]: %s\n", i, argv[i]);

	for (ptr = environ; *ptr != 0; ++ptr)
		printf("%s\n", *ptr);

	exit(0);
}

// 8-10 执行一个解释器文件的程序
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	pid_t pid;

	if ((pid = fork()) < 0)
		printf("fork error\n");
	else if (pid == 0)
	{
		if (execl("/home/vincent/apue/chapter8/testinterp", "testinterp", "myarg1", "MY ARG2", (char*)0) < 0)
			printf("execl error\n");
	}
	if (waitpid(pid, NULL, 0) < 0)
		printf("waitpid error\n");
	return 0;
}

// 8-11 作为解释器文件的awk程序
#! /bin/awk -f
BEGIN {
	for (i = 0; i < ARGC; ++i)
		printf "ARGV[%d]\n", i, ARGV[i]
	exit
}

// 8-12 system函数（没有信号处理）
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>

int system(const char* cmdstring)
{
	pid_t pid;
	int status;

	if (cmdstring == NULL)
		return 1;

	if ((pid = fork()) < 0)
	{
		status = -1;
	}
	else if (pid == 0)
	{
		execl("/bin/sh", "sh", "-c", cmdstring, (char*)0);
		_exit(127);
	}
	else
	{
		while(waitpid(pid, &status, 0) < 0)
		{
			if (errno != EINTR)
			{
				status = -1;
				break;
			}
		}
	}
	return 0;
}

// 8-13 调用system函数
#include <stdio.h>
int main(void)
{
	int status;

	if ((status = system("date")) < 0)
		printf("system() error\n");
	pr_exit(status);

	if ((status = system("nosuchcommand")) < 0)
		printf("system() error\n");
	pr_exit(status);

	if ((status = system("who; exit 44")) < 0)
		printf("system() error\n");
	pr_exit(status);

	return 0;
}

// 8-14 用system执行命令行
#include <stdio.h>
int main(int argc, char** argv)
{
	int status;

	if (argc < 2)
		printf("command-line argument required\n");

	if ((status = system(argv[1])) < 0)
		printf("system() error\n");
	pr_exit(status);

	return 0;
}

// 8-15 打印实际和有效用户ID
#include <stdio.h>

int main(void)
{
	printf("real uid = %d, effective uid = %d\n", getuid(), geteuid());
	return 0;
}