#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    // variables that will be shared.
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
        printf("hello ya\n");
    }
    else
    {
        int spinCount = 100000;
        int h = 100;
        for (size_t i = 0; i < spinCount; i++)
        {
            h += 1;
        }

        printf("goodbye ya\n");
    }

    return 0;
}
