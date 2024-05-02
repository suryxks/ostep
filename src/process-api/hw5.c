#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "failed to fork process");
  } else if (rc == 0) {
    wait(NULL);
    printf("in child process pid: %d\n", (int)getpid());
  } else {
    int rc_wait = wait(NULL);
    printf("in parent process pid: %d , rc_wait: %d\n", (int)getpid(), rc_wait);
    printf("Goodbye from parent\n");
  }
  return 0;
}
/*
 wait() system call reutrns the process id of the child
 calling wait() in children will retrun as there is no child process to wait for
*/