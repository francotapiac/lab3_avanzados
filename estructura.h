#ifndef _ESTRUCTURAS_H
#define _ESTRUCTURAS_H

typedef struct lista lista;
typedef int boolean;
#define true 1
#define false 0


typedef struct lista{

	char *coloniaBacteria;
	struct lista *siguiente;

}lista;

#endif