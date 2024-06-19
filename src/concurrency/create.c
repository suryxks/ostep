#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int a;
  int b;
} myarg_t;
typedef struct {
  int x;
  int y;
} myret_t;
void *my_thread(void *arg) {
  myarg_t *args = (myarg_t *)arg;
  myret_t *rvals = malloc(sizeof(myret_t));
  rvals->x = args->a + 10;
  rvals->y = args->b + 20;
  printf("%d %d\n", args->a, args->b);
  return (void *)rvals;
}

int main(int argc, char *argv[]) {
  pthread_t p;
  myarg_t arg = {1, 2};
  myret_t *rvals;
  int rc = pthread_create(&p, NULL, my_thread, &arg);
  pthread_join(p, (void **)&rvals);
  printf("%d %d\n", rvals->x, rvals->y);
  return 0;
}