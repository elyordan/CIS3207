#include <stdio.h>
#include <stdlib.h>

typedef struct {

  int jobId;
  int jobType;
  int jobTime;

  struct Job * next;
  
} Job;