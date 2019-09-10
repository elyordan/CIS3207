// Structure for JOBS using typedef:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 
struct Node {
	int data;
	struct Node *next;
};
 
struct Queue {
	struct Job *front;
	struct Node *last;
	unsigned int size;
};
 
void init(struct Queue *q) {
	q->front = NULL;
	q->last = NULL;
	q->size = 0;
}
 
int front(struct Queue *q) {
	return q->front->data;
}
 
void pop(struct Queue *q) {
	q->size--;
 
	struct Node *tmp = q->front;
	q->front = q->front->next;
	free(tmp);
}
 
void push(struct Queue *q, int data) {
	q->size++;
 
	if (q->front == NULL) {
		q->front = (struct Node *) malloc(sizeof(struct Node));
		q->front->data = data;
		q->front->next = NULL;
		q->last = q->front;
	} else {
		q->last->next = (struct Node *) malloc(sizeof(struct Node));
		q->last->next->data = data;
		q->last->next->next = NULL;
		q->last = q->last->next;
	}
}
 
// Driver code.
int main(void) {
	struct Queue q;
	init(&q);
	push(&q, 1);
	push(&q, 2);
	printf("%d\n", front(&q));
	pop(&q);
	printf("%d\n", front(&q));
}


































typedef struct {

  int jobId;
  int jobType;
  int jobtime;

  struct Job * next;
  
} Job;




