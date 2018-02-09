#include<string.h>
#include<time.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<sys/errno.h>

#define S_IRUSR 256   // Allow the owner of the message queue to read from it.
#define S_IWUSR 128   // Allow the owner of the message queue to write to it.
#define S_IRGRP 32    // Allow the group of the message queue to read from it.
#define S_IWGRP 16    // Allow the group of the message queue to write to it.
#define S_IROTH 4     // Allow others to read from the message queue.
#define S_IWOTH 2     // Allow others to write to the message queue.

#define MSGTXTLEN 128   // msg text length

int msgqid, rc;
int done;

struct msg_buf {
  long mtype;
  char mtext[MSGTXTLEN];
} msg;

int main(int argc,char **argv)
{
  key_t key = 10;

  // Create a message queue , if returns a negative numbers means error
  msgqid = msgget(key, IPC_CREAT|S_IRUSR|S_IWUSR|
                         S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
  if (msgqid < 0)
  {
    printf("Failed to create message queue\n");
    return 1;
  }
  else
    printf("Success(msgget)...\n\rMessage Queue ID: %p\n",msgqid);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // message to send
  msg.mtype = 1; // set the type of message
  sprintf (msg.mtext, "%s\n", "a text msg..."); /* setting the right time format by means of ctime() */

  // send the message to queue
  rc = msgsnd(msgqid, &msg, sizeof(msg.mtext), 0); // the last param can be: 0, IPC_NOWAIT, MSG_NOERROR, or IPC_NOWAIT|MSG_NOERROR.
  if (rc < 0) {
    perror( strerror(errno) );
    printf("msgsnd failed, rc = %d\n", rc);
    return 1;
  }

  // read the message from queue
  rc = msgrcv(msgqid, &msg, sizeof(msg.mtext), 0, 0);
  if (rc < 0) {
    perror( strerror(errno) );
    printf("msgrcv failed, rc=%d\n", rc);
    return 1;
  }
  printf("received msg: %s\n", msg.mtext);

  // remove the queue
  rc=msgctl(msgqid,IPC_RMID,NULL);
  if (rc < 0) {
    perror( strerror(errno) );
    printf("msgctl (return queue) failed, rc=%d\n", rc);
    return 1;
  }
  printf("message queue %d is gone\n",msgqid);

  return 0;
}
