/**
    MASTER
        - slave 1
            -
        - slave 2
            -
        - slave 3
    
    masterPipe1, masterPipe2, masterPipe3
    pipe12, pipe13, pipe23

**/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define RED "\033[0;31m"
#define GREEN "\033[32m"
#define DF "\033[0m"

#define MAX_SLAVES 10
#define MAX_ARGS 600 //Maximum command length
#define MAX_MSG 500 //Maximum message length

#define PIPE_SLAVE "/tmp/fifoSlave"  //Name of the slave pipes
#define PIPE_MASTER "/tmp/fifoMaster" //Name of the master pipes

char fifoMaster[MAX_SLAVES][100]; //The names of the pipes used to communicate with slaves
int fifoMasterFD[MAX_SLAVES]; //File descriptors of the pipes used to communicate with slaves

// Error printing function
void perr(char * str){
    fprintf(stderr,"%s%s%s\n",RED,str,DF);
}






//Quit method
void quit(int signo){
    printf("\nQuitting programm...\n");

    for(int i = 0; i< MAX_SLAVES; i++){
        close(fifoMasterFD[i]);
    }

    //Terminate all children
    kill(0,SIGTERM);
    while(wait(NULL)>0);
    printf("END OF PROGRAM\n");
    exit(0);
}







int main(int argc, char ** argv){
    //Force quit on CTRL+C
    signal(SIGINT,quit);
    
    
    //Check parameters
    if(argc < 2){
        perr("Invalid number of parameters");
        exit(1);
    }

    //Get number of slaves
    int slaves = atoi(argv[1]);
    if(slaves < 0 || slaves > MAX_SLAVES){
        perr("Invalid argument");
        exit(2);
    }
    






    //Create FIFOs
    char str2[10], tmp[100];

    for (int i = 1; i <= slaves; i++){
        strcpy(fifoMaster[i-1],PIPE_MASTER);
        //Convert int i to string
        sprintf(str2, "%d", i);

        //Create string '/tmp/fifoMaster1/2/...'
        strcat(fifoMaster[i-1], str2);
        //Create file for FIFO
        unlink(fifoMaster[i-1]);
        //Create FIFO
        printf("Creating fifo '%s'\n",fifoMaster[i-1]);
        mkfifo(fifoMaster[i-1],0666);

        printf("Creating pipes for slaves\n");
        //Create a fifo for each pair of processes so that the pipe name betwen x and y 
        // is pipeNameXY if x < y. 
        for (int j = i+1; j <= slaves; j++){
            strcpy(tmp,PIPE_SLAVE);
            sprintf(str2, "%d%d", i,j); 
            strcat(tmp, str2);
            unlink(tmp);
            mkfifo(tmp,0666);
        }
        
    }


    
    //Execute the slaves
    char tmpArg[10],tmpArg2[10];
    //Create the argument array containing the number of slave, the number of slaves and the pipe root names
    char * argExec[] = {"./slave.out","0",tmpArg2,PIPE_MASTER,PIPE_SLAVE,NULL};
    //Convert to string the number of slaves
    sprintf(tmpArg2, "%d", slaves);
    
    printf("Creating slaves\n");
    for (int i = 1; i <= slaves; i++){
        //Pass as argument the number of the slaves
        sprintf(tmpArg, "%d", i);
        argExec[1]=tmpArg;
        if(fork()==0)
            execv(argExec[0],argExec);
    }




    


    //Ignore signal term to prevent QUIT from terminating the master.
    signal(SIGTERM,SIG_IGN);

    //Open the master pipes in write
    for (int i = 0; i < slaves; i++){
        //Open pipe in write
        fifoMasterFD[i] = open(fifoMaster[i],O_WRONLY);
    }
    printf("All pipes opened\n");
    







    char buffer[MAX_ARGS], msg[MAX_MSG];
    int source = 0, dest = 0, ind = 0;
    
    //Parse commands
    while(1){
        sleep(1);
        printf("\nNext command: ");fflush(stdout);
    
        //Fetch command from STDIN
        int r = read(STDIN_FILENO, buffer, MAX_ARGS-1);
        buffer[r-1] = 0; //Terminate string removing new line
        
        for(int i = 0; i<r;i++){
            //Check for the directional character
            if(buffer[i]=='<'){
                //Save operand  1<23 ciao
                strncpy(tmp,buffer,i);
                tmp[i]=0;

                //Convert operand to int
                dest=atoi(tmp);
                if(dest<= 0 || dest > slaves){
                    break;
                }
                ind = i+1;
            }else if(buffer[i]=='>'){
                //Save operand
                strncpy(tmp,buffer,i);
                tmp[i]=0;

                //Convert operand to int
                source=atoi(tmp);
                if(source<= 0 || source > slaves){
                    break;
                }
                ind = i+1;
            }else if(buffer[i] == ' '){ //This should be the message 
                //Check if destination or source was set
                if(dest == 0 && source == 0){
                    break;
                }
                //Copy operand
                strncpy(tmp,buffer+ind,i-ind);
                tmp[i]=0;

                //Check whether we need to save the dest or the source
                if(dest == 0){
                    dest=atoi(tmp);
                    if(dest<= 0 || dest > slaves){
                        break;
                    }
                }else{ //Save source
                    source=atoi(tmp);
                    if(source<= 0 || source > slaves){
                        break;
                    }
                }
                if(dest == source){
                    break;
                }

                //Copy the body of the message
                strncpy(msg,buffer+i+1,r-i+1);

                //Create command message for the slave "2>4 ciao come va"
                //Syntax: source msg. Esempio: '4 ciao come va' sent to 2.
                sprintf(tmp,"%d ",dest);
                strcpy(buffer,tmp);
                strcat(buffer,msg);
                
                if(strlen(msg)<=0){
                    break;
                }
                
                //Send command to slave using the master fifo
                write(fifoMasterFD[source-1],buffer,strlen(buffer));
                break;
            }  
        }
        //If dest or source are 0 then the message was not sent
        if(dest == 0 || source == 0 || dest > slaves || source > slaves || dest == source || strlen(msg)<=0){
            perr("Wrong command");
        }
        dest=0; source=0;
    }

}