#include <stdio.h>
#include <pthread.h>
static volatile int counter = 0;
// 반복문을 사용하여 단순히 1씩 더하기
// 10,000,000을 변수 counter에 더하는 방법이 아니다.
// 하지만, 문제가 무엇인지 명확하게 해준다.
void *myThread(void *arg);

// 두 개의 쓰레드를 실행하고 (pthread_create)
// 대기한다 (pthread_join)
int main()
{
  pthread_t p1, p2;
  printf("main : begin(counter = % d)\n", counter);
  pthread_create(&p1, NULL, myThread, "A");
  pthread_create(&p2, NULL, myThread, "B");
  // 쓰레드가 종료할 수 있도록 대기 중인 쓰레드를 병합 한다
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("main : done with both(counter = % d)\n", counter);
  return 0;
}

void *myThread(void *arg)
{

  printf("%s: begin\n", (char *)arg);
  int i;
  for (i = 0; i < (int)1e7; i++)
  {
    counter = counter + 1;
  }
  printf("%s : done\n", (char *)arg);
  return NULL;
}