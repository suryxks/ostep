#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd[2];
  pid_t pid;

  if (pipe(fd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  } else if (pid == 0) { // Child process
    close(fd[0]);        // Close the read end of the pipe
    char message[] = "Hello, parent!";

    // Write the message to the write end of the pipe
    if (write(fd[1], message, sizeof(message)) == -1) {
      perror("write");
      exit(EXIT_FAILURE);
    }

    close(fd[1]); // Close the write end of the pipe
    exit(EXIT_SUCCESS);
  } else {        // Parent process
    close(fd[1]); // Close the write end of the pipe
    char buffer[100];

    // Read from the read end of the pipe
    ssize_t bytes_read = read(fd[0], buffer, sizeof(buffer));
    if (bytes_read == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }

    printf("Message from child: %s\n", buffer);

    close(fd[0]); // Close the read end of the pipe
    exit(EXIT_SUCCESS);
  }

  return 0;
}
