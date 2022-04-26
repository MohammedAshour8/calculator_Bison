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
    insertar(&tablaSimbolos, "PHI", PHI, CONSTANT);
    insertar(&tablaSimbolos, "H", H, CONSTANT);
    insertar(&tablaSimbolos, "NA", NA, CONSTANT);
    insertar(&tablaSimbolos, "G", G, CONSTANT);
    insertar(&tablaSimbolos, "C", C, CONSTANT);
    insertar(&tablaSimbolos, "KB", KB, CONSTANT);
}

/**
 * función que se encargará de insertar en la tabla una nueva variable declarada por el usuario
 * @param nombreVariable nombre de la variable que se desea insertar
 * @param valor valor que se le asignará a la variable
 */
void insertarVariableEnTabla(char *nombreVariable, float valor) {
    insertar(&tablaSimbolos, nombreVariable, valor, VARIABLE);
}

/**
 * función que se encarga de imprimir la tabla de símbolos por pantalla. Se llama a una función de abb.h
 */
void imprimirTabla() {
    printf("\n\n===================== TABLA DE SIMBOLOS =====================\n");
    // se realiza una llamada a una función del abb.c
    _imprimirTabla(&tablaSimbolos);
    printf("=============================================================\n");
}


/**
 * función que se encarga de imprimir por pantalla el espacio de trabajo, esto es, las variables almacenadas en la
 * sesión actual de trabajo y sus valores. Se llama a una función de abb.h
 */
void imprimirEspacioTrabajo() {
    printf("\n\n===================== ESPACIO DE TRABAJO =====================\n");
    _imprimirEspacioTrabajo(&tablaSimbolos);
    printf("=============================================================\n");
}


/**
 * función que se encarga de actualizar el valor de la variable en función del nuevo valor que le asigna el usuario.
 * Se llama a una función de abb.h
 * @param componentelex nombre de la variable que se desea actualizar
 * @param valor nuevo valor que se le asignará a la variable
 */
void actualizarValorVariable(char *componentelex, float valor) {
    componente lex;
    lex.tipoElemento = VARIABLE;
    lex.value.valor = valor;
    lex.lexema = componentelex;
    modificar(tablaSimbolos, lex);
}

/**
 * función que se encarga de eliminar el espacio de trabajo. Dentro del espacio de trabajo solo se contemplan las
 * variables declaradas por el usuario, las constantes y funciones no se eliminarán. Se llama a una función de abb.h
 */
void eliminarEspacioTrabajo() {
    if (!es_vacio(tablaSimbolos)) {
        _eliminarEspacioTrabajo(&tablaSimbolos);
    }
}

/**
 * función que se encargará de buscar una variable o constrante almacenado en la tabla de símbolos a través de su nombre
 * y se devolverá el valor asignado. Se llama a una función de abb.h
 * @param componentelex nombre de la variable o constante en cuestión.
 */
float obtenerValor(char *componentelex) {
    // llamada a una función de abb.h
    return _obtenerValor(&tablaSimbolos, componentelex);
}

/**
 * función encargada de devolver el tipo de elemento del componente buscado en la tabla de símbolos (variable, función
 * o constante). Se llama a una función de abb.h
 * @param componentelex nombre de la variable, función o constante en cuestión.
 * @return tipo de elemento de la variable, función o constante.
 */
int obtenerTipo(char *componentelex) {
    // llamada a una función de abb.h
    return _obtenerTipo(&tablaSimbolos, componentelex);
}

/**
 * función que se encarga de insertar una función en la tabla de símbolos. Se llama a una función de abb.h
 * @param componentelex nombre de la función que se desea insertar
 * @param valor parámetro de la función que se desea insertar
 * @return devuelve el resultado de la función teniendo en cuenta su valor.
 */
double insertaFuncion(char *componentelex, float valor) {
    return _insertaFuncion(&tablaSimbolos, componentelex, valor);
}

/**
 *
 * @param componentelex
 * @param valor
 * @return
 */
double ejecutarFuncion(char *componentelex, float valor) {
    return _ejecutaFuncion(&tablaSimbolos, componentelex, valor);
}

void destruirTabla() {
    destruir(&tablaSimbolos);
}
