#include "../introduction/common.h"
#include "../introduction/common_threads.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>

void *mythread(void *arg) {
  printf("%s\n", (char *)arg);
  return NULL;
}
int main(int argc, char *argv[]) {
  pthread_t t1, t2;
  int rc;
  printf("main: begin\n");
  Pthread_create(&t1, NULL, mythread, "A");
  Pthread_create(&t2, NULL, mythread, "B");

  Pthread_join(t1, NULL);
  Pthread_join(t2, NULL);
  printf("main: end\n");
  return 0;
}