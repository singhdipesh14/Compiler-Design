#ifndef __OPERATORS_H__
#define __OPERATORS_H__
void Relop()
{
	get();
	if (strcmp(tkn->lexeme, "==") == 0 || strcmp(tkn->lexeme, "!=") == 0 || strcmp(tkn->lexeme, ">=") == 0 || strcmp(tkn->lexeme, "<=") == 0 || strcmp(tkn->lexeme, ">") == 0 || strcmp(tkn->lexeme, "<") == 0)
	{
		return;
	}
	else
	{
		failure("fail");
	}
}

void Addop()
{
	get();
	if (strcmp(tkn->lexeme, "+") == 0 || strcmp(tkn->lexeme, "-") == 0)
	{
		return;
	}
	else
	{
		failure("fail");
	}
}

void Mulop()
{
	get();
	if (strcmp(tkn->lexeme, "*") == 0 || strcmp(tkn->lexeme, "/") == 0 || strcmp(tkn->lexeme, "%%") == 0)
	{
		return;
	}
	else
	{
		failure("fail");
	}
}
#endif