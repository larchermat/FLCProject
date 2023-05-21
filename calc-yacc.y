%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>
#include "list.h"

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(1);
}

int yylex(void);
struct symtab* table;
 
%}

//vardelo dio porco
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

%type <value> expr
%type <condition> cond
%type <lexeme> var

%nonassoc '\n'
%nonassoc '='
%left '+' '-'
%left '*' '/'
%left '<' '>'
%right '(' ')'

%start line

%%
//vardelo dio can
line  : expr '\n'      {printf("Result: %5.2f\n", $1); exit(0);}
      ;
expr  : expr '+' expr  {$$ = $1 + $3;}
      | expr '-' expr  {$$ = $1 - $3;}
      | expr '*' expr  {$$ = $1 * $3;}
      | expr '/' expr  {$$ = $1 / $3;}
      | '(' expr ')'   {$$ = $2;}
      | IF '(' cond ')' expr expr  {$$ = $3 ? $5:$6;}
      | NUM            {$$ = $1;}
      | var            {$$ = getFVal(table,$1);}
      ;
cond  : expr '<' expr  {$$ = $1 < $3;}
      | expr '>' expr  {$$ = $1 > $3;}
      ;
var   : INTEGER ID NUM {table = add(table, $2, "int", $3);
                        printf("Variable %s = %d\n", $2, getIVal(table,$2));
                        $$ = $2;}
      | DOOBLE ID NUM  {table = add(table, $2, "float", $3);
                        printf("Variable %s = %2.2f\n", $2, getFVal(table,$2));
                        $$ = $2;}
      | var '=' expr   {table = update_val(table, $1, $3);
                        $$ = $1;}
      | ID             {$$ = $1;}
      ;

%%

#include "lex.yy.c"
	
int main(void)
{
      table = NULL;
  return yyparse();}
