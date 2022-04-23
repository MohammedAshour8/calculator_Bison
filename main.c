#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TablaSimbolos/TablaSimbolos.h"
#include "lex.yy.h"
#include "definiciones.h"
#include "semantico.tab.h"

int main(int argc, char **argv){
    inicializarTabla();
    yyparse();
    destruirTabla();
    return 0;
}
