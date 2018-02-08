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

