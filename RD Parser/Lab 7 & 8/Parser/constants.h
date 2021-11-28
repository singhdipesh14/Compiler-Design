#ifndef __RDCONSTANTS_H__
#define __RDCONSTANTS_H__
enum NON_TERMINALS
{ // types for non terminals.
	PROGRAM,
	DECLARATIONS,
	IDENTIFIERLIST,
	IDENTIFIERLISTPRIME,
	STATEMENT_LIST,
	STATEMENT,
	ASSIGN_STAT,
	EXPN,
	EPRIME,
	SIMPLE_EXP,
	SEPRIME,
	TERM,
	TPRIME,
	FACTOR,
	RELOP,
	ADDOP,
	MULOP
};

// ToDo: calculate the first and follow of the grammar

char first[][4][20] = {
	{"int"},
	{"int",
	 "char",
	 "double",
	 "float"},
	{"id"},
	{","}};
char follow[][2][20] = {
	{"$"},
	{"id"},
	{";"},
	{";"}};

int firstSz[] = {
	1,
	4,
	1,
	2,
	1,
	1};
int followSz[] = {
	1,
	1,
	2,
	1,
	1,
	1};
#endif