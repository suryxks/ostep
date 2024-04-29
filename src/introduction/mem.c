#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int *p = malloc(sizeof(int));
  assert(p != NULL);
  printf("(%d) address pointed by p: %p\n", getpid(), p);
  *p = 0;
  while (1) {
    *p = *p + 1;
    printf("(%d) p: %d\n", getpid(), *p);
  }
  return 0;
}