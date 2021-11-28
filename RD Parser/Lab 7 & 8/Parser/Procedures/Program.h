#ifndef __PROGRAM_H__
#define __PROGRAM_H__

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
						if (search_first(DECLARATIONS, tkn->lexeme, tkn->type) == 1)
						{
							prev_flag = true;
							Declarations();
						}
						else
						{
							failure("Data Type expected!");
						}
						get();
						if (search_first(STATEMENT_LIST, tkn->lexeme, tkn->type) == 1)
						{ // CHANGE
							prev_flag = true;
							Statement_List();
						}
						else
						{
							failure("Invalid Identifier!");
						}
						get();
						if (strcmp(tkn->lexeme, "return") == 0)
						{
							get();
							if (tkn->type == NUMERIC_CONSTANT)
							{
								get();
								if (strcmp(tkn->lexeme, ";") == 0)
								{
									get();
									if (strcmp(tkn->lexeme, "}") == 0)
									{
										success();
									}
									else
									{
										failure("No closing curly braces found!");
									}
								}
								else
								{
									failure("No Semi-Colon found!");
								}
							}
							else
							{
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

#endif