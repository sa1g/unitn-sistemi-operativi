#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // threadCreate . c
void *my_fun(void *param)
{
    printf("This is a thread that received %d\n", *(int *)param);
    return (void *)3;
}
void main()
{
    pthread_t t_id;
    int arg = 10;
    pthread_create(&t_id, NULL, my_fun, (void *)&arg);
    printf("Executed thread with id %ld\n", t_id);
    sleep(3);
}
