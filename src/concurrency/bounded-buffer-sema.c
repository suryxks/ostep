#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
const int MAX = 10;
int buffer[10];
int fill = 0;
int use = 0;
int loops = 10;
sem_t empty;
sem_t full;
sem_t mutex;
void put(int value) {
  buffer[fill] = value;
  fill = (fill + 1) % MAX;
}

int get() {
  int tmp = buffer[use];
  use = (use + 1) % MAX;
  return tmp;
}

void *producer(void *arg) {
  int i;
  for (i = 0; i < loops; i++) {
    sem_wait(&empty);
    sem_wait(&mutex);
    put(i);
    sem_post(&mutex);
    sem_post(&full);
  }
}

void *consumer(void *arg) {
  int tmp = 0;
  while (tmp != -1) {
    sem_wait(&full);
    sem_wait(&mutex);
    tmp = get();
    sem_post(&mutex);
    sem_post(&empty);
    printf("%d\n", tmp);
  }
}

int main() {
  pthread_t t1, t2, t3, t4;
  sem_init(&mutex, 0, 1);
  sem_init(&empty, 0, MAX);
  sem_init(&full, 0, 0);
  pthread_create(&t1, NULL, producer, NULL);
  pthread_create(&t2, NULL, producer, NULL);
  pthread_create(&t3, NULL, consumer, NULL);
  pthread_create(&t4, NULL, consumer, NULL);
  pthread_join(t1, NULL);
  pthread_join(t2, NULL);
  pthread_join(t3, NULL);
  pthread_join(t4, NULL);

  return 0;
}