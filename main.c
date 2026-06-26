#include <stdio.h>
#include <stdlib.h>

#include "menus.h"

void limpiarBuffer();

int main(){

    int opcion;

    do{

        opcion = menuPrincipal();

        switch(opcion){

            case 1:
                printf("\nIngresar...\n");
                break;

            case 2:
                printf("\nModo desarrollador...\n");
                break;

            case 3:
                printf("\nHasta luego.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
        }

    }while(opcion != 3);

    return 0;
}

void limpiarBuffer(){

    int c;

    while((c = getchar()) != '\n' && c != EOF);

}