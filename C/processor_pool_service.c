#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>

static  int      nchildren;
static  pid_t    *pids;
static  

void    sig_int(int signo);
pid_t   child_make(int);
void    child_main(int);

int main(int argc, char **argv)
{   
    int i;

    if (argc != 2)
    {
        printf("Usage Error!\n");
    }

    nchildren = atoi(argv[1]);
    pids = calloc(nchildren, sizeof(pid_t));

    for (i = 0; i < nchildren; i++)
    {
        pids[i] = child_make(i);
    }

    signal(SIGINT, sig_int);

    for ( ; ; )
    {
        pause();
    }
}

void sig_int(int signo)
{
    int i;
    for (i = 0; i < nchildren; ++i)
    {
        kill(pids[i], SIGTERM);
    }

    while (wait(NULL) > 0)
        ;

    if (errno != ECHILD)
    {
        printf("wait error\n");
    }
    exit (0);
}

pid_t child_make (int i)
{
    pid_t pid;
    if ((pid = fork() > 0))
    {
        return pid;
    }
    printf("I'm processor %d, pid = %d\n", i, getpid());
    exit(0);
}