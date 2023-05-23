%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#define FILENAME "input_file.txt"

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(1);
}

int yylex(void);
struct symtab* table;
 
%}

%union {
       char* lexeme;			//name of an identifier
       float value;			//attribute of a token of type NUM
       bool condition;
       }

%token <value>  NUM
%token IF
%token <lexeme> ID
%token INTEGER
%token DOOBLE
%token PRINT

%type <value> expr
%type <condition> cond
%type <value> term
%type <lexeme> statement
%type <lexeme> assignment
%type <lexeme> declaration

%nonassoc '='
%left '+' '-'
%left '*' '/'
%left '<' '>'
%right '(' ')'

%start line

%%
line  : statement '\n' {;}
      | line statement '\n'  {;}
      ;

expr  : expr '+' expr  {$$ = $1 + $3;}
      | expr '-' expr  {$$ = $1 - $3;}
      | expr '*' expr  {$$ = $1 * $3;}
      | expr '/' expr  {$$ = $1 / $3;}
      | '(' expr ')'   {$$ = $2;}
      | term           {$$ = $1;}
      ;

cond  : expr '<' expr  {$$ = $1 < $3;}
      | expr '>' expr  {$$ = $1 > $3;}
      ;

assignment  : ID '=' expr   {table = update_val(table, $1, $3);
                              $$ = $1;}
      ;

declaration : INTEGER ID {table = add(table, $2, "int", 0);
                          printf("Variable %s = %d\n", $2, getIVal(table,$2));
                          $$ = $2;}
            | DOOBLE ID  {table = add(table, $2, "float", 0.0);
                          printf("Variable %s = %2.2f\n", $2, getFVal(table,$2));
                          $$ = $2;}
      ;

term  : NUM            {$$ = $1;}
      | ID             {$$ = getFVal(table,$1);}
      ;

statement : assignment {;}
          | declaration {;}
          | PRINT ID {printf("%s = %2.2f\n", $2, getFVal(table,$2));}
          | PRINT {print_list(table);}
          ;

%%

#include "lex.yy.c"
	
int main(void)
{
yyrestart(fopen(FILENAME,"r"));
      table = NULL;
  return yyparse();}
