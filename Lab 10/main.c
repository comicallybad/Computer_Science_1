#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node
{
    int data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

int c = 0;
tree_node *create_node(int val);
void inorder(tree_node *current_ptr);
tree_node *insert(tree_node *root, tree_node *element);

int find(tree_node *current_ptr, int val)
{
    if (current_ptr == NULL)
        return 0;
    if (current_ptr->data == val)
        return 1;
    else
    {
        if (current_ptr->data > val)
            return find(current_ptr->left, val);
        else
            return find(current_ptr->right, val);
    }
}

int find2(tree_node *current_ptr, int val)
{
    if (current_ptr == NULL)
        return 0;
    if (current_ptr->data == val)
        return 1;

    return find(current_ptr, val) || find(current_ptr, val);
}

int add(tree_node *current_ptr)
{
    if (current_ptr == NULL)
        return 0;
    else
        return current_ptr->data + add(current_ptr->left) + add(current_ptr->right);
}

int num_leaves(tree_node *current_ptr)
{
    if (current_ptr == NULL)
        return 0;
    if (current_ptr->left == NULL && current_ptr->right == NULL)
        return 1;
    else
        return num_leaves(current_ptr->left) + num_leaves(current_ptr->right);
}

int main(void)
{
    tree_node *my_root = NULL, *temp_node;

    int element;

    printf("Enter a number to insert in the tree: ");
    scanf("%d", &element);

    while (element != 0)
    {
        temp_node = create_node(element); // Create the node.
        // Insert the value.
        my_root = insert(my_root, temp_node);

        printf("In-order traversal: ");
        inorder(my_root);

        printf("\nEnter a number to insert in the tree: ");
        scanf("%d", &element);
    }
    int toFind;
    printf("Input value to find: ");
    scanf("%d", &toFind);

    printf("Is the value inside of our tree? %d\n", find(my_root, toFind));
    printf("Total of tree nodes: %d", add(my_root));

    return 0;
}

//take the root of the tree and insert the node element in the tree. Returns the root of the tree

tree_node *insert(tree_node *root, tree_node *element)
{
    if (root == NULL)
        return element;
    else
    {
        if (element->data > root->data)
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

void inorder(tree_node *current_ptr)
{
    if (current_ptr != NULL)
    {
        inorder(current_ptr->left);
        printf("%d ", current_ptr->data);
        inorder(current_ptr->right);
    }
}

//take an integer and return a new node filling up with the integer with left and right pointers as NULL
tree_node *create_node(int val)
{

    // Allocate space for the node, set the fields.
    tree_node *temp;
    temp = (tree_node *)malloc(sizeof(tree_node));
    temp->data = val;
    temp->left = NULL;
    temp->right = NULL;

    return temp; // Return a pointer to the created node.
}
