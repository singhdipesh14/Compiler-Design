#ifndef __ASSIGN_H__
#define __ASSIGN_H__
void AssignStat()
{
	get();
	if (search_symbol(tkn->lexeme) != -1)
	{
		get();
		if (strcmp(tkn->lexeme, "=") == 0)
		{
			Expn();
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

#endif