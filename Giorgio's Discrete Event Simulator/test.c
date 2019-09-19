#include <stdio.h>
#include "queue.h"

int main()
{

    // Job* j1 = init_job(1, 2, 15);
    // Job* j2 = init_job(2, 5, 10);
    // Job* j3 = init_job(3, 10, 5);
    // queue* q = init_queue(0);
    // add_queue(q, j1);
    // add_queue(q, j2);
    // add_queue(q, j3);
    // print_queue(q);
    // del_queue(q);
    // puts("");
    // print_queue(q);
    // del_queue(q);
    // puts("");
    // print_queue(q);
    // del_queue(q);
    // puts("");
    // print_queue(q);

    // del_queue(q);
    // print_queue(q);

    // puts("TESTING PRIORITY QUEUE\n\n");
    // queue* q2 = init_queue(1);
    // add_queue(q2, j1);
    // add_queue(q2, j2);
    // add_queue(q2, j3);
    // Job* j4 = init_job(4, 3, 11);
    // print_queue(q2);

    /*for (size_t i = 0; i < 2; i++)
    
    {

      Job *removeJob =  del_queue(priorityQueue);
      print_queue(priorityQueue);
      add_queue(cpuQueue, removeJob);
    
    }*/
    
    queue* cpuQueue = init_queue(0);
    queue* disk1Queue = init_queue(0);
    queue* disk2Queue = init_queue(0);
    queue* priorityQueue = init_queue(1);

    Job* j1 = init_job(1, 3);
    Job* j2 = init_job(2, 4);
    Job* j3 = init_job(3, 8);
    Job* j4 = init_job(4, 7);
    queue* q = init_queue(1);

    
    add_queue(q, j1);
    add_queue(q, j2);
    add_queue(q, j3);
    add_queue(q, j4);    
    print_queue(q);


}
