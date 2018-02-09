# MessageQueue_cecs326
Interprocess communication and basic coordination using message queue
![message](https://user-images.githubusercontent.com/13907836/35985602-db61a2d8-0cab-11e8-9e72-f49e184b447e.gif)(figure 1)


**IPC**: Inter-processing Communcaiton

**Message Queue**: Two (or more) processes can exchange information via access to a common system message queue. The sending process places via some (OS) message-passing module a message onto a queue which can be read by another process.Each message is given an identification or type so that processes can select the appropriate message. Process must share a common key in order to gain access to the queue in the first place.

IPC messaging lets processes send and receive messages, and queue messages for processing in an arbitrary order(figure1).

Before a process can send or receive a message, the queue must be initialized (through the msgget function) Operations to send and receive messages are performed by the msgsnd() and msgrcv() functions, respectively. 

When a message is sent, its text is copied to the message queue. The msgsnd() and msgrcv() functions can be performed as either blocking or non-blocking operations. Non-blocking operations allow for asynchronous message transfer -- the process is not suspended as a result of sending or receiving a message. In blocking or synchronous message passing the sending process cannot continue until the message has been transferred or has even been acknowledged by a receiver. IPC signal and other mechanisms can be employed to implement such transfer. A blocked message operation remains suspended until one of the following three conditions occurs: 

  * The call succeeds

  * The process receives a signal
  
  * The queue is removed

## Initialising the Message Queue 
The **msgget()** function initializes a new message queue or returns the message queue identifier associated with the key parameter for an existing message queue: 
```C
msgget(key_t key, int msgflg):
```
@param key: is used to identify a message queue

@param msgflg: Operations and permissions flag. The value of msgflg is either zero or is obtained by performing an OR operation on one or more of the following constants: 

S_IRUSR (0x00000100): Allow the owner of the message queue to read from it.

S_IWUSR (0x00000080): Allow the owner of the message queue to write to it.

S_IRGRP (0x00000020): Allow the group of the message queue to read from it.

S_IWGRP (0x00000010): Allow the group of the message queue to write to it.

S_IROTH (0x00000004): Allow others to read from the message queue.

S_IWOTH (0x00000002): Allow others to write to the message queue.

IPC_CREAT (0x00000200): Create the message queue if it does not exist.

IPC_EXCL (0x00000400): Return an error if the IPC_CREAT flag is set and the message queue already exists.

Return value: If successful, the return value will be the message queue identifier (a nonnegative integer , msqid), otherwise -1 with errno indicating the error. 

## Sending and Receiving Messages 
The **msgsnd()** and **msgrcv()** functions send and receive messages, respectively.
```C
int msgsnd(int msqid, const void *msgp, size_t msgsz,int msgflg);
int msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
```
The msqid argument must be the ID of an existing message queue. 

The msgp  argument is a pointer to a structure that contains the type of the message and its text.
example of what this user-defined buffer might look like: 
```C
 struct mymsg 
 {
   long msgtype;      /* message type */
   char mtext[MSGSZ]; /* message text of length MSGSZ */
 }
```
The msgsz argument specifies the length of the message in bytes. 

The structure member msgtype is the received message's type as specified by the sending process. 

The argument msgflg specifies the action to be taken if one or more of the following are true: 

* The number of bytes already on the queue is equal to msg_qbytes. 
* The total number of messages on all queues system-wide is equal to the system-imposed limit. 

These actions are as follows: 
* If (msgflg & IPC_NOWAIT) is non-zero, the message will not be sent and the calling process will return immediately. 
* If (msgflg & IPC_NOWAIT) is 0, the calling process will suspend execution until one of the following occurs: 
    * The condition responsible for the suspension no longer exists, in which case the message is sent. 
    * The message queue identifier msqid is removed from the system; when this occurs, errno is set equal to EIDRM and -1 is returned. 
    * The calling process receives a signal that is to be caught; in this case the message is not sent and the calling process resumes execution. 

Upon successful completion, the following actions are taken with respect to the data structure associated with msqid: 
    
* msg_qnum is incremented by 1. 
* msg_lspid is set equal to the process ID of the calling process.
* msg_stime is set equal to the current time. 

## POSIX Messages
The POSIX message queue functions are:

**mq_open()** -- Connects to, and optionally creates, a named message queue.

**mq_close()** -- Ends the connection to an open message queue.

**mq_unlink()** -- Ends the connection to an open message queue and causes the queue to be removed when the last process closes it.

**mq_send()** -- Places a message in the queue.

**mq_receive()** -- Receives (removes) the oldest, highest priority message from the queue.

**mq_notify()** -- Notifies a process or thread that a message is available in the queue.

**mq_setattr()** -- Set or get message queue attributes. 



















