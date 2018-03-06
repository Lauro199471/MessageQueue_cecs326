/*******************************************************************************
* 997 sender                                                                   *
*   - sends each event to all receivers and requires acknowledgement           *
*     for each message from both receivers before it continues execution       *
*   - sender generates random numbers (32-bit value)                           *
*   - Terminates when it gets/observes a random number smaller than 100        *
*   - Starts Queue                                                             *
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

#define S_IRUSR 256   // Allow the owner of the message queue to read from it.
#define S_IWUSR 128   // Allow the owner of the message queue to write to it.
#define S_IRGRP 32    // Allow the group of the message queue to read from it.
#define S_IWGRP 16    // Allow the group of the message queue to write to it.
#define S_IROTH 4     // Allow others to read from the message queue.
#define S_IWOTH 2     // Allow others to write to the message queue.

#define MSGSZ 256   // msg text length
#define running 1

using namespace std;

// Declare the message structure
typedef struct msg_buf {
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t);
int main()
{
  bool divisable;
  int randomNumber;
  unsigned int marker;
  int i = 0;
  
  /* Title */
  cout << "\033[1;31mSender997 pid: " << getpid() 
        << "\033[1;31m\n\r===================\n\r" << endl;
  
  /* initialize random seed: */
  srand(time(NULL));

  /* Generate a random marker value */
  marker = RAND_MAX;

  message_buffer msgbf;
  size_t buf_length;

  // Create a message queue , if returns a negative numbers means error
  key_t key  = 1234;
  int msgflag = IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
  int mq_ID = msgget(key,msgflag);

  /* We'll use type msg 117 */
  msgbf.mtype = 117;
  buf_length = MSGSZ;
  
  /* Wait for Ready from Reciever */
  (void)msgrcv(mq_ID,&msgbf,buf_length,msgbf.mtype,0);
   
  
  // MAIN LOOP
  while(running)
  {
    /* Get a random 32-bit value & check divisible */
    randomNumber = rand();
    divisable = ((randomNumber % marker) == 0)? 1 : 0;

    /* If random number is less then 100 then quit program */
    if(randomNumber <= -1 )
    {
        printf("Random Number: %d\n" red "EXITING...\n" reset , randomNumber);
        return 1;
    }

    /* If divisible send message */
    if(divisable == 1)
    {
        if(i == 5)
        {
            system("clear");
            cout << "\033[1;31mSender997 pid: " << getpid() 
                << "\033[0m\n\r===================\n\r" << endl;
        }
        
        cout << endl;
        // reciever 1
        msgbf.mtype = 119;
        sendMSG(&msgbf,mq_ID,buf_length);
        (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
        printf("%s\n\r", msgbf.mtext);
        
        // reciever 2
        msgbf.mtype = 121;
        sendMSG(&msgbf,mq_ID,buf_length);
        (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
        printf("%s\n\r", msgbf.mtext);

        i++;
    }

    if(i == 5)
    {
        system("clear");
        cout << "\033[1;31mSender997 pid: " << getpid() 
            << "\033[0m\n\r===================\n\r" << endl;
    }
    i++;
  }// END LOOP

  return 0;
}

void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
    string s;
    cout << "Sent msg @\033[1;31m" << getpid() << "\033[0m\n";
    s = "Hello @\033[1;31m" + to_string(getpid()) +"\033[0m";
    strcpy((*msgbf).mtext , s.c_str());
    (void)msgsnd(msgID,msgbf,buf_length,0);
}