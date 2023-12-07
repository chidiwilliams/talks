---
theme: apple-basic
highlighter: shiki
lineNumbers: false
info:
drawings:
  persist: false
title: Classical Synchronization Problems
mdc: true
layout: intro
author: Chidi Williams
keywords: systems-design,concurrency
colorSchema: "dark"
fonts:
  sans: IBM Plex Sans
---

# Classical Synchronization Problems

<div class="absolute bottom-10">
  <span class="font-400 text-neutral-500">
    <span class="text-green-400 font-600">SysDsgn Pop-up</span> / 2023-12-06 / Chidi Williams
  </span>
</div>

---

# About me

<div class="flex gap-32">
  <div class="flex-1">

Chidi Williams, Software Engineer

<v-clicks>

- Previously at Eyowo, now at GS in London
- Write a programming blog at [chidiwilliams.com](https://chidiwilliams.com)
- Co-organize SysDsgn
- Often build projects in web animations, languages and compilers, and (more recently) AI
- Love to play music — guitar, piano
</v-clicks>

  </div>
  <div style="width: 150px; height: 150px">
  <img class="rounded-lg shadow-xl" src="/img/profile.jpg" />
  </div>
</div>

---

# Introduction to concurrency

- Computers need concurrency so they can run multiple applications at the time.
- Without concurrency, the computer will have to wait for each application to complete before running the next one.
- However, concurrency introduces several issues including resource sharing, synchronization, and ...
- We'll have a look at some of these problems and learn about various concurrency primitives and concepts.

---

# Producer-consumer problem

- "Bounded buffer" problem.
- > "Consider two processes, which are called the **'producer'** and the **'consumer'** respectively. The producer is a cyclic process and each time it goes through its cycle it produces a certain portion of information, that has to be processed by the consumer. The consumer is also a cyclic process and each time it goes through its cycle, it can process the next portion of information, as has been produced by the producer ... if the two are coupled via a buffer of finite size, say _N_ portions." - _Djikstra_
- Applications in queueing, logging, stream processing systems.

<ProducerConsumer />

---

# Producer-consumer problem

<br> <br>

<!-- prettier-ignore-start -->
<div class="flex justify-between">

```c
#define BUFFER_SIZE 10
#define NUM_ITEMS 50

int buffer[BUFFER_SIZE];
int count = 0;

void *producer() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    buffer[count++] = i;
  }
  return NULL;
}
```

<v-clicks>

```c
void *consumer() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    int item = buffer[--count];
    printf("Consumed: %d\n", item);
  }
  return NULL;
}
```

```c
int main() {
  pthread_t prod, cons;

  pthread_create(
    &prod, NULL, producer, NULL);
  pthread_create(
    &cons, NULL, consumer, NULL);

  pthread_join(prod, NULL);
  pthread_join(cons, NULL);

  return 0;
}
```
</v-clicks>
</div>

<!-- prettier-ignore-end -->

---

# _That doesn't work!_

```text
> gcc -fsanitize=undefined -o producer_consumer producer_consumer.c && ./producer_consumer
producer_consumer.c:13:5: runtime error: index 10 out of bounds for type 'int[10]'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior producer_consumer.c:13:5 in
producer_consumer.c:20:16: runtime error: index 10 out of bounds for type 'int[10]'
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior producer_consumer.c:20:16 in
Consumed: 11
Consumed: 49
Consumed: 48
Consumed: 47
Consumed: 46
Consumed: 45
Consumed: 44
Consumed: 43
Consumed: 42
Consumed: 41
Consumed: 40
...
```

<v-clicks>

The producer and consumer aren't synchronized, so they access the buffer out of its bounds and produce unpredictable behaviour.
</v-clicks>

---

# How do we fix this?

- The producer and consumer should not access the shared variables at the same time.
- The producer should wait when the buffer is full, and the consumer when the buffer is empty.

<br>

<!-- prettier-ignore-start -->

<div class="flex justify-around">
<v-clicks>
```c {1,5-8,10}
pthread_mutex_t mutex;

void *producer() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    pthread_mutex_lock(&mutex);
    while (count == BUFFER_SIZE) {
      printf("Wait for an item to be consumed...\n");
    }
    buffer[count++] = i;
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

```

```c {3-6,8}
void *consumer() {
  for (int i = 0; i < NUM_ITEMS; i++) {
    pthread_mutex_lock(&mutex);
    while (count == 0) {
      printf("Wait for an item to be produced...\n");
    }
    int item = buffer[--count];
    pthread_mutex_unlock(&mutex);
    printf("Consumed: %d\n", item);
  }
  return NULL;
}
```

</v-clicks>
</div>

<!-- prettier-ignore-end -->

---

# Mutex

<v-clicks>

- Guarantees \[mut]ual \[ex]clusion: When a thread is accessing a shared resource, no other concurrent thread can access it.
- One implementation uses **shared memory** and an **atomic test-and-set operation**.
- To "lock" the mutex, each process tries to test-and-set a location in shared memory. But only one wins, since the operation is atomic!
- Unsuccessful processes can keep checking the flag until they can acquire it.
- CPU pre-emption is possible, so the system can do other things while a process waits for the lock.

</v-clicks>

<div v-click>
```asm
lock:
    mov al, 1           ; Load AL with the value 1 (indicating locked)
    xchg [mutex], al    ; Atomically exchange the value at 'mutex' with AL
    test al, al         ; Test if the original value in AL was 0 (lock was free)
    jnz lock            ; If it was not 0, lock was already held, so try again
    ret
```

```asm
unlock:
    mov byte [mutex], 0  ; Set the mutex back to 0 (indicating unlocked)
    ret

```

</div>

---

# What happens when we run this?

```txt
> gcc -fsanitize=undefined -o producer_consumer producer_consumer.c && ./producer_consumer
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
Wait for an item to be consumed...
```

<v-clicks>

- We're in a **deadlock**! The producer is stuck waiting for the consumer to run but never releases the lock.
- But we can't just release the lock till we know it's safe to produce more items.
- We need each party to release the lock and regain it when its counterparty signals that it's safe to do so.

</v-clicks>

---

# Condition variables

<div class="flex justify-around">

```c {1-2,8,11}
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
```

<v-clicks>

```c {5,8}
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
```

</v-clicks>
</div>

<div v-click>

- `pthread_cond_wait` waits for its condition variable to be signalled.
- It releases its lock before waiting and tries to regain it after the signal.
</div>

---

# _No more deadlock!_

```text
> gcc -fsanitize=undefined -o producer_consumer producer_consumer.c && ./producer_consumer
Consumed: 9
Consumed: 10
Consumed: 8
Consumed: 7
Consumed: 6
...
```

<br>

<div v-click>

> **Exercise:** How can the producer-consumer problem be solved using other concurrency primitives:
>
> - Semaphores?
> - Channels?
> - Something else?

</div>

---

# References

- [The Little Book of Semaphores - Downey](https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf)
- [Modern Operating Systems - Tanenbaum](https://en.wikipedia.org/wiki/Modern_Operating_Systems)
