%{
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "list.h"
#include <stdbool.h>
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
%token IF "if"
%token <lexeme> ID
%token INTEGER
%token DOOBLE
%token PRINT
%token BOOL
%token AND "&&"
%token OR "||"
%token NOT "!"
%token NE "!="
%token BE "=="

%type <value> expr
%type <condition> cond
%type <value> term
%type <lexeme> statement
%type <lexeme> assignment
%type <lexeme> declaration

%nonassoc '=' 
%left AND OR NOT
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
      | cond "&&" cond {$$ = $1 && $3;}
      | cond "||" cond {$$ = $1 || $3;}
      | "!" cond       {$$ = ! $2;}
      | expr "!=" expr {$$ = $1 != $3;}
      | expr "==" expr {$$ = $1 == $3;}
      | '(' cond ')'   {$$ = $2;}
      ;

assignment  : ID '=' expr   { char buf[20];
                              gcvt($3, 10, buf);
                              table = update_val_new(table, $1, buf);
                              $$ = $1;}
            | ID '=' cond   { table = update_val_new(table, $1, $3 ? "true":"false");
                              $$ = $1;}
      ;

declaration : INTEGER ID {table = add_new(table, $2, "int", "0");
                          printf("Variable %s\n", $2);
                          $$ = $2;}
            | DOOBLE ID  {table = add_new(table, $2, "float", "0.0");
                          printf("Variable %s\n", $2);
                          $$ = $2;}
            | BOOL ID   {table = add_new(table, $2, "bool", "true");
                         printf("Variable %s\n", $2);
                         $$ = $2;}
      ;

term  : NUM            {$$ = $1;}
      | ID             {$$ = getFVal(table,$1);}
      ;

statement : assignment {;}
          | declaration {;}
          | PRINT ID {print_element(table,$2);}
          | PRINT {print_list(table);}
          ;
%%

#include "lex.yy.c"
	
int main(void)
{
yyrestart(fopen(FILENAME,"r"));
      table = NULL;
  return yyparse();}