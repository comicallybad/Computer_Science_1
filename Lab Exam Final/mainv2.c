#include <stdio.h>
#include <stdlib.h>

struct tree_node
{
    int income, people;
    struct tree_node *left;
    struct tree_node *right;
};

struct tree_node *create_node(int income, int people);
void inorder(struct tree_node *current_ptr);
struct tree_node *insert(struct tree_node *root, struct tree_node *element);
void oddNode(struct tree_node *root);
int totalHighest(struct tree_node *root);

int main()
{
    FILE *ifp = fopen("in.txt", "r");
    struct tree_node *my_root = NULL, *temp_node;
    int n, i, income, people;

    fscanf(ifp, "%d", &n);

    for (i = 0; i < n; i++)
    {
        fscanf(ifp, "%d %d", &income, &people);
        temp_node = create_node(income, people);
        my_root = insert(my_root, temp_node);
    }

    printf("Tree constructed from the file");
    printf("\nIn-order: ");
    inorder(my_root);
    printf("\nIncomes with Odd number of people count: ");
    oddNode(my_root);
    printf("\nTotal number of people with the highest income: %d", totalHighest(my_root));

    fclose(ifp);
    return 0;
}

struct tree_node *create_node(int income, int people)
{
    struct tree_node *temp;
    temp = (struct tree_node *)malloc(sizeof(struct tree_node));
    temp->income = income;
    temp->people = people;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

struct tree_node *insert(struct tree_node *root, struct tree_node *element)
{
    if (root == NULL)
    {
        return element;
    }
    else
    {
        if (element->income > root->income)
        {
            if (root->right != NULL)
                root->right = insert(root->right, element);
            else
                root->right = element;
        }
        else
        {
            if (root->left != NULL)
                root->left = insert(root->left, element);
            else
                root->left = element;
        }
        return root;
    }
}

void inorder(struct tree_node *current_ptr)
{
    if (current_ptr != NULL)
    {
        inorder(current_ptr->left);
        printf("(%d, %d), ", current_ptr->income, current_ptr->people);
        inorder(current_ptr->right);
    }
}

void oddNode(struct tree_node *root)
{
    if (root != NULL)
    {
        oddNode(root->left);

        if (root->people % 2 != 0)
            printf("%d ", root->income);

        oddNode(root->right);
    }
}

int totalHighest(struct tree_node *root)
{
    if (root == NULL)
        return 0;
    if (root->right != NULL)
    {
        totalHighest(root->right);
    }
    else
        return root->people;
}