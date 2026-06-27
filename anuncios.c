#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "anuncios.h"

/* Inicializa la cola vacia */
void inicializarColaAnuncios(ColaAnuncios *cola){

    cola->frente = NULL;
    cola->final = NULL;
}

/* Verifica si la cola esta vacia */
int colaAnunciosVacia(ColaAnuncios cola){

    if(cola.frente == NULL){
        return 1;
    }

    return 0;
}

/* Agrega un anuncio al final de la cola */
void encolarAnuncio(ColaAnuncios *cola, char contenido[], char anunciante[]){

    Anuncio *nuevo;

    nuevo = (Anuncio *)malloc(sizeof(Anuncio));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para el anuncio.\n");
        return;
    }

    strcpy(nuevo->contenido, contenido);
    strcpy(nuevo->anunciante, anunciante);

    nuevo->sig = NULL;

    if(cola->frente == NULL){
        cola->frente = nuevo;
        cola->final = nuevo;
    }
    else{
        cola->final->sig = nuevo;
        cola->final = nuevo;
    }

    printf("\nAnuncio agregado correctamente.\n");
}

/* Muestra un anuncio y lo vuelve a colocar al final de la cola */
void mostrarAnuncio(ColaAnuncios *cola, Usuario *usuario){

    Anuncio *anuncioMostrado;

    if(cola->frente == NULL){
        printf("\nNo hay anuncios disponibles.\n");
        return;
    }

    anuncioMostrado = cola->frente;

    printf("\n========== ANUNCIO ==========\n");
    printf("Anunciante: %s\n", anuncioMostrado->anunciante);
    printf("Contenido: %s\n", anuncioMostrado->contenido);
    printf("=============================\n");

    if(usuario != NULL){
        usuario->anunciosMostrados++;
    }

    /* Sacamos el anuncio del frente */
    cola->frente = cola->frente->sig;

    if(cola->frente == NULL){
        cola->final = NULL;
    }

    /* Lo volvemos a poner al final para reutilizarlo */
    anuncioMostrado->sig = NULL;

    if(cola->final == NULL){
        cola->frente = anuncioMostrado;
        cola->final = anuncioMostrado;
    }
    else{
        cola->final->sig = anuncioMostrado;
        cola->final = anuncioMostrado;
    }
}

/* Muestra todos los anuncios registrados */
void mostrarColaAnuncios(ColaAnuncios cola){

    Anuncio *actual;
    int contador;

    if(cola.frente == NULL){
        printf("\nNo hay anuncios registrados.\n");
        return;
    }

    actual = cola.frente;
    contador = 1;

    printf("\n========== ANUNCIOS REGISTRADOS ==========\n");

    while(actual != NULL){
        printf("\n%d. Anunciante: %s", contador, actual->anunciante);
        printf("\n   Contenido: %s\n", actual->contenido);

        actual = actual->sig;
        contador++;
    }
}