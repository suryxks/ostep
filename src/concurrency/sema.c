#include "../introduction/common_threads.h"
#include <semaphore.h>
#include <stdio.h>
sem_t s;

void *child(void *arg) {
  printf("child\n");
  sem_post(&s);
  return NULL;
}

int main() {
  sem_open("/s", O_CREAT, 0644, 0);
  printf("parent: begin\n");
  pthread_t t;
  Pthread_create(&t, NULL, child, NULL);
  sem_wait(&s);
  Pthread_join(t, NULL);
  printf("parent: end\n");
  return 0;
}
