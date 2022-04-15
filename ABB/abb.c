#include "abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////// ESTRUCTURAS DE DATOS

struct celda {
    componente info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIONES


/////////////////////////////////////////////////////////////
/////////////////////////// INICIO PARTE MODIFICABLE

/*Extraer la clave de una celda */
tipoclave _clave_elem(componente *E) {
    return E->lexema;
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

void leer(abb A, componente *E) {
    *E = A->info;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, componente E) {
    return _comparar_claves(cl, _clave_elem(&E));
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

unsigned es_miembro(abb A, componente E) {
    return _es_miembro_clave(A, _clave_elem(&E));
}

int buscar_nodo(abb *A, char *lexema) {
    if (es_vacio(*A)) {
        // insertar(A, lexema, IDENTIFICADOR);
        // return IDENTIFICADOR;
        return 0;
    }

    int comp = strcmp(lexema, (*A)->info.lexema);
    if (comp == 0) {
        return (*A)->info.tipoElemento;
    } else if (comp < 0) {
        return (buscar_nodo(&(*A)->izq, lexema));
    } else {
        return (buscar_nodo(&(*A)->der, lexema));
    }

}
//OPERACIONES DE MODIFICACIÓN

/* Funcion recursiva para insertar un nuevo nodo
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertar(abb *A, char *componenteLexico, int lexema) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof(struct celda));
        (*A)->info.lexema = (char *) malloc(strlen(componenteLexico) + 1 * sizeof(char));
        strcpy((*A)->info.lexema, componenteLexico);
        (*A)->info.lexema[strlen(componenteLexico)] = '\0';
        (*A)->info.tipoElemento = lexema;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }

    int comparacion = strcmp(componenteLexico, (*A)->info.lexema);

    if (comparacion > 0) {
        insertar(&(*A)->der, componenteLexico, lexema);
    } else {
        insertar(&(*A)->izq, componenteLexico, lexema);
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

void _imprimirTabla(abb *A) {
    if (!es_vacio(*A)) {
        if (&(*A)->izq != NULL) {
            _imprimirTabla(&(*A)->izq);
        }

        switch ((*A)->info.tipoElemento) {
            case 400:
                printf("\033[1;33m");
                printf("Lexema: %d\t\t\tComponente léxico: %s\n", (*A)->info.tipoElemento, (*A)->info.lexema);
                printf("\033[0m");
                break;
            default:
                printf("\033[0;32m");
                printf("Lexema: %d\t\t\tComponente léxico: %s\n", (*A)->info.tipoElemento, (*A)->info.lexema);
                printf("\033[0m");
        }
        if (&(*A)->der != NULL) {
            _imprimirTabla(&(*A)->der);
        }
    }
}