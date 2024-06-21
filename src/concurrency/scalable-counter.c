#include "../introduction/common.h"
#include "../introduction/common_threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
const int NUMCPUS = 8;
typedef struct {
  int global;
  pthread_mutex_t glock;
  int local[NUMCPUS];
  pthread_mutex_t llock[NUMCPUS];
  int threshold;
} counter_t;

void init(counter_t *c, int threshold) {
  c->threshold = threshold;
  pthread_mutex_init(&c->glock, NULL);
  int i;
  for (i = 0; i < NUMCPUS; i++) {
    pthread_mutex_init(&c->llock[i], NULL);
  }
}

void update(counter_t *c, int threadID, int amt) {
  int cpu = threadID % NUMCPUS;
  Pthread_mutex_lock(&c->llock[cpu]);

  c->local[cpu] += amt;
  if (c->local[cpu] >= c->threshold) {
    Pthread_mutex_lock(&c->glock);
    c->global += c->local[cpu];
    c->local[cpu] = 0;
    Pthread_mutex_unlock(&c->glock);
  }
  Pthread_mutex_unlock(&c->llock[cpu]);
}

int get(counter_t *c) { return c->global; }
void *incthread(void *arg) {
  counter_t *c = (counter_t *)arg;
  int tid = (int)pthread_self();
  for (int i = 0; i < 100000000; i++) {
    update(c, tid, 1);
  }
  printf("from inc: %d \n", c->global);

  return NULL;
}
void *decthread(void *arg) {
  counter_t *c = (counter_t *)arg;
  int tid = (int)pthread_self();
  for (int i = 0; i < 10000000; i++) {
    update(c, tid, -1);
  }
  printf("from dec: %d \n", c->global);

  return NULL;
}
int main() {
  counter_t c;
  init(&c, 5);
  pthread_t t1, t2, t3;
  Pthread_create(&t1, NULL, incthread, &c);
  Pthread_create(&t2, NULL, decthread, &c);
  Pthread_create(&t3, NULL, incthread, &c);
  Pthread_join(t1, NULL);
  Pthread_join(t2, NULL);
  Pthread_join(t3, NULL);
  printf("from main: %d \n", c.global);
  return 0;
}