/******************************************************************************
* - Simple Reciever *
*******************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;


#define S_IRUSR 256   // Allow the owner of the message queue to read from it.
#define S_IWUSR 128   // Allow the owner of the message queue to write to it.
#define S_IRGRP 32    // Allow the group of the message queue to read from it.
#define S_IWGRP 16    // Allow the group of the message queue to write to it.
#define S_IROTH 4     // Allow others to read from the message queue.
#define S_IWOTH 2     // Allow others to write to the message queue.

#define MSGSZ 256   // msg text length
#define running 1

// Declare the message structure
typedef struct msg_buf {
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;

int main() {
    message_buffer msgbf;
    size_t buf_length;

    // Create a message queue , if returns a negative numbers means error
    key_t key  = 1234;
    int msgflg = IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
    int mq_ID = msgget(key, msgflg);

    // We'll recieve message type 117
    msgbf.mtype = 117;
    buf_length = MSGSZ;

    // MAIN LOOP
    while(running)
    {
      (void)msgrcv(mq_ID,&msgbf,buf_length,msgbf.mtype,0);
      printf("Recieved: %s \n",msgbf.mtext);
      strcpy(msgbf.mtext, "Yes");
      (void)msgsnd(mq_ID, &msgbf, buf_length, 0);
      printf("Sent: %s \n\n",msgbf.mtext);
    }

    return 0;
}


