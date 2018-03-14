/******************************************************************************
* Reciever 1                                                                  *
*   - starts queue and ends it                                                *
*   - recieves from sender 997 and sender 251                                 *
*   - sends acknowledgement to 997                                            *
*******************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <stdio.h>
#include <string>
using namespace std;

#define S_IRUSR 256   // Allow the owner of the message queue to read from it.
#define S_IWUSR 128   // Allow the owner of the message queue to write to it.
#define S_IRGRP 32    // Allow the group of the message queue to read from it.
#define S_IWGRP 16    // Allow the group of the message queue to write to it.
#define S_IROTH 4     // Allow others to read from the message queue.
#define S_IWOTH 2     // Allow others to write to the message queue.

#define MSGSZ 256 // msg text length
#define running 1
#define HOLD 1

// Declare the message structure
typedef struct msg_buf
{
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t);

int main()
{
  int nodes = 2;
  bool liveNode997 = 1, liveNode251 = 1;
  cout << "\033[1;32mReciever1 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;
  
  message_buffer msgbf;
  size_t buf_length = MSGSZ;
  
  // Create a message queue , if returns a negative numbers means error
  key_t key = 1234;
  int msgflag = IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
  int mq_ID = msgget(key, msgflag);
  // MAIN LOOP
  while (running)
  {
    // Recieve Message type 117
    msgbf.mtype = 117;
    (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
    printf("@\033[1;32m%d\033[0m recieved: %s nodes: %d\n\r", 
            getpid(), msgbf.mtext , nodes);
    
    // Send Message if (997)
    if(msgbf.mtext[0] == '(' && msgbf.mtext[1] == '9')
    {
      msgbf.mtype = 500;
      sendMSG(&msgbf,mq_ID,buf_length);
    }
    // Check who died
    if(strcmp(msgbf.mtext,"died_997") == 0 && liveNode997 == 1)
    {
      cout << "\nDAMN SON :'( : 997" << endl;
      liveNode997 = 0;
      nodes--;
    }
    if(strcmp(msgbf.mtext,"died_251") == 0 && liveNode251 == 1)
    {
      cout << "\nDAMN SON :'( : 251" << endl;
      nodes--;
      liveNode251 = 0;
    }
    if(liveNode251 == 0 && liveNode997 == 0)
    {
      cout << "\nDAMN SON :'( : I die" << endl;
      break;
    }
  }
  
  msgctl(mq_ID,IPC_RMID,NULL);
  cout << "\n\n\r DONE";
  while(HOLD);
  return 0;
}

void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
  string s;
  s = "Ack.@\033[1;32m"+to_string(getpid())+"\033[0m";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}