#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>

int main()
{
    int fd;
    int len;
    char buf[1024];

    if(mkfifo("fifo2", 0666) < 0 && errno!=EEXIST) // 创建FIFO管道
        perror("Create FIFO Failed");

    if((fd = open("fifo1", O_RDONLY)) < 0)  // 以读打开FIFO
    {
        perror("Open FIFO Failed");
        exit(1);
    }
    
    while((len = read(fd, buf, 1024)) > 0) // 读取FIFO管道
        printf("Read message: %s", buf);

    close(fd);  // 关闭FIFO文件
    return 0;
}