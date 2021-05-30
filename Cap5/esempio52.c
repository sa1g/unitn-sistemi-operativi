#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // thJoin . c
void *my_fun(void *param){
    printf("Thread % ld started \n", *(pthread_t *)param);
    sleep(3);
    char *str = "Returned string";
    pthread_exit((void *)str); // or ' return ( void *) str ; '
}
void main()
{
    pthread_t t_id;
    void *retFromThread;                                // This must be a pointer to void !
    pthread_create(&t_id, NULL, my_fun, (void *)&t_id); // Create
    pthread_join(t_id, &retFromThread);                 // wait thread
    // We must cast the returned value !
    printf("Thread %ld returned '%s'\n", t_id, (char *)retFromThread);
}