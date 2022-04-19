%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TablaSimbolos/TablaSimbolos.h"
#include "definiciones.h"
#include "lex.yy.h"

extern int yylex();
void yyerror(char *s);
void ayuda();
%}

%union{
	float valor;
	char *componente;
}

%start input

%token <num> NUM
%token <lexema> IDENTIFIER
%token <lexema> FILE

%token HELP
%token EXIT
%token CLEAR
%token CONSTRAINTS
%token WORKSPACE
%token TABLE

%token SUM_OP
%token SUB_OP
%token MUL_OP
%token DIV_OP
%token MOD_OP
%token POW_OP

%right ASSIGN_OP
%left '+' '-' SUM_OP SUB_OP
%left '*' '/' MUL_OP DIV_OP
%left '%' MOD_OP
%left NEGATIVE
%right '^' POW_OP

input:
	| input line
;

line:	'\n'
	| exp ';' '\n' {printf ("\t%.10g\n", $1);}
	| exp '\n' {printf("\n");}
	| error {yyclearin; yyerrok;}
;

exp:	NUM	{$$ = $1;}
	| IDENTIFIER {if buscar_elem