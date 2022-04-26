#include "abb.h"
#include "../definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <gnu/lib-names.h>

///////////////////////// ESTRUCTURAS DE DATOS

struct celda {
    componente info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIONES


/////////////////////////////////////////////////////////////
/////////////////////////// INICIO PARTE MODIFICABLE

/*Extraer la clave de una celda */
tipoclave _clave_elem(componente *celda) {
    return celda->lexema;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    return strcmp(cl1, cl2) == 0 ? 0 : strcmp(cl1, cl2) > 0 ? 1 : -1;
}

/////////////////////////// FIN PARTE MODIFICABLE
/////////////////////////////////////////////////////////////

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}

void destruir(abb *A) {
    if (*A != NULL) {
        destruir(&(*A)->izq);
        free((*A)->info.lexema);
        destruir(&(*A)->der);
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}

void leer(abb A, componente *celda) {
    *celda = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, componente celda) {
    return _comparar_claves(cl, _clave_elem(&celda));
}
//Función privada para informar si una clave está en el árbol

unsigned _es_miembro_clave(abb A, tipoclave cl) {
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { //cl == A->info
        return 1;
    }
    if (comp > 0) { //cl > A->info
        return _es_miembro_clave(der(A), cl);
    }
    //cl < A->info
    return _es_miembro_clave(izq(A), cl);
}

//Funciones públicas

unsigned es_miembro(abb A, componente celda) {
    return _es_miembro_clave(A, _clave_elem(&celda));
}

float _obtenerValor(abb *A, char *lexema) {
    if (es_vacio(*A)) {
        return 0;
    }

    int comp = strcmp(lexema, (*A)->info.lexema);
    if (comp == 0) {
        return (*A)->info.value.valor;
    } else if (comp < 0) {
        return (_obtenerValor(&(*A)->izq, lexema));
    } else {
        return (_obtenerValor(&(*A)->der, lexema));
    }
}

int _obtenerTipo(abb *tablaSimbolos, char *componentelex) {
    if (es_vacio(*tablaSimbolos)) {
        return 0;
    }

    int comp = strcmp(componentelex, (*tablaSimbolos)->info.lexema);
    if (comp == 0) {
        return (*tablaSimbolos)->info.tipoElemento;
    } else if (comp < 0) {
        return (_obtenerTipo(&(*tablaSimbolos)->izq, componentelex));
    } else {
        return (_obtenerTipo(&(*tablaSimbolos)->der, componentelex));
    }
}
//OPERACIONES DE MODIFICACIÓN

/* Funcion recursiva para insertar un nuevo nodo
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertar(abb *A, char *componenteLexico, float valor, int tipoElemento) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof(struct celda));
        (*A)->info.lexema = (char *) malloc(strlen(componenteLexico) + 1 * sizeof(char));
        strcpy((*A)->info.lexema, componenteLexico);
        (*A)->info.lexema[strlen(componenteLexico)] = '\0';
        (*A)->info.value.valor = valor;
        (*A)->info.tipoElemento = tipoElemento;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }

    int comparacion = strcmp(componenteLexico, (*A)->info.lexema);

    if (comparacion > 0) {
        insertar(&(*A)->der, componenteLexico, valor, tipoElemento);
    } else {
        insertar(&(*A)->izq, componenteLexico, valor, tipoElemento);
    }
}

/* Funcion privada que devuelve mínimo de subárbol dcho */
componente _suprimir_min(abb *A) {//Se devuelve el elemento más a la izquierda
    abb aux;
    componente ele;
    if (es_vacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}

/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.*/
void _modificar(abb A, tipoclave cl, componente nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);
    if (comp == 0) {
        A->info = nodo;
    } else if (comp < 0) {
        _modificar(A->izq, cl, nodo);
    } else {
        _modificar(A->der, cl, nodo);
    }
}


/* Permite modificar el nodo extrayendo del mismo la clave */
void modificar(abb A, componente nodo) {
    tipoclave cl = _clave_elem(&nodo);
    _modificar(A, cl, nodo);
}

void _suprimirElem(abb *A, componente elem) {
    abb aux;
    if (es_vacio(*A)) {
        return;
    }

    tipoclave cl = _clave_elem(&elem);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp < 0) {
        _suprimirElem(&(*A)->izq, elem);
    } else if (comp > 0) {
        _suprimirElem(&(*A)->der, elem);
    } else if (es_vacio((*A)->izq) && es_vacio((*A)->der)) {
        free((*A)->info.lexema);
        free(*A);
        *A = NULL;
    } else if (es_vacio((*A)->izq)) {
        aux = *A;
        *A = (*A)->der;
        free(aux->info.lexema);
        free(aux);
    } else if (es_vacio((*A)->der)) {
        aux = *A;
        *A = (*A)->izq;
        free(aux->info.lexema);
        free(aux);
    } else {
        componente elem = _suprimir_min(&(*A)->izq);
        (*A)->info = elem;
    }
}

