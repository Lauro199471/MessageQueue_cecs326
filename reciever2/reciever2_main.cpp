/******************************************************************************
* - Reciever 2
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

#define MSGSZ 256 // msg text length
#define running 1

// Declare the message structure
typedef struct msg_buf
{
  long mtype;
  char mtext[MSGSZ] = {};
} message_buffer;

void sendMSG(message_buffer* , int , size_t);
void deadMSG(message_buffer* , int , size_t);

int main()
{
  int event_counter = 0;
  cout << "\033[1;33mReciever2 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;
  
  message_buffer msgbf;
  size_t buf_length;
  
  key_t key = 1234;
  int mq_ID = msgget(key, 0);

  buf_length = MSGSZ;

  // MAIN LOOP
  while (running)
  {
    // Recieve Message type 119
    msgbf.mtype = 119;
    (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
    
    // Check after 5000 msgs have passed
    if(event_counter == 5000)
    {
      // Let sender997 know its done
      msgbf.mtype = 123;
      deadMSG(&msgbf,mq_ID,buf_length);
      
      cout << "\nDAMN SON :'(" << endl;
      break;
    }
    else
      printf("@\033[1;33m%d\033[0m recieved: %s \n\r", getpid(), msgbf.mtext);
    
    // Send Message
    msgbf.mtype = 123;
    sendMSG(&msgbf,mq_ID,buf_length);
    event_counter = event_counter + 1;
  }

  return 0;
}

void sendMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
  string s;
  s = "Ack.@\033[1;33m"+to_string(getpid())+"\033[0m";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}

/* To let sender know I terminated */
void deadMSG(message_buffer* msgbf, int msgID,size_t buf_length)
{
  string s = "died_2";
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}