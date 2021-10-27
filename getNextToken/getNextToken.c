#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#define MAX_SIZE 20

int space()
{
 FILE *fa, *fb;
 int ca, cb;
 fa = fopen("getNextToken.c", "r");
 if (fa == NULL)
 {
		printf("Cannot open file \n");
		exit(0);
 }
 fb = fopen("space_output.c", "w");
 ca = getc(fa);
 while (ca != EOF)
 {
		if (ca == ' ' || ca == '\t')
		{
			putc(' ', fb);
			while (ca == ' ' || ca == '\t')
				ca = getc(fa);
		}
		if (ca == '/')
		{
			cb = getc(fa);
			if (cb == '/')
			{
				while (ca != '\n')
					ca = getc(fa);
			}
			else if (cb == '*')
			{
				do
				{
					while (ca != '*')
						ca = getc(fa);
					ca = getc(fa);
				} while (ca != '/');
			}
			else
			{
				putc(ca, fb);
				putc(cb, fb);
			}
		}
		else
			putc(ca, fb);
		ca = getc(fa);
 }
 fclose(fa);
 fclose(fb);
 return 0;
}

int process()
{
 FILE *finp = fopen("space_output.c", "r");
 char c = 0;
 char buffer[100];
 buffer[0] = '\0';
 int i = 0;
 char *includeStr = "include", *defineStr = "define", *mainStr = "main";
 int mainFlag = 0, row = 1;
 while (c != EOF)
 {
		c = fgetc(finp);
		if (c == '#' && mainFlag == 0)
		{
			c = 'a';
			while (isalpha(c) != 0)
			{
				c = fgetc(finp);
				buffer[i++] = c;
			}
			buffer[i] = '\0';
			if (strstr(buffer, includeStr) != NULL || strstr(buffer, defineStr) != NULL)
			{
				row++;
				while (c != '\n')
				{
					c = fgetc(finp);
				}
			}
			else
			{
				for (int j = 0; j < i; j++)
					;
				while (c != '\n')
				{
					c = fgetc(finp);
				}
			}
			i = 0;
			buffer[0] = '\0';
		}
		else
		{
			if (mainFlag == 0)
			{
				buffer[i++] = c;
				buffer[i] = '\0';
				if (strstr(buffer, mainStr) != NULL)
				{
					mainFlag = 1;
				}
			}
			if (c == ' ' || c == '\n')
			{
				buffer[0] = '\0';
				i = 0;
			}
		}
 }
 fclose(finp);
 return row;
}

char keywords[32][10] = {"auto", "double", "int", "struct", "break", "else", "long", "switch", "case", "enum", "register", "typedef", "char", "extern", "return", "union", "const", "float", "short", "unsigned", "continue", "for", "signed", "void", "default", "goto", "sizeof", "voltile", "do", "if", "static", "while"}; // list of keywords sd

char operators[5] = {'+', '-', '/', '%', '*'};
char brackets[6] = {'(', ')', '[', ']', '{', '}'};
char special_symbols[12] = {'*', ';', ':', '.', ',', '^', '&', '!', '>', '<', '~', '`'};

typedef struct node
{
 char *cur;
 int row, col;
 struct node *next;
} * Node; // element for hash table

Node hashTable[MAX_SIZE]; // hash table

int compare(char buffer[]) // function to check for keyword
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

int isoperator(char c)
{
 for (int i = 0; i < 5; i++)
 {
		if (operators[i] == c)
			return 1;
 }
 return 0;
}

int isspecial(char c)
{
 for (int i = 0; i < 12; i++)
 {
		if (special_symbols[i] == c)
			return 1;
 }
 return 0;
}

int isbracket(char c)
{
 for (int i = 0; i < 6; i++)
 {
		if (brackets[i] == c)
			return 1;
 }
 return 0;
}

int hash(int size) // hashing function
{
 return (size) % MAX_SIZE;
}

int search(char buffer[]) // to search in hash table
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

