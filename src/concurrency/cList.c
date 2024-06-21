#include "../introduction/common.h"
#include "../introduction/common_threads.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct __node_t {
  int value;
  struct node_t *next;
} node_t;

typedef struct __list_t {
  node_t *head;
  pthread_mutex_t lock;
} list_t;

void init(list_t *L) {
  L->head = NULL;
  pthread_mutex_init(&L->lock, NULL);
}

int List_Insert(list_t *L, int key) {
  node_t *new = malloc(sizeof(node_t));
  if (new == NULL) {
    perror("malloc");
    pthread_mutex_unlock(&L->lock);
    return -1; // fail
  }
  Pthread_mutex_lock(&L->lock);
  new->value = key;
  new->next = L->head;
  L->head = new;
  pthread_mutex_unlock(&L->lock);
  return 0;
}

int List_Lookup(list_t *L, int key) {
  node_t *curr = L->head;
  int rerturn_value = -1;
  Pthread_mutex_lock(&L->lock);
  while (curr != NULL) {
    if (curr->value == key) {
      rerturn_value = 0;
      break; // success
    }
    curr = curr->next;
  }
  Pthread_mutex_unlock(&L->lock);
  return -1; // failure
}