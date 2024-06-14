#include <stdio.h>
#include <assert.h>
#include <pthread.h>

void *myThread(void *arg);

int main()
{

  pthread_t p1, p2;
  printf("main : begin\n");
  pthread_create(&p1, NULL, myThread, "A");
  pthread_create(&p2, NULL, myThread, "B");
  // 종료 할 수 있도록 대기 중인 쓰레드 병합하기
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("main : end\n");
  return 0;
}

void *myThread(void *arg)
{
  printf("thread %s : begin\n", (char *)arg);
  printf("thread %s : end\n", (char *)arg);
  return NULL;
}
