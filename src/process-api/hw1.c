#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  printf("hello (pid:%d)\n", (int)getpid());
  int x = 100;
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "fork not created\n");
    exit(1);
  } else if (rc == 0) {
    printf("value of x: %d\n", x);
    x += 100;
    printf("value of x: %d\n", x);
  } else {
    printf("value of x: %d\n", x);
    x += 100;
    printf("value of x: %d\n", x);
  }
  return 0;
}
/*Observations:
1) both child and parent processes have their own set of variables and memory

2) mutating the variable in child process does not mutate the variable in parent
process and vice versa

3) the reason for 2 is virtualization of memory and resources for each process.
*/
