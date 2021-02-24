//This code shows performing various operations on linked list recursively.
// insert, delete, free, display, copy
#include<stdio.h>
#include <stdlib.h>
#include	"leak_detector_c.h"

struct node {
     int data;
     struct node  *next;
};

struct node* insert(struct node* list,int d );
struct node* del(struct node* list,int d );
void print( struct node *list);
void freeList(struct node* list);
void copy ( struct node *q, struct node **s );

int main( ) {

    atexit(report_mem_leak); //for leak detector
    int number = 0, choice=0;
    struct node *pList=NULL;
    struct node *nList = NULL;

    // Let the user add values until they enter -1.
    while(choice!= 4)
    {
        // Get the operation.
        printf("\nDo you want to (1)insert, (2)delete, (3)Copy (4)quit.\n");
        scanf("%d", &choice);

        printf("Your choice is %d\n", choice);

        // Execute the operation.
        if (choice == 1)
        {
           // Get the number.
            printf("Enter the value to insert\n");
            scanf("%d", &number);
            pList = insert(pList, number);
                    // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            //printf("\n");
        }
        else if (choice == 2)
        {    // Get the number.
            printf("Enter the value to delete.\n");
            scanf("%d", &number);
            pList = del(pList, number);
                    // Look at the list.
            printf("Items in linked list: ");
            print(pList);
            //printf("\n");
        }
        else if (choice == 3)
        {
            if (nList)
                freeList(nList);

            copy(pList, &nList); //passing reference of nList as it is not returning anything
                    // Look at the list.
            printf("Items in NEW linked list: ");
            print(nList);
           // printf("\n");


        }
        else
        {
              break;

        }

    }
    freeList(nList);
    freeList(pList);
    printf("\nBye..\n");
    return 0;
}


/* copies a linked list into another */
void copy ( struct node *source, struct node **dest )
{
    if (source != NULL)
    {
        *dest = malloc(sizeof(struct node));

        (*dest)->data = source -> data; //need double dereference to access nList's pointed data
        (*dest)->next = NULL ;

        copy(source->next, &((*dest)->next)); //call recursively with source next and reference of nList-> next
    }
}

// Recursively inserts item into the LL pointed to by list in order.
struct node* insert(struct node *list,int item) {

    // Node is at front, insert and return.
    if (list == NULL || item <= list->data) {
        struct node * pNew= malloc(sizeof(struct node));
        pNew->data = item;
        pNew->next = list;
        return pNew;
    }

    // Recursively insert and return the front of the list.
    list->next = insert(list->next, item);
    return list;
}

// Recursively deletes the first node storing item in the list pointed to
// by list. If no such node exists, no changes are made. a pointer to the front
// of the resulting list is returned.
struct node* del(struct node *list, int item) {

    // Simple case.
    if (list == NULL)
        return NULL;

    // Free this node and return a pointer to the rest of the list.
    if (list->data == item) {
        struct node* rest = list->next;
        free(list);
        return rest;
    }

    // Recursively delete and return the front of the list.
    list->next = del(list->next, item);
    return list;
}

void print(struct node *list) {
    if(list != NULL) {
    printf("%d ", list->data);
    print(list->next);
    }
}

// Frees each node in the LL pointed to by list.
void freeList(struct node* list) {
    if(list != NULL) freeList(list->next);
    free(list);
}
