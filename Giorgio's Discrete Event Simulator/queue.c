#include "queue.h"


//function to initialize the queue
queue* init_queue(int pri)
{
    queue* toRet = (queue*)malloc(sizeof(queue));//typecast queue as pointer then allocote memory
    toRet->head = NULL;
    toRet->tail = NULL;
    toRet->priority = pri;
    return toRet;
}
//function to add jobs to the queue
void add_queue(queue* q, Job* j)
{   
    //printf("%d\n", q->priority);
    if (q->size == 0) { //check if the size of the queue is 0
            q->head = j;
            q->tail = j;
    }
    else if (!q->priority) { //if is not a priority queue
        q->tail->next = j;
        q->tail = j;
        q->tail->next = NULL;
    }
    else { //if it is a priority queue
        Job* prev = NULL;
        Job* curr = q->head;
        int i;
        for (i = 0; i < q->size; i++) {
            //printf("%d %d %d\n", i, curr->jobId, curr->jobTime);

            // sort the priority queue by comparing the first element to every other element
            // and inserting then in the right position based on time

            if (j->jobTime <= curr->jobTime) {
                if (prev != NULL) {
                    prev->next = j;
                    j->next = curr;
                }
                else {
                    j->next = curr;
                    q->head = j;
                }
                break;
            }
            else {
                prev = curr;
                curr = curr->next;
            }
        }
        if (i == q->size) {
            q->tail->next = j;
            q->tail = j;
        }

    }    
    q->size++;
}


//function to delete jobs from queue
Job* del_queue(queue* q)
{
    if (q->size > 0) {
        Job* toRet = q->head;
        q->head = q->head->next;
        q->size--;
        return toRet;
    }
    return NULL;
    
}

//function to print queue
void print_queue(queue* q)
{
    Job* temp = q->head;
    for (int i = 0; i < q->size; i++) {
        print_job(temp);
        temp = temp->next;
    }
}

//function to print job
void print_job(Job* j)
{
    printf("ID: %d, TYPE: %d, TIME: %d\n", j->jobId,j->jobType, j->jobTime);
}

//function to initialize job
Job* init_job(int id, int type, int time)
{   
    Job* toRet = (Job*)malloc(sizeof(Job));
    toRet->jobId = id;
    toRet->jobType = type;
    toRet->jobTime = time;
    toRet->next = NULL;
    return toRet;

}


