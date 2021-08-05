#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define MITTENTI 5

//definizione whitelist
int whitelist[MITTENTI][2] = {0};
//variabili globali per i counter di SIGUSR1 e SIGUSR2 
int cSU1=0, cSU2=0;

//signal handler stampa
void sighandlerE(int signum){
    for(int i=0; i<MITTENTI; i++){
        printf("CS: '%d' | counter: %d\n", whitelist[i][0], whitelist[i][1]);
        printf("CS: '%d' | counter: %d\n", whitelist[i][0], whitelist[i][2]);
        printf("\n");
    }

    exit (1);
}

//signal handler input
void sighandler1(int signum, siginfo_t *info, void *context){
    int pp=1;

   for(int i=0; i<MITTENTI; i++){
        if(whitelist[i][0]==info->si_pid){
            pp=0;
        }
    }

    for(int i=0; i<MITTENTI; i++){
        if(pp && whitelist[i][0]==0){
            whitelist[i][0]=info->si_pid;
            //printf("SS %d %d - %d -%d\n",i, whitelist[i][0], whitelist[i][1], whitelist[i][2]);
            break;
        }
    }

    for(int i=0; i<MITTENTI; i++){
        if(whitelist[i][0]==info->si_pid){
            if(signum==10){
                whitelist[i][1]++;
              //  printf("aggiunto -10\n");

            }
            if(signum==12){
                //printf("aggiunto -12\n");
                whitelist[i][2]++;
            }
            break;
        }
    }
}




int main(int argc, char ** argv){
    //stampa PID del programma
    printf("Main PID: %d\n", getpid());

    //stampa codice segnale + riferimento del mittente (che cazzo vuol dire? (il PID)) se in foreground
    //nnt se in background
   
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = sighandler1;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    //ricezione SIGINT o SIGTERM il programma termina stampando i counter suddivisi per mittente (PID)
    //di SIGUSR1 e  SIGUSR2  
    signal(SIGTERM, sighandlerE);
    signal(SIGINT , sighandlerE);
    while(1){}
    
}