#include <pthread.h>
#include <iostream>

using std::cout;
using std::endl;

#define THREAD_NUMS 5

void* PrintHelloPthread(void *args)
{
    cout << "THREAD  Hello, pthread : " << (long)args << endl;
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    pthread_attr_t pthread_attr_;
    pthread_attr_init(&pthread_attr_);
    pthread_t threads[THREAD_NUMS];
    long i;
    for(i = 0; i < THREAD_NUMS; i++)
    {
        cout << "In main ==> Create " << i << " thread!" << endl;
        int rc = pthread_create(&threads[i], NULL, PrintHelloPthread, (void *)i);
        if(rc < 0)
        {
            cout << "Create thread error!" << endl;
            exit(-1);
        }
    }

    pthread_exit(NULL);
    return 0;
}