/*******************************************************************************
* - 997 sender sends each event to all receivers and requires acknowledgement *
*   for each message from both receivers before it continues execution        *
* - sender generates random numbers (32-bit value)                            *
* - Terminates when it gets/observes a random number smaller than 100         *
*******************************************************************************/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

int main()
{
  printf("Sender 997\n");
  srand(time(NULL));
  unsigned int r = rand(); // generates a random number (32-bit)
  printf("%d\n" , r);
  return 0;
}
