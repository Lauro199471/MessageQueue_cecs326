/*******************************************************************************
* 251 sender                                                                   *
*   - sends each event to receiver(1)                                          *
*   - sender generates random numbers (32-bit value)                           *
*   - Terminates when it gets/observes a SIGUSR1                               *
*******************************************************************************/

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
#include "get_info.h"

#define MSGSZ 256   // msg text length
#define running 1
#define HOLD 1
using namespace std;

bool signl = 0;
// Declare the message structure
typedef struct msg_buf 
{
  long mtype;
  char mtext[256] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t ,int);
void deadMSG(message_buffer* , int , size_t);
void get_info(int qid, message_buffer* exitmsg, int size, long mtype);

void signalHandler(int signal)
{
  printf("Cought signal %d!\n",signal);
  signl = 1;
  cout << "\n\nDONE\n";
}

int main()
{
  int randomNumber;
  bool divisable;
  
  /* initialize random seed: */
  srand(time(NULL));

  message_buffer msgbf;
  size_t buf_length = MSGSZ;

  key_t key  = 1234;
  int mq_ID = msgget(key,0);
  msgbf.mtype = 117;
  
  int event_counter = 0;
  
  /* Generate a marker value */
  int marker = RAND_MAX/20000;
  
  signal(SIGUSR1,signalHandler);
  
  /* Title */
  cout << "\033[1;36mSender251 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;
  
  //get_info(mq_ID,&msgbf,buf_length,msgbf.mtype);
  while(running) 
  {
    /* Get a random 32-bit value & check divisible */
    randomNumber = rand();
    divisable = ((randomNumber % marker) == 0)? 1 : 0;
    
    // Dead MSG
    if(signl == 1)
    {
      deadMSG(&msgbf,mq_ID,buf_length);
      break;
    }
    // Regular MSG
    if(divisable)
    {
      sendMSG(&msgbf,mq_ID,buf_length,event_counter);
      event_counter++;
    }
  }
  while(HOLD);
  return 0;
}
void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length,int i)
{
    cout << "msg sent @\033[1;36m" << getpid() << "\033[0m\n";
  string s = "(251) Hello: "+ to_string(i) +" @\033[1;36m" + to_string(getpid()) 
           +"\033[0m";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}

/* To let recievers know I terminated */
void deadMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
  string s = "died_251";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}