#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define RED "\033[0;31m"
#define GREEN "\033[32m"
#define DF "\033[0m"
#define MAX_SLAVES 10
#define MAX_MSG 500

char fifoMaster[100];
int fifoMasterFD;
char fifoSlave[MAX_SLAVES][100]; //Array of FIFO between slaves
int fifoSlaveFD[MAX_SLAVES]; //Array of FD for the fifo between slaves

int canRead = 1;

int processNumber; //Current process number

// Error printing function
void perr(char * str){
    fprintf(stderr,"%s[%d]%s%s\n",RED,processNumber,str,DF);
}

//MEthod to receive the messages from the master
void  messageReceiveHandler(){
    //Open master pipe in read
    char buf[MAX_MSG+10],dest[10],msg[MAX_MSG];
    int r,ind,target;
    
    //Keep on receiving messages (until SIGTERM is received)
    while(1){
        r = read(fifoMasterFD,&buf,MAX_MSG-1);
        if (r==0){
            printf("[%d]Nothing to read\n",processNumber);
            continue;
        }
        buf[r] = 0;
        ind = 0;
        //Extract target process  4 ejoafeo 
        for(int i = 0; i < r; i++){
            if(buf[i] == ' '){
                ind = i;
                break;
            }
        }
        //Store in 'dest' the target node
        strncpy(dest,buf,ind);
        target = atoi(dest);

        //Check if target is valid
        if(target <= 0 || target>MAX_SLAVES){
            printf("[%d]Wrong target '%s'\n",processNumber,buf);
            continue;
        }
        strcpy(msg,buf+ind+1);
        //Set read flag to 0 so that this process (sender) doesn't read the message
        canRead=0;

        //Send message
        write(fifoSlaveFD[target-1],msg,strlen(msg));
        printf("[%d]Sent '%s' to %d\n",processNumber,msg,target);
        //Give time to the other process to read message, then reactivate reading
        sleep(1);
        canRead=1;
    }
}

//Thread for incoming messages
void * slaveCommunication(void * param){
    int fd = *(int *)param;
    char buf[MAX_MSG];
    printf("%s[%d]Thread for watching FD %d%s\n",RED,processNumber,fd,DF);
    
    //Keep on receiving messages (until SIGTERM)
    while(1){
        if(canRead){
            int r = read(fd,buf,MAX_MSG-1);
            if(r>0){
                buf[r] = 0;
                printf("[%d]Received '%s'\n",processNumber,buf);
            }
        }
    }
}

//SIGTERM
void termHandler(int signo){
    //Close pipes
    for (int i = 1; i <= MAX_SLAVES; i++){
        close(fifoSlaveFD[i-1]);
    }
    close(fifoMasterFD);
    printf("[%d]Terminating",processNumber);
}

int main(int argc, char ** argv){
    
    //Check parameters
    if(argc < 5){
        perr("Invalid number of parameters");
        exit(1);
    }

    //Get own process number
    processNumber = atoi(argv[1]);
    //Get total processes
    int totProcesses = atoi(argv[2]);
    if(processNumber <= 0 || totProcesses<0 || totProcesses > MAX_SLAVES || totProcesses < processNumber){
        perr("Invalid argument");
        exit(2);
    }
    

    //Craft the fifo names
    char str1[10];
    strcpy(fifoMaster,argv[3]);
    sprintf(str1, "%d", processNumber);
    strcat(fifoMaster,str1); 

    //Open master pipe for incoming commands
    fifoMasterFD = open(fifoMaster,O_RDONLY);








/**
    slave 2:
        - thread MasterSlvae
        - thread read 1
        -treahd read 3,....

**/









    pthread_t t_ids[MAX_SLAVES]; //Arrays of threads
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    
    int err = 0;
    //Compute the pipe names
    for (int i = 1; i <= totProcesses; i++){
        //Craft the various pipe names
        if(i == processNumber){
            continue;
        }else if(i<processNumber){
            sprintf(str1, "%d%d", i,processNumber); //2 i= 1  fifo12
        }else{
            sprintf(str1, "%d%d", processNumber, i); // 23
        }
        strcpy(fifoSlave[i-1],argv[4]);
        strcat(fifoSlave[i-1],str1);
        //printf("[%d]Using %s\n",processNumber,fifoSlave[i-1]);

        //Open fifo in read write mode for slave communication
        fifoSlaveFD[i-1] = open(fifoSlave[i-1],O_RDWR|O_NONBLOCK);

        //Create a thread for each pipe, on which the programm will listen for incoming messages
        pthread_create(t_ids+i-1, &attr, slaveCommunication, (void *)&fifoSlaveFD[i-1]);
        
    }
    
    messageReceiveHandler();

}
        
    
