#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leak_detector_c.h"

#define MAXLEN 30

typedef struct itemNode
{
    char *name;
    int count;
    struct itemNode *left, *right;
} itemNode;
typedef struct treeNameNode
{
    char *treeName;
    struct treeNameNode *left, *right;
    itemNode *theTree;
} treeNameNode;

treeNameNode *createTreeNameNode(char *name)
{
    treeNameNode *nameNode = (treeNameNode *)malloc(sizeof(treeNameNode));
    nameNode->treeName = malloc(sizeof(char) * strlen(name));
    strcpy(nameNode->treeName, name);
    nameNode->left = NULL;
    nameNode->right = NULL;
    nameNode->theTree = NULL;
    return nameNode;
}

itemNode *createItemNode(char *name, int count)
{
    itemNode *node = (itemNode *)malloc(sizeof(itemNode));
    node->name = malloc(sizeof(char) * strlen(name));
    strcpy(node->name, name);
    node->count = count;
    node->left = NULL;
    node->right = NULL;
    return node;
}

treeNameNode *insertNameNode(treeNameNode *root, treeNameNode *newNode)
{
    if (root == NULL)
        return newNode;
    else
    {
        if (strcmp(root->treeName, newNode->treeName) < 0)
        {
            if (root->right != NULL)
                root->right = insertNameNode(root->right, newNode);
            else
                root->right = newNode;
        }
        else
        {
            if (root->left != NULL)
                root->left = insertNameNode(root->left, newNode);
            else
                root->left = newNode;
        }
    }
    return root;
}

itemNode *insertItemNode(itemNode *treeRoot, itemNode *newNode)
{
    if (treeRoot == NULL)
        return newNode;
    else
    {
        if (strcmp(treeRoot->name, newNode->name) < 0)
        {
            if (treeRoot->right != NULL)
                treeRoot->right = insertItemNode(treeRoot->right, newNode);
            else
                treeRoot->right = newNode;
        }
        else
        {
            if (treeRoot->left != NULL)
                treeRoot->left = insertItemNode(treeRoot->left, newNode);
            else
                treeRoot->left = newNode;
        }
    }
    return treeRoot;
}

treeNameNode *buildNameTree(FILE *inFile, int N)
{
    if (inFile == NULL)
        return NULL;

    treeNameNode *nameRoot = NULL;
    char name[MAXLEN];
    for (int i = 0; i < N; i++)
    {
        fscanf(inFile, "%s", name);
        treeNameNode *newNameNode = createTreeNameNode(name);
        nameRoot = insertNameNode(nameRoot, newNameNode);
    }
    return nameRoot;
}

treeNameNode *searchNameNode(treeNameNode *root, char treeName[50])
{
    if (root == NULL)
        return NULL;
    treeNameNode *nameNode;
    if (strcmp(root->treeName, treeName) == 0)
        return root;
    else if (strcmp(root->treeName, treeName) > 0)
        nameNode = searchNameNode(root->left, treeName);
    else
        nameNode = searchNameNode(root->right, treeName);
    return nameNode;
}

void populateTrees(FILE *inFile, treeNameNode *nameRoot, int I)
{
    if (inFile == NULL)
        return;
    else
    {
        int count;
        char treeName[MAXLEN];
        char itemName[MAXLEN];
        for (int i = 0; i < I; i++)
        {
            fscanf(inFile, "%s %s %d", treeName, itemName, &count);
            itemNode *newItemNode = createItemNode(itemName, count);
            treeNameNode *treeNode = searchNameNode(nameRoot, treeName);
            treeNode->theTree = insertItemNode(treeNode->theTree, newItemNode);
        }
    }
}

void displayInOrderNameTree(treeNameNode *root, FILE *ofp)
{
    if (root != NULL)
    {
        displayInOrderNameTree(root->left, ofp);
        printf("%s ", root->treeName);
        fprintf(ofp, "%s ", root->treeName);
        displayInOrderNameTree(root->right, ofp);
    }
}

void traverseSubTree(itemNode *root, FILE *ofp)
{
    if (root != NULL)
    {
        traverseSubTree(root->left, ofp);
        printf("%s ", root->name);
        fprintf(ofp, "%s ", root->name);
        traverseSubTree(root->right, ofp);
    }
}

void traverse_in_traverse(treeNameNode *root, FILE *ofp)
{
    if (root != NULL)
    {
        traverse_in_traverse(root->left, ofp);
        printf("\n===%s===\n", root->treeName);
        fprintf(ofp, "\n===%s===\n", root->treeName);
        traverseSubTree(root->theTree, ofp);
        traverse_in_traverse(root->right, ofp);
    }
}

void freeTree(itemNode *root)
{
    if (root != NULL)
    {
        free(root->name);
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void freeAll(treeNameNode *root)
{
    if (root != NULL)
    {
        free(root->treeName);
        freeAll(root->left);
        freeAll(root->right);
        freeTree(root->theTree);
        free(root);
    }
}

int searchTree(itemNode *root, char nodeName[])
{
    if (root == NULL)
        return 0;
    if (strcmp(root->name, nodeName) == 0)
        return root->count;
    else if (strcmp(root->name, nodeName) > 0)
        return searchTree(root->left, nodeName);
    else
        return searchTree(root->right, nodeName);
}

void search(treeNameNode *root, char treeName[], char nodeName[], FILE *ofp)
{
    treeNameNode *tree = searchNameNode(root, treeName);
    int found = searchTree(tree->theTree, nodeName);
    if (found == 0)
    {
        printf("\n%s not found in %s", nodeName, treeName);
        fprintf(ofp, "\n%s not found in %s", nodeName, treeName);
    }
    else
    {
        printf("\n%d %s found in %s", found, nodeName, treeName);
        fprintf(ofp, "\n%d %s found in %s", found, nodeName, treeName);
    }
}

void queries(treeNameNode *root, FILE *inFile, FILE *ofp, int Q)
{
    char querie[MAXLEN];
    char treeName[MAXLEN];
    char nodeName[MAXLEN];
    int count;

    fscanf(inFile, "%s", querie);

    if (strcmp(querie, "search") == 0 || strcmp(querie, "item_before") == 0 || strcmp(querie, "delete") == 0)
        fscanf(inFile, "%s %s", treeName, nodeName);
    else if (strcmp(querie, "height_balance") == 0 || strcmp(querie, "count") == 0 || strcmp(querie, "delete_name") == 0)
        fscanf(inFile, "%s", treeName);
    else if (strcmp(querie, "reduce") == 0)
        fscanf(inFile, "%s %s %d", treeName, nodeName, &count);

    search(root, treeName, nodeName, ofp);
}

int main(void)
{
    atexit(report_mem_leak);
    int N, I, Q;
    FILE *inFile = fopen("in.txt", "r");
    FILE *ofp;
    ofp = fopen("out.txt", "w");
    fscanf(inFile, "%d %d %d", &N, &I, &Q);
    treeNameNode *nameRoot = buildNameTree(inFile, N);
    populateTrees(inFile, nameRoot, I);
    displayInOrderNameTree(nameRoot, ofp);
    traverse_in_traverse(nameRoot, ofp);

    queries(nameRoot, inFile, ofp, Q);

    freeAll(nameRoot);
    fclose(inFile);
    fclose(ofp);
}