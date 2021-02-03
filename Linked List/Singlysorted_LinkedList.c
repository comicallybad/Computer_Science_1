//this program implements a sorted singly linked list
#include<stdio.h>
#include <stdlib.h>


 typedef struct node{
	int info;
	struct node *next;
}node;


node* SortInsert(node *root, int item)
{
    node *temp;
    node *t;
    temp= (node *) malloc(sizeof(node));
    temp->info=item;
    temp->next=NULL;
    if (root==NULL || root->info >=item)
    {
      temp->next = root;
      root = temp;
    }
    else
    {
      t = root;
      while (t->next != NULL && t->next->info <item)
        t = t->next;
    
      temp->next = t->next; //if the loop breaks for t->next == NULL, then temp next is becoming NULL too. So, no problem
      t->next = temp;
    }

    return root;
}

void display(node* t)
{
  printf("\nPrinting your link list.......");

	while(t!=NULL)
	{
		printf("%d ",t->info);
		t=t->next;
	}

}

int main()
{
	node* root=NULL;
	node *t;
	int ch,ele;
	printf("\nThis program creates a sorted link list \n");
	while(1){
		printf("\n\nIf you want to link a data press 1, for exit press 2 : ");
	  scanf("%d",&ch);
		
    if(ch==2)
		{
			printf("\n<<<<<<<GOOD BYE>>>>>>\n\n\n");
			break;
		}
		if(ch==1)
		{
			printf("\nEnter information(an integer): ");
			scanf("%d",&ele);
			root = SortInsert(root, ele);
			display(root);
		}
	}
  return 0;
}

