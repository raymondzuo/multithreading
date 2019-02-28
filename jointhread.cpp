#include <pthread.h>
#include <iostream>
#include <math.h>
#define NUM_THREADS 4

using std::cout;
using std::endl;

void *BusyWork(void *t)
{
    int i;
    long tid;
    double result=0.0;
    tid = (long)t;
    printf("Thread %ld starting...\n",tid);
    for (i=0; i<1000000; i++)
    {
       result = result + sin(i) * tan(i);
    }
    printf("Thread %ld done. Result = %e\n",tid, result);
    pthread_exit((void*) t);
}

int main(int argc, char ** argv)
{
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    int rc;
    long t;
    void *status;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for(t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_create(&thread[t], &attr, BusyWork, (void *)t);
        if(rc)
        {
            cout << "Create error of : " << t << endl;
            exit(-1);
        }
    }

    pthread_attr_destroy(&attr);

    for( t = 0; t < NUM_THREADS - 2; t++)
    {
        rc = pthread_join(thread[t], &status);
        if(rc)
        {
            cout << "Join thread error of : " << t << endl;
            exit(-1);
        }
        cout << "main: complete join with thread: " << t <<  " with status: " << (long)status << endl;
    }
    cout << "main function end!" << endl;
    pthread_exit(NULL);

    return 0;
}