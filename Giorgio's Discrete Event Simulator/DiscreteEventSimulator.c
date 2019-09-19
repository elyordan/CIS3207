#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

//Global Variables
float SEED = 0;
int INIT_TIME = 0;
int  FIN_TIME = 0;
int ARRIVE_MIN = 0;
int ARRIVE_MAX = 0;
int CPU_MIN = 0;
int CPU_MAX = 0;
int DISK1_MIN = 0;
int DISK1_MAX = 0;
int DISK2_MIN = 0;
int DISK2_MAX = 0;
float QUIT_PROB = 0;
int CURRENTTIME = 0;

//cpu disk1 and disk2 states 0 close and 1 open
int cpuState = 1;
int disk1State = 1;
int disk2State = 1;


//Function Prototypes
void readFile();
void writeLog ();
int cpu (int eventType, int eventTime );
int disk1 (int eventType, int eventTime );
int disk2 (int eventType, int eventTime );


int main() {

    //first read the file
    readFile();
    CURRENTTIME = INIT_TIME;

    //create the seed
    srand(SEED);
    

    //create the priorityQueue, cpuQueue, disk1Queue, disk2Queue
    queue* cpuQueue = init_queue(0);
    queue* disk1Queue = init_queue(0);
    queue* disk2Queue = init_queue(0);
    queue* priorityQueue = init_queue(1);
    queue* testQueue = init_queue(0);


    //start the for loop with fin_time and then the whole program goes inside the for loop
    for (size_t i = 0; i < 64; i++)
    {
        //create jobs
        Job* otherJobs = init_job(i, (rand() % ((ARRIVE_MAX - ARRIVE_MIN ) + i)));

        //push jobs into cpu queue
        add_queue(cpuQueue, otherJobs); 
        
        //pull job from cpu queue and send it to cpu if is free
        if (cpuState == 1)
        {
            int cpuResponse = cpu(otherJobs->jobId, otherJobs->jobTime);

            if (cpuResponse == 1)
            {
                //job exit the cpu
                printf("Job got out of program\n");
                Job* removeJob = del_queue(cpuQueue);
                add_queue(testQueue, removeJob);

                //cpu ready to receive another job
                cpuState = 1;
            }
            else
            {
                //cpu still busy send job to disk 1 or 2
                printf("CPU still busy\n");
                Job *removeJob =  del_queue(cpuQueue);
                add_queue(disk1Queue, removeJob);
                cpuState = 0;
            }
            

        }
        else if (disk1State == 1)
        {
            int disk1Response = disk1(otherJobs->jobId, otherJobs->jobTime);

            if (disk1Response == 1)
            {
                //job exit the disk1
                printf("Job got out of disk1\n");
                Job* removeJob = del_queue(disk1Queue);
                add_queue(cpuQueue, removeJob);

                //disk1 ready to receive another job
                disk1State = 1;
            }
            else
            {
                //disk1 still busy 
                printf("disk1 still busy\n");
                disk1State = 0;
            }
        }
        else if (disk2State == 1)
        {
            int disk2Response = disk2(otherJobs->jobId, otherJobs->jobTime);

            if (disk2Response == 1)
            {
                //job exit the disk2
                printf("Job got out of disk2\n");
                Job* removeJob = del_queue(disk2Queue);
                add_queue(cpuQueue, removeJob);

                //disk2 ready to receive another job
                disk2State = 1;
            }
            else
            {
                //disk2 still 
                printf("disk2 still busy\n");
                disk2State = 0;
            }
        }
        else
        {
            /* code */
        }
        
    }

    puts("This is the priority queue:\n");
    print_queue(priorityQueue);
    puts("\nThis is the cpu queue:");
    print_queue(cpuQueue);
    puts("\nThis is the disk1 queue:");
    print_queue(disk1Queue);
    puts("\nThis is the disk2 queue:");
    print_queue(disk2Queue);
    puts("\nThis is the test queue:");
    print_queue(testQueue);

    free(cpuQueue);
    free(priorityQueue);
    free(disk1Queue);
    free(disk2Queue);
    free(testQueue);
}


