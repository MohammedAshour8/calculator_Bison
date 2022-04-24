%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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
%token WORKSPACE
%token TABLE

%token SUM_OP
%token SUB_OP
%token MUL_OP
%token DIV_OP
%token MOD_OP
%token POW_OP

%right ASSIGN_OP
%left '+' '-'
%left '*' '/'
%left '%'
%left NEGATIVE
%right '^'

%type <num> exp
%type <num> define
%type <num> operations

%%

input:
	| input line
;

line:	'\n'	{printf("$ ");}
	| exp ';' '\n' {printf ("> %f\n$ ", $1);}
	| exp '\n' {printf ("$ ");}
	| error {yyclearin; yyerrok;}
;

exp:	NUM	{$$ = $1;}
	| IDENTIFIER {if (buscarElemento($1) != 0) {$$ = buscarElemento($1);} else {yyerror("Variable no declarada");}}
	| '(' exp ')' {$$ = $2;}
	| TABLE {imprimirTabla();}
	| WORKSPACE {imprimirEspacioTrabajo();}
	| CLEAR {eliminarEspacioTrabajo();}
	| HELP {ayuda();}
	| operations
	| define
;

define:	IDENTIFIER '=' exp {if(buscarElemento($1) == 0) {insertarEnTabla($1, $3, VARIABLE); $$ = $3;}}

operations:	exp '+' exp {$$ = $1 + $3;}
		| exp '-' exp {$$ = $1 - $3;}
		| exp '*' exp {$$ = $1 * $3;}
		| exp '/' exp {if($3 != 0) {$$ = $1 / $3;} else {yyerror("Division por cero");}}
		| exp '^' exp {$$ = pow($1, $3);}
;

%%

void yyerror(char *s) {
	fprintf(stderr, "Error: %s\n", s);
}

void ayuda() {
	printf("\n\tHELP\n\t\tMuestra esta ayuda\n\n");
	printf("\tEXIT\n\t\tCierra el programa\n\n");
	printf("\tCLEAR\n\t\tElimina variables y funciones de la tabla\n\n");
	printf("\tCONSTRAINTS\n\t\tMuestra las restricciones\n\n");
	printf("\tWORKSPACE\n\t\tMuestra el espacio de trabajo\n\n");
	printf("\tTABLE\n\t\tMuestra la tabla de simbolos\n\n");
}