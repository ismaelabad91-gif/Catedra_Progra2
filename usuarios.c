#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "usuarios.h"

/* Lee una cadena con espacios */
static void leerCadena(char mensaje[], char destino[], int tamanio){

    printf("%s", mensaje);

    fgets(destino, tamanio, stdin);

    /* Elimina el salto de linea que deja fgets */
    destino[strcspn(destino, "\n")] = '\0';
}

/* Crea un usuario nuevo reservando memoria con malloc */
Usuario *crearUsuario(void){

    Usuario *nuevo;

    nuevo = (Usuario *)malloc(sizeof(Usuario));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para el usuario.\n");
        return NULL;
    }

    printf("\n===== CREAR USUARIO =====\n");

    leerCadena("Correo electronico: ", nuevo->correo, MAX_CORREO);
    leerCadena("Nombre: ", nuevo->nombre, MAX_NOMBRE);
    leerCadena("Pais de origen: ", nuevo->pais, MAX_PAIS);
    leerCadena("Nickname: ", nuevo->nickname, MAX_NICKNAME);
    leerCadena("Contrasena: ", nuevo->contrasena, MAX_CONTRASENA);

    /* Por defecto, todo usuario nuevo empieza con plan free */
    strcpy(nuevo->plan, "free");

    nuevo->premiumActivo = 0;
    strcpy(nuevo->fechaVencimientoPremium, "N/A");
    nuevo->valorPremium = 0;

    nuevo->cancionesEscuchadasDesdeAnuncio = 0;
    nuevo->anunciosMostrados = 0;
    nuevo->tiempoTotalReproduccion = 0;

    nuevo->playlists = NULL;
    nuevo->historial = NULL;
    nuevo->amigos = NULL;

    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

/* Inserta un usuario en el ABB usando el correo como criterio */
void insertarUsuario(Usuario **raiz, Usuario *nuevo){

    int comparacion;

    if(nuevo == NULL){
        return;
    }

    if(*raiz == NULL){
        *raiz = nuevo;
        printf("\nUsuario registrado correctamente.\n");
        return;
    }

    comparacion = strcmp(nuevo->correo, (*raiz)->correo);

    if(comparacion < 0){
        insertarUsuario(&((*raiz)->izq), nuevo);
    }
    else if(comparacion > 0){
        insertarUsuario(&((*raiz)->der), nuevo);
    }
    else{
        printf("\nERROR: Ya existe un usuario con ese correo.\n");
        free(nuevo);
    }
}

/* Busca un usuario en el ABB usando el correo */
Usuario *buscarUsuarioPorCorreo(Usuario *raiz, char correo[]){

    int comparacion;

    if(raiz == NULL){
        return NULL;
    }

    comparacion = strcmp(correo, raiz->correo);

    if(comparacion == 0){
        return raiz;
    }
    else if(comparacion < 0){
        return buscarUsuarioPorCorreo(raiz->izq, correo);
    }
    else{
        return buscarUsuarioPorCorreo(raiz->der, correo);
    }
}

/* Muestra los usuarios ordenados por correo */
void mostrarUsuariosInorden(Usuario *raiz){

    if(raiz != NULL){

        mostrarUsuariosInorden(raiz->izq);

        printf("\n------------------------------\n");
        printf("Correo: %s\n", raiz->correo);
        printf("Nombre: %s\n", raiz->nombre);
        printf("Pais: %s\n", raiz->pais);
        printf("Nickname: %s\n", raiz->nickname);
        printf("Plan: %s\n", raiz->plan);

        mostrarUsuariosInorden(raiz->der);
    }
}