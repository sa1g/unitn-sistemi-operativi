#include <unistd.h> // execv1.out
#include <stdio.h>
void main()
{
    char *argv[] = {"par1", "par2", NULL};
    execv("./esempio6_execv2", argv); // sostituisce il processo attuale e passa argv -- NB il nome del programma che si vuole eseguire.
    printf("This is execv1 \n"); //se non esegue execv2 allora stampa questo messaggio e continua il programma attuale
}