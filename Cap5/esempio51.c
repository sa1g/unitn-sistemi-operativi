#include <stdio.h>
#include <pthread.h>
#include <unistd.h> // thCancel . c
int i = 1;
void * my_fun ( void * param ){
if (i - -) pthread_ set cancel state ( PTHREAD_CANCEL_DISABLE , NULL ); // Change m o d e p t h r e a d _ s e t c a n c
printf ( "Thread %ld started \n" ,*( pthread_t *) param );
sleep (3);
printf ( "Thread %ld finished\n" ,*( pthread_t *) param );
}
void main (){
pthread_t t_id1 , t_id2 ;
pthread_create (& t_id1 , NULL , my_fun , ( void *)& t_id1 );
sleep (1); // Create
pthread_cancel ( t_id1 ); // Cancel
printf ( "Sent cancellation request for thread %ld \n" , t_id1 );
pthread_create (& t_id2 , NULL , my_fun , ( void *)& t_id2 );
sleep (1); // Create
pthread_cancel ( t_id2 ); // Cancel
printf ( "Sent cancellation request for thread % ld \n" , t_id2 );
sleep (5);
printf ( "Terminating program \n" );
}