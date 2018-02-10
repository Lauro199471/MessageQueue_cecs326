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
void counter_open(int thread_num);

// Create a common variable
int counter = 0;

// Create a Mutex
pthread_mutex_t my_mutex;

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

void thread1_main(void)
{
    unsigned int exec_period_usecs;
    exec_period_usecs = 1000000; /*in micro-seconds*/
    while(1)
    {
        usleep(exec_period_usecs);
        counter_open(1);
    }
}


void thread2_main(void) {
    unsigned int exec_period_usecs;
    exec_period_usecs = 1000000; /*in micro-seconds*/
    while(1)
    {
        usleep(exec_period_usecs);
        counter_open(2);
    }
}

void counter_open(int thread_num) {
    int i;
    timer_t clk = time(NULL);

    pthread_mutex_lock(&my_mutex);

    if(thread_num == 1)
    {
      for (i=0; i<5; i++)
      {
        clk = time(NULL);
        counter += 1;
        printf("\033[1;32mThread %d\033[0m, counter =  %d @%s",thread_num,counter,ctime(&clk));
        usleep(50);
      }
    }

    else if(thread_num == 2)
    {
      for (i=0; i<5; i++)
      {
        clk = time(NULL);
        counter += 1;
        printf("\033[1;31mThread %d\033[0m, counter =  %d @%s",thread_num,counter,ctime(&clk));
        usleep(50);
      }
    }

    printf("\n");
    pthread_mutex_unlock(&my_mutex);
}
