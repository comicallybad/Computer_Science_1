// --X29-- read the instrction provided above before starting  --X29--

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int info;
    struct node *next;
} node;

node *SortInsert(node *root, int item); //this function is complete
void simplePrint(node *root);           //this function is complete
int sumMyList(node *root);              //you have to write this function, see bellow //total grade 50
node *BackToFrontMove(node *root);      //you have to write this function, see bellow // total grade 50

int main()
{
    node *head = NULL;
    node *head2 = NULL;

    node *t;
    int ch, ele;
    head = SortInsert(head, 4);
    head = SortInsert(head, 6);
    head = SortInsert(head, 3);
    head = SortInsert(head, 5);

    printf("\nSimple print List 1: ");
    simplePrint(head);

    printf("\nsum of the list %d", sumMyList(head)); //modify the sumMyList function to make it work. It should print 18.

    head = BackToFrontMove(head); //modify the BackToFrontMove function to make it work
    printf("\nSimple print: ");   //it should print 6, 3, 4, 5
    simplePrint(head);

    return 0;
}

void simplePrint(node *root)
{
    node *t = root;
    while (t != NULL)
    {
        printf("%d ", t->info);
        t = t->next;
    }
}

node *SortInsert(node *root, int item)
{
    node *temp;
    node *t;
    temp = (node *)malloc(sizeof(node));
    temp->info = item;
    temp->next = NULL;
    if (root == NULL || root->info >= item)
    {
        temp->next = root;
        root = temp;
    }
    else
    {
        t = root;
        while (t->next != NULL && t->next->info < item)
            t = t->next;
        temp->next = t->next;
        t->next = temp;
    }

    return root;
}

///////// All questions are starting here//////////////////

int sumMyList(node *root)
{
    if (root == NULL)
        return 0;
    else
        return root->info + sumMyList(root->next); //this is a dummy return. Remove it when you write your function.
};

node *BackToFrontMove(node *root)
{
    /*this function takes the head of a linked list and move the tail node's item in the linked list to the head
    and return the new head. Example: Linked list 3, 4, 5, 6 will be changed to 6, 3, 4, 5
    At the end, the function returns the head*/
    if (root == NULL || root->next == NULL)
        return root;

    node *temp = NULL;
    node *t = root;

    while (t->next != NULL)
    {
        temp = t;
        t = t->next;
    }

    temp->next = NULL;
    t->next = root;

    root = t;

    return root;
};