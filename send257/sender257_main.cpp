#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {
    // create my msgQ with key value from ftok()
    int qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);

    // declare my message buffer
    struct buf {
        long mtype; // required
        char greeting[50]; // mesg content
    };

    buf msg;
    int size = sizeof(msg)-sizeof(long);
    while(1)
    {
        msgrcv(qid, (struct msgbuf *)&msg, size, 147, 0); // read mesg

        cout << getpid() << ": gets message" << endl;
        cout << "message: " << msg.greeting << endl;
        if(strcmp(msg.greeting, "dead_2") == 0)
        {
            cout << "Kill message from Receiver 2 was recevied\n";
            exit(0);
        }
        else
        {
            msg.mtype = 169; // only reading mesg with type mtype = 314
            strcpy(msg.greeting, "Microwave is turning into a toaster");
            msgsnd(qid, (struct msgbuf *)&msg, size, 0);
        }
    } // END LOOP
}