#ifndef _LAB3_C_
#define _LAB3_C_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "estructura.h"
#include "funciones.h"


//Función que crea nodo de lista
//Entrada: string representativo a la colonia de bacterias
//Salida: lista con colonia de bacterias
lista *crearNodo(char *coloniaBacteria){

	lista *nueva = (lista*)malloc(sizeof(lista));
	nueva->coloniaBacteria = (char*)malloc(sizeof(char)*30);
	strcpy(nueva->coloniaBacteria,coloniaBacteria);
	nueva->siguiente = NULL;
	return nueva;
}

//Función que inserta un elemento al final de la lista
//Entrada: lista l, colonia de string
//Salida: lista con nuevo elemento
lista *insertarFinal(lista *l,char *colonia){

	lista *nodo = crearNodo(colonia);
	if(l == NULL)
		return nodo;

	lista *indice = l;
	while(indice->siguiente != NULL){
		indice = indice->siguiente;
	}
	indice->siguiente = nodo;
	return l;
}

//Función que borra cada elemento de la lista
//Entrada: lista a borrar
//Salida: lista vacía
lista *anular(lista *l){

	while(l != NULL){
		l = borrar(l);
	}
	return NULL;

}

//Función que borra elemento de la lista
//Entrada: lista con elemento a borrar
//Salida: lista sin elemento
lista *borrar(lista *l){

	if(l != NULL){
		lista *aux = l->siguiente;
		free(l);
		return aux;
	}
	return l;
}

//Función encargada de abrir el archivo entrada.in
//Entrada: nombre archivo
//Salida: archivo
FILE *abrirArchivo(char *nombre_archivo){

	FILE* archivo = NULL;
	archivo = fopen(nombre_archivo,"r");
	if(archivo == NULL){
        printf(" Error: no se ha podido abrir el archivo correctamente \n Verifique si el archivo se encuentra en la misma carpeta de su programa");
        exit(-1);
	}
	return archivo;
}

//Función que lee y guarda colonia inicial
//Entrada: archivo
//Salida: colonia presente en el archivo
char *leerArchivo(FILE *archivo){

	char *coloniaInicial = (char*)malloc(sizeof(char)*30);
	fscanf(archivo,"%s",coloniaInicial);
	fclose(archivo);
	return coloniaInicial;
}

//Función que compara cada bacteria de la colonia
//Entrada: char con el primer elemento, char con el segundo elemento
//Salida: nueva bacteria
char compararColonia(char primera, char segunda){

	if(primera == '1' && segunda == '2')
		return '3';
	if(primera == '2' && segunda == '1')
		return '3';
	if(primera == '1' && segunda == '3')
		return '2';
	if(primera == '3' && segunda == '1')
		return '2';
	if(primera == '2' && segunda == '3')
		return '1';
	if(primera == '3' && segunda == '2')
		return '1';
	return '4';

}

//Función que encuentra menor elemento de la lista
//Entrada: lista con colonias
//Salida: menor colonia
char *encontrarMenor(lista *l){

	char *menor = (char*)malloc(sizeof(char)*30);
	strcpy(menor,l->coloniaBacteria);
	lista *indice = l->siguiente;
	while(indice != NULL){
		if(strcmp(indice->coloniaBacteria,menor) < 0){
			strcpy(menor,indice->coloniaBacteria);
		}
		indice = indice->siguiente;
	}
	return menor;
}

//Función que une las bacterias de la colonia
//Entrada: colonia de bacterias, nueva colonia a agregar, posicion primero, posicion segunda
char *unirBacterias(char *coloniaBacteria,char nuevaColonia, int primero, int segundo){

	char *coloniaBacteriaAux = (char*)malloc(sizeof(char)*30);
	strcpy(coloniaBacteriaAux,coloniaBacteria);
	coloniaBacteriaAux[primero] = nuevaColonia;
	int i;

	for(i = segundo; coloniaBacteriaAux[i] != '\0'; i++){
		coloniaBacteriaAux[i] = coloniaBacteriaAux[i + 1];		
	}

	return coloniaBacteriaAux;
}

//Función que encuentra las colonias con mayor probabilidad de sobrevivencia
//Entrada: colonia inicial
//lista con colonias que sobreviven
lista *modificarColoniasGoloso(char *coloniaInicial){

	if(coloniaInicial == NULL)
		return NULL;

	lista *listaColonias = NULL;
	lista *listaColoniasFinal = NULL;
	listaColonias = insertarFinal(listaColonias,coloniaInicial);
	
	while(listaColonias != NULL){
		char *coloniaAux1 = (char*)malloc(sizeof(char)*30);
		coloniaAux1 = encontrarMenor(listaColonias);
		listaColonias = anular(listaColonias);
		int i;
		for(i = 0; i < strlen(coloniaAux1) - 1; i++){
			char nuevoTipoColonia = compararColonia(coloniaAux1[i],coloniaAux1[i+1]);
			if(nuevoTipoColonia != '4'){ //El valor -4 indica que no se pueden unir
				char *coloniaAux2 = (char*)malloc(sizeof(char)*30);
				coloniaAux2 = unirBacterias(coloniaAux1,nuevoTipoColonia,i,i+1);
				listaColonias = insertarFinal(listaColonias,coloniaAux2);
			}
		}
		listaColoniasFinal = insertarFinal(listaColoniasFinal,coloniaAux1);
	}
	return listaColoniasFinal;
	
}

//Función encargada de mostrar en un archivo la salida
//Entrada: lista con colonias
//Salida:
void escribirSalida(lista *l){

	FILE* archivo = NULL;
	char* nombre = "salida.out";
	archivo = fopen(nombre,"w");
 	if(archivo == NULL)
    	printf("error \n");	
    
	lista *indice = l;
	while(indice != NULL){
		fprintf(archivo,"%s\n",indice->coloniaBacteria );
		indice = indice->siguiente;
	}
}


int main(int argc, char const *argv[]){
	FILE *archivo = abrirArchivo("entrada.in");
	char *colonia = leerArchivo(archivo);
	lista *listaColoniasFinal = modificarColoniasGoloso(colonia);
	escribirSalida(listaColoniasFinal);

	return 0;
}

#endif