/* 

This is a simple illustration of the use of:
	ftok, msgget, msgsnd, msgrcv

Program B creates a message queue to be shared with Program A.
Then, they will pass messages back and forth.

Program A sends the first message and reads the reply. Program A
also sends a "fake" message to the msgQ that will never be read
by Program B.

Both child processes use message type mtype = 113 and 114.

*/

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

#define MSGSZ 256 // msg text length
#define running 1

int main() {
  // create my msgQ with key value from ftok()
  int qid = msgget(1234, IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);

  // declare my message buffer
  struct buf {
          long mtype; // required
          char greeting[50]; // mesg content
  };

  buf msg;
  int size = sizeof(msg)-sizeof(long);
  
  while(1)
  {
    msg.mtype = 117;
    msgrcv(qid, (struct msgbuf *)&msg, size, msg.mtype, 0); // read mesg
    cout << getpid() << ": gets message" << endl;
    cout << "message: " << msg.greeting << endl;

    strcat(msg.greeting, " and Adios.");
    cout << getpid() << ": sends reply" << endl;

    msg.mtype = 314; // only reading mesg with type mtype = 314
    msgsnd(qid, (struct msgbuf *)&msg, size, 0);
    cout << getpid() << ": now exits" << endl;
  }

  // now safe to delete message queue
  msgctl (qid, IPC_RMID, NULL);

  exit(0);
}

