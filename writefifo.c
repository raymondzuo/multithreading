#include<stdio.h>
#include<stdlib.h>   // exit
#include<fcntl.h>    // O_WRONLY
#include<sys/stat.h>
#include<time.h>     // time

int main()
{
    int fd;
    int n, i;
    char buf[1024];
    time_t tp;

    printf("I am %d process", getpid());

    if((fd = mkfifo("fifo2", O_WRONLY)) < 0)
    {
        printf("Open fifo error!");
        exit(-1);
    }

    for(i = 0; i < 10; i++)
    {
        time(&tp);
        n=sprintf(buf,"Process %d's time is %s",getpid(),ctime(&tp));
        printf("Send message: %s", buf); // 打印

        if(write(fd, buf, n+1) < 0)  // 写入到FIFO中
        {
            perror("Write FIFO Failed");
            close(fd);
            exit(1);
        }
        sleep(2);  // 休眠1秒write(fd, buf, n + 1);
    }

    close(fd);
    return 0;
}