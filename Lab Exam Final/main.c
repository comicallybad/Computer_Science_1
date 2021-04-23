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
int singleChild(struct tree_node *root);
int findTotal(struct tree_node *current_ptr);
int isBST(struct tree_node *node);

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
    printf("\nTotal single children in the tree: %d", singleChild(my_root));
    printf("\nTotal income in the area: %d", findTotal(my_root));
    printf("\nIs this a Binary Search Tree? Answer: %s", (isBST(my_root) == 0) ? "no" : "yes");

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

int singleChild(struct tree_node *root)
{
    if (root == NULL)
        return 0;

    int count = 0;
    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        count++;

    count += (singleChild(root->left) + singleChild(root->right));
    return count;
}

int findTotal(struct tree_node *current_ptr)
{

    if (current_ptr != NULL)
        return (current_ptr->income * current_ptr->people) + findTotal(current_ptr->left) +
               findTotal(current_ptr->right);
    else
        return 0;
}

int isBST(struct tree_node *node)
{
    if (node == NULL)
        return 1;
    if (node->left != NULL && node->left->income > node->income)
        return 0;
    if (node->right != NULL && node->right->income < node->income)
        return 0;
    if (!isBST(node->left) || !isBST(node->right))
        return 0;
    return 1;
}