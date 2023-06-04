%option noyywrap
%{
#include <stdlib.h>
#include <string.h>
%}

DIGIT    [0-9]
NUM      {DIGIT}+(\.{DIGIT}+)?

LETTER   [a-zA-Z]
ID       {LETTER}({LETTER}|{DIGIT})*


%%

[ ]     { /* skip blanks */ }

if      {return IF;}
and     {return AND;}
or      {return OR;}
integer {return INTEGER;}
dooble  {return DOOBLE;}
bool    {return BOOL;}
print   {return PRINT;}
{NUM}   {yylval.value = atof(yytext);
          return NUM;}
{ID}    {yylval.lexeme = strdup(yytext);
          return ID;}

"+"     {return '+';}
"-"     {return '-';}
"*"     {return '*';}
"/"     {return '/';}
"("     {return '(';}
")"     {return ')';}
"<"     {return '<';}
">"     {return '>';}
"="     {return '=';}
\n      {return '\n';}

%%
