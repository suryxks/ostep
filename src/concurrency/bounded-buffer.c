#include "../introduction/common_threads.h"
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
int buffer;
int count = 0;
pthread_mutex_t l = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
void put(int value) {
  assert(count == 0);
  count = 1;
  buffer = value;
}
int get() {
  assert(count == 1);
  count = 0;
  return buffer;
}

void *producer(void *arg) {
  int i;
  int loops = (int)arg;
  for (i = 0; i < loops; i++) {
    pthread_mutex_lock(&l);
    while (count == 1) {
      Pthread_cond_wait(&empty, &l);
    }
    put(i);
    Pthread_cond_signal(&full);
    pthread_mutex_unlock(&l);
  }
  return NULL;
}

void *consumer(void *arg) {
  while (1) {
    pthread_mutex_lock(&l);
    while (count == 0) {
      Pthread_cond_wait(&full, &l);
    }
    int tmp = get();
    Pthread_cond_signal(&empty);
    printf("%d\n", tmp);
    pthread_mutex_unlock(&l);
  }
  return NULL;
}

int main() {
  pthread_t t1, t2, t3;
  Pthread_create(&t1, NULL, producer, (void *)1000);
  Pthread_create(&t2, NULL, consumer, NULL);
  Pthread_create(&t3, NULL, consumer, NULL);
  Pthread_join(t1, NULL);
  Pthread_join(t2, NULL);
  Pthread_join(t3, NULL);
  return 0;
}