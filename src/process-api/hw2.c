#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int fd = open("./src/hw2-outout.txt", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  int rc = fork();
  char buf1[] = "content1\n";
  char buf2[] = "content2\n";

  if (rc < 0) {
    fprintf(stderr, "failed to fork process");
  } else if (rc == 0) {
    printf("in child process (pid:%d) , file descriptor value: %d\n",
           (int)getpid(), fd);
    write(fd, buf1, sizeof(buf1) - 1);
  } else {

    printf("in parent process (pid:%d) , file descriptor value: %d\n",
           (int)getpid(), fd);
    write(fd, buf2, sizeof(buf2) - 1);
  }
  return 0;
}