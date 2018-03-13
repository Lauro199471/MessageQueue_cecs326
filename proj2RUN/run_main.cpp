/*
 * Project 2 Order
 * 1) Reciever 1(starts/ends queue)
 * 2) Reciever 2
 * 3) Sender 251
 * 4) Sender 257
 * 5) Sender 997
 * 
 */

#include <cstdlib>

using namespace std;

int main(int argc, char** argv) {
  
  // 1) Reciever 1(starts/ends queue)
  system("gnome-terminal -e '/home/lauro199471/Documents/MessageQueue_cecs326/reciever1/dist/Debug/GNU-Linux/reciever1'");
  // 2) Reciever 2
  system("gnome-terminal -e '/home/lauro199471/Documents/MessageQueue_cecs326/reciever2/dist/Debug/GNU-Linux/reciever2'");
  // 3) Sender 251
  system("gnome-terminal -e '/home/lauro199471/Documents/MessageQueue_cecs326/sender251/dist/Debug/GNU-Linux/sender251'");
  // 4) Sender 257
  system("gnome-terminal -e '/home/lauro199471/Documents/MessageQueue_cecs326/sender257/dist/Debug/GNU-Linux/sender257'");
  // 5) Sender 997
  system("gnome-terminal -e '/home/lauro199471/Documents/MessageQueue_cecs326/sender997/dist/Debug/GNU-Linux/sender997'");
  
  return 0;
}

