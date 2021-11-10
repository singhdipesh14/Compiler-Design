#ifndef __GET_NEXT_TOKEN_H
#define __GET_NEXT_TOKEN_H
char keywords[32][10] = {
    "auto",
    "double",
    "int",
    "struct",
    "break",
    "else",
    "long",
    "switch",
    "case",
    "enum",
    "register",
    "typedef",
    "char",
    "extern",
    "return",
    "union",
    "const",
    "float",
    "short",
    "unsigned",
    "continue",
    "for",
    "signed",
    "void",
    "default",
    "goto",
    "sizeof",
    "voltile",
    "do",
    "if",
    "static",
    "while"}; // list of keywords
char data_types[][10] = {
    "double",
    "int",
    "char",
    "float"};
char operators[5] = {
    '+',
    '-',
    '/',
    '%',
    '*'};
char brackets[6] = {
    '(',
    ')',
    '[',
    ']',
    '{',
    '}'};
char special_symbols[12] = {
    '*',
    ';',
    ':',
    '.',
    ',',
    '^',
    '&',
    '!',
    '>',
    '<',
    '~',
    '`'};
enum TYPE
{
  IDENTIFIER,
  KEYWORD,
  STRING_LITERAL,
  NUMERIC_CONSTANT,
  OPERATOR,
  BRACKET,
  SPECIAL_SYMBOL,
  RELATIONAL_OPERATOR,
  CHARACTER_CONSTANT
};
char types[][30] = {
    "IDENTIFIER",
    "KEYWORD",
    "STRING_LITERAL",
    "NUMERIC_CONSTANT",
    "OPERATOR",
    "BRACKET",
    "SPECIAL_SYMBOL",
    "RELATIONAL_OPERATOR",
    "CHARACTER_CONSTANT"};
typedef struct node
{
  char *cur;
  int(row), col;
  struct node *next;
  enum TYPE type;
} * Node; // element for hash table

typedef struct symbol
{
  char *name;
  char *data_type;
  struct symbol *next;
  unsigned int size, (row), col;
} * Symbol; // element for symbol table

typedef struct token
{
  char *lexeme;
  enum TYPE type;
  int(row), col;
} * Token; // token returned by getNextToken()

