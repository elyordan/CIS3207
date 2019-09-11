  
#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>

  //           ******************************************
 //                           Data Structures       
//             ******************************************


//Event Queue - Jobs
typedef struct Job {

  int jobId;
  int jobType;
  int jobTime;

  struct Job * next;
  
} Job;

/*//Linked List Data Structure
typedef struct {

  Job *head;
  Job *tail;
  int size;

  struct Job * next;
  
} queue;*/












#endif
