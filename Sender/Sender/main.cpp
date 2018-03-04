/******************************************************************************
* - Simple Sender *
*******************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <sstream>  // Required for stringstreams
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>

using namespace std;

#define S_IRUSR 256 // Allow the owner of the message queue to read from it.
#define S_IWUSR 128 // Allow the owner of the message queue to write to it.
#define S_IRGRP 32 // Allow the group of the message queue to read from it.
#define S_IWGRP 16 // Allow the group of the message queue to write to it.
#define S_IROTH 4 // Allow others to read from the message queue.
#define S_IWOTH 2 // Allow others to write to the message queue.

#define MSGSZ 256 // msg text length
#define running 1


// Declare the message structure
typedef struct msg_buf {
    long mtype;
    char mtext[MSGSZ] = {};
} message_buffer;

int main()
{
    int i = 0;
    string s;

    cout << "MSGQ A(tx)\n\r==========\n\r";
    message_buffer msgbf;
    size_t buf_length;

    // Create a message queue , if returns a negative numbers means error
    key_t key = 1234;
    int msgflag = IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int mq_ID = msgget(key, msgflag);

    // We'll send message type 117
    msgbf.mtype = 117;
    buf_length = MSGSZ;

    // MAIN LOOP
    while (running)
    {
        sleep(1);
        cout << "Sent(" << i << ")" << endl;
        s = "Hello" + to_string(i);
        strcpy(msgbf.mtext, s.c_str());
        (void)msgsnd(mq_ID, &msgbf, buf_length, 0);
        i++;
    }

    return 0;
}
