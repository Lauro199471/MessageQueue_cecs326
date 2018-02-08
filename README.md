# MessageQueue_cecs326
Interprocess communication and basic coordination using message queue
![message](https://user-images.githubusercontent.com/13907836/35985602-db61a2d8-0cab-11e8-9e72-f49e184b447e.gif)(figure 1)

** Notes **

IPC: Inter-processing Communcaiton

Message Queue: Two (or more) processes can exchange information via access to a common system message queue. The sending process places via some (OS) message-passing module a message onto a queue which can be read by another process.Each message is given an identification or type so that processes can select the appropriate message. Process must share a common key in order to gain access to the queue in the first place.

IPC messaging lets processes send and receive messages, and queue messages for processing in an arbitrary order(figure1).

Before a process can send or receive a message, the queue must be initialized (through the msgget function see below) Operations to send and receive messages are performed by the msgsnd() and msgrcv() functions, respectively. 
