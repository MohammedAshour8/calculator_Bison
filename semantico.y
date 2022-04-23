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
	float num;
	char *lexema;
}

%start input

%token <num> NUM
%token <lexema> IDENTIFIER

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

%type <num> exp

%%

input:
	| input line
;

line:	'\n'
	| exp ';' '\n' {printf ("\t%.10g\n", $1);}
	| exp '\n' {printf("\n");}
	| error {yyclearin; yyerrok;}
;

exp:	NUM	{$$ = $1;}
;

%%

void yyerror(char *s) {
	fprintf(stderr, "Error: %s\n", s);
}

void ayuda() {
	printf("\n\tHELP\n\t\tMuestra esta ayuda\n\n");
	printf("\tEXIT\n\t\tCierra el programa\n\n");
	printf("\tCLEAR\n\t\tLimpia la pantalla\n\n");
	printf("\tCONSTRAINTS\n\t\tMuestra las restricciones\n\n");
	printf("\tWORKSPACE\n\t\tMuestra el espacio de trabajo\n\n");
	printf("\tTABLE\n\t\tMuestra la tabla de simbolos\n\n");
}