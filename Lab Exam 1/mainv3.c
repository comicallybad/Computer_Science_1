/*
 Write your name here: Mayank Goyal
 your UCFID: 4609647
*/

//--X28-- Please read the instruction provided above before starting your code --X28--
#include <stdio.h>
#include <stdlib.h>

typedef struct nod
{
    int info;
    struct nod *next;
} node;

node *SortInsert(node *root, int item); //this function is complete
void simplePrint(node *root);           //this function is complete
int countNodes(node *root);             //you have to write this function, see bellow //total grade 50
node *EvenCopy(node *root);             //you have to write this function, see bellow // total grade 50

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

    printf("\nCount Nodes %d", countNodes(head)); //modify the countNodes function to make it work

    head2 = EvenCopy(head); //modify the  EvenCopy function to make it work
    printf("\nSimple print after EvenCopy: ");
    simplePrint(head2); //This call should print 4, 6

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

int countNodes(node *root)
{
    /*this function takes the head of a linked list and returns the number of nodes available in the linked list. If you can use recursion you will get 50/50. If you use loop without recursion, you can get maximum 40/50. If you are not confident about recursion, try with loop first. If you get time later on, try for recursion */
    if (root == NULL)
        return 0;
    else
        return 1 + countNodes(root->next); //this is dummy return. remove it when you change your code
}

node *EvenCopy(node *root)
{
    /*this function takes the head of a linked list and copies all the even numbers to a new linked list and return the
    head of the new linked list. Note that a number is considered as even if number%2 is 0.
    Example: passing the head of a linked list containing 3, 4, 5, 6 would return another linked list containing 4, 6 */
    node *current = root;
    node *newList = NULL;
    node *tail = NULL;

    while (current != NULL)
    {
        if (current->info % 2 == 0)
        {
            if (newList == NULL)
            {
                newList = (node *)malloc(sizeof(node));
                newList->info = current->info;
                newList->next = NULL;
                tail = newList;
            }
            else
            {
                tail->next = (node *)malloc(sizeof(node));
                tail = tail->next;
                tail->info = current->info;
                tail->next = NULL;
            }
        }
        current = current->next;
    }
    return newList; //this is dummy return. remove it when you change your code
}