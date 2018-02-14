/******************************************************************************
* - 997 sender sends each event to all receivers and requires acknowledgement *
*   for each message from both receivers before it continues execution        *
* - sender generates random numbers (32-bit value)                            *
* - Terminates when it gets/observes a random number smaller than 100         *
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
#define marker 7     // marker for 'event'
#define running 1

using namespace std;

// Declare the message structure
typedef struct msg_buf {
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;



int main()
{
  bool divisable;
  int randomNumber;
  /* initialize random seed: */
  srand(time(NULL));

  message_buffer msgbf;
  size_t buf_length;

  // Create a message queue , if returns a negative numbers means error
  key_t key  = 1234;
  int msgflag = IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
  int mq_ID = msgget(key,msgflag);

  // We'll send message type 117
  msgbf.mtype = 118;
  buf_length = MSGSZ;

  // MAIN LOOP
  while(running)
  {
    randomNumber = rand(); // get a random 32-bit value

    // current date/time based on current system
    //time_t now = time(0);
    // convert now to string form
    //char* dt = ctime(&now);

    // If random number is less then 100 then quit program
    if(randomNumber <= 100 )
    {
        printf("Random Number: %d\n" red "EXITING...\n" reset , randomNumber);
        return 1;
    }
    divisable = ((randomNumber%marker)==0)?1:0;
    if(divisable == 1)
    {
        printf(green "Send MSG\n" reset);
        strcpy(msgbf.mtext, "Can you hear me?");
        (void)msgsnd(mq_ID, &msgbf, buf_length, 0);
        (void)msgrcv(mq_ID,&msgbf,buf_length,msgbf.mtype,0);
        printf(blue "Recieved MSG(1)\n\n" reset);
    }




    /*
    strcpy(msgbf.mtext, "Can you hear me?");
    (void)msgsnd(mq_ID, &msgbf, buf_length, 0);
    printf("Sent: %s \n",msgbf.mtext);
    (void)msgrcv(mq_ID,&msgbf,buf_length,msgbf.mtype,0);
    printf("Recieved: %s \n\n",msgbf.mtext);*/
  }

  return 0;
}
