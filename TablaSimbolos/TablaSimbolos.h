#include "../ABB/abb.h"

void inicializarTabla();

void insertarEnTabla(char *componente, float valor, int tipo);

void imprimirTabla();

float obtenerValor(char *componentelex);

int obtenerTipo(char *componentelex);

void eliminarEspacioTrabajo();

void imprimirEspacioTrabajo();

void actualizarValorVariable(char *componentelex, float valor);

double insertaFuncion(char *componentelex, float valor);

double ejecutarFuncion(char *componentelex, float valor);

void destruirTabla();