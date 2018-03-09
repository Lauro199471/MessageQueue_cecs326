#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>


using namespace std;

// Declare the message structure
typedef struct msg_buf 
{
  long mtype;
  char mtext[256] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t ,int);
void deadMSG(message_buffer* , int , size_t);

void signalHandler(int signal)
{
    printf("Cought signal %d!\n",signal);
    exit(0);
}

int main()
{
    bool divisable;
    int randomNumber;
    printf("PID=%d\n",getpid());
    srand(time(NULL));
    signal(SIGUSR1,signalHandler);
    

    while(1)
    {
    randomNumber = rand();
    divisable = ((randomNumber % marker) == 0)? 1 : 0;

       // std::cout << "I am john, and i like big culones and males ass " <<
         //       getpid() << std::endl;
    }
    return 0;
}
