/******************************************************************************
* Reciever 2                                                                  *
*   - recieves from sender 997 and sender 257                                 *
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
void deadMSG(message_buffer* , int , size_t);
void givePID(message_buffer* , int , size_t);

int main()
{
  int event_counter = 0;
  cout << "\033[1;33mReciever2 pid: " << getpid() 
  << "\033[0m\n\r===================\r" << endl;
  
  message_buffer msgbf;
  size_t buf_length;
  
  key_t key = 1234;
  //int msgflag = IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH;
  int mq_ID = msgget(key, 0);

  buf_length = MSGSZ;

  // Let sender257 know its PID
  msgbf.mtype = 45;
  givePID(&msgbf,mq_ID,buf_length);

  // MAIN LOOP
  while (running)
  {
    // Recieve Message type 119
    msgbf.mtype = 119;
    (void)msgrcv(mq_ID, &msgbf, buf_length, msgbf.mtype, 0);
    
    // Check after 5000 msgs have passed 
    if(event_counter == 5001)
    {
      // Let sender997 know its done
      msgbf.mtype = 502;
      deadMSG(&msgbf,mq_ID,buf_length);
      
      // Let sender257 know its done
      //msgbf.mtype = 23;
      //deadMSG(&msgbf,mq_ID,buf_length); 
      
      break;
    }
    printf("@\033[1;33m%d\033[0m recieved: %s \n\r", getpid(), msgbf.mtext);
    
    // Send Message to 997
    msgbf.mtype = 502;
    sendMSG(&msgbf,mq_ID,buf_length);
    
    // Send Message to 257
    //msgbf.mtype = 23;
    //sendMSG(&msgbf,mq_ID,buf_length);
    
    event_counter = event_counter + 1;
  }
  
  cout << "\n\n\rDONE\n";
  
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

void givePID(message_buffer* msgbf, int msgID,size_t buf_length)
{
  string s;
  s = to_string(getpid());
  strcpy((*msgbf).mtext , s.c_str());
  (void)msgsnd(msgID,msgbf,buf_length,0);
}