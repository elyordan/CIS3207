  
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

  //           ******************************************
 //                           Data Structures       
//             ******************************************


// strut for events creation
typedef struct Event 
{

  int eventId;
  int eventType;
  int eventTime;

  struct Event * next;
  
} Event;

Event* init_event(int, int, int);

// strut for jobs creation
typedef struct Job 
{

  int jobId;
  int jobTime;

  struct Job * next;
  
} Job;

Job* init_job(int, int);

// queue as a linked list
typedef struct queue
{

  Job *head;
  Job *tail;
  int size;

  // added int priority so that if is 0 is a regular queue 
  //and if is 1 is going to be a priority queue
  int priority;
  
} queue;

typedef struct Eventqueue
{

  Event *head;
  Event *tail;
  int size;

  // added int priority so that if is 0 is a regular queue 
  //and if is 1 is going to be a priority queue
  int priority;
  
} Eventqueue;

// prototypes for functions on the queue.c files
queue* init_queue(int);
void add_queue(queue*, Job*);
Job* del_queue(queue*);
void print_queue(queue*);
void print_job(Job*);
void print_event(Event*);
void add_Eventqueue(Eventqueue * , Event *);
Event* del_eventqueue(Eventqueue*);


#endif

