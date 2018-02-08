/*
    typedef struct
    {
      int __detachstate;
      int __schedpolicy;
      struct sched_param __schedparam;
      int __inheritsched;
      int __scope;
      size_t __guardsize;
      int __stackaddr_set;
      void *__stackaddr;
      unsigned long __stacksize;
    }
    pthread_attr_t;
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <sys/time.h>


void thread1_main(void);
void thread2_main(void);


int main()
{
   // Thread ID
   pthread_t thread1; // Created a thread called: thread1
   pthread_t thread2; // Created a thread called: thread2

   // Create Attributes : controls how threads function
   pthread_attr_t attr;
   pthread_attr_init(&attr);

   pthread_create(&thread1, &attr, (void*)&thread1_main , NULL);
   pthread_create(&thread2, &attr, (void*)&thread2_main , NULL);


   // Wait until thread is done its work
   pthread_join(thread1, NULL);
   pthread_join(thread2, NULL);

   return 0;
}

void thread1_main(void) {
    unsigned int run_cnt;
    unsigned int exec_period_usecs;
    struct timeval ts;

    exec_period_usecs = 1000000; /*in micro-seconds*/

    printf("Thread 1 started. Execution period = %d uSecs\n",\
                                           exec_period_usecs);
    run_cnt = 0;

    while(1) {
        usleep(exec_period_usecs);
        gettimeofday(&ts, NULL);
        printf("%06lu.%06lu: --- Thread1 run_cnt = %d ---\n",\
                                           (unsigned int)ts.tv_sec,\
                                           (unsigned int)ts.tv_usec,\
                                           run_cnt);
        run_cnt += 1;
    }
}


void thread2_main(void) {
    unsigned int run_cnt;
    unsigned int exec_period_usecs;
    struct timeval ts;

    exec_period_usecs = 5000000; /*in micro-seconds*/

    printf("Thread 2 started. Execution period = %d uSecs\n",\
                                           exec_period_usecs);
    run_cnt = 0;

    while(1) {
        usleep(exec_period_usecs);
        gettimeofday(&ts, NULL);
        printf("%06lu.%06lu: --- XXXXXX --- Thread2 run_cnt = %d --- XXXXXX ---\n",\
                                           (unsigned int)ts.tv_sec,\
                                           (unsigned int)ts.tv_usec,\
                                           run_cnt);
        run_cnt += 1;
    }
}
