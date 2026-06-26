#include <stdio.h>
#include "menus.h"

int menuPrincipal(){

    int opcion;

    printf("===============================\n");
    printf("\n\t S P O T I F Y\n");
    printf("\n===============================\n");

    printf("\n1. Ingresar");
    printf("\n2. Modo desarrollador");
    printf("\n3. Salir");

    printf("\n\nSeleccione una opcion: ");
    scanf("%d", &opcion);

    return opcion;
}