%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TablaSimbolos/TablaSimbolos.h"
#include "definiciones.h"
#include "sintactico.tab.h"

void abrirArchivo(char *nombreArchivo);
void cerrar();
%}

%option noyywrap

%option yylineno

%option noinput

%option nounput

NEWLINE                 \n
SPACE                   [ ]
SEPARATOR               ({SPACE}|\t|\r)+
SEMICOLON               ;

UNICODE_CHAR            .
UNICODE_LETTER          [a-zA-Z]
UNICODE_DIGIT           [0-9]

LETTER                  {UNICODE_LETTER}|_
DECIMAL_DIGIT           {UNICODE_DIGIT}

DECIMAL_LIT             0|[1-9](_?{DECIMAL_DIGIT})*

DECIMALS                {DECIMAL_DIGIT}+
DECIMAL_EXPONENT        [eE][+-]?{DECIMALS}
FLOAT_LIT               {DECIMALS}\.{DECIMALS}?{DECIMAL_EXPONENT}?|\.{DECIMALS}{DECIMAL_EXPONENT}?|{DECIMALS}{DECIMAL_EXPONENT}?

NUMBER			        {DECIMAL_LIT}|{FLOAT_LIT}

IDENTIFIER              {LETTER}({LETTER}|{UNICODE_DIGIT})*

FILE_NAME               {IDENTIFIER}\.?{LETTER}+

OPERATORS               [+*/%&,;.:|^<>=!~()[\]{}-]
SUMASSIGN_OP            \+=
SUBASSIGN_OP            -=
MULTASSIGN_OP           \*=
DIVASSIGN_OP            \/=
MODASSIGN_OP            %=
POWASSIGN_OP            \^=
BIGGEREQUAL_OP          >=
SMALLEREQUAL_OP         <=
EQUALEQUAL_OP           ==
ASSIGN_OP               =

%x READ

%%

"HELP"                  {return HELP;}
"EXIT"			        {yyterminate();}
"CLEAR"                 {return CLEAR;}
"WORKSPACE"             {return WORKSPACE;}
"TABLE"                 {return TABLE;}
"LOAD "                 {BEGIN(READ); return LOAD;}

{NEWLINE}               return ((int) *yytext);
{SEPARATOR}

{IDENTIFIER}            {yylval.lexema = (char *) malloc(sizeof(yytext)); yylval.lexema = strdup(yytext); return IDENTIFIER;}
{NUMBER}                {yylval.num = atof(yytext); return NUM;}

<READ>{FILE_NAME}       {yylval.lexema = (char *) malloc(sizeof(yytext)); yylval.lexema = strdup(yytext); BEGIN(INITIAL); return FILE_NAME;}

{OPERATORS}             {return ((int) *yytext);}
{SUMASSIGN_OP}          return SUM_OP;
{SUBASSIGN_OP}          return SUB_OP;
{MULTASSIGN_OP}         return MUL_OP;
{DIVASSIGN_OP}          return DIV_OP;
{MODASSIGN_OP}          return MOD_OP;
{POWASSIGN_OP}          return POW_OP;
{BIGGEREQUAL_OP}        return BIGEQ_OP;
{SMALLEREQUAL_OP}       return SMAEQ_OP;
{EQUALEQUAL_OP}         return EQEQ_OP;
<<EOF>>                 {cerrar(); yyrestart(stdin);}

%%

void abrirArchivo(char *nombreArchivo) {
    if((yyin = fopen(nombreArchivo, "r")) == NULL) {
        perror("Error al abrir el archivo");
        yyin = stdin;
    }
}

void cerrar() {
    fclose(yyin);
}