void insert(char buffer[], int row, int col, int type)
{ // insert in hash table
 if (type == 1)
 {
		if (search(buffer) == 0)
		{
			printf("< %s | %d | %d >\n", buffer, row, col);
			int index = hash(strlen(buffer));
			Node n = (Node)malloc(sizeof(struct node));
			char *str = (char *)calloc(strlen(buffer) + 1, sizeof(char));
			strcpy(str, buffer);
			n->cur = str;
			n->next = NULL;
			n->row = row;
			n->col = col;
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
 }
 else
 {
		printf("< %s | %d | %d >\n", buffer, row, col);
		int index = hash(strlen(buffer));
		Node n = (Node)malloc(sizeof(struct node));
		char *str = (char *)calloc(strlen(buffer) + 1, sizeof(char));
		strcpy(str, buffer);
		n->cur = str;
		n->next = NULL;
		n->row = row;
		n->col = col;
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
}

int main()
{
 space();													// from spaces.h
 int row = process(); // from preprocess.h
 for (int i = 0; i < MAX_SIZE; i++)
		hashTable[i] = NULL;
 FILE *finp = fopen("space_output.c", "r");
 if (finp == NULL)
 {
		printf("Cannot Find file, exiting ... ");
		return 0;
 }
 char buffer[100], c = 0;
 int i = 0, col_global = 1, col, temp_row = --row;
 while (temp_row > 0)
 {
		c = fgetc(finp);
		if (c == '\n')
			temp_row--;
 }
 while (c != EOF)
 {
		if (isalpha(c) != 0 || c == '_')
		{
			buffer[i++] = c;
			col = col_global;
			while (isalpha(c) != 0 || c == '_' || isdigit(c) != 0)
			{
				c = fgetc(finp);
				col_global++;
				if (isalpha(c) != 0 || c == '_' || isdigit(c) != 0)
					buffer[i++] = c;
			}
			buffer[i] = '\0';
			if (compare(buffer) == 1)
			{
				insert(buffer, row, col - 1, 1); // keyword
			}
			else
			{
				insert("id", row, col - 1, 0); // identifier
			}
			i = 0;
			if (c == '\n')
				row++, col_global = 1;
			buffer[0] = '\0';
			// c = fgetc(finp);
			// col_global++;
		}
		else if (isdigit(c) != 0)
		{
			buffer[i++] = c;
			col = col_global;
			while (isdigit(c) != 0 || c == '.')
			{
				c = fgetc(finp);
				col_global++;
				if (isdigit(c) != 0 || c == '.')
					buffer[i++] = c;
			}
			buffer[i] = '\0';
			insert("num", row, col - 1, 0); // numerical constant
			i = 0;
			if (c == '\n')
				row++, col_global = 1;
			buffer[0] = '\0';
			// c = fgetc(finp);
			// col_global++;
		}
		else if (c == '\"')
		{
			col = col_global;
			buffer[i++] = c;
			c = 0;
			while (c != '\"')
			{
				c = fgetc(finp);
				col_global++;
				buffer[i++] = c;
			}
			buffer[i] = '\0';
			insert(buffer, row, col - 1, 0); // string literals
			buffer[0] = '\0';
			i = 0;
			c = fgetc(finp);
			col_global++;
		}
		else if (c == '\'')
		{
			col = col_global;
			buffer[i++] = c;
			c = 0;
			c = fgetc(finp);
			col_global++;
			buffer[i++] = c;
			if (c == '\\')
			{
				c = fgetc(finp);
				col_global++;
				buffer[i++] = c;
			}
			c = fgetc(finp);
			col_global++;
			buffer[i++] = c;
			buffer[i] = '\0';
			insert(buffer, row, col - 1, 0); // character constants
			buffer[0] = '\0';
			i = 0;
			c = fgetc(finp);
			col_global++;
		}
		else
		{
			col = col_global;
			if (c == '=')
			{ // relational and logical operators
				c = fgetc(finp);
				col_global++;
				if (c == '=')
				{
					insert("==", row, col - 1, 1);
				}
				else
				{
					insert("=", row, col - 1, 1);
					fseek(finp, -1, SEEK_CUR);
					col_global--;
				}
			}
			else if (c == '>' || c == '<' || c == '!')
			{
				char temp = c;
				c = fgetc(finp);
				col_global++;
				if (c == '=')
				{
					char temp_str[3] = {temp, '=', '\0'};
					insert(temp_str, row, col - 1, 1);
				}
				else
				{
					char temp_str[2] = {temp, '\0'};
					insert(temp_str, row, col - 1, 1);
					fseek(finp, -1, SEEK_CUR);
					col_global--;
				}
			}
			else if (isbracket(c) == 1 || isspecial(c) == 1)
			{ // parentheses and special symbols
				char temp_string[2] = {c, '\0'};
				insert(temp_string, row, col - 1, 1);
			}
			else if (isoperator(c) == 1)
			{ // operators
				char temp = c;
				c = fgetc(finp);
				col_global++;
				if (c == '=' || (temp == '+' && c == '+') || (temp == '-' && c == '-'))
				{
					char temp_string[3] = {temp, c, '\0'};
					insert(temp_string, row, col - 1, 1);
				}
				else
				{
					char temp_String[2] = {temp, '\0'};
					insert(temp_String, row, col - 1, 1);
					fseek(finp, -1, SEEK_CUR);
					col_global--;
				}
			}
			else if (c == '\n')
				row++, col_global = 1;
			c = fgetc(finp);
			col_global++;
		}
 }
 return 0;
}