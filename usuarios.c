#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "usuarios.h"

#define VALOR_PREMIUM 5.00

/* Lee una cadena con espacios */
static void leerCadena(char mensaje[], char destino[], int tamanio){

    printf("%s", mensaje);

    fgets(destino, tamanio, stdin);

    /* Elimina el salto de linea que deja fgets */
    destino[strcspn(destino, "\n")] = '\0';
}

/* Calcula la fecha de vencimiento un mes despues de la fecha actual */
static void calcularFechaPremium(char destino[]){

    time_t tiempoActual;
    struct tm fecha;

    tiempoActual = time(NULL);
    fecha = *localtime(&tiempoActual);

    /* Suma un mes a la fecha actual */
    fecha.tm_mon = fecha.tm_mon + 1;

    /* Ajusta automaticamente el mes y el anio si es necesario */
    mktime(&fecha);

    strftime(destino, MAX_FECHA, "%d/%m/%Y", &fecha);
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

/* Inicia sesion buscando el usuario por correo y comparando contrasena */
int iniciarSesion(Usuario *raiz, char correo[], char contrasena[], Usuario **usuarioActual){

    Usuario *encontrado;

    encontrado = buscarUsuarioPorCorreo(raiz, correo);

    if(encontrado == NULL){
        printf("\nNo existe un usuario con ese correo.\n");
        return 0;
    }

    if(strcmp(encontrado->contrasena, contrasena) != 0){
        printf("\nContrasena incorrecta.\n");
        return 0;
    }

    *usuarioActual = encontrado;

    printf("\nInicio de sesion correcto. Bienvenido, %s.\n", encontrado->nickname);

    return 1;
}

/* Compra el plan premium por primera vez */
void comprarPremium(Usuario *usuario){

    if(usuario == NULL){
        return;
    }

    if(usuario->premiumActivo == 1){
        printf("\nEl usuario ya tiene premium activo.\n");
        printf("Fecha de vencimiento: %s\n", usuario->fechaVencimientoPremium);
        return;
    }

    usuario->premiumActivo = 1;
    strcpy(usuario->plan, "premium");

    usuario->valorPremium = VALOR_PREMIUM;
    calcularFechaPremium(usuario->fechaVencimientoPremium);

    printf("\nPlan premium comprado correctamente.\n");
    printf("Valor: $%.2f\n", usuario->valorPremium);
    printf("Valido hasta: %s\n", usuario->fechaVencimientoPremium);
}

/* Renueva el plan premium */
/* Renueva el plan premium por un mes mas desde la fecha actual */
void renovarPremium(Usuario *usuario){

    if(usuario == NULL){
        return;
    }

    if(usuario->premiumActivo == 0){
        printf("\nEl usuario no tiene premium activo. Primero debe comprar premium.\n");
        return;
    }

    usuario->valorPremium = VALOR_PREMIUM;
    calcularFechaPremium(usuario->fechaVencimientoPremium);

    printf("\nPlan premium renovado correctamente.\n");
    printf("Valor: $%.2f\n", usuario->valorPremium);
    printf("Nueva fecha de vencimiento: %s\n", usuario->fechaVencimientoPremium);
}

/* Libera la memoria de las playlists de un usuario */
static void liberarPlaylistsUsuario(Playlist *playlists){

    Playlist *playlistActual;
    Playlist *playlistEliminar;
    NodoCancionPlaylist *cancionActual;
    NodoCancionPlaylist *cancionEliminar;

    playlistActual = playlists;

    while(playlistActual != NULL){

        cancionActual = playlistActual->canciones;

        while(cancionActual != NULL){

            cancionEliminar = cancionActual;
            cancionActual = cancionActual->sig;

            if(cancionEliminar->cancion != NULL && cancionEliminar->cancion->enPlaylists > 0){
                cancionEliminar->cancion->enPlaylists--;
            }

            free(cancionEliminar);
        }

        playlistEliminar = playlistActual;
        playlistActual = playlistActual->sig;

        free(playlistEliminar);
    }
}

/* Libera la memoria del historial de un usuario */
static void liberarHistorialUsuario(NodoHistorial *historial){

    NodoHistorial *actual;
    NodoHistorial *eliminar;

    actual = historial;

    while(actual != NULL){
        eliminar = actual;
        actual = actual->sig;

        free(eliminar);
    }
}

/* Libera la memoria de la lista de amigos de un usuario */
static void liberarAmigosUsuario(NodoAmigo *amigos){

    NodoAmigo *actual;
    NodoAmigo *eliminar;

    actual = amigos;

    while(actual != NULL){
        eliminar = actual;
        actual = actual->sig;

        free(eliminar);
    }
}

/* Libera solo las estructuras internas del usuario */
static void liberarDatosUsuario(Usuario *usuario){

    if(usuario == NULL){
        return;
    }

    liberarPlaylistsUsuario(usuario->playlists);
    liberarHistorialUsuario(usuario->historial);
    liberarAmigosUsuario(usuario->amigos);

    usuario->playlists = NULL;
    usuario->historial = NULL;
    usuario->amigos = NULL;
}

/* Actualiza datos editables de un usuario */
/* El correo no se cambia porque es la clave del ABB */
void actualizarUsuario(Usuario *usuario){

    char nuevoNombre[MAX_NOMBRE];
    char nuevoPais[MAX_PAIS];
    char nuevoNickname[MAX_NICKNAME];
    char nuevaContrasena[MAX_CONTRASENA];

    if(usuario == NULL){
        printf("\nNo hay usuario seleccionado.\n");
        return;
    }

    printf("\n===== ACTUALIZAR USUARIO =====\n");
    printf("Correo: %s\n", usuario->correo);
    printf("Si no desea cambiar un dato, presione ENTER.\n");

    leerCadena("Nuevo nombre: ", nuevoNombre, MAX_NOMBRE);
    if(strlen(nuevoNombre) > 0){
        strcpy(usuario->nombre, nuevoNombre);
    }

    leerCadena("Nuevo pais: ", nuevoPais, MAX_PAIS);
    if(strlen(nuevoPais) > 0){
        strcpy(usuario->pais, nuevoPais);
    }

    leerCadena("Nuevo nickname: ", nuevoNickname, MAX_NICKNAME);
    if(strlen(nuevoNickname) > 0){
        strcpy(usuario->nickname, nuevoNickname);
    }

    leerCadena("Nueva contrasena: ", nuevaContrasena, MAX_CONTRASENA);
    if(strlen(nuevaContrasena) > 0){
        strcpy(usuario->contrasena, nuevaContrasena);
    }

    printf("\nUsuario actualizado correctamente.\n");
}

/* Extrae el menor nodo de un subarbol */
/* Se usa para eliminar un usuario con dos hijos */
static Usuario *extraerMenorUsuario(Usuario **raiz){

    Usuario *menor;

    if(raiz == NULL || *raiz == NULL){
        return NULL;
    }

    if((*raiz)->izq == NULL){

        menor = *raiz;
        *raiz = (*raiz)->der;

        menor->izq = NULL;
        menor->der = NULL;

        return menor;
    }

    return extraerMenorUsuario(&((*raiz)->izq));
}

/* Elimina un usuario del ABB usando el correo */
void eliminarUsuario(Usuario **raiz, char correo[]){

    int comparacion;
    Usuario *eliminar;
    Usuario *sucesor;

    if(raiz == NULL || *raiz == NULL){
        printf("\nNo se encontro un usuario con ese correo.\n");
        return;
    }

    comparacion = strcmp(correo, (*raiz)->correo);

    if(comparacion < 0){
        eliminarUsuario(&((*raiz)->izq), correo);
    }
    else if(comparacion > 0){
        eliminarUsuario(&((*raiz)->der), correo);
    }
    else{

        eliminar = *raiz;

        /* Caso 1: no tiene hijos */
        if(eliminar->izq == NULL && eliminar->der == NULL){

            *raiz = NULL;

            liberarDatosUsuario(eliminar);
            free(eliminar);

            printf("\nUsuario eliminado correctamente.\n");
        }

        /* Caso 2: solo tiene hijo derecho */
        else if(eliminar->izq == NULL){

            *raiz = eliminar->der;

            liberarDatosUsuario(eliminar);
            free(eliminar);

            printf("\nUsuario eliminado correctamente.\n");
        }

        /* Caso 3: solo tiene hijo izquierdo */
        else if(eliminar->der == NULL){

            *raiz = eliminar->izq;

            liberarDatosUsuario(eliminar);
            free(eliminar);

            printf("\nUsuario eliminado correctamente.\n");
        }

        /* Caso 4: tiene dos hijos */
        else{

            sucesor = extraerMenorUsuario(&(eliminar->der));

            sucesor->izq = eliminar->izq;
            sucesor->der = eliminar->der;

            *raiz = sucesor;

            liberarDatosUsuario(eliminar);
            free(eliminar);

            printf("\nUsuario eliminado correctamente.\n");
        }
    }
}