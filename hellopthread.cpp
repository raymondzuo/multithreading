#include <pthread.h>
#include <iostream>
using std::cout;
using std::endl;

const int NUM_THREADS = 5;

void * PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    cout << "======> hello pthread, thread id: " << tid << endl;    
    pthread_exit(NULL);
}

struct hellopthread
{
    const char * name;
    int index;
};


void * PrintHelloStruct(void *threadid)
{
    struct hellopthread *phellop;
    phellop = (hellopthread *)threadid;
    cout << "======> hello pthread, name: " << phellop->name << " index: " << phellop->index << endl;    
    pthread_exit(NULL);
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int ret;
    long t;
    for(t = 0; t < NUM_THREADS; t++)
    {
        cout << "In main, creating thread: " << t << endl;
        //ret = pthread_create(&threads[t], NULL, &PrintHello, (void *)t);
        struct hellopthread hellopthreadvar;
        hellopthreadvar.name = "Lala";
        hellopthreadvar.index = t;
        ret = pthread_create(&threads[t], NULL, &PrintHelloStruct, (void *)&hellopthreadvar);
        if(ret)
        {
            cout << "Create error: " << ret << endl;
            exit(-1);
        }
    }

    pthread_exit(NULL);
    return 0;
}