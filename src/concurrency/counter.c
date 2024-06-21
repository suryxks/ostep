#include "../introduction/common.h"
#include "../introduction/common_threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int value;
  pthread_mutex_t lock;
} counter_t;

void init(counter_t *c) {
  c->value = 0;
  pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value++;
  Pthread_mutex_unlock(&c->lock);
}

void decrement(counter_t *c) {
  Pthread_mutex_lock(&c->lock);
  c->value--;
  Pthread_mutex_unlock(&c->lock);
}

int get(counter_t *c) { return c->value; }
void *incthread(void *arg) {
  counter_t *c = (counter_t *)arg;
  for (int i = 0; i < 100000000; i++) {
    increment(c);
  }
  printf("from inc: %d \n", c->value);

  return NULL;
}
void *decthread(void *arg) {
  counter_t *c = (counter_t *)arg;
  for (int i = 0; i < 10000000; i++) {
    decrement(c);
  }
  printf("from dec: %d \n", c->value);

  return NULL;
}
int main() {
  counter_t c;
  init(&c);
  pthread_t t1, t2, t3;
  Pthread_create(&t1, NULL, incthread, &c);
  Pthread_create(&t2, NULL, decthread, &c);
  Pthread_create(&t3, NULL, incthread, &c);
  Pthread_join(t1, NULL);
  Pthread_join(t2, NULL);
  Pthread_join(t3, NULL);
  printf("from main: %d \n", c.value);
  return 0;
}