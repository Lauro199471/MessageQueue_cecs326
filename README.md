# MessageQueue_cecs326
Interprocess communication and basic coordination using message queue
![message](https://user-images.githubusercontent.com/13907836/35985602-db61a2d8-0cab-11e8-9e72-f49e184b447e.gif)(figure 1)

** Notes **

IPC: Inter-processing Communcaiton

Message Queue: Two (or more) processes can exchange information via access to a common system message queue. The sending process places via some (OS) message-passing module a message onto a queue which can be read by another process.Each message is given an identification or type so that processes can select the appropriate message. Process must share a common key in order to gain access to the queue in the first place.

IPC messaging lets processes send and receive messages, and queue messages for processing in an arbitrary order(figure1).

Before a process can send or receive a message, the queue must be initialized (through the msgget function) Operations to send and receive messages are performed by the msgsnd() and msgrcv() functions, respectively. 

When a message is sent, its text is copied to the message queue. The msgsnd() and msgrcv() functions can be performed as either blocking or non-blocking operations. Non-blocking operations allow for asynchronous message transfer -- the process is not suspended as a result of sending or receiving a message. In blocking or synchronous message passing the sending process cannot continue until the message has been transferred or has even been acknowledged by a receiver. IPC signal and other mechanisms can be employed to implement such transfer. A blocked message operation remains suspended until one of the following three conditions occurs: 

  *The call succeeds

  *The process receives a signal
  
  *The queue is removed

## Initialising the Message Queue 
The msgget() function initializes a new message queue or returns the message queue identifier associated with the key parameter for an existing message queue: 

msgget(key_t key, int msgflg):

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

Return value: If successful, the return value will be the message queue identifier (a nonnegative integer), otherwise -1 with errno indicating the error. 

