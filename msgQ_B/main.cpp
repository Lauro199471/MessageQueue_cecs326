#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <time.h>

#define MSGSZ 256   // msg text length
#define running 1

using namespace std;

// Declare the message structure
typedef struct msg_buf 
{
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t);

int main()
{
  /* Title */
  cout << "\033[1;31mSender997 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;

  message_buffer msgbf;
  size_t buf_length = MSGSZ;

  key_t key  = 1234;
  int mq_ID = msgget(key,0);
 
  // MAIN LOOP
  while(running)
  {
    /* Send Event to recievers */
    msgbf.mtype = 117;
    sendMSG(&msgbf,mq_ID,buf_length);
  }// END LOOP
  return 0;
}

void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
  cout << "msg sent @\033[1;31m" << getpid() << "\033[0m\n";
  string s = "(A) Hello @\033[1;31m" + to_string(getpid()) +"\033[0m";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}

