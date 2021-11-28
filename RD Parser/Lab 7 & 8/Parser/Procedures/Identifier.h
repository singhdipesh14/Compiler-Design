#ifndef __IDENTIFIER_H__
#define __IDENTIFIER_H__
void Identifier()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		get();
		prev_flag = true;
		if (search_first(IDENTIFIERLISTPRIME, tkn->lexeme, tkn->type) == 1)
		{
			IdentifierPrime();
		}
		else if (search_follow(IDENTIFIERLISTPRIME, tkn->lexeme, tkn->type) == 0)
		{ // change
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
		if (search_first(IDENTIFIERLIST, tkn->lexeme, tkn->type) == 1)
		{
			prev_flag = true;
			Identifier();
		}
		else if (strcmp(tkn->lexeme, "[") == 0)
		{
			get();
			if (tkn->type == NUMERIC_CONSTANT)
			{
				get();
				if (strcmp(tkn->lexeme, "]") == 0)
				{
					IdentifierPrimePrime();
				}
				else
				{
					failure("fail");
				}
			}
			else
			{
				failure("fail");
			}
		}
		else
		{
			failure("Invalid Identifier!");
		}
	}
	else
	{
		prev_flag = true;
	}
}

void IdentifierPrimePrime()
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
#endif