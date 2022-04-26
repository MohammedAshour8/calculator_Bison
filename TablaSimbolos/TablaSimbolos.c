#include <stdio.h>
#include <stdlib.h>
#include "../ABB/abb.h"
#include "../definiciones.h"

// estructura de datos ordenada que se encargará de almacenar las palabras clave e identificadores
abb tablaSimbolos;

void inicializarTabla() {
    crear(&tablaSimbolos);
    insertar(&tablaSimbolos, "PI", PI, CONSTANT);
    insertar(&tablaSimbolos, "E", E, CONSTANT);
}

/**
 * función que se encargará de insertar en la tabla un componente léxico determinado
 * @param componente componente léxico que se almacena
 * @param lexema entero que identifica al componente léxico
 */
void insertarEnTabla(char *componente, float valor, int tipo){
    // se realiza una llamada a la función insertar del abb.h
    switch (tipo) {
        case VARIABLE:
            insertar(&tablaSimbolos, componente, valor, VARIABLE);
            break;
    }
}
/**
 * función que se encarga de imprimir la tabla de símbolos por pantalla
 */
void imprimirTabla(){
    printf("\n\n===================== TABLA DE SIMBOLOS =====================\n");
    // se realiza una llamada a una función del abb.c
    _imprimirTabla(&tablaSimbolos);
    printf("=============================================================\n");
}

void imprimirEspacioTrabajo(){
    printf("\n\n===================== ESPACIO DE TRABAJO =====================\n");
    _imprimirEspacioTrabajo(&tablaSimbolos);
    printf("=============================================================\n");
}

void actualizarValorVariable(char *componentelex, float valor){
    componente lex;
    lex.tipoElemento = VARIABLE;
    lex.value.valor = valor;
    lex.lexema = componentelex;
    modificar(tablaSimbolos, lex);
}

void eliminarEspacioTrabajo(){
    if(!es_vacio(tablaSimbolos)){
        _eliminarEspacioTrabajo(&tablaSimbolos);
    }
}

/**
 * función que se encargará de buscar un lexema almacenado en la tabla de símbolos a través del componente léxico que se
 * pase
 * @param componentelex componente léxico al cual se está buscando su lexema
 * @param estructuraComponente estructura de datos donde se almacena el componente léxico y el lexema
 */
float obtenerValor(char *componentelex){
    // llamada a una función de abb.h
    return _obtenerValor(&tablaSimbolos, componentelex);
}

int obtenerTipo(char *componentelex){
    // llamada a una función de abb.h
    return _obtenerTipo(&tablaSimbolos, componentelex);
}

double insertaFuncion(char *componentelex, float valor){
    return _insertaFuncion(&tablaSimbolos, componentelex, valor);
}

double ejecutarFuncion(char *componentelex, float valor){
    return _ejecutaFuncion(&tablaSimbolos, componentelex, valor);
}

void destruirTabla(){
    destruir(&tablaSimbolos);
}
