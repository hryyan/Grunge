//4-1 对每个命令行参数打印文件类型

#include "aque.h"

int main(int argc, char* argv[])
{
	int 	i;
	struct 	stat buf;
	char 	*ptr;

	for (i = 1; i < argc; ++i)
	{
		printf("%s: ", argv[i]);
		if (lstat(argv[i], &buf) < 0)
		{
			err_ret("lstat error");
			continue;
		}
		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);
	}
	exit(0);
}

//4-2 access函数实例

#include "aque.h"
#include <fcntl.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <pathname>");
	if (access(argv[1], R_OK) < 0)
		err_ret("access error for %s", argv[1]);
	else
		printf("read access OK\n");
	if (open(argv[1], O_RDONLY) < 0)
		err_ret("open error for %s", argv[1]);
	else
		printf("open for reading OK\n");
	exit(0);
}

//4-3 umask函数实例

#include "aque.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void)
{
	umask(0);
	if (create("foo", RWRWRW) < 0)
		err_sys("create error for foo");
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (create("bar", RWRWRW) < 0)
		err_sys("create error for bar");
	exit(0);
}

//4-4 chmod函数实例

#include "aque.h"

int main(void)
{
	struct stat statbuf;

	if (stat("foo", &statbuf) < 0)
		err_sys("stat error for foo");
	if (chmod("foo", (statbuf.st_mode & ~S_IXGRP) | S_ISGID) < 0)
		err_sys("chmod error for foo");

	if (chmod("bar", S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH) < 0)
		err_sys("chmod error for foo");
	exit(0);
}

//4-5 打开一个文件，然后unlink它

#include "aque.h"
#include <fcntl.h>

int main(void)
{
	if (open("tempfile", O_RDWR) < 0)
		err_sys("open error");
	if (unlink("tempfile") < 0)
		err_sys("unlink error");
	printf("file unlinked");
	sleep(15);
	printf("done\n");
	exit(0);
}

//4-6 utime函数实例

#include "aque.h"
#include <fcntl.h>
#include <utime.h>

int main(int argc, char* argv[])
{
	int				i, fd;
	struct stat 	statbuf;
	struct utimbuf	timebuf;

	for (i = 1; i < argc; i++)
	{
		if (stat(argv[i], &statbuf) < 0)
		{
			err_ret("%s: stat error", argv[i]);
			continue;
		}
		if ((fd = open(argv[i], O_RDWR | O_TRUNC)) < 0)
		{
			err_ret("%s: open error", argv[i]);
			continue;
		}
		close(fd);
		timebuf.actime = statbuf.st_atime;
		timebuf.modtime = statbuf.st_mtime;
		if (utime(argv[i], &timebuf) < 0)
		{
			err_ret("%s: utime error", argv[i]);
			continue;
		}
	}
	exit(0);
}

//4-7 递归降序遍历目录层次结构，并按文件类型计数

#include "aque.h"
#include <dirent.h>
#include <limit.h>

typedef	int Myfunc(const char*, const struct stat*, int);
static Myfunc 	myfunc;
static int 		myftw(char*, Myfunc*);
static int 		dopath(Myfunc*);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, ntot;

int main (int argc, char* argv[])
{
	int 	ret;

	if (argc != 2)
		err_quit("usage:	ftw  <starting-pathname>");

	ret = myftw(argv[1], myfunc);

	ntot = nreg + nblk + nchr + nfifo + nslink + nsock;
	if (ntot == 0)
		ntot = 1;
	printf("regular files	= %7ld, %5.2f %%\n", nreg, nreg*100.0/ntot);
	printf("directories		= %7ld, %5.2f %%\n", ndir, ndir*100.0/ntot);
	printf("block special	= %7ld, %5.2f %%\n", nblk, nblk*100.0/ntot);
	printf("char special	= %7ld, %5.2f %%\n", nchr, nchr*100.0/ntot);
	printf("FIFOs			= %7ld, %5.2f %%\n", nfifo, nfifo*100.0/ntot);
	printf("symbolic links	= %7ld, %5.2f %%\n", nslink, nslink*100.0/ntot);
	printf("sockets			= %7ld, %5.2f %%\n", nsock, nsock*100.0/ntot);

	exit(ret);
}

