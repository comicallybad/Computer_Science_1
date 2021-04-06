// Arup Guha
// 4/11/2016
// Written in COP 3502H - example of a hash table using quadratic probing.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int f(char* str, int n);
void insert(char** table, char* str);
int search(char** table, char* str);

#define SIZE 489761
#define MAXWORD 20

int sumSearch;

int main() {

    // Set up our table.
    char** table = malloc(sizeof(char*)*SIZE);
    int i = 0;
    for (i=0; i<SIZE; i++)
        table[i] = NULL;

    // Get ready to read from the dictionary.
    int numWords;
    FILE* ifp = fopen("dictionary.txt", "r");
    fscanf(ifp, "%d", &numWords);
    char** dictionary = malloc(sizeof(char*)*numWords);

    // Read all words and insert.
    for (i=0; i<numWords; i++) {
        dictionary[i] = malloc(sizeof(char)*(MAXWORD+1));
        fscanf(ifp, "%s", dictionary[i]);
        insert(table, dictionary[i]);
    }

    // Search for everything.
    sumSearch = 0;
    for (i=0; i<numWords; i++) {
        if (!search(table, dictionary[i]))
            printf("Error, %s not found.\n", dictionary[i]);
    }

    // Print average search time.
    printf("Average search time = %lf.\n", (double)sumSearch/numWords);

    //  Free stuff.
    free(table);
    for (i=0; i<numWords; i++)
        free(dictionary[i]);
    free(dictionary);

    fclose(ifp);
    return 0;
}

// Random hash function I made up.
int f(char* str, int n) {
    int res = 0, i;
    for (i=0; i<strlen(str); i++)
        res = (337*res + str[i])%n;
    return res;
}

// Inserts the string pointed to by str into table.
void insert(char** table, char* str) {

    int loc = f(str, SIZE);
    int skip = 1;

    // Find a empty location, using quadratic probing.
    while (table[loc] != NULL) {
        loc = (loc+skip)%SIZE;
        skip = skip + 2;
    }

    // Store it!
    table[loc] = str;
}

// Returns 1 iff table stores the string pointed to by str.
int search(char** table, char* str) {

    // Get set up.
    sumSearch++;
    int loc = f(str, SIZE);
    int skip = 1;

    // Look for str!
    while (table[loc] != NULL) {

        // Found it!
        if (strcmp(table[loc], str) == 0)
            return 1;

        // Update for our next location.
        loc = (loc+skip)%SIZE;
        skip = skip + 2;
        sumSearch++;
    }

    // Never found it.
    return 0;
}
