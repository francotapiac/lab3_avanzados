#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_
#include "estructura.h"

FILE *abrirArchivo(char *nombre_archivo);
char *leerArchivo(FILE *archivo);

lista *crearNodo(char *coloniaBacteria);
int largo(lista *l);
lista *insertarFinal(lista *l,char *colonia);
lista *anular(lista *l);
lista *borrar(lista *l);

char compararColonia(char primera, char segunda);
char *unirBacterias(char *coloniaBacteria,char nuevaColonia, int primero, int segundo);
lista *modificarColoniasGoloso(char *coloniaInicial);
void escribirSalida(lista *l);


#endif