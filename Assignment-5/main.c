#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define A2I(X) ((X) - 'a')
#define I2A(X) ((X) + 'a')

struct trie
{
	int f, sum, max;
	struct trie **next;
};
typedef struct trie trie;

void error(char *s)
{
	fprintf(stderr, s);
	exit(1);
}

trie *trie_new()
{
	trie *t = (trie *)malloc(sizeof(trie));
	if (!t)
		error("malloc failed.");
	memset(t, 0, sizeof(trie));
	return t;
}

void trie_free(trie *head)
{
	if (head->next)
	{
		for (int i = 0; i < 26; ++i)
			if (head->next[i])
				trie_free(head->next[i]);
		free(head->next);
	}
	free(head);
}

void trie_ins(trie *head, char *word, int n)
{
	if (A2I(*word) < 0 || A2I(*word) >= 26)
		error("char exceeding alphabet");

	if (!head->next)
	{
		head->next = (trie **)malloc(26 * sizeof(trie *));
		if (!head->next)
		{
			error("malloc failed.");
			return;
		}
		memset(head->next, 0, 26 * sizeof(trie *));
	}

	trie *next = head->next[A2I(*word)];
	if (!next)
		head->next[A2I(*word)] = next = trie_new();

	next->sum += n;
	if (n > next->max)
		next->max = n;

	if (word[1])
		trie_ins(next, word + 1, n);
	else
		next->f++;
}

int trie_query(trie *node, char *word)
{
	while (*word)
	{
		if (node->next && node->next[A2I(*word)])
			node = node->next[A2I(*word)];
		else
			return 0;
		++word;
	}
	if (!node->next)
		return 0;

	for (int i = 0; i < 26; i++)
		if (node->next[i] && node->next[i]->max >= node->max)
			printf("%c", I2A(i));

	return 1;
}

int main()
{
	FILE *f = fopen("in.txt", "r");

	int n = -1;
	int count, temp;
	char word[128];

	trie *head = trie_new();

	fscanf(f, "%d", &count);

	for (int i = 0; i < count; i++)
	{
		fscanf(f, "%d", &temp);
		if (temp == 1)
			fscanf(f, "%s %d ", word, &n);
		else
			fscanf(f, "%s", word);

		if (n != -1)
			trie_ins(head, word, n);
		else
		{
			int c = trie_query(head, word);
			if (!c)
				printf("unknown word");
			printf("\n");
		}
		n = -1;
	}

	trie_free(head);

	return 0;
}