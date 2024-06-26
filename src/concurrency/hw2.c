#include "../introduction/common_threads.h"
#include "zemaphore.h"
#include <stdio.h>
#include <unistd.h>
// If done correctly, each child should print their "before" message
// before either prints their "after" message. Test by adding sleep(1)
// calls in various locations.

Zem_t s1, s2;

void *child_1(void *arg) {
  printf("child 1: before\n");
  // what goes here?
  Zem_wait(&s2);
  Zem_post(&s1);
  printf("child 1: after\n");
  return NULL;
}

void *child_2(void *arg) {
  printf("child 2: before\n");
  // what goes here?

  Zem_post(&s2);
  Zem_wait(&s1);
  sleep(1);
  printf("child 2: after\n");
  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;
  printf("parent: begin\n");
  // init semaphores here
  Zem_init(&s1, 0);
  Zem_init(&s2, 0);

  Pthread_create(&p1, NULL, child_1, NULL);
  Pthread_create(&p2, NULL, child_2, NULL);
  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);
  sleep(1);
  printf("parent: end\n");
  return 0;
}