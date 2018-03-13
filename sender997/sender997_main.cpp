/*******************************************************************************
* 997 sender                                                                   *
*   - sends each event to all receivers and requires acknowledgement           *
*     for each message from both receivers before it continues execution       *
*   - sender generates random numbers (32-bit value)                           *
*   - Terminates when it gets/observes a random number smaller than 100        *
*******************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>
#include "color.h"

#define MSGSZ 256   // msg text length
#define running 1
#define HOLD 1

using namespace std;

// Declare the message structure
typedef struct msg_buf 
{
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t ,int);
void deadMSG(message_buffer* , int , size_t);

int main()
{
  bool divisable;
  int randomNumber;
  int i = 0 , event_marker_cntr = 0;
  bool liveNode_reciever1 = 1 , liveNode_reciever_2 = 1;
  
  /* Title */
  cout << "\033[1;31mSender997 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;

  /* initialize random seed: */
  srand(time(NULL));

  /* Generate a marker value */
  int marker = RAND_MAX/20000000;

  message_buffer msgbf;
  size_t buf_length = MSGSZ;

  key_t key  = 1234;
  int mq_ID = msgget(key,0);
 
  // MAIN LOOP
  while(running)
  {
    /* Get a random 32-bit value & check divisible */
    randomNumber = rand();
    divisable = ((randomNumber % marker) == 0)? 1 : 0;

    /* If random number is less then 100 then quit program */
    if(randomNumber <= 100)
    {
      printf("\nRandom Number: %d\n" red "DONE\n" reset , randomNumber);
      msgbf.mtype = 117;
      deadMSG(&msgbf,mq_ID,buf_length);
      break;
    }

    /* If divisible send message */
    else if(divisable == 1)
    {
      event_marker_cntr++;
      
      cout << "\nSent MSG Total: " << event_marker_cntr << endl;
      
      /* Send Event to recievers */
      msgbf.mtype = 117;
      sendMSG(&msgbf,mq_ID,buf_length,event_marker_cntr);
       /* Check if we can send to reciever 2  */
      if(liveNode_reciever_2 == 1)
      {
        msgbf.mtype = 119;
        sendMSG(&msgbf,mq_ID,buf_length,event_marker_cntr);
      }
      
      /* Recieve acknowlegment from recievers */
      msgbf.mtype = 500;
      (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
      printf("@\033[1;31m%d\033[0m recieved: %s \n\r", getpid(), msgbf.mtext);
      
      /* Check if we can recieve to reciever 2  */
      if(liveNode_reciever_2 == 1)
      {
        msgbf.mtype = 502;
        (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
        printf("@\033[1;31m%d\033[0m recieved: %s \n\r", getpid(), msgbf.mtext);
      }
      
      // Check if reciever 2 died
      if(strcmp(msgbf.mtext,"died_2") == 0)
      {
        // If true means reciever2 is died :(
        liveNode_reciever_2 = 0;
      }
    }
  }// END LOOP
  
  cout << "\n\n\r DONE";
  while(HOLD);
  return 0;
}

void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length,int i)
{
  cout << "msg sent @\033[1;31m" << getpid() << "\033[0m\n";
  string s = "(997) Hello: "+ to_string(i) +" @\033[1;31m" + to_string(getpid()) +"\033[0m";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}

/* To let recievers know I terminated */
void deadMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
  string s = "died_997";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}