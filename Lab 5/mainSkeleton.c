// Arup Guha
// 6/26/07
//modified by Tanvir Ahmed 5/29/2020
// Example of how to implement a queue with a linked list.
#include <stdio.h>
#include <stdlib.h>

#define EMPTY -1

// Stores one node of the linked list.
struct node
{
    int data;
    struct node *next;
};

// Stores our queue.
struct queue
{
    struct node *front;
    struct node *back;
};

void init(struct queue *qPtr);
int enqueue(struct queue *qPtr, int val);
int dequeue(struct queue *qPtr);
int empty(struct queue *qPtr);
int front(struct queue *qPtr);
void displayQueue(struct queue *MyQueuePtr);

int main()
{

    // Allocate space for our queue and initialize it.
    struct queue *MyQueuePtr = (struct queue *)malloc(sizeof(struct queue));
    init(MyQueuePtr);

    int choice;
    int data;

    int i;

    while (1)
    {
        printf("\n1.Insert element to queue \n");
        printf("2.Delete element from queue \n");
        printf("3.Display all elements of queue \n");
        printf("4.Quit \n");
        printf("Enter your choice : ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("\nWhat data you want to put in the queue?: ");
            scanf("%d", &data);
            enqueue(MyQueuePtr, data);
            displayQueue(MyQueuePtr);
            break;
        case 2:
            data = dequeue(MyQueuePtr);
            if (data != EMPTY)
            {
                printf("\n%d deleted from queue\n", data);
                displayQueue(MyQueuePtr);
            }
            else
                printf("Empty queue\n");
            break;
        case 3:
            displayQueue(MyQueuePtr);
            break;
        case 4:
            exit(1);
        default:
            printf("Wrong choice \n");
        } /*End of switch*/
    }     /*End of while*/
    return 0;
} /*End of main()*/

void displayQueue(struct queue *MyQueuePtr)
{
    struct node *t = MyQueuePtr->front;
    while (t)
    {
        printf("%d ", t->data);
        t = t->next;
    }
}
// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: The struct that qPtr points to will be set up to represent an
//                 empty queue.
void init(struct queue *qPtr)
{
    // Just set both pointers to NULL!
    qPtr->front = NULL;
    qPtr->back = NULL;
}

// Pre-condition: qPtr points to a valid struct queue and val is the value to
//                enqueue into the queue pointed to by qPtr.
// Post-condition: If the operation is successful, 1 will be returned, otherwise
//                 no change will be made to the queue and 0 will be returned.
int enqueue(struct queue *qPtr, int val)
{

    struct node *temp;

    // Allocate space for a new node to add into the queue.
    temp = malloc(sizeof(struct node));

    // This case checks to make sure our space got allocated.
    if (temp != NULL)
    {

        // Initialize temp, and insert into queue
        temp->data = val;
        temp->next = NULL;

        // If the queue is NOT empty, we must set the old "last" node to point
        // to this newly created node.
        if (qPtr->back != NULL)
            qPtr->back->next = temp;

        // Now, we must reset the back of the queue to our newly created node.
        qPtr->back = temp;

        // If the queue was previously empty we must ALSO set the front of the
        // queue.
        if (empty(qPtr))
            qPtr->front = temp;

        // Signifies a successful operation.
        return 1;
    }

    // No change to the queue was made because we couldn't find space for our
    // new enqueue.
    else
        return 0;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: If the queue pointed to by qPtr is non-empty, then the value
//                 at the front of the queue is deleted from the queue and
//                 returned. Otherwise, -1 is returned to signify that the queue
//                 was already empty when the dequeue was attempted.
int dequeue(struct queue *qPtr)
{

    struct node *tmp;
    int retval;

    // Check the empty case.
    if (empty(qPtr))
        return EMPTY;

    // Store the front value to return.
    retval = qPtr->front->data;

    // Set up a temporary pointer to use to free the memory for this node.
    tmp = qPtr->front;

    // Make front point to the next node in the queue.
    qPtr->front = qPtr->front->next;

    // If deleting this node makes the queue empty, we have to change the back
    // pointer also!
    if (qPtr->front == NULL)
        qPtr->back = NULL;

    // Free our memory.
    free(tmp);

    // Return the value that just got dequeued.
    return retval;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: returns true iff the queue pointed to by pPtr is empty.
int empty(struct queue *qPtr)
{
    return qPtr->front == NULL;
}

// Pre-condition: qPtr points to a valid struct queue.
// Post-condition: if the queue pointed to by qPtr is non-empty, the value
//                 stored at the front of the queue is returned. Otherwise,
//                 -1 is returned to signify that this queue is empty.
int front(struct queue *qPtr)
{
    if (!empty(qPtr))
        return qPtr->front->data;
    else
        return EMPTY;
}
