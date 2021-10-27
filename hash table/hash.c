#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 20

char keywords[32][10] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "voltile", "do", "if", "static", "while"};

typedef struct node
{
 char *cur;
 struct node *next;
} * Node;

Node hashTable[MAX_SIZE];

int compare(char buffer[])
{
 for (int i = 0; i < 32; i++)
 {
		if (strcmp(buffer, keywords[i]) == 0)
		{
			return 1;
		}
 }
 return 0;
}

int hash(int size)
{
 return (size) % MAX_SIZE;
}

int search(char buffer[])
{
 int index = hash(strlen(buffer));
 if (hashTable[index] == NULL)
		return 0;
 Node cur = hashTable[index];
 while (cur != NULL)
 {
		if (strcmp(cur->cur, buffer) == 0)
			return 1;
		cur = cur->next;
 }
 return 0;
}

void insert(char buffer[])
{
 if (search(buffer) == 0)
 {
		int index = hash(strlen(buffer));
		Node n = (Node)malloc(sizeof(struct node));
		char *str = (char *)calloc(strlen(buffer) + 1, sizeof(char));
		strcpy(str, buffer);
		n->cur = str;
		n->next = NULL;
		if (hashTable[index] == NULL)
		{
			hashTable[index] = n;
			return;
		}
		Node cur = hashTable[index];
		while (cur->next != NULL)
		{
			cur = cur->next;
		}
		cur->next = n;
 }
 else
		return;
}

int main()
{
 for (int i = 0; i < MAX_SIZE; i++)
		hashTable[i] = NULL;
 FILE *finp = fopen("input.c", "r");
 if (finp == NULL)
 {
		printf("Cannot Find file, exiting ... ");
		return 0;
 }
 char buffer[100], c = 0;
 int i = 0;
 while (c != EOF)
 {
		if (isalpha(c) != 0)
		{
			while (isalpha(c) != 0)
			{
				c = fgetc(finp);
				if (isalpha(c) != 0)
					buffer[i++] = c;
			}
			buffer[i] = '\0';
			if (compare(buffer) == 1)
			{
				insert(buffer);
			}
			i = 0;
			buffer[0] = '\0';
		}
		else
		{
			c = fgetc(finp);
			if (isalpha(c) != 0)
			{
				buffer[i++] = c;
			}
		}
 }
 for (int i = 0; i < MAX_SIZE; i++)
 {
		if (hashTable[i] != NULL)
		{
			Node cur = hashTable[i];
			while (cur)
			{
				printf("%s\n", cur->cur);
				cur = cur->next;
			}
		}
 }
 return 0;
}