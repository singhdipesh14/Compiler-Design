#include "rdParser.h" 

int row, col_global;
char data_type_buffer[100], c = 0;
FILE *finp;
Token tkn = NULL;
int prev_flag = false;

enum NON_TERMINALS { // types for non terminals.
	PROGRAM,
	DECLARATIONS,
	ASSIGNSTAT,
	ASSIGNSTATPRIME,
	IDENTIFIERLIST,
	IDENTIFIERLISTPRIME
};

char first[][4][20] = {{"int"}, {"int", "char", "double", "float"}, {"id"}, {"id", "num"}, {"id"}, {","}};
char follow[][2][20] = {{"$"}, {"id"}, {"id", "num"}, {"return"}, {";"}, {";"}};

int firstSz[] = {1, 4, 1, 2, 1, 1};
int followSz[] = {1, 1, 2, 1, 1, 1};

int search_first(enum NON_TERMINALS val, char* buffer, enum TYPE type){
	if(type == IDENTIFIER){
		return search_symbol(buffer) != -1 && search_first(val, "id", KEYWORD);
	}
	if(type == NUMERIC_CONSTANT){
		return search_first(val, "num", KEYWORD);
	}
	for(int i = 0; i<firstSz[val]; i++){
		if(strcmp(buffer, first[val][i]) == 0){
			return 1;
		}
	}
	return 0;
}

int search_follow(enum NON_TERMINALS val, char* buffer, enum TYPE type){
	if(type == IDENTIFIER){
		return search_follow(val, "id", KEYWORD) && search_symbol(buffer) != -1;
	}
	if(type == NUMERIC_CONSTANT){
		return search_follow(val, "num", KEYWORD);
	}
	for(int i = 0; i<followSz[val]; i++){
		if(strcmp(buffer, follow[val][i]) == 0){
			return 1;
		}
	}
	return 0;
}

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
		tkn = getNextToken(finp, &row, &col_global, data_type_buffer, &c);
	}
	if (strcmp(tkn->lexeme, "EOF") == 0)
	{
		failure("End of file encountered!");
	}
	prev_flag = false;
}

int main(int argn, char *args[])
{
	if (argn < 2)
	{
		printf("No file specified, exiting ...\n");
		return 0;
	}
	removeExcess(args[1]);
	row = removePreprocess();
	enum TYPE type;
	for (int i = 0; i < MAX_SIZE; i++)
		hashTable[i] = NULL;
	finp = fopen("space_output.c", "r");
	if (finp == NULL)
	{
		printf("Cannot Find file, exiting ... ");
		return 0;
	}
	int temp_row = --row;
	while (temp_row > 0)
	{
		c = fgetc(finp);
		if (c == '\n')
			temp_row--;
	}
	row;
	col_global = 1;
	get();
	prev_flag = true;
	if(search_first(PROGRAM, tkn->lexeme, tkn->type) == 1){
		Program();
	}
	else{
		failure("No Return type found!");
	}
	printf("\nSymbol Table : \n\n");
	display_st();
	printf("\n");
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
						get();
						if(search_first(DECLARATIONS, tkn->lexeme, tkn->type) == 1){
							prev_flag = true;
							Declarations();							
						}
						else{
							failure("Data Type expected!");
						}
						get();
						if(search_first(ASSIGNSTAT, tkn->lexeme, tkn->type) == 1){
							prev_flag = true;
							AssignStat();
						}
						else{
							failure("Invalid Identifier!");
						}
						get();
						if (strcmp(tkn->lexeme, "return") == 0)
						{
							get();
							if(tkn->type == NUMERIC_CONSTANT){
								get();
								if(strcmp(tkn->lexeme, ";") == 0){
									get();
									if(strcmp(tkn->lexeme, "}") == 0){
									success();
									}
									else{
										failure("No closing curly braces found!");
									}
								}
								else{
									failure("No Semi-Colon found!");
								}
							}
							else{
								failure("Numeric Value Expected!");
							}
						}
						else
						{
							failure("No return statement found!");
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
			failure("No main found!");
		}
	}
	else
	{
		failure("No return type found!");
	}
}

void Declarations()
{
	get();
	if (isdatatype(tkn->lexeme))
	{
		get();
		if(search_first(IDENTIFIERLIST, tkn->lexeme, tkn->type) == 1){
			prev_flag = true;
			Identifier();
		}
		else{
			failure("Identifier expected!");
		}
		get();
		if (strcmp(tkn->lexeme, ";") == 0)
		{
			get();
			prev_flag = true;
			if(search_first(DECLARATIONS, tkn->lexeme, tkn->type) == 1){
				Declarations();
			}
			else if(search_follow(DECLARATIONS, tkn->lexeme, tkn->type) == 0){
				failure("Invalid Identifier");
			}
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
	if (isdatatype(tkn->lexeme) == 0)
	{
		failure("Data Type Expected!");
	}
}

void Identifier()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		get();
		prev_flag = true;
		if(search_first(IDENTIFIERLISTPRIME, tkn->lexeme, tkn->type) == 1){
			IdentifierPrime();
		}
		else if(search_follow(IDENTIFIERLISTPRIME, tkn->lexeme, tkn->type) == 0){
			failure(", or ; expected");
		}
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
		get();
		if(search_first(IDENTIFIERLIST, tkn->lexeme, tkn->type) == 1){
			prev_flag = true;
			Identifier();
		}
		else{
			failure("Invalid Identifier!");
		}
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
			get();
			if(search_first(ASSIGNSTATPRIME, tkn->lexeme, tkn->type) == 1){
				prev_flag = true;
				AssignStatPrime();
			}
			else{
				failure("Invalid Identifier or numeric value expected!");
			}
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
	printf("\n***NOT ACCEPTED***\n%s Row : %d, Col : %d\n", msg, tkn->row, tkn->col);
	exit(0);
}

void success()
{
	printf("\n###ACCEPTED###\n");
}