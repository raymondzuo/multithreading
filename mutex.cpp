#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

pthread_mutex_t global_mutex;
int global = 0;

void * add_one(void * arg)
{
    pthread_mutex_lock(&global_mutex);
    global++;
    cout << "global ===> " << global << endl;
    pthread_mutex_unlock(&global_mutex);
}

int main(int argc, char **argv)
{
    const int THREAD_COUNT = 5;
    pthread_t threads[THREAD_COUNT];
    pthread_attr_t attr_;
    pthread_attr_init(&attr_);
    pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&global_mutex, NULL);

    for(int i = 0; i < THREAD_COUNT; i++)
    {
        int res = pthread_create(&threads[i], &attr_, add_one, NULL);
        if(res < 0)
        {
            cout << "Create thread error!";
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr_);

    for(int i = 0; i < THREAD_COUNT; i++)
    {
        int res = pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&global_mutex);
    pthread_exit(NULL);
}