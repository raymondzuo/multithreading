#include <pthread.h>
#include <iostream>
#include <unistd.h>

using std::cout;
using std::endl;

#define THREAD_NUM 3
#define TCOUNT 10
#define COUNT_LIMIT 12

int count = 0;
int thread_ids[3] = {1,2,3};
pthread_mutex_t count_mutex;
pthread_cond_t count_threshold_cv;

void *inc_count(void * t)
{
    int i;
    long my_id = (long)t;
    for(i = 0; i < TCOUNT; i++)
    {
        pthread_mutex_lock(&count_mutex);
        count++;

        if(count == COUNT_LIMIT)
        {
            pthread_cond_signal(&count_threshold_cv);
            cout << "inc_count() : thread: " << my_id << " count: " << count <<" threshold reached!"
                 << endl;
        }

        cout << "inc_count() : thread: " << my_id << " count: " << count << " unlocking mutex!" << endl;
        pthread_mutex_unlock(&count_mutex);

        usleep(1000);
    }

    pthread_exit(NULL);
}

void *watch_count(void * t)
{
    long my_id = (long)t;
    cout << "Starting watch_count() : thread: " << my_id << endl;

    pthread_mutex_lock(&count_mutex);

    while(count < COUNT_LIMIT)
    {
        pthread_cond_wait(&count_threshold_cv, &count_mutex);
        cout << "watch_count() : thread " << my_id << " condition signal received!" << endl;
    }

    count += 125;
    cout << "watch_count() : thread " << my_id << " count " << count << endl;
    pthread_mutex_unlock(&count_mutex);
    pthread_exit(NULL); 
}

int main()
{
    int i, rc;
    long t1 = 1, t2 = 2, t3 = 3;
    pthread_t threads[3];
    pthread_attr_t attr_;

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold_cv, NULL);

    pthread_attr_init(&attr_);
    pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);
    
    pthread_create(&threads[0], &attr_,  watch_count, (void *)t1);
    pthread_create(&threads[1], &attr_,  inc_count, (void *)t2);
    pthread_create(&threads[2], &attr_,  inc_count, (void *)t3);

    for(i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threads[i], NULL);
    }

    cout << "Main() waited on 3 threads" << endl;

    pthread_attr_destroy(&attr_);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);

    pthread_exit(NULL);
}