Discrete Event Simulator Homework for CIS3207

Yunior Lopez

In this project I have created Georgio’s Discrete Event Simulator, that simulates the whole operation of a computer virtually. In my simulator I have 1 CPU and 2 disks. 

How it works:

At the start of the program 2 initial jobs are created and loaded into the priority queue and then 1 job is removed from the queue and sent to the CPU function processCpu(), for processing. In the CPU the job is given a processing time randomly and the CPU waits until it’s time to release the job and move on to the next job. After a job is completed by the CPU,then in the same function I checked the probability, to see if the job will leave the simulation or not. If it leaves it’s given an job type of 3 and loaded back into the priority queue. If it moves on to the disk1 then job type would be 4 and then the job is sent to the priority queue. It works the same for disk2 and simulation end. when sending a job the the disk, my implementation was to alternate between disk1 and disk2.

Here are all my values for the job types:

#define TRUE 1
#define FALSE 0
#define CPU_ARRIVAL 2
#define CPU_FINISH 3
#define DISK1_ARRIVAL 4
#define DISK1_FINISH 5
#define DISK2_ARRIVAL 6
#define DISK2_FINISH 7
#define SIMULATION_END 8

 
How to compile:
To run the program use the comand "gcc DiscreteEventSimulator.c queue.c" and then "./a.out"
