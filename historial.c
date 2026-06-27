#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "historial.h"

/* Agrega una cancion al inicio del historial */
/* Esto funciona como push en una pila */
void pushHistorial(Usuario *usuario, Cancion *cancion, char fecha[]){

    NodoHistorial *nuevo;

    if(usuario == NULL){
        printf("\nNo hay usuario activo.\n");
        return;
    }

    if(cancion == NULL){
        printf("\nNo se puede agregar una cancion vacia al historial.\n");
        return;
    }

    nuevo = (NodoHistorial *)malloc(sizeof(NodoHistorial));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para el historial.\n");
        return;
    }

    nuevo->cancion = cancion;
    strcpy(nuevo->fecha, fecha);

    nuevo->sig = usuario->historial;
    usuario->historial = nuevo;
}

/* Muestra el historial desde la ultima cancion hasta la primera */
void mostrarHistorial(Usuario *usuario){

    NodoHistorial *actual;
    int contador;

    if(usuario == NULL){
        printf("\nNo hay usuario activo.\n");
        return;
    }

    if(usuario->historial == NULL){
        printf("\nEl historial esta vacio.\n");
        return;
    }

    actual = usuario->historial;
    contador = 1;

    printf("\n========== HISTORIAL ==========\n");

    while(actual != NULL){

        printf("\n%d. %s", contador, actual->cancion->nombre);
        printf("\n   Artista: %s", actual->cancion->artista);
        printf("\n   Fecha: %s\n", actual->fecha);

        actual = actual->sig;
        contador++;
    }
}