#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "playlist.h"

/* Lee texto con espacios */
static void leerTexto(char mensaje[], char destino[], int tamanio){

    printf("%s", mensaje);

    fgets(destino, tamanio, stdin);

    destino[strcspn(destino, "\n")] = '\0';
}

/* Crea una playlist nueva */
Playlist *crearPlaylist(void){

    Playlist *nueva;

    nueva = (Playlist *)malloc(sizeof(Playlist));

    if(nueva == NULL){
        printf("\nNo se pudo reservar memoria para la playlist.\n");
        return NULL;
    }

    printf("\n===== CREAR PLAYLIST =====\n");

    leerTexto("Nombre de la playlist: ", nueva->nombre, MAX_NOMBRE);

    nueva->canciones = NULL;
    nueva->sig = NULL;

    return nueva;
}

/* Agrega una playlist al final de la lista de playlists del usuario */
void agregarPlaylistAUsuario(Usuario *usuario, Playlist *nuevaPlaylist){

    Playlist *actual;

    if(usuario == NULL){
        printf("\nNo hay usuario activo.\n");
        return;
    }

    if(nuevaPlaylist == NULL){
        return;
    }

    if(usuario->playlists == NULL){
        usuario->playlists = nuevaPlaylist;
        printf("\nPlaylist creada correctamente.\n");
        return;
    }

    actual = usuario->playlists;

    while(actual->sig != NULL){
        actual = actual->sig;
    }

    actual->sig = nuevaPlaylist;

    printf("\nPlaylist creada correctamente.\n");
}

/* Busca una playlist por nombre dentro de un usuario */
Playlist *buscarPlaylist(Usuario *usuario, char nombrePlaylist[]){

    Playlist *actual;

    if(usuario == NULL){
        return NULL;
    }

    actual = usuario->playlists;

    while(actual != NULL){

        if(strcmp(actual->nombre, nombrePlaylist) == 0){
            return actual;
        }

        actual = actual->sig;
    }

    return NULL;
}

/* Muestra todas las playlists de un usuario */
void mostrarPlaylists(Usuario *usuario){

    Playlist *actual;
    int contador;

    if(usuario == NULL){
        printf("\nNo hay usuario activo.\n");
        return;
    }

    if(usuario->playlists == NULL){
        printf("\nEl usuario no tiene playlists.\n");
        return;
    }

    actual = usuario->playlists;
    contador = 1;

    printf("\n========== MIS PLAYLISTS ==========\n");

    while(actual != NULL){
        printf("\n%d. %s\n", contador, actual->nombre);

        actual = actual->sig;
        contador++;
    }
}

/* Agrega una cancion a una playlist */
void agregarCancionAPlaylist(Playlist *playlist, Cancion *cancion){

    NodoCancionPlaylist *nuevo;
    NodoCancionPlaylist *actual;

    if(playlist == NULL){
        printf("\nNo hay playlist seleccionada.\n");
        return;
    }

    if(cancion == NULL){
        printf("\nNo hay cancion seleccionada.\n");
        return;
    }

    actual = playlist->canciones;

    while(actual != NULL){

        if(actual->cancion == cancion){
            printf("\nLa cancion ya esta en esta playlist.\n");
            return;
        }

        actual = actual->sig;
    }

    nuevo = (NodoCancionPlaylist *)malloc(sizeof(NodoCancionPlaylist));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para agregar la cancion.\n");
        return;
    }

    nuevo->cancion = cancion;
    nuevo->sig = NULL;

    if(playlist->canciones == NULL){
        playlist->canciones = nuevo;
    }
    else{
        actual = playlist->canciones;

        while(actual->sig != NULL){
            actual = actual->sig;
        }

        actual->sig = nuevo;
    }

    cancion->enPlaylists++;

    printf("\nCancion agregada correctamente a la playlist.\n");
}

/* Quita una cancion de una playlist */
void quitarCancionDePlaylist(Playlist *playlist, char nombreCancion[]){

    NodoCancionPlaylist *actual;
    NodoCancionPlaylist *anterior;

    if(playlist == NULL){
        printf("\nNo hay playlist seleccionada.\n");
        return;
    }

    if(playlist->canciones == NULL){
        printf("\nLa playlist no tiene canciones.\n");
        return;
    }

    actual = playlist->canciones;
    anterior = NULL;

    while(actual != NULL){

        if(strcmp(actual->cancion->nombre, nombreCancion) == 0){

            if(anterior == NULL){
                playlist->canciones = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            actual->cancion->enPlaylists--;

            free(actual);

            printf("\nCancion quitada correctamente de la playlist.\n");
            return;
        }

        anterior = actual;
        actual = actual->sig;
    }

    printf("\nNo se encontro esa cancion en la playlist.\n");
}

/* Muestra las canciones de una playlist */
void mostrarCancionesPlaylist(Playlist *playlist){

    NodoCancionPlaylist *actual;
    int contador;

    if(playlist == NULL){
        printf("\nNo hay playlist seleccionada.\n");
        return;
    }

    if(playlist->canciones == NULL){
        printf("\nLa playlist no tiene canciones.\n");
        return;
    }

    actual = playlist->canciones;
    contador = 1;

    printf("\n========== CANCIONES DE %s ==========\n", playlist->nombre);

    while(actual != NULL){

        printf("\n%d. %s", contador, actual->cancion->nombre);
        printf("\n   Artista: %s", actual->cancion->artista);
        printf("\n   Duracion: %d segundos\n", actual->cancion->duracionSegundos);

        actual = actual->sig;
        contador++;
    }
}