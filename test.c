#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t cpid;
    // create pipe descriptors
    pipe(fd);

    // fork() returns 0 for child process, child-pid for parent process.
    if (fork() != 0)
    {
        // parent: writing only, so close read-descriptor.
        close(fd[0]);

        int n;
        // send the value on the write-descriptor.
        scanf("%d",&n);

        write(fd[1], &n, sizeof(n));

        // close the write descriptor
        close(fd[1]);
        cpid = wait(NULL); // parent will wait till child gets executed
        //printf("sdfsdf\n");
        if(fork()==0) // child c2 created
        {
            printf("Hi, I'm the second child\n");
            exit(0);
        }
        else
        {
            cpid = wait(NULL);
            printf("work is done thanks to c1 and c2\n");
        }
    }
    else
    {   // child: reading only, so close the write-descriptor
        close(fd[1]);
        int val;
        // now read the data
        // value of n gets stored in val
        read(fd[0], &val, sizeof(val));
        printf("Sum from 1 to %d is :",val);
        printf("%d\n",(val*(val+1))/2);

        // close the read-descriptor
        close(fd[0]);
        exit(0);
    }
    return 0;
}