#define FTW_F	1
#define FTW_D	2
#define FTW_DNR	3
#define FTW_NS	4

static char *fullpath;

static int myftw(char* pathname, Myfunc* func)
{
	int len;
	fullpath = path_alloc(&len);

	strncpy(fullpath, pathname, len);
	fullpath[len-1] = 0;

	return(dopath(func));
}


static int dopath(Myfunc* func)
{
	struct stat 	statbuf;
	struct dirent	*dirp;
	DIR 			*dp;
	int 			ret;
	char 			*ptr;

	if (lstat(fullpath, &statbuf) < 0)
		return(func(fullpath, &statbuf, FTW_NS));
	if (S_ISDIR(statbuf.st_mode) == 0)
		return(func(fullpath, &statbuf, FTW_F));

	if ((ret = func(fullpath, &statbuf, FTW_D)) != 0)
		return(ret);

	ptr = fullpath + strlen(fullpath);
	*ptr++ = '/';
	*ptr = 0;

	if ((dp = opendir(fullpath)) == NULL)
		return(func(fullpath, &statbuf, FTW_DNR));

	while ((dirp = readdir(dp)) != NULL)
	{
		if (strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name, "..") == 0)
			continue;

		strcpy(ptr, dirp->d_name);

		if ((ret = dopath(func)) != 0)
			break;
	}
	ptr[-1] = 0;

	if (closedir(dp) < 0)
		err_ret("can't close directory %s", fullpath);

	return(ret);
}

static int myfunc(conts char* pathname, const struct *statptr, int type)
{
	switch (type) {
	case FTW_F:
		switch (statptr->st_mode & S_IFMT)
		{
		case S_IFREG: 	nreg++;		break;
		case S_IFBLK: 	nblk++; 	break;
		case S_IFCHR:	nchr++; 	break;
		case S_IFIFO:	nfifo++;	break;
		case S_IFLNK:	nslink++; 	break;
		case S_IFSOCK:	nsock++;	break;
		case S_IFDIR:	
			err_dump("for S_IFDIR for %s", pathname);
		}
		break;

	case FTW_D:
		ndir++;
		break;

	case FTW_DNR:
		err_ret("can't read directory %s", pathname);
		break;

	case FTW_NS:
		err_ret("stat error for %s", pathname);
		break;

	default:
		err_dump("unknown type %d for pathname %s", type, pathname);
	}
	return(0);
}

//4-8 chdir函数实例

#include "aque.h"

int main(void)
{
	if (chdir("/tmp") < 0)
		err_sys("chdir error");
	printf("chdir to /tmp succeeded\n");
	exit(0);
}

//4-9 getcwd函数实例

#include "aque.h"

int main(void)
{
	char* 	ptr;
	int 	size;

	if (chdir("/usr/spool/uucppublic") < 0)
		err_sys("chdir failed");

	ptr = path_alloc(&size);
	if (getcwd(ptr, size) == NULL)
		err_sys("getcwd failed");

	printf("cwd = %s\n", ptr);
	exit(0);
}

//4-10 打印st_dev和st_rdev值

#include "aque.h"
#ifdef SOLARIS
#include <sys/mkdev.h>
#endif

int main(int argc, char const *argv[])
{
	int 		i;
	struct stat buf;

	for (i = 1; i < argc; i++)
	{
		printf("%s: ", argv[i]);
		if (stat(argv[i], &buf) < 0)
		{
			err_ret("stat error");
			continue;
		}

		printf("dev = %d/%d", major(buf.st_dev), minor(buf.st_dev));
		if (S_ISCHR(buf.st_mode) || S_ISBLK(buf.st_mode))
		{
			printf(" (%s) rdev = %d %d", (S_ISCHR(buf.st_mode)) ? "character" : "block", major(buf.st_dev), minor(buf.st_mode));
		}
		printf("\n");
	}

	exit(0);
}