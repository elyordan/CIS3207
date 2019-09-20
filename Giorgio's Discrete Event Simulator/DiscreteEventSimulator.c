#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

#define TRUE 1
#define FALSE 0
#define CPU_ARRIVAL 2
#define CPU_FINISH 3
#define DISK1_ARRIVAL 4
#define DISK1_FINISH 5
#define DISK2_ARRIVAL 6
#define DISK2_FINISH 7
#define SIMULATION_END 8
#define IDLE  0
#define BUSY  1

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
int boolean = 1;
int jobCount = 2;
int utiltimecpu = 0;
int maxResponseCpu = 0;
int diskNum = 0;

//Function Prototypes
void readFile();
void processCpu(queue *pq, queue *cpuq, Job *e);
void processDisk1(queue *pq, queue *disk1queue, Job *e);
void processDisk2(queue *pq, queue *disk2queue, Job *e);
int randomNumber (int min, int max);
int quitProb (int percent);
int whatDisk ();

//creating the file to write the log
FILE *f;

int main() {

    //open file 
    f = fopen("log.txt", "w");

    if (f == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }
    
    //read the file
    readFile();
    CURRENTTIME = INIT_TIME;

    //create the priorityQueue, cpuQueue, disk1Queue, disk2Queue
    queue* cpuQueue = init_queue(0);
    queue* disk1Queue = init_queue(0);
    queue* disk2Queue = init_queue(0);
    queue* priorityQueue = init_queue(1);

    //First 2 jobs for the priority queue
    Job* job0 = init_job(0, SIMULATION_END, FIN_TIME);
    Job* job1 = init_job(1, CPU_ARRIVAL, 0);

    //Add jobs to priority queue
    add_queue(priorityQueue, job0); 
    add_queue(priorityQueue, job1); 

    //Start loop with while checking for size of queue and time
    while((priorityQueue->size != 0) && (CURRENTTIME < FIN_TIME))
    {
        
        //take job to be process from the priorityQueue
        Job* curr_job = del_queue(priorityQueue);

        //Set current time = to job time
        CURRENTTIME = curr_job->jobTime;

        //Switch statement based on the type of job
        switch (curr_job->jobType)
        {
        case CPU_ARRIVAL : processCpu(priorityQueue, cpuQueue, curr_job);
        //printf("CPU_ARRIVAL\n");
            break;        
         case CPU_FINISH : processCpu(priorityQueue, cpuQueue, curr_job);
         //printf("CPU_FINISH\n");
             break;
        
         case DISK1_ARRIVAL : processDisk1(priorityQueue, disk1Queue, curr_job);
         //printf("DISK1_ARRIVAL\n");
             break;

         case DISK1_FINISH : processDisk1(priorityQueue, disk1Queue, curr_job);
         //printf("DISK1_FINISH\n");
           break;

         case DISK2_ARRIVAL : processDisk2(priorityQueue, disk2Queue, curr_job);
         //printf("DISK2_ARRIVAL\n");
             break;

         case DISK2_FINISH : processDisk2(priorityQueue, disk2Queue, curr_job);
         //printf("DISK2_FINISH\n");
             break;

         case SIMULATION_END : 
         //printf("SIMULATION_END\n");
             break;
        
        default:
        //printf("JOB ID : %d, JOB TYPE : %d, JOB TIME : %d\n", curr_job->jobId, curr_job->jobType, curr_job->jobTime);
            break;
        }
    }

    // puts("This is the priority queue:\n");
    // print_queue(priorityQueue);
    // puts("\nThis is the cpu queue:");
    // print_queue(cpuQueue);
    // puts("\nThis is the disk1 queue:");
    // print_queue(disk1Queue);
    // puts("\nThis is the disk2 queue:");
    // print_queue(disk2Queue);

    //Close file
    fclose(f);
    

    free(cpuQueue);
    free(priorityQueue);
    free(disk1Queue);
    free(disk2Queue);
}


