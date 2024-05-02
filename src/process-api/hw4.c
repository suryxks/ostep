#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int rc = fork();
  //   char *args[] = {"/bin/ls", "-l", "-a", NULL};

  if (rc < 0) {
    fprintf(stderr, "failed to fork process");
  } else if (rc == 0) {
    // execl("/bin/ls", "-l", "-a", NULL);

    // execle("/bin/ls", "-l", "-a", (char *)0, NULL);
    execlp("/bin/ls", "-l", "-a", NULL);
  } else {
    printf("Goodbye from parent\n");
  }
  return 0;
}