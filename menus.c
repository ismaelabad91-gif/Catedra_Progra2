#include <stdio.h>
#include "menus.h"

/* Limpia el buffer para evitar errores con scanf */
static void limpiarBuffer(void){

    int c;

    while((c = getchar()) != '\n' && c != EOF){
    }
}

/* Lee una opcion entera y valida si el usuario escribio bien */
int leerOpcion(void){

    int opcion;

    if(scanf("%d", &opcion) != 1){
        limpiarBuffer();
        return -1;
    }

    limpiarBuffer();

    return opcion;
}

/* Menu principal del sistema */
void menuPrincipal(void){

    int opcion;

    do{
        printf("\n===============================\n");
        printf("\n\t S P O T I F Y\n");
        printf("\n===============================\n");

        printf("\n1. Ingresar");
        printf("\n2. Modo desarrollador");
        printf("\n3. Salir");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                menuIngresar();
                break;

            case 2:
                menuDesarrollador();
                break;

            case 3:
                printf("\nHasta luego.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 3);
}

/* Menu para usuario normal */
void menuIngresar(void){

    int opcion;

    do{
        printf("\n========== INGRESAR ==========\n");
        printf("\n1. Iniciar sesion");
        printf("\n2. Registrarse");
        printf("\n3. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                printf("\nIniciar sesion...\n");
                break;

            case 2:
                printf("\nRegistrarse...\n");
                break;

            case 3:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 3);
}

/* Menu para administrador o desarrollador */
void menuDesarrollador(void){

    int opcion;

    do{
        printf("\n====== MODO DESARROLLADOR ======\n");
        printf("\n1. CRUD usuarios");
        printf("\n2. CRUD artistas");
        printf("\n3. CRUD canciones");
        printf("\n4. Gestionar anuncios");
        printf("\n5. Reportes");
        printf("\n6. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                printf("\nCRUD usuarios...\n");
                break;

            case 2:
                printf("\nCRUD artistas...\n");
                break;

            case 3:
                printf("\nCRUD canciones...\n");
                break;

            case 4:
                printf("\nGestionar anuncios...\n");
                break;

            case 5:
                printf("\nReportes...\n");
                break;

            case 6:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 6);
}