//Function to read the values from values.txt
void readFile () {

    //file reader variables
    const char *configTypes[12] = {"SEED", "INIT_TIME", "FIN_TIME", "ARRIVE_MIN", "ARRIVE_MAX", "CPU_MIN", "CPU_MAX","DISK1_MIN", "DISK1_MAX", "DISK2_MIN", "DISK2_MAX", "QUIT_PROB"};
    int configValues[12] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    //File reading
    FILE *fp = NULL;
    fp = fopen("values.txt", "r");
    
    
    if (fp != NULL) {
        
        int lineLength = 1024;
        char *token;
        char stringSearch[lineLength];
        float valueSearch;
        char line[lineLength];
        int i;
        
        while (fgets(line, lineLength, fp) != NULL) {

            token = strtok(line, " ");
            
            if (token != NULL) {

                strcpy(stringSearch, token);
            }

            else {

                continue;
            }

            token = strtok(NULL, " ");

            if (token != NULL) {

                valueSearch = atof(token);
            }

            else {

                valueSearch = 0;
            }
            
            for (i = 0; i < 12; i++) {

                if (strcmp(stringSearch, configTypes[i]) == 0) {

                    configValues[i] = (int)valueSearch;
                }
            }
        }
    }
    
    /*for (int t = 0; t < 12; t++) {
        
        printf("%s: %d\n", configTypes[t], configValues[t]);
    }*/
    
    SEED = configValues[0];
    INIT_TIME = configValues[1];
    FIN_TIME = configValues[2];
    ARRIVE_MIN = configValues[3];
    ARRIVE_MAX = configValues[4];
    CPU_MIN = configValues[5];
    CPU_MAX = configValues[6];
    DISK1_MIN = configValues[7];
    DISK1_MAX = configValues[8];
    DISK2_MIN = configValues[9];
    DISK2_MAX = configValues[10];
    QUIT_PROB = configValues[11];

    QUIT_PROB = QUIT_PROB/100;

}

//write to the file called log from the priorityQueue
void writeLog () {




}



int cpu (int jobIdCpu, int jobTimeCpu ) 
{   
    
    //create ramdon number for time calculation
    int randomNumber = (rand() % ((CPU_MAX - CPU_MIN ) + 1));
    
    //add ramdon number to job time
    CURRENTTIME = CURRENTTIME +(jobTimeCpu + randomNumber);
    int timeSpend = jobTimeCpu + randomNumber;

    printf("randomNumber : %d\n", randomNumber);
    printf("Job ID : %d\n", jobIdCpu );
    printf("Cureent Time : %d\n", CURRENTTIME);

    printf("Job ID on CPU : %d Job Time on CPU : %d\n", jobIdCpu, jobTimeCpu);
    while (timeSpend)
    {
        cpuState = 0;
        printf("CPU is on working state. time spend %d\n", timeSpend);
        timeSpend--;
    }
    
    //QUIT_PROB calculations
    int exit = rand() < QUIT_PROB * ((double)RAND_MAX +1.0);
    printf("Exit : %d\n", exit);

    return exit;
    
}

int disk1 (int jodIdDisk1, int jobTimeDisk1 ) {
    
    //create ramdon number for time calculation
    int randomNumber = (rand() % ((CPU_MAX - CPU_MIN ) + 1));
    
    //add ramdon number to job time
    CURRENTTIME = CURRENTTIME +(jobTimeDisk1 + randomNumber);
    int timeSpend = jobTimeDisk1 + randomNumber;

    printf("randomNumber : %d\n", randomNumber);
    printf("Job ID : %d\n", jodIdDisk1 );
    printf("Cureent Time : %d\n", CURRENTTIME);

    printf("Job ID on disk1 : %d Job Time on disk1 : %d\n", jodIdDisk1, jobTimeDisk1);
    while (timeSpend)
    {
        disk1State = 0;
        printf("disk1 is on working state. time spend %d\n", timeSpend);
        timeSpend--;
    }
    
    //QUIT_PROB calculations
    int exit = rand() < QUIT_PROB * ((double)RAND_MAX +1.0);
    printf("Exit : %d\n", exit);

    return exit;
}

int disk2 (int jodIdDisk2, int jobTimeDisk2 ) {
    
    //create ramdon number for time calculation
    int randomNumber = (rand() % ((CPU_MAX - CPU_MIN ) + 1));
    
    //add ramdon number to job time
    CURRENTTIME = CURRENTTIME +(jobTimeDisk2 + randomNumber);
    int timeSpend = jobTimeDisk2 + randomNumber;

    printf("randomNumber : %d\n", randomNumber);
    printf("Job ID : %d\n", jodIdDisk2 );
    printf("Cureent Time : %d\n", CURRENTTIME);

    printf("Job ID on CPU : %d Job Time on CPU : %d\n", jodIdDisk2, jobTimeDisk2);
    while (timeSpend)
    {
        cpuState = 0;
        printf("CPU is on working state. time spend %d\n", timeSpend);
        timeSpend--;
    }
    
    //QUIT_PROB calculations
    int exit = rand() < QUIT_PROB * ((double)RAND_MAX +1.0);
    printf("Exit : %d\n", exit);

    return exit;
}



