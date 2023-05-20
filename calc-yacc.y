%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdbool.h>

void yyerror(const char *s)
{
    fprintf(stderr, "%s\n", s);
    exit(1);
}

int yylex(void);
 
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

%type <value> expr
%type <condition> cond

%left '+' '-'
%left '*' '/'
%left '<' '>'
%right '(' ')'

%start line

%%
//vardelo dio can
line  : expr '\n'      {printf("Result: %5.2f\n", $1); exit(0);}
      | ID             {printf("IDentifier: %s\n", $1); exit(0);}
      ;
expr  : expr '+' expr  {$$ = $1 + $3;}
      | expr '-' expr  {$$ = $1 - $3;}
      | expr '*' expr  {$$ = $1 * $3;}
      | expr '/' expr  {$$ = $1 / $3;}
      | '(' expr ')'   {$$ = $2;}
      | IF '(' cond ')' expr expr  {$$ = $3 ? $5:$6;}
      | NUM            {$$ = $1;}
      ;
cond  : expr '<' expr  {$$ = $1 < $3;}
      | expr '>' expr  {$$ = $1 > $3;}
      ;

%%

#include "lex.yy.c"
	
int main(void)
{
  return yyparse();}
