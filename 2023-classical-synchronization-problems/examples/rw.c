#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_WRITERS 5

sem_t rw_mutex;
sem_t mutex;
int read_count = 0;

void *writer(void *arg) {
  int id = *((int *)arg);

  sem_wait(&rw_mutex);

  printf("Writer %d is writing\n", id);
  sleep(2);
  printf("Writer %d finished writing\n", id);

  sem_post(&rw_mutex);
  return NULL;
}

void *reader(void *arg) {
  int id = *((int *)arg);

  // Acquire rw_mutex if this is the only reader
  sem_wait(&mutex);
  read_count++;
  if (read_count == 1) {
    sem_wait(&rw_mutex);
  }
  sem_post(&mutex);

  printf("Reader %d is reading\n", id);
  sleep(1);
  printf("Reader %d finished reading\n", id);

  // Release rw_mutex if this is the last reader
  sem_wait(&mutex);
  read_count--;
  if (read_count == 0) {
    sem_post(&rw_mutex);
  }
  sem_post(&mutex);

  return NULL;
}

int main() {
  pthread_t readers[5], writers[5];
  int ids[5];

  sem_init(&mutex, 0, 1);
  sem_init(&rw_mutex, 0, 1);

  for (int i = 0; i < 5; i++) {
    ids[i] = i;
    pthread_create(&writers[i], NULL, writer, &ids[i]);
    pthread_create(&readers[i], NULL, reader, &ids[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(readers[i], NULL);
    pthread_join(writers[i], NULL);
  }

  sem_destroy(&mutex);
  sem_destroy(&rw_mutex);

  return 0;
}