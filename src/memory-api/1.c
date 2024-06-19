#include <stdlib.h>
#include <string.h>
int main() {
  char *src = "hello";
  char *dst = (char *)malloc(sizeof(char)); // oops! unallocated
  strcpy(dst, src);                         // segfault and die
}