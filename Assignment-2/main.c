/* COP 3502C Assignment 2
This program is written by: John Seredick */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "leak_detector_c.h"

#define EMPTY -1

typedef struct soldier
{
    int sequenceNumber;
    struct soldier *next;
    struct soldier *prev;
} soldier;

typedef struct queue
{
    int groupNumber;
    int soldierCount;
    int k;
    int th;
    char *queueName;
    soldier *front;
    soldier *back;
} queue;

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: The struct that qPtr points to will be set up to represent an
//                 empty queue.
void init(queue *qPtr)
{
    // Just set both pointers to NULL!
    qPtr->front = NULL;
    qPtr->back = NULL;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: returns true iff the queue pointed to by pPtr is empty.
int isEmpty(queue *qPtr)
{
    return qPtr->front == NULL;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: If the queue pointed to by qPtr is non-empty, then the value
//                 at the front of the queue is deleted from the queue and
//                 returned. Otherwise, -1 is returned to signify that the queue
//                 was already empty when the dequeue was attempted.
// Deletes the first node in the queue
void dequeue(queue *q)
{
  if(q->soldierCount > 0)
  {
    soldier *temp = q->front;
    q->front = q->front->next;
    q->back->next = q->front;
    q->front->prev = temp->prev;
    q->soldierCount -= 1;
    if(q->soldierCount == 0)
    {
      q->front = NULL;
      q->back = NULL;
    }
    free(temp);
  }
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: if the queue pointed to by qPtr is non-empty, the value
//                 stored at the front of the queue is returned. Otherwise,
//                 -1 is returned to signify that this queue is empty.
int front(struct queue *qPtr)
{
    if (!isEmpty(qPtr))
        return qPtr->front->sequenceNumber;
    else
        return EMPTY;
}

// Displays the contents of the queue given
void display(queue q, FILE *ofp)
{
  soldier *temp = q.front;
  if(temp!=NULL)
  {
    printf("%d %s", q.groupNumber, q.queueName);
    fprintf(ofp, "%d %s", q.groupNumber, q.queueName);
    while (temp->next!=q.front)
    {
      printf(" %d",temp->sequenceNumber);
      fprintf(ofp, " %d", temp->sequenceNumber);
      temp = temp->next;
    }
    printf(" %d",temp->sequenceNumber);
    fprintf(ofp, " %d", temp->sequenceNumber);
  printf("\n");
  fprintf(ofp, "\n");
  }
}

//Take sequence number and returns a soldier;
soldier *createSoldier(int sequence)
{
    soldier *temp;
    temp = (soldier *)malloc(sizeof(soldier));
    temp->sequenceNumber = sequence;
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}

// Returns the soldier number of the first node in the queue
int peek(queue *q)
{
  return q->front->sequenceNumber;
}

// Pre-condition: qPtr points to a valid struct queue and val is the value to
//                enqueue into the queue pointed to by qPtr.
// Post-condition: If the operation is successful, 1 will be returned, otherwise
//                 no change will be made to the queue and 0 will be returned.
void enqueue(queue *qPtr, int val)
{
    soldier *newSoldier = createSoldier(val);
    soldier *temp = qPtr->back;
    temp->next = newSoldier;
    newSoldier->prev = temp;
    newSoldier->next = qPtr->front;
    qPtr->front->prev = newSoldier;
    qPtr->back = newSoldier;
}

/*takes root of a linked list and insert item to the end of the list.
Returns the root of the list after insertion*/
void createReverseCircle(queue *q)
{
  q->front = createSoldier(q->soldierCount);
  q->front->next = q->front;
  q->front->prev = q->front;
  q->back = q->front->prev;
  for(int i = q->soldierCount-1;i>0;i--)
  {
    enqueue(q,i);
  }
  q->back = q->front->prev;
}

//Rearrange the circle so that it starts from 1 and counts up
void rearrangeCircle(queue *q)
{
  if(q->front == NULL) return;
  soldier *curr, *temp;
  
  q->front = q->front->prev;
  curr = q->front;
  for(int i = 0; i < q->soldierCount; i++)
  {
    temp = curr->next;
    curr->next = curr->prev;
    curr->prev = temp;
    curr = curr->next;
  }
}

//Create Singular group
void createGroup(queue *q, int groupNumber, FILE *inFile)
{
    char name[256];
    int soldierCount;
    int k, th;
    fscanf(inFile, "%s", name);
    q->queueName = malloc(sizeof(char) * (strlen(name)) + 1);
    strcpy(q->queueName, name);
    fscanf(inFile, "%d %d %d", &soldierCount, &k, &th);
    q->soldierCount = soldierCount;
    q->k = k;
    q->th = th;
    q->groupNumber = groupNumber;
    createReverseCircle(q);
}

//Print out the group number, group, and soldiers, then reverse the soldier order
void printStep1(queue *MyQueuePtr, FILE *inFile, FILE *ofp)
{
    int groupCount;
    int groupNumber;
    fscanf(inFile, "%d", &groupCount);
    for (int i = 0; i < groupCount; i++)
    {
        fscanf(inFile, "%d", &groupNumber);
        createGroup(&MyQueuePtr[groupNumber], groupNumber, inFile);
    }
    printf("Initial nonempty lists status\n");
    fprintf(ofp, "Initial nonempty lists status\n");
    for (int i = 1; i <= 10; i++)
    {
        display(MyQueuePtr[i], ofp);
    }
    printf("\nAfter ordering nonempty lists status\n");
    fprintf(ofp, "\nAfter ordering nonempty lists status\n");
    for (int i = 1; i <= 10; i++)
    {
        rearrangeCircle(&MyQueuePtr[i]);
        display(MyQueuePtr[i], ofp);
    }
}

//Execute stage one for individual queue
void phase1Execution(queue *q, FILE *ofp)
{
  soldier *temp, *curr;
  curr = q->front;
  
  int count = q->soldierCount;
  
  while(count > q->th)
  {
    for(int i = 0; i < q->k-1; i++)
    {
      curr = curr->next;
    }
    temp = curr;
    curr = curr->next;
    if(temp->sequenceNumber == q->front->sequenceNumber)
      q->front = q->front->next;
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    printf("Soldier# %d executed\n",temp->sequenceNumber);
    fprintf(ofp, "Soldier# %d executed\n", temp->sequenceNumber);
    count-=1;
    free(temp);
  }
  q->soldierCount = count;
}

//Start First Execution for each queue element
void firstExecution(queue *q, FILE *ofp)
{ 
  for(int i=1; i<=10; i++){
    if(!isEmpty(&q[i])){
      printf("Line# %d %s\n", q[i].groupNumber, q[i].queueName);
      fprintf(ofp, "Line# %d %s\n", q[i].groupNumber, q[i].queueName);
      phase1Execution(&q[i], ofp);
      printf("\n");
      fprintf(ofp, "\n");
    }
  }
}

//Start phase 2 execution process
void phase2Execution(queue *q, int length, FILE *ofp)
{
  int highest = 0;
  for(int i = 0; i < length; i++)
  {
    if(!isEmpty(&q[i]))
      if(highest < peek(&q[i]))
        highest = peek(&q[i]);
  }
  for(int i = 0; i < length; i++)
  {
    if (!isEmpty(&q[i]))
    {
      if (peek(&q[i]) == highest)
      {
        dequeue(&q[i]);
        printf("\nExecuted Soldier %d from line %d",highest,q[i].groupNumber);
        fprintf(ofp, "\nExecuted Soldier %d from line %d", highest, q[i].groupNumber);
        break;
      }
    }
  }
}

//Collect final soldiers for phase 2 execution
void secondExecution(queue *q, FILE *ofp)
{
  int totalSoldiers = 0;
  int numGroups = 0;
  for(int i = 0; i <= 10; i++)
  {
    if(!isEmpty(&q[i]))
    totalSoldiers += q[i].soldierCount;
    numGroups++;
  }
  //Repeat phase 2 of execution until there is only 1 soldier
  while(totalSoldiers > 1)
  {
    phase2Execution(q, numGroups, ofp);
    totalSoldiers -= 1;
  }
}

//Finds the survivor
void findSurvivor(queue *q, FILE *ofp)
{
  int lastSoldier = 0;
  int lastGroup = 0;
  // Stores the survivors value
  for(int i = 1; i <= 10; i++)
  {
    if(!isEmpty(&q[i]))
    {
      lastSoldier = peek(&q[i]);
      lastGroup = q[i].groupNumber;
    }
  }
  printf("\n\nSoldier %d from line %d will survive",lastSoldier,lastGroup);
  fprintf(ofp, "\n\nSoldier %d from line %d will survive\n", lastSoldier, lastGroup);
}

//Release all allocated memory by dequeue and free()
void release_memory(queue *q)
{
  for (int i = 1; i <= 10; i++)
  {
    free(q[i].queueName);
    while (!isEmpty(&q[i]))
    {
      dequeue(&q[i]);
    }
  }
  free(q);
}

int main(void)
{
    atexit(report_mem_leak); //for memory leak detector.

    FILE *inFile, *outFile;
    inFile = fopen("in.txt", "r");
    outFile = fopen("out.txt", "w");

    soldier *root = NULL;

    queue *MyQueuePtr = (queue *)malloc(sizeof(queue) * 11);

    if (inFile != NULL)
    {
        //Initialize the 10 queue's
        for (int i = 1; i <= 10; i++)
        {
            init(&MyQueuePtr[i]);
        }
        
        printStep1(MyQueuePtr, inFile, outFile);

        printf("\nPhase1 execution\n\n");
        fprintf(outFile, "\nPhase1 execution\n\n");

        firstExecution(MyQueuePtr, outFile);

        printf("Phase2 execution");
        fprintf(outFile, "Phase2 execution");

        secondExecution(MyQueuePtr, outFile);

        findSurvivor(MyQueuePtr, outFile);
    }
    else
    {
        printf("Please provide correct input file");
        fprintf(outFile,"Please provide correct input file");
        exit(-1);
    }

    release_memory(MyQueuePtr);
    fclose(inFile);
    return 0;
}