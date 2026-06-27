#include <stdio.h>
#include <string.h>

#include "menus.h"
#include "usuarios.h"

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

/* Lee texto con espacios usando fgets */
static void leerTexto(char mensaje[], char destino[], int tamanio){

    printf("%s", mensaje);

    fgets(destino, tamanio, stdin);

    /* Quita el salto de linea que deja fgets */
    destino[strcspn(destino, "\n")] = '\0';
}

/* Menu principal del sistema */
void menuPrincipal(Usuario **raizUsuarios){

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
                menuIngresar(raizUsuarios);
                break;

            case 2:
                menuDesarrollador(raizUsuarios);
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
void menuIngresar(Usuario **raizUsuarios){

    int opcion;
    Usuario *nuevo;

    do{
        printf("\n========== INGRESAR ==========\n");
        printf("\n1. Iniciar sesion");
        printf("\n2. Registrarse");
        printf("\n3. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                printf("\nIniciar sesion pendiente de implementar.\n");
                break;

            case 2:
                nuevo = crearUsuario();

                if(nuevo != NULL){
                    insertarUsuario(raizUsuarios, nuevo);
                }

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
void menuDesarrollador(Usuario **raizUsuarios){

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
                menuCRUDUsuarios(raizUsuarios);
                break;

            case 2:
                printf("\nCRUD artistas pendiente de implementar.\n");
                break;

            case 3:
                printf("\nCRUD canciones pendiente de implementar.\n");
                break;

            case 4:
                printf("\nGestionar anuncios pendiente de implementar.\n");
                break;

            case 5:
                printf("\nReportes pendiente de implementar.\n");
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

/* Menu CRUD de usuarios */
void menuCRUDUsuarios(Usuario **raizUsuarios){

    int opcion;
    Usuario *nuevo;
    Usuario *encontrado;
    char correo[MAX_CORREO];

    do{
        printf("\n========== CRUD USUARIOS ==========\n");
        printf("\n1. Crear usuario");
        printf("\n2. Buscar usuario por correo");
        printf("\n3. Mostrar usuarios");
        printf("\n4. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                nuevo = crearUsuario();

                if(nuevo != NULL){
                    insertarUsuario(raizUsuarios, nuevo);
                }

                break;

            case 2:
                leerTexto("\nIngrese el correo a buscar: ", correo, MAX_CORREO);

                encontrado = buscarUsuarioPorCorreo(*raizUsuarios, correo);

                if(encontrado != NULL){
                    printf("\nUsuario encontrado:\n");
                    printf("Correo: %s\n", encontrado->correo);
                    printf("Nombre: %s\n", encontrado->nombre);
                    printf("Pais: %s\n", encontrado->pais);
                    printf("Nickname: %s\n", encontrado->nickname);
                    printf("Plan: %s\n", encontrado->plan);
                }
                else{
                    printf("\nNo existe un usuario con ese correo.\n");
                }

                break;

            case 3:
                if(*raizUsuarios == NULL){
                    printf("\nNo hay usuarios registrados.\n");
                }
                else{
                    printf("\nUsuarios registrados:\n");
                    mostrarUsuariosInorden(*raizUsuarios);
                }

                break;

            case 4:
                printf("\nVolviendo al modo desarrollador...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 4);
}