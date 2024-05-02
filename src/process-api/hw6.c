#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int rc = fork();
  if (rc < 0) {
    fprintf(stderr, "failed to fork process");
  } else if (rc == 0) {
    printf("in child process pid: %d\n", (int)getpid());
  } else {
    int status;
    waitpid(rc, &status, WUNTRACED);
    printf("Goodbye from parent\n");
  }
  return 0;
}

/*
  passing in WUNTRACED To waitpid waits till the child process has stopped or
  terminated.
*/