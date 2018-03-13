/*******************************************************************************
* 257 sender                                                                   *
*   - sends each event to receiver(2)                                          *
*   - sender generates random numbers (32-bit value)                           *
*   - Terminates when it sends 5000 msgs                                       *
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

#define MSGSZ 256   // msgbf text length
#define running 1
#define HOLD 1
using namespace std;

// Declare the message structure
typedef struct msg_buf 
{
  long mtype;
  char mtext[256] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t ,int);

int main() {
  
  /* Title */
  cout << "\033[1;39mSender257 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;
  
  int randomNumber;
  bool divisable;
  
  /* initialize random seed: */
  srand(time(NULL));

  message_buffer msgbf;
  size_t buf_length = MSGSZ;

  key_t key  = 1234;
  int mq_ID = msgget(key,0);
  
  int event_counter = 0;
  
  /* Generate a marker value */
  int marker = RAND_MAX/20000;
  
  /* Reciever reciever 2 pid*/
  msgbf.mtype = 45;
  (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
  pid_t reciever2_pid = (pid_t)(atoi(msgbf.mtext));
  
  while(running)
  {
    /* Get a random 32-bit value & check divisible */
    randomNumber = rand();
    divisable = ((randomNumber % marker) == 0)? 1 : 0;
    
    //check if reciever 2 died
    if (getpgid(reciever2_pid) < 0)
    {
        break;
    }
    
    // Regular MSG
    if(divisable)
    {
      msgbf.mtype = 119;
      sendMSG(&msgbf,mq_ID,buf_length,event_counter);
      event_counter++;
    }
  }
  
  cout << "\n\n\rDONE\n";
  while(HOLD);
  return 0;
}

void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length,int i)
{
  cout << "msg sent @\033[1;39m" << getpid() << "\033[0m\n";
  string s = "(257) Hello: "+ to_string(i) +" @\033[1;39m" + to_string(getpid()) 
           +"\033[0m";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}