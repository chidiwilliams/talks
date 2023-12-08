#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 10
#define NUM_ITEMS 50

int buffer[BUFFER_SIZE];
int count = 0;

pthread_mutex_t mutex;
pthread_cond_t can_produce;
pthread_cond_t can_consume;

void *producer() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    pthread_mutex_lock(&mutex);
    while (count == BUFFER_SIZE) {
      pthread_cond_wait(&can_produce, &mutex);
    }
    buffer[count++] = i;
    pthread_cond_signal(&can_consume);
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *consumer() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    pthread_mutex_lock(&mutex);
    while (count == 0) {
      pthread_cond_wait(&can_consume, &mutex);
    }
    int item = buffer[--count];
    pthread_cond_signal(&can_produce);
    pthread_mutex_unlock(&mutex);
    printf("Consumed: %d\n", item);
  }
  return NULL;
}

int main() {
  pthread_t prod, cons;

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&can_produce, NULL);
  pthread_cond_init(&can_consume, NULL);

  pthread_create(&prod, NULL, producer, NULL);
  pthread_create(&cons, NULL, consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&can_produce);
  pthread_cond_destroy(&can_consume);

  return 0;
}