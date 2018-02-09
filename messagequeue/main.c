#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define S_IRUSR 256   // Allow the owner of the message queue to read from it.
#define S_IWUSR 128   // Allow the owner of the message queue to write to it.
#define S_IRGRP 32    // Allow the group of the message queue to read from it.
#define S_IWGRP 16    // Allow the group of the message queue to write to it.
#define S_IROTH 4     // Allow others to read from the message queue.
#define S_IWOTH 2     // Allow others to write to the message queue.

#define MSGSZ 128   // msg text length

// Declare the message structure
typedef struct msg_buf {
  long mtype;
  char mtext[MSGSZ];
} message_buffer;

int main()
{
  int msgqid;
  int msgflg = IPC_CREAT|S_IRUSR|S_IWUSR|
                 S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;

  key_t key = 1234;
  message_buffer sbuf;
  size_t buf_length;

  printf("\nmsgget: Calling msgget(%d,%d)\n",key,msgflg);

  // Create a message queue , if returns a negative numbers means error
  msgqid = msgget(key, msgflg);
  if (msgqid < 0)
  {
    printf("Failed to create message queue\n");
    return 1;
  }
  else
      printf("msgget: msgget succeeded: msqid = %d\n", msgqid);

  return 0;
}
