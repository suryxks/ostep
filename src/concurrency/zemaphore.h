#include "../introduction/common_threads.h"
#include <pthread.h>
typedef struct __Zem_t {
  int value;
  pthread_cond_t cond;
  pthread_mutex_t lock;

} Zem_t;
void Zem_init(Zem_t *z, int value) {
  z->value = value;
  Cond_init(&z->cond);
  Mutex_init(&z->lock);
}

void Zem_wait(Zem_t *z) {
  Pthread_mutex_lock(&z->lock);
  z->value--;
  while (z->value < 0) {
    Pthread_cond_wait(&z->cond, &z->lock);
  }
  Pthread_mutex_unlock(&z->lock);
  return;
}

void Zem_post(Zem_t *z) {
  Pthread_mutex_lock(&z->lock);
  z->value++;
  Cond_signal(&z->cond);
  Pthread_mutex_unlock(&z->lock);
}
