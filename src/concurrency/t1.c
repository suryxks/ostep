#include "../introduction/common.h"
#include "../introduction/common_threads.h"
#include <pthread.h>
#include <stdio.h>
static volatile int counter = 0;

void *myThread(void *arg) {
  printf("%s: begin\n", (char *)arg);
  int i;
  for (i = 0; i < 1e7; i++) {
    counter += 1;
  }
  printf("%s: end\n", (char *)arg);
  return NULL;
}
int main(int arc, char *argv[]) {
  pthread_t p1, p2;
  printf("main: begin (counter = %d)\n", counter);
  Pthread_create(&p1, NULL, myThread, "A");
  Pthread_create(&p2, NULL, myThread, "B");
  // join waits for the threads to finish

  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  printf("main: done with both (counter = %d)\n", counter);

  return 0;
}