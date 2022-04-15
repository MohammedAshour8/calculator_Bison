%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TablaSimbolos/TablaSimbolos.h"
#include "definiciones.h"

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

NUMBER			{DECIMAL_LIT}|{FLOAT_LIT}

IDENTIFIER              {LETTER}({LETTER}|{UNICODE_DIGIT})*

FILE_NAME               {IDENTIFIER}

OPERATORS               [+*/%&,;.:|^<>=!~()[\]{}-]
SUMASSIGN_OP            \+=
SUBASSIGN_OP            -=
MULTASSIGN_OP           \*=
DIVASSIGN_OP            \/=
ASSIGN_OP               =

%x READ

%%

"QUIT"			{yyterminate();}
"WORKSPACE"		{