#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void printX(int x, char *suffix)
{
    printf("process [pid:%d]: x is %d %s\n", (int)getpid(), x, suffix);
}

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    // variables that will be shared.
    int x = 100;
    printf("x is (%d)\n", x);
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printX(x, "before setting x=0");
        x = 0;
        printX(x, "after setting x=0");
    }
    else
    {
        printX(x, "before setting x=5");
        x = 5;
        printX(x, "after setting x=5");
    }

    printX(x, "after everything");

    return 0;
}
