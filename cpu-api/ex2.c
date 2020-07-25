#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{

    close(STDOUT_FILENO);
    int file_ret = open("./ex2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
    fprintf(stderr, "file_ret (%d)\n", file_ret);
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child: redirect standard output to a file

        char str[] = "qingchun\n";
        int count = 100;
        for (size_t i = 0; i < count; i++)
        {
            write(file_ret, str, 9);
        }

        // now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p4.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
    }
    else
    {
        // parent goes down this path (original process)
        
        char str[] = "baba!\n";
        int count = 100;
        
        for (size_t i = 0; i < count; i++)
        {
            write(file_ret, str, sizeof(str));
        }
        int wc = wait(NULL);
        assert(wc >= 0);
    }
    return 0;
}
