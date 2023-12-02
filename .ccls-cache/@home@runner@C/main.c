#include <stdio.h>
#include <unistd.h>

int main(void) {

  int counter = 1;
  while(counter < 6){
      pid_t pid = getpid();
    printf("This is the pid: %u\n", pid);
    counter+= 1;
  }
  
  return 0;
}