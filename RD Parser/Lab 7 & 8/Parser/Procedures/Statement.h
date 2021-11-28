#ifndef __STATEMENT_H__
#define __STATEMENT_H__
void Statement_List()
{
	Statement();
	Statement_List(); // check for epsilon via first
}

void Statement()
{
	AssignStat();
}
#endif