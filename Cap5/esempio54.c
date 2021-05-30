#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // thJoin . c
void *my_fun(void *param){
    sleep(2);
}

void *my_fun2(void *param){
    if (pthread_join(*(pthread_t *)param, NULL) != 0)
        printf("Error\n");
}

void main(){
    pthread_t t_id, t_id2;
    pthread_create(&t_id, NULL, my_fun, NULL);           // Create
    pthread_create(&t_id2, NULL, my_fun, (void *)&t_id); // Create
    pthread_join(t_id, NULL);                            // wait thread
    sleep(1);
    perror();
}