void _imprimirTabla(abb *A) {
    if (!es_vacio(*A)) {
        if (&(*A)->izq != NULL) {
            _imprimirTabla(&(*A)->izq);
        }

        switch ((*A)->info.tipoElemento) {
            case CONSTANT:
                printf("\033[1;33m");
                if((*A)->info.value.valor < 0.0001 || (*A)->info.value.valor > 1.0E+8){
                    printf("[CTE]\t%s = %E\n", (*A)->info.lexema, (*A)->info.value.valor);
                } else{
                    printf("[CTE]\t%s = %f\n", (*A)->info.lexema, (*A)->info.value.valor);
                }
                printf("\033[0m");
                break;
            case VARIABLE:
                printf("\033[0;36m");
                if((*A)->info.value.valor < 0.0001 || (*A)->info.value.valor > 1.0E+8){
                    printf("[VAR]\t%s = %E\n", (*A)->info.lexema, (*A)->info.value.valor);
                } else{
                    printf("[VAR]\t%s = %f\n", (*A)->info.lexema, (*A)->info.value.valor);
                }
                printf("\033[0m");
                break;
            default:
                printf("\033[0;32m");
                printf("[FNC]\t%s\n", (*A)->info.lexema);
                printf("\033[0m");
        }
        if (&(*A)->der != NULL) {
            _imprimirTabla(&(*A)->der);
        }
    }
}

void _imprimirEspacioTrabajo(abb *A) {
    if (!es_vacio(*A)) {
        if (&(*A)->izq != NULL) {
            _imprimirEspacioTrabajo(&(*A)->izq);
        }

        if ((*A)->info.tipoElemento == VARIABLE) {
            printf("\033[0;36m");
            if((*A)->info.value.valor < 0.0001 || (*A)->info.value.valor > 1.0E+8){
                printf("[VAR]\t%s = %E\n", (*A)->info.lexema, (*A)->info.value.valor);
            } else{
                printf("[VAR]\t%s = %f\n", (*A)->info.lexema, (*A)->info.value.valor);
            }
            printf("\033[0m");
        }
        if (&(*A)->der != NULL) {
            _imprimirEspacioTrabajo(&(*A)->der);
        }
    }
}

void __insertaFuncionEnTabla(abb *A, char *componentelex, void *fnc){
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof(struct celda));
        (*A)->info.lexema = (char *) malloc(strlen(componentelex) * sizeof(char));
        (*A)->info.lexema[0] = '\0';
        strncat((*A)->info.lexema, componentelex, strlen(componentelex));
        (*A)->info.tipoElemento = FUNCTION;
        (*A)->info.value.fnc = fnc;
        (*A)->izq = NULL;
        (*A)->der = NULL;
    } else if (strcmp(componentelex, (*A)->info.lexema) < 0) {
        __insertaFuncionEnTabla(&(*A)->izq, componentelex, fnc);
    } else if (strcmp(componentelex, (*A)->info.lexema) > 0) {
        __insertaFuncionEnTabla(&(*A)->der, componentelex, fnc);
    }
}

double _insertaFuncion(abb *A, char *componentelex, float valor) {
    void *handle;
    double (*function)(double);
    char *error;

    handle = dlopen (LIBM_SO, RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }

    function = dlsym(handle, componentelex);
    if ((error = dlerror()) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }

    __insertaFuncionEnTabla(A, componentelex, function);
    dlclose(handle);
    return ((*function)(valor));
}

void _eliminarEspacioTrabajo(abb *A) {
    if (!es_vacio(*A)) {
        _eliminarEspacioTrabajo(&(*A)->izq);
        _eliminarEspacioTrabajo(&(*A)->der);

        if ((*A)->info.tipoElemento == VARIABLE) {
            _suprimirElem(A, (*A)->info);
        }
    }
}

double _ejecutaFuncion(abb *A, char *lexema, float valor){
    if(!es_vacio(*A)){
        if(strcmp(lexema, (*A)->info.lexema) == 0){
            return (*A)->info.value.fnc(valor);
        } else if(strcmp(lexema, (*A)->info.lexema) < 0){
            return _ejecutaFuncion(&(*A)->izq, lexema, valor);
        } else {
            return _ejecutaFuncion(&(*A)->der, lexema, valor);
        }
    }

    return 0;
}

