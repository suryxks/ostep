#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "failed to fork process");
  } else if (rc == 0) {
    close(STDOUT_FILENO);
    printf("in child process pid: %d\n", (int)getpid());
  } else {
    printf("Goodbye from parent\n");
  }
  return 0;
}
/**
  closing the standard output using close(STDOUT_FILENO) std out file descriptor
and no output is printed in the child process

**/