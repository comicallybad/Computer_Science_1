/* Tanvir Ahmed
This code implements some basic operation of singly linked list like inserting in the beginning and end, delete operation, and display operation
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
	int data;
	struct node *next;
} node;

//this function takes an item and insert it in the linked list pointed by root.
node *insert_front(node *root, int item)
{
	node *temp;
	//create a new node and fill-up the node
	temp = (node *)malloc(sizeof(node));
	temp->data = item;
	temp->next = NULL;
	if (root == NULL) //if there is no node in the linked list
		root = temp;
	else //there is an existing linked list, so put existing root after temp
	{
		temp->next = root; //put the existing root after temp
		root = temp;	   //make the temp as the root!
	}
	return root;
}

//this function takes an item and insert it in the end of the linked list
node *insert_end(node *root, int item)
{
	node *t;
	node *temp;
	//create a new node and fill-up the node
	temp = (node *)malloc(sizeof(node));
	temp->data = item;
	temp->next = NULL;
	if (root == NULL) //if there is no node in the linked list, make temp as the root
		root = temp;
	else //there is an existing linked list and we need to traverse to reach the end node
	{
		t = root;				//t is being used to start traversing
		while (t->next != NULL) //keep going till the end
			t = t->next;

		t->next = temp; //t is at the last node of the linked list, so add temp after t.
	}
	return root;
}

void addN(struct node *list, int n)
{
	if (list == NULL)
	{
		printf("There is no data.");
	}
	else
	{
		while (list != NULL)
		{
			list->data += n;
			list = list->next;
		}
	}
}

node *deleteFirst(struct node *list)
{
	if (list == NULL)
		printf("There is no data");
	else
	{
		node *temp = malloc(sizeof(node));
		temp = list;
		list = list->next;
		free(temp);
	}
	return list;
}

node *question4(struct node *list)
{
	struct node *a = list;
	struct node *b = list;
	struct node *c;
	if (a == NULL)
		return NULL;
	while (a->next != NULL)
		a = a->next;
	a->next = b;
	c = b->next;
	b->next = NULL;
	return c;
}

int isSorted(struct node *list)
{
	if (list != NULL)
	{
		int min;
		int boolean = 1;

		min = list->data;
		while (list->next != NULL)
		{
			list = list->next;
			if (list->data < min)
				boolean = 0;
		}
		return boolean;
	}
	else
		return -9999;
}

struct node *copy(struct node *list)
{
	struct node *current = list;
	struct node *newList = NULL;
	struct node *tail = NULL;

	while (current != NULL)
	{
		if (newList == NULL)
		{
			newList = (struct node *)malloc(sizeof(struct node));
			newList->data = current->data;
			newList->next = NULL;
			tail = newList;
		}
		else
		{
			tail->next = (struct node *)malloc(sizeof(struct node));
			tail = tail->next;
			tail->data = current->data;
			tail->next = NULL;
		}
		current = current->next;
	}

	return newList;
}

void list_42(node *list)
{
	struct node *current = list;
	struct node *temp;
	while (current != NULL)
	{
		if (current->data == 4)
		{
			temp = malloc(sizeof(struct node));
			temp->data = 2;
			temp->next = current->next;
			current->next = temp;
		}
		current = current->next;
	}
}

/*this function deletes the first occurrence of a given item from linked list.
it returns the updated/original root
*/
node *DelList(node *root, int item)
{
	node *t;
	node *temp;
	if (root == NULL) //if there is no linked list, just return root/null
		return root;
	if (root->data == item) //if root contains the item, remove the current root and change it to the next node
	{
		temp = root;	   //put existing root to temp so that we can free it. Otherwise, there will be memory leak
		root = root->next; //change the root by the next node of the current root.
		free(temp);
		return root;
	}

	//the code will reach here if the item is not in the root. So, we need to traverse.
	t = root;

	/*keep going until we reach to the end or we find the item.
	note that we look ahead so that we will be one node before the node we will be deleting
	*/
	while (t->next != NULL && t->next->data != item)
		t = t->next;
	if (t->next == NULL) //if the above loop breaks for this reason, it means the item does not exist. So, return from the function
		return root;
	/*if the code reach here, it indicates the loop exited as the item was found
    now, the node we want to delete is in t->next.*/

	temp = t->next;			 //we will delete t->next. So, putting it in temp
	t->next = t->next->next; //change the t->next to the the next of the node we will be deleting
	free(temp);
	return root;
}

void display(node *t)
{
	printf("\nPrinting your link list.......");

	while (t != NULL)
	{
		printf("%d ", t->data);
		t = t->next;
	}
}
int main()
{
	node *root = NULL; //very important line. Otherwise all function will fail
	node *t;
	int ch, ele, v, del;
	while (1)
	{
		printf("\nMenu: 1. insert at front, 2. insert at end, 3. Delete, 4. Add Number, 5. Delete First, 6. Copy list, 7. Question 4, 8. Check if sorted, 9. List 42 10. exit: ");
		scanf("%d", &ch);
		if (ch == 10)
		{
			printf("\nGOOD BYE>>>>\n");
			break;
		}
		if (ch == 1)
		{
			printf("\nEnter data(an integer): ");
			scanf("%d", &ele);
			root = insert_front(root, ele);

			display(root);
		}
		if (ch == 2)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d", &ele);
			root = insert_end(root, ele);
			display(root);
		}
		if (ch == 3)
		{
			printf("\nEnter info which u want to DELETE: ");
			scanf("%d", &del);
			root = DelList(root, del);
			display(root);
		}
		if (ch == 4)
		{
			printf("\nEnter how much you want to add to each element: ");
			scanf("%d", &v);
			addN(root, v);
			display(root);
		}
		if (ch == 5)
		{
			printf("\nRemoving first element.\n");
			root = deleteFirst(root);
			display(root);
		}
		if (ch == 6)
		{
			printf("\nCopying linked list.\n");
			node *temp = copy(root);
			display(temp);
		}
		if (ch == 7)
		{
			printf("\nQuestion 4 stuff.\n");
			root = question4(root);
			display(root);
		}
		if (ch == 8)
		{
			v = isSorted(root);
			if (v == 0)
				printf("\nList is not in order.\n");
			else
				printf("\nList is in order.\n");
			display(root);
		}
		if (ch == 9)
		{
			printf("\nQuestion 7 stuff.\n");
			list_42(root);
			display(root);
		}
	}
	return 0;
}