Node hashTable[MAX_SIZE];    // hash table
Symbol st[MAX_SIZE];         // symbol table
int isKeyword(char buffer[]) // function to check for keyword
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
int isDatatype(char buffer[])
{ // function to check for data_Type
  for (int i = 0; i < 4; i++)
  {
    if (strcmp(buffer, data_types[i]) == 0)
      return 1;
  }
  return 0;
}
int isOperator(char(c))
{
  for (int i = 0; i < 5; i++)
  {
    if (operators[i] == (c))
      return 1;
  }
  return 0;
}
int isSpecial(char(c))
{
  for (int i = 0; i < 12; i++)
  {
    if (special_symbols[i] == (c))
      return 1;
  }
  return 0;
}
int isBracket(char(c))
{
  for (int i = 0; i < 6; i++)
  {
    if (brackets[i] == (c))
      return 1;
  }
  return 0;
}
int hash(int size) // hashing function
{
  return (size) % MAX_SIZE;
}
void display_st() // display the symbol table
{
  printf("      Name   |       Type    |       Size    \n");
  for (int i = 0; i < MAX_SIZE; i++)
  {
    if (st[i] != NULL)
    {
      Symbol cur = st[i];
      while (cur != NULL)
      {
        printf("%10s    |%10s    |%10d    \n", cur->name, cur->data_type, cur->size);
        cur = cur->next;
      }
    }
  }
}
int search_symbol(char identifier[]) // to search in symbol_table
{
  int index = hash(strlen(identifier));
  if (st[index] == NULL)
    return -1;
  Symbol cur = st[index];
  int i = 0;
  while (cur != NULL)
  {
    if (strcmp(identifier, cur->name) == 0)
      return i;
    cur = cur->next;
    i++;
  }
  return -1;
}
int search(char buffer[], enum TYPE type) // to search in hash table
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
void insert_symbol(char identifier[], char data_type[])
{ // insert in symbol table
  // printf("reached insert symbol with %s\n",identifier);
  if (search_symbol(identifier) == -1)
  {
    Symbol n = (Symbol)malloc(sizeof(struct symbol));
    char *str = (char *)calloc(strlen(identifier) + 1, sizeof(char));
    strcpy(str, identifier);
    n->name = str;
    char *typee = (char *)calloc(strlen(data_type) + 1, sizeof(char));
    strcpy(typee, data_type);
    n->data_type = typee;
    if (strcmp(data_type, "int") == 0)
      n->size = 4;
    else if (strcmp(data_type, "double") == 0)
      n->size = 8;
    else if (strcmp(data_type, "char") == 0)
      n->size = 1;
    else if (strcmp(data_type, "function") == 0)
      n->size = 0;
    else
      n->size = 4;
    int index = hash(strlen(identifier));
    // printf("%10s    |%10s    |%10d    \n",n->name, n-> data_type, n -> size);
    if (st[index] == NULL)
    {
      st[index] = n;
      return;
    }
    Symbol cur = st[index];
    while (cur->next != NULL)
      cur = cur->next;
    cur->next = n;
  }
}
Token insert(char buffer[], int(row), int col, enum TYPE type)
{ // insert in hash table
  // printf("reached insert\n");
  Token tkn = (Token)malloc(sizeof(struct token));

  tkn->lexeme = (char *)calloc(strlen(buffer) + 1, sizeof(char));
  strcpy(tkn->lexeme, buffer);
  tkn->type = type;
  tkn->col = col;
  tkn->row = row;
  if (type == IDENTIFIER || search(buffer, type) == 0)
  {
    // printf("< %s | %d | %d | %s >\n", buffer, (row), col, types[type]);
    int index = hash(strlen(buffer));
    Node n = (Node)malloc(sizeof(struct node));
    char *str = (char *)calloc(strlen(buffer) + 1, sizeof(char));
    strcpy(str, buffer);
    n->cur = str;
    n->next = NULL;
    n->row = (row);
    n->col = col;
    n->type = type;
    if (hashTable[index] == NULL)
    {
      hashTable[index] = n;
      return tkn;
    }
    Node cur = hashTable[index];
    while (cur->next != NULL)
    {
      cur = cur->next;
    }
    cur->next = n;
  }
  return tkn;
}
Token getNextToken(FILE *finp, int *(row), int *(col_pos), char *data_type_buffer, char *c)
{

  char buffer[100];
  int i = 0, col;
  Token tkn = NULL;

  // while ((*c) != EOF)

  if (isalpha((*c)) != 0 || (*c) == '_')
  {
    buffer[i++] = (*c);
    col = (*col_pos);
    while (isalpha((*c)) != 0 || (*c) == '_' || isdigit((*c)) != 0)
    {
      (*c) = fgetc(finp);
      (*col_pos)++;
      if (isalpha((*c)) != 0 || (*c) == '_' || isdigit((*c)) != 0)
        buffer[i++] = (*c);
    }
    buffer[i] = '\0';

    // inserting into hashtable
    if (isDatatype(buffer) == 1)
    {
      tkn = insert(buffer, (*row), col - 1, KEYWORD); // data type
      strcpy(data_type_buffer, buffer);
    }
    else if (isKeyword(buffer) == 1)
    {
      tkn = insert(buffer, (*row), col - 1, KEYWORD); // keyword
    }
    else
    {
      tkn = insert(buffer, (*row), col - 1, IDENTIFIER); // identifier

      if ((*c) == '(')
        insert_symbol(buffer, "function");
      else
        insert_symbol(buffer, data_type_buffer); // as data type would already be stored in data_type_buffer
      // data_type_buffer[0] = '\0';
    }
    i = 0;
    if ((*c) == '\n')
      (*row)++, (*col_pos) = 1;
    buffer[0] = '\0';
    // i = 0;
    //(*c) = fgetc(finp);
    //(*col_pos)++;
  }
  else if (isdigit((*c)) != 0)
  {
    buffer[i++] = (*c);
    col = (*col_pos);
    while (isdigit((*c)) != 0 || (*c) == '.')
    {
      (*c) = fgetc(finp);
      (*col_pos)++;
      if (isdigit((*c)) != 0 || (*c) == '.')
        buffer[i++] = (*c);
    }
    buffer[i] = '\0';
    tkn = insert(buffer, (*row), col - 1, NUMERIC_CONSTANT); // numerical constant
    i = 0;
    if ((*c) == '\n')
      (*row)++, (*col_pos) = 1;
    buffer[0] = '\0';

    //(*c) = fgetc(finp);
    //(*col_pos)++;
  }
  else if ((*c) == '\"')
  {
    col = (*col_pos);
    buffer[i++] = (*c);
    (*c) = 0;
    while ((*c) != '\"')
    {
      (*c) = fgetc(finp);
      (*col_pos)++;
      buffer[i++] = (*c);
    }
    buffer[i] = '\0';
    tkn = insert(buffer, (*row), col - 1, STRING_LITERAL); // string literals
    buffer[0] = '\0';
    i = 0;
    (*c) = fgetc(finp);
    (*col_pos)++;
  }
  else if ((*c) == '\'')
  {
    col = (*col_pos);
    buffer[i++] = (*c);
    (*c) = 0;
    (*c) = fgetc(finp);
    (*col_pos)++;
    buffer[i++] = (*c);
    if ((*c) == '\\')
    {
      (*c) = fgetc(finp);
      (*col_pos)++;
      buffer[i++] = (*c);
    }
    (*c) = fgetc(finp);
    (*col_pos)++;
    buffer[i++] = (*c);
    buffer[i] = '\0';
    tkn = insert(buffer, (*row), col - 1, CHARACTER_CONSTANT); // character constants
    buffer[0] = '\0';
    i = 0;
    (*c) = fgetc(finp);
    (*col_pos)++;
  }
  else
  {
    col = (*col_pos);
    if ((*c) == '=')
    { // relational and logical operators
      (*c) = fgetc(finp);
      (*col_pos)++;
      if ((*c) == '=')
      {
        tkn = insert("==", (*row), col - 1, RELATIONAL_OPERATOR);
      }
      else
      {
        tkn = insert("=", (*row), col - 1, RELATIONAL_OPERATOR);
        fseek(finp, -1, SEEK_CUR); // to go back one char
        (*col_pos)--;
      }
    }
    else if ((*c) == '>' || (*c) == '<' || (*c) == '!')
    {
      char temp = (*c);
      (*c) = fgetc(finp);
      (*col_pos)++;
      if ((*c) == '=')
      {
        char temp_str[3] = {
            temp,
            '=',
            '\0'};
        tkn = insert(temp_str, (*row), col - 1, RELATIONAL_OPERATOR);
      }
      else
      {
        char temp_str[2] = {
            temp,
            '\0'};
        tkn = insert(temp_str, (*row), col - 1, RELATIONAL_OPERATOR);
        fseek(finp, -1, SEEK_CUR);
        (*col_pos)--;
      }
    }
    else if (isBracket((*c)) == 1)
    { // parentheses and special symbols
      char temp_string[2] = {
          (*c),
          '\0'};
      tkn = insert(temp_string, (*row), col - 1, BRACKET);
    }
    else if (isSpecial((*c)) == 1)
    { // parentheses and special symbols
      char temp_string[2] = {
          (*c),
          '\0'};
      tkn = insert(temp_string, (*row), col - 1, SPECIAL_SYMBOL);
    }
    else if (isOperator((*c)) == 1)
    { // operators
      char temp = (*c);
      (*c) = fgetc(finp);
      (*col_pos)++;
      if ((*c) == '=' || (temp == '+' && (*c) == '+') || (temp == '-' && (*c) == '-'))
      {
        char temp_string[3] = {
            temp,
            (*c),
            '\0'};
        tkn = insert(temp_string, (*row), col - 1, OPERATOR);
      }
      else
      {
        char temp_String[2] = {
            temp,
            '\0'};
        tkn = insert(temp_String, (*row), col - 1, OPERATOR);
        fseek(finp, -1, SEEK_CUR);
        (*col_pos)--;
      }
    }
    else if ((*c) == '\n')
      (*row)++, (*col_pos) = 1;
    else if (*c == '$')
    {
      Token eof = (Token)malloc(sizeof(struct token));
      eof->lexeme = "EOF";
      return eof;
    }
    (*c) = fgetc(finp);
    (*col_pos)++;
  }
  return tkn;
}
#endif
