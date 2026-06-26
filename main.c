#include <stdio.h>
#include "menus.h"

int main(void){

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
                break;
        }

    }while(opcion != 3);

    return 0;
}