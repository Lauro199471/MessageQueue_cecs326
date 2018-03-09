#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <iostream>

void signalHandler(int signal)
{
    printf("Cought signal %d!\n",signal);
    exit(0);
}

int main()
{
    signal(SIGUSR1,signalHandler);
    
    printf("PID=%d\n",getpid());
    while(1)
    {
        std::cout << "I am john, and i like big culones and males ass " <<
                getpid() << std::endl;
    }
    return 0;
}
