// Please read all the comments in this code for instruction
//Note that you will have to submit the entire code so that we can just copy paste your code and run it while grading.

/* Do not share or post this question partly or completely as it will be considered as dishonesty. This is a closed note and individual exam.
The following piece of code creates a sorted linked list with 3, 4, 5, 6. A simplePrint function is used to print the data in the linked list. You can run and test the content of the linked list.

What you have to do:

There are two blank functions bellow that you should complete based on the requirements described as comments inside the function.
To test your function you may or may not need to uncomment/add lines in the main function. Compare your result with the comment given in main function.

After completing the code and testing, submit the modified code before the due time as the answer in the quiz. 
[Caution!!! If you run out of time, you will loss all the codes from online gdb compiler. So, periodically copy back the code to submission system]
Use pre-formatted text option to format your code (click the paragraph option the text editor to see the Preformatted option). If you do not use the pre-formatted optoion, there will be 5% some penalty 

Caution: No code will be accepted in email if you miss the deadline. Also do not share your code as sharing will be considered as dishonesty and will be treated accordingly.

Do not hard code to print just the numbers without really calculating it. Hard code will result in -100

                  Write your name here: John Seredick
                   your UCFID: 5331481

*/

//--X27-- Please read the instruction provided above before starting your code --X27--
#include <stdio.h>
#include <stdlib.h>

typedef struct nod
{
    int info;
    struct nod *next;
} node;

node *SortInsert(node *root, int item);   //this function is complete
void simplePrint(node *root);             //this function is complete
void printLast(node *root);               //you have to write this function, see bellow //total grade 50
node *InsertAfter5(node *root, int item); //you have to write this function, see bellow // total grade 50

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
    head = SortInsert(head, 5);

    printf("\nSimple print List 1: ");
    simplePrint(head);

    printLast(head); ////modify the printLast function to make it work

    head = InsertAfter5(head, 100); //modify the InsertAfter5 function to make it work
    printf("\nSimple print after InsertAfter5 with 100: ");
    simplePrint(head); //This call should print 3, 4, 5, 100, 5, 100, 6

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

void printLast(node *root)
{
    /*this function takes the head of a linked list and print the last  or known as tail item in the linked list
    for example: passing the head of a linked list containing 3, 4, 5, 5, 6 would print 6
      If you use recursion you will get 50/50. If you use loop, you will get 40/50 */

    //start writing your code from here
    if (root->next != NULL)
        printLast(root->next);
    else
        printf("\nThe last item in this list is: %d", root->info); //this is a dummy print. Remove this line when you write your function.
};

node *InsertAfter5(node *root, int item)
{
    /*this function takes the head of a linked list and an integer item.
  The function add the integer item in a node after the node containing 5. Next, it returns the head.
  Example: if item = 100, Linked list 3, 4, 5, 5, 6 will be changed to 3, 4, 5, 100, 5, 100, 6 */
    node *current = root;
    node *temp;
    while (current != NULL)
    {
        if (current->info == 5)
        {
            temp = malloc(sizeof(node));
            temp->info = item;
            temp->next = current->next;
            current->next = temp;
        }
        current = current->next;
    }
    return root;
};