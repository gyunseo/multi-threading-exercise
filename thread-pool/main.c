#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 4
typedef struct task {
  int a, b;
} Task;

Task taskQueue[256];
pthread_mutex_t lockForQueue = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condForQueue = PTHREAD_COND_INITIALIZER;
int taskCount = 0;

void enqueueTask(Task task);
void executeTask(Task *task);

void *startThread();

int main() {
  pthread_t threads[NUM_THREADS];
  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&threads[i], NULL, startThread, NULL) != 0) {
      perror("pthread_create");
    }
  }
  srand(time(NULL));
  for (int i = 0; i < 100; i++) {
    Task task = {
        .a = rand() % 100,
        .b = rand() % 100,
    };
    enqueueTask(task);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_join(threads[i], NULL) != 0) {
      perror("pthread_join");
    }
  }
  pthread_mutex_destroy(&lockForQueue);
  pthread_cond_destroy(&condForQueue);
  return 0;
}
void enqueueTask(Task task) {
  pthread_mutex_lock(&lockForQueue);
  taskQueue[taskCount++] = task;
  pthread_mutex_unlock(&lockForQueue);
  pthread_cond_signal(&condForQueue);
}
void executeTask(Task *task) {
  int res = task->a + task->b;
  printf("the sum of %d and %d is %d\n", task->a, task->b, res);
}

void *startThread() {
  while (true) {
    Task task;
    pthread_mutex_lock(&lockForQueue);
    while (taskCount == 0) {
      pthread_cond_wait(&condForQueue, &lockForQueue);
    }

    task = taskQueue[0];
    for (int i = 0; i < taskCount - 1; i++) {
      taskQueue[i] = taskQueue[i + 1];
    }
    taskCount--;

    pthread_mutex_unlock(&lockForQueue);
    executeTask(&task);
  }
}