#include <pthread.h>
#include <stdio.h>

int count; /* общие данные для потоков */
// int atoi(const char *nptr);
void *potok(void *param); /* потоковая функция */

int main(int argc, char *argv[])
{
  pthread_t tid; /* идентификатор потока */
  pthread_attr_t attr; /* отрибуты потока */

/* получаем дефолтные значения атрибутов */
  pthread_attr_init(&attr);

/* создаем новый поток */
  pthread_create(&tid, &attr, potok, argv[1]);

/* ждем завершения исполнения потока */
  pthread_join(tid,NULL);
  printf("count = %d\n",count);
}

/* Контроль переходит потоковой функции */
void *potok(void *param) 
{
  int i;
  count = 0;
  for (i = 1; i <= 15; i++)
  count += i;

  pthread_exit(0);
}