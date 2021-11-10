#include "rdParser.h"
int row, col_pos;
char data_type_buffer[100], c = 0;
FILE *finp;
Token tkn = NULL;
int prev_flag = false;

void Program();
void Declarations();
void DataType();
void Identifier();
void IdentifierPrime();
void AssignStat();
void AssignStatPrime();
void success();
void failure(char *msg);

void get()
{
	tkn = prev_flag == true ? tkn : NULL;
	while (tkn == NULL)
	{
		tkn = getNextToken(finp, &row, &col_pos, data_type_buffer, &c);
	}
	if (strcmp(tkn->lexeme, "EOF") == 0)
	{
		failure("End of file encountered!");
	}
	printf("%s\n", tkn->lexeme);
	prev_flag = false;
}

int main(int argn, char *args[])
{
	row = 1;
	if (argn < 2)
	{
		printf("No file specified, exiting ...\n");
		return 0;
	}
	prep(); // from remove_preprocessors.h
	enum TYPE type;
	for (int i = 0; i < MAX_SIZE; i++)
		hashTable[i] = NULL;
	finp = fopen("prep_output.c", "r");
	if (finp == NULL)
	{
		printf("Cannot Find file, exiting ... ");
		return 0;
	}

	col_pos = 1;
	Program();
	printf("\nSymbol Table : \n\n");
	display_st();
	return 0;
}

void Program()
{
	get();
	if (strcmp(tkn->lexeme, "int") == 0)
	{
		get();
		if (strcmp(tkn->lexeme, "main") == 0)
		{
			get();
			if (strcmp(tkn->lexeme, "(") == 0)
			{
				get();
				if (strcmp(tkn->lexeme, ")") == 0)
				{
					get();
					if (strcmp(tkn->lexeme, "{") == 0)
					{
						Declarations();
						AssignStat();
						get();
						if (strcmp(tkn->lexeme, "}") == 0)
						{
							success();
						}
						else
						{
							failure("No closing curly bracket found!");
						}
					}
					else
					{
						failure("No starting curly bracket found!");
					}
				}
				else
				{
					failure("No function closing parentheses found!");
				}
			}
			else
			{
				failure("No function starting parentheses found!");
			}
		}
		else
		{
			failure("No main function found!");
		}
	}
	else
	{
		failure("No return type for function found!");
	}
}

void Declarations()
{
	get();
	if (isDatatype(tkn->lexeme))
	{
		Identifier();
		get();
		if (strcmp(tkn->lexeme, ";") == 0)
		{
			Declarations();
		}
		else
		{
			failure("Semi Colon Expected!");
		}
	}
	else
	{
		prev_flag = true;
	}
}

void DataType()
{
	get();
	if (isDatatype(tkn->lexeme) == 0)
	{
		failure("Data Type Expected!");
	}
}

void Identifier()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		IdentifierPrime();
	}
	else
	{
		failure("Invalid Identifier!");
	}
}

void IdentifierPrime()
{
	get();
	if (strcmp(tkn->lexeme, ",") == 0)
	{
		Identifier();
	}
	else
	{
		prev_flag = true;
	}
}

void AssignStat()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		get();
		if (strcmp(tkn->lexeme, "=") == 0)
		{
			AssignStatPrime();
		}
		else
		{
			failure("= sign not found!");
		}
	}
	else
	{
		failure("Invalid Identifier!");
	}
}

void AssignStatPrime()
{
	get();
	if (tkn->type == IDENTIFIER && search_symbol(tkn->lexeme) != -1)
	{
		get();
		if (strcmp(tkn->lexeme, ";") != 0)
		{
			failure("Semi-Colon Expected!");
		}
	}
	else if (tkn->type == NUMERIC_CONSTANT)
	{
		get();
		if (strcmp(tkn->lexeme, ";") != 0)
		{
			failure("Semi-Colon Expected!");
		}
	}
	else
	{
		failure("Invalid Assignment!");
	}
}

void failure(char *msg)
{
	printf("***NOT ACCEPTED***\n%s Row : %d, Col : %d\n", msg, tkn->row, tkn->col);
	exit(0);
}

void success()
{
	printf("###ACCEPTED###\n");
}