//Function to read the values from values.txt
void readFile () 
{
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
    
    for (int t = 0; t < 12; t++) {
        
        fprintf(f,"%s: %d\n", configTypes[t], configValues[t]);
    }
    fprintf(f, "\n\n");
    
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

//Function for CPU processing
void processCpu(queue *pq, queue *cpuq, Job *e)
{
    // it processes the job it sees and adds it to the CPU queue, then after this if statement, 
    // it should actually process the next job in the CPU queue
    if (e->jobType == CPU_ARRIVAL)
    {
        Job* next_job = init_job(jobCount, CPU_ARRIVAL, e->jobTime + randomNumber(ARRIVE_MIN, ARRIVE_MAX));

        //printf("Creating Job Number %d\n", jobCount);
        fprintf(f, "At Time %d Job Number %d Arrives\n", CURRENTTIME, jobCount - 1);
        jobCount++;
        add_queue(pq, next_job);
        add_queue(cpuq, e);

        // //keep track of max cpu size
        // if (cpu.current > maxSizeCpu)
        // {
        //     maxSizeCpu = cpu.current;
        // }
        
    }
    else
    {
        //cpu.status = IDLE;
        fprintf(f, "At Time %d Job Number %d Finishes at CPU\n",CURRENTTIME, e->jobId);
        //competedJobCpu++;
        if(!quitProb(QUIT_PROB))
        {
            Job* disk_job = init_job(e->jobId, whatDisk(), e->jobTime + randomNumber(CPU_MIN, CPU_MAX));
            add_queue(pq, disk_job);
            fprintf(f, "Job %d quit from CPU\n", e->jobId);

        }
    }

    //if the cpu queue is not empty, process the next job in the cpu queue
    if (cpuq->size != 0)
    {
        // dequeue the job from the cpu queue
        Job* task = del_queue(cpuq);
        // make a new job with a finish time
        Job* finish_job = init_job(task->jobId, CPU_FINISH, e->jobTime + randomNumber(CPU_MIN, CPU_MAX));
        // add to the priority queue with the jobs
        add_queue(pq, finish_job); 
        //printf("Finish Job Number %d\n", finish_job->jobId);       
        
        // this is for just the statistics at the end. Not important for the processCPU function
        if(finish_job->jobTime < FIN_TIME)
        {
            utiltimecpu += (finish_job->jobTime - e->jobTime);
        }
        if (((finish_job->jobTime - task->jobTime) > maxResponseCpu) && (finish_job->jobTime < FIN_TIME))
        {
            maxResponseCpu = (finish_job->jobTime - task->jobTime);
        }
    }
       
}

//Function for DISK1 processing
void processDisk1(queue *pq, queue *disk1queue, Job *e)
{
    // it processes the job it sees and adds it to the CPU queue, then after this if statement, 
    // it should actually process the next job in the CPU queue
    if (e->jobType == DISK1_ARRIVAL)
    {
        Job* next_job = init_job(jobCount, DISK1_ARRIVAL, e->jobTime + randomNumber(ARRIVE_MIN, ARRIVE_MAX));

        //printf("Creating Job Number %d\n", jobCount);
        fprintf(f, "At time %d job number %d arrives at DISK1\n", CURRENTTIME, jobCount - 1);
        add_queue(pq, next_job);
        add_queue(disk1queue, e);

        // //keep track of max cpu size
        // if (cpu.current > maxSizeCpu)
        // {
        //     maxSizeCpu = cpu.current;
        // }
        
    }
    else
    {
        //cpu.status = IDLE;
        fprintf(f, "At time %d job Number %d finished processing on DISK1 \n",CURRENTTIME, e->jobId);
        //competedJobCpu++;
        if(!quitProb(QUIT_PROB))
        {
            Job* disk_job = init_job(e->jobId, DISK1_FINISH, e->jobTime + randomNumber(CPU_MIN, CPU_MAX));
            add_queue(pq, disk_job);
            fprintf(f, "Job %d quit from Disk1\n", e->jobId);

        }
    }

    //if the cpu queue is not empty, process the next job in the cpu queue
    if (disk1queue->size != 0)
    {
        // dequeue the job from the cpu queue
        Job* task = del_queue(disk1queue);
        // make a new job with a finish time
        Job* finish_job = init_job(task->jobId, DISK1_FINISH, e->jobTime + randomNumber(CPU_MIN, CPU_MAX));
        // add to the priority queue with the jobs
        add_queue(pq, finish_job); 
        //printf("Finish Job Number %d\n", finish_job->jobId);       
        
        // this is for just the statistics at the end. Not important for the processCPU function
        if(finish_job->jobTime < FIN_TIME)
        {
            utiltimecpu += (finish_job->jobTime - e->jobTime);
        }
        if (((finish_job->jobTime - task->jobTime) > maxResponseCpu) && (finish_job->jobTime < FIN_TIME))
        {
            maxResponseCpu = (finish_job->jobTime - task->jobTime);
        }
    }
       
}
 
//Function for DISK2 processing
void processDisk2(queue *pq, queue *disk2queue, Job *e)
{
    // it processes the job it sees and adds it to the CPU queue, then after this if statement, 
    // it should actually process the next job in the CPU queue
    if (e->jobType == DISK2_ARRIVAL)
    {
        Job* next_job = init_job(jobCount, DISK2_ARRIVAL, e->jobTime + randomNumber(ARRIVE_MIN, ARRIVE_MAX));

        //printf("Creating Job Number %d\n", jobCount);
        fprintf(f, "At time %d job number %d arrives at DISK2\n", CURRENTTIME, jobCount - 1);
        add_queue(pq, next_job);
        add_queue(disk2queue, e);

        // //keep track of max cpu size
        // if (cpu.current > maxSizeCpu)
        // {
        //     maxSizeCpu = cpu.current;
        // }
        
    }
    else
    {
        //cpu.status = IDLE;
        printf( "At time %d job number %d finished processing at DISK2\n",CURRENTTIME, e->jobId);
        //competedJobCpu++;
        if(!quitProb(QUIT_PROB))
        {
            Job* disk_job = init_job(e->jobId, DISK2_FINISH, e->jobTime + randomNumber(CPU_MIN, CPU_MAX));
            add_queue(pq, disk_job);
            fprintf(f,"Job %d quit from DISK2\n", e->jobId);

        }
    }

    //if the cpu queue is not empty, process the next job in the cpu queue
    if (disk2queue->size != 0)
    {
        // dequeue the job from the cpu queue
        Job* task = del_queue(disk2queue);
        // make a new job with a finish time
        Job* finish_job = init_job(task->jobId, DISK2_FINISH, e->jobTime + randomNumber(CPU_MIN, CPU_MAX));
        // add to the priority queue with the jobs
        add_queue(pq, finish_job); 
        //printf("Finish Job Number %d\n", finish_job->jobId);       
        
        // this is for just the statistics at the end. Not important for the processCPU function
        if(finish_job->jobTime < FIN_TIME)
        {
            utiltimecpu += (finish_job->jobTime - e->jobTime);
        }
        if (((finish_job->jobTime - task->jobTime) > maxResponseCpu) && (finish_job->jobTime < FIN_TIME))
        {
            maxResponseCpu = (finish_job->jobTime - task->jobTime);
        }
    }
       
}
 
//function for random number
int randomNumber (int min, int max)
{
    if(boolean) {
        
        //create the seed
        srand(SEED);
        boolean--;
    }
    int range = 1 + max - min;
    return (rand() % range) + min;
}

//Probability of job from quitting the component
int quitProb (int percent)
{
    if ((percent < 0) || (percent > 100) )
    {
        perror("Percent out of Bounds!\n");
        exit(-1);
    }
    else
    {
        int temp = randomNumber(0 , 100);
        if (temp <= percent)
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
        
    }
}

//function to alternate between DISK1 and DISK2
int whatDisk ()
{

    if (diskNum % 2 == 0)
    {
        diskNum++;
        return DISK1_ARRIVAL;
        
    }
    else
    {
        diskNum++;
        return DISK2_ARRIVAL;
    }
    
    
}
