#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// file descriptors are how we refer tp specific open files
// "ticket" handed to the operating system via the system call interface.

int main() {
  int fd = open("file.txt", O_CREAT | O_RDONLY);
  int fd2 = dup(fd);
  assert(fd >= 0);
  int rc = fork();
  if (rc == 0) {
    rc = lseek(fd, 10, SEEK_SET);
    printf("child offset %d\n", rc);
  } else if (rc > 0) {
    (void)wait(NULL);
    printf("parent offset %d\n", (int)lseek(fd, 0, SEEK_CUR));
  }
  return 0;
}

/*
in  cases , the mapping of the file descriptor to an entry in the open
file table is a ont-to-one mapping. For example , when a process runs, it might
decide

*/