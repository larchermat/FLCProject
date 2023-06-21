%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
%}

DIGIT    [0-9]
NUM      {DIGIT}+(\.{DIGIT}+)?

BOOLEAN  [true|false]

LETTER   [a-zA-Z]
ID       {LETTER}({LETTER}|{DIGIT})*



%%

[ ]     { /* skip blanks */ }

&&      {return AND;}
or      {return OR;}
!       {return NOT;}
!=      {return NE;}
==      {return BE;}
"<="    {return LE;}
>=      {return GE;}
,       {return VS;}
rad     {return RAD;}
pow     {return POW;}
integer {return INTEGER;}
float   {return FLOAT;}
bool    {return BOOL;}
print   {return PRINT;}
{NUM}   {yylval.value = atof(yytext);
          return NUM;}
{ID}    {yylval.lexeme = strdup(yytext);
          return ID;}
{BOOLEAN}   {yylval.lexeme = strdup(yytext);
              return BOOLEAN;}

"+"     {return '+';}
"-"     {return '-';}
"*"     {return '*';}
"/"     {return '/';}
"("     {return '(';}
")"     {return ')';}
"<"     {return '<';}
">"     {return '>';}
"="     {return '=';}
":"     {return ':';}
\n      {return '\n';}

%%
