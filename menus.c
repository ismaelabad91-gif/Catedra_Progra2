#include <stdio.h>
#include "menus.h"

/* Limpia el buffer para evitar errores con scanf */
static void limpiarBuffer(void){ //el static significa que esta funcion solo se puede usar dentro de esr=te archivo

    int c;

    while((c = getchar()) != '\n' && c != EOF){
    }
}

int menuPrincipal(void){

    int opcion;

    printf("\n===============================\n");
    printf("\n\t S P O T I F Y\n");
    printf("\n===============================\n");

    printf("\n1. Ingresar");
    printf("\n2. Modo desarrollador");
    printf("\n3. Salir");

    printf("\n\nSeleccione una opcion: ");

    if(scanf("%d", &opcion) != 1){
        limpiarBuffer();
        return -1;
    }

    limpiarBuffer();

    return opcion;
}