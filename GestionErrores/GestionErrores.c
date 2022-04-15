#include <stdio.h>

/**
 * función que se encargará de imprimir los errores que se puedan producir detectar en el análisis del código
 * @param codigo identificador del código del error. Cada tipo de error tendrá su propio código de error
 * @param descripcion texto que describirá el error para que el usuario tenga una constancia sobre el mismo
 */
void imprimirError(int codigo, int numeroLinea){
    printf("\033[0;31m");
    switch (codigo) {
        case 400:
            printf("[%d]: Línea %d --> Composición de número incorrecta", codigo, numeroLinea);
            break;
    }
    printf("\033[0m");
}