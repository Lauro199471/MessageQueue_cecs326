#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define MSGSZ 128   // msg text length

// Declare the message structure
typedef struct msg_buf {
  long mtype;
  char mtext[MSGSZ];
} message_buffer;

int main()
{
   // printf() displays the string inside quotation
   printf("Hello, World!-Reciever\n");
   return 0;
}
