#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 1024
#define SHM_KEY 0x1234

struct shmseg
{
    int cnt;
    int complete;
    char buf[BUF_SIZE];
};

int fill_buffer(char *buffptr, int size);

int main(int argc, char ** argv)
{
    int shmid, numtimes;
    struct shmseg *shmp;
    char *bufptr;
    int spaceavalible;

    printf("pid is: %d", getpid());
    printf("ppid is: %d", getppid());
    exit(0);
}