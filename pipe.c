#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int fd[2];
    __pid_t pid;
    char buff[20];

    printf("haha");
    if(pipe(fd) < 0)
        printf("Create pipe error!\n");
    
    if((pid = fork()) < 0)
        printf("Fork a child process error! \n");
    else if(pid > 0)
    {
        close(fd[0]);
        printf("ready to write\n");
        write(fd[1], "hello world\n", 12);
    }
    else
    {
        close(fd[1]);
        printf("ready to read\n");
        read(fd[0], buff, 20);
        printf("%s", buff);
    }

    return 0;
}