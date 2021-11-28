#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__
void Expn()
{
	Simple_Exp();
	EPrime();
}

void EPrime()
{
	Relop();
	Simple_Exp();
	// check for epsillon
}

void Simple_Exp()
{
	Term();
	SePrime();
}

void SePrime()
{
	Addop();
	Term();
	SePrime();
	// check for epsilon via first
}

void Term()
{
	Factor();
	TPrime();
}

void TPrime()
{
	Mulop();
	Factor();
	TPrime();
	// check for epsilon via first
}

void Factor()
{
	get();
	if (search_symbol(tkn->lexeme) == -1 && tkn->type != NUMERIC_CONSTANT)
	{
		failure("fail");
	}
}

#endif