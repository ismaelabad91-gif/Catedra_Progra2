#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "persistencia.h"
#include "usuarios.h"
#include "anuncios.h"
#include "artistas.h"
#include "playlist.h"

/* Copia texto de forma segura */
static void copiarTexto(char destino[], char origen[], int tamanio){

    strncpy(destino, origen, tamanio - 1);
    destino[tamanio - 1] = '\0';
}

/* Guarda un usuario en una linea del archivo */
static void guardarUnUsuario(FILE *archivo, Usuario *usuario){

    fprintf(
        archivo,
        "%s|%s|%s|%s|%s|%s|%d|%s|%.2f|%d|%d|%d\n",
        usuario->correo,
        usuario->nombre,
        usuario->pais,
        usuario->nickname,
        usuario->contrasena,
        usuario->plan,
        usuario->premiumActivo,
        usuario->fechaVencimientoPremium,
        usuario->valorPremium,
        usuario->cancionesEscuchadasDesdeAnuncio,
        usuario->anunciosMostrados,
        usuario->tiempoTotalReproduccion
    );
}

/* Recorre el ABB en inorden para guardar todos los usuarios */
static void guardarUsuariosRecursivo(FILE *archivo, Usuario *raiz){

    if(raiz != NULL){
        guardarUsuariosRecursivo(archivo, raiz->izq);
        guardarUnUsuario(archivo, raiz);
        guardarUsuariosRecursivo(archivo, raiz->der);
    }
}

/* Guarda todos los usuarios del ABB en un archivo txt */
void guardarUsuariosEnArchivo(Usuario *raiz, char nombreArchivo[]){

    FILE *archivo;

    archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL){
        printf("\nNo se pudo abrir el archivo de usuarios para guardar.\n");
        return;
    }

    guardarUsuariosRecursivo(archivo, raiz);

    fclose(archivo);

    printf("\nUsuarios guardados correctamente en %s.\n", nombreArchivo);
}

/* Crea un usuario a partir de una linea del archivo */
static Usuario *crearUsuarioDesdeLinea(char linea[]){

    Usuario *nuevo;
    char *campo;

    nuevo = (Usuario *)malloc(sizeof(Usuario));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para cargar usuario.\n");
        return NULL;
    }

    campo = strtok(linea, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->correo, campo, MAX_CORREO);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->nombre, campo, MAX_NOMBRE);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->pais, campo, MAX_PAIS);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->nickname, campo, MAX_NICKNAME);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->contrasena, campo, MAX_CONTRASENA);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->plan, campo, MAX_PLAN);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->premiumActivo = atoi(campo);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    copiarTexto(nuevo->fechaVencimientoPremium, campo, MAX_FECHA);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->valorPremium = atof(campo);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->cancionesEscuchadasDesdeAnuncio = atoi(campo);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->anunciosMostrados = atoi(campo);

    campo = strtok(NULL, "|");
    if(campo == NULL){
        free(nuevo);
        return NULL;
    }
    nuevo->tiempoTotalReproduccion = atoi(campo);

    /* Los punteros no se leen del archivo, se inicializan en NULL */
    nuevo->playlists = NULL;
    nuevo->historial = NULL;
    nuevo->amigos = NULL;

    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

/* Carga usuarios desde un archivo txt y los inserta en el ABB */
void cargarUsuariosDesdeArchivo(Usuario **raiz, char nombreArchivo[]){

    FILE *archivo;
    char linea[500];
    Usuario *nuevo;

    archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL){
        printf("\nNo se encontro %s. Se iniciara sin usuarios guardados.\n", nombreArchivo);
        return;
    }

    while(fgets(linea, sizeof(linea), archivo) != NULL){

        linea[strcspn(linea, "\n")] = '\0';

        if(strlen(linea) > 0){
            nuevo = crearUsuarioDesdeLinea(linea);

            if(nuevo != NULL){
                insertarUsuario(raiz, nuevo);
            }
        }
    }

    fclose(archivo);

    printf("\nUsuarios cargados correctamente desde %s.\n", nombreArchivo);
}

/* Guarda todos los anuncios de la cola en un archivo txt */
void guardarAnunciosEnArchivo(ColaAnuncios cola, char nombreArchivo[]){

    FILE *archivo;
    Anuncio *actual;

    archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL){
        printf("\nNo se pudo abrir el archivo de anuncios para guardar.\n");
        return;
    }

    actual = cola.frente;

    while(actual != NULL){

        fprintf(
            archivo,
            "%s|%s\n",
            actual->contenido,
            actual->anunciante
        );

        actual = actual->sig;
    }

    fclose(archivo);

    printf("\nAnuncios guardados correctamente en %s.\n", nombreArchivo);
}

/* Carga anuncios desde un archivo txt y los inserta en la cola */
void cargarAnunciosDesdeArchivo(ColaAnuncios *cola, char nombreArchivo[]){

    FILE *archivo;
    char linea[400];
    char contenido[MAX_ANUNCIO];
    char anunciante[MAX_ANUNCIANTE];
    char *campo;

    archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL){
        printf("\nNo se encontro %s. Se iniciara sin anuncios guardados.\n", nombreArchivo);
        return;
    }

    while(fgets(linea, sizeof(linea), archivo) != NULL){

        linea[strcspn(linea, "\n")] = '\0';

        if(strlen(linea) > 0){

            campo = strtok(linea, "|");

            if(campo != NULL){
                copiarTexto(contenido, campo, MAX_ANUNCIO);

                campo = strtok(NULL, "|");

                if(campo != NULL){
                    copiarTexto(anunciante, campo, MAX_ANUNCIANTE);

                    encolarAnuncio(cola, contenido, anunciante);
                }
            }
        }
    }

    fclose(archivo);

    printf("\nAnuncios cargados correctamente desde %s.\n", nombreArchivo);
}

/* Crea un artista desde archivo sin pedir datos por teclado */
static Artista *crearArtistaDesdeArchivo(char nombre[]){

    Artista *nuevo;

    nuevo = (Artista *)malloc(sizeof(Artista));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para cargar artista.\n");
        return NULL;
    }

    copiarTexto(nuevo->nombre, nombre, MAX_NOMBRE);

    nuevo->listaDiscos = NULL;

    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

/* Crea un disco desde archivo sin pedir datos por teclado */
static Disco *crearDiscoDesdeArchivo(char nombre[], char fecha[]){

    Disco *nuevo;

    nuevo = (Disco *)malloc(sizeof(Disco));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para cargar disco.\n");
        return NULL;
    }

    copiarTexto(nuevo->nombre, nombre, MAX_NOMBRE);
    copiarTexto(nuevo->fechaLanzamiento, fecha, MAX_FECHA);

    nuevo->listaCanciones = NULL;
    nuevo->sig = NULL;

    return nuevo;
}

/* Crea una cancion desde archivo sin pedir datos por teclado */
static Cancion *crearCancionDesdeArchivo(char artista[], char nombre[], int duracion, char archivoOrigen[], int reproducciones, int enPlaylists){

    Cancion *nueva;

    nueva = (Cancion *)malloc(sizeof(Cancion));

    if(nueva == NULL){
        printf("\nNo se pudo reservar memoria para cargar cancion.\n");
        return NULL;
    }

    copiarTexto(nueva->artista, artista, MAX_NOMBRE);
    copiarTexto(nueva->nombre, nombre, MAX_NOMBRE);
    nueva->duracionSegundos = duracion;
    copiarTexto(nueva->archivoOrigen, archivoOrigen, MAX_ORIGEN);

    nueva->reproducciones = reproducciones;
    nueva->enPlaylists = enPlaylists;

    nueva->sig = NULL;

    return nueva;
}

/* Guarda todas las canciones de un disco */
static void guardarCancionesDisco(FILE *archivo, char nombreArtista[], Disco *disco){

    Cancion *actual;

    actual = disco->listaCanciones;

    while(actual != NULL){

        fprintf(
            archivo,
            "%s|%s|%s|%s|%d|%s|%d|%d\n",
            nombreArtista,
            disco->nombre,
            disco->fechaLanzamiento,
            actual->nombre,
            actual->duracionSegundos,
            actual->archivoOrigen,
            actual->reproducciones,
            actual->enPlaylists
        );

        actual = actual->sig;
    }
}

/* Guarda todos los discos de un artista */
static void guardarDiscosArtista(FILE *archivo, Artista *artista){

    Disco *actual;

    actual = artista->listaDiscos;

    while(actual != NULL){

        guardarCancionesDisco(archivo, artista->nombre, actual);

        actual = actual->sig;
    }
}

/* Recorre el ABB de artistas para guardar todo */
static void guardarArtistasRecursivo(FILE *archivo, Artista *raiz){

    if(raiz != NULL){

        guardarArtistasRecursivo(archivo, raiz->izq);

        guardarDiscosArtista(archivo, raiz);

        guardarArtistasRecursivo(archivo, raiz->der);
    }
}

/* Guarda artistas, discos y canciones en archivo txt */
void guardarArtistasEnArchivo(Artista *raiz, char nombreArchivo[]){

    FILE *archivo;

    archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL){
        printf("\nNo se pudo abrir el archivo de artistas para guardar.\n");
        return;
    }

    guardarArtistasRecursivo(archivo, raiz);

    fclose(archivo);

    printf("\nArtistas guardados correctamente en %s.\n", nombreArchivo);
}

/* Carga una linea del archivo de artistas */
static void cargarLineaArtista(Artista **raiz, char linea[]){

    char *campo;

    char nombreArtista[MAX_NOMBRE];
    char nombreDisco[MAX_NOMBRE];
    char fechaDisco[MAX_FECHA];
    char nombreCancion[MAX_NOMBRE];
    char archivoOrigen[MAX_ORIGEN];

    int duracion;
    int reproducciones;
    int enPlaylists;

    Artista *artistaEncontrado;
    Disco *discoEncontrado;
    Cancion *cancionNueva;

    campo = strtok(linea, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(nombreArtista, campo, MAX_NOMBRE);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(nombreDisco, campo, MAX_NOMBRE);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(fechaDisco, campo, MAX_FECHA);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(nombreCancion, campo, MAX_NOMBRE);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    duracion = atoi(campo);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(archivoOrigen, campo, MAX_ORIGEN);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    reproducciones = atoi(campo);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    enPlaylists = atoi(campo);

    artistaEncontrado = buscarArtista(*raiz, nombreArtista);

    if(artistaEncontrado == NULL){

        artistaEncontrado = crearArtistaDesdeArchivo(nombreArtista);

        if(artistaEncontrado == NULL){
            return;
        }

        insertarArtista(raiz, artistaEncontrado);
    }

    discoEncontrado = buscarDisco(artistaEncontrado, nombreDisco);

    if(discoEncontrado == NULL){

        discoEncontrado = crearDiscoDesdeArchivo(nombreDisco, fechaDisco);

        if(discoEncontrado == NULL){
            return;
        }

        agregarDiscoAArtista(artistaEncontrado, discoEncontrado);
    }

    cancionNueva = crearCancionDesdeArchivo(
        nombreArtista,
        nombreCancion,
        duracion,
        archivoOrigen,
        reproducciones,
        0
    );

    if(cancionNueva != NULL){
        agregarCancionADisco(discoEncontrado, cancionNueva);
    }
}

/* Carga artistas, discos y canciones desde archivo txt */
void cargarArtistasDesdeArchivo(Artista **raiz, char nombreArchivo[]){

    FILE *archivo;
    char linea[600];

    archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL){
        printf("\nNo se encontro %s. Se iniciara sin artistas guardados.\n", nombreArchivo);
        return;
    }

    while(fgets(linea, sizeof(linea), archivo) != NULL){

        linea[strcspn(linea, "\n")] = '\0';

        if(strlen(linea) > 0){
            cargarLineaArtista(raiz, linea);
        }
    }

    fclose(archivo);

    printf("\nArtistas cargados correctamente desde %s.\n", nombreArchivo);
}

/* Guarda las canciones de una playlist */
static void guardarUnaPlaylist(FILE *archivo, char correoUsuario[], Playlist *playlist){

    NodoCancionPlaylist *actual;

    if(playlist->canciones == NULL){

        fprintf(
            archivo,
            "%s|%s|VACIO|VACIO\n",
            correoUsuario,
            playlist->nombre
        );

        return;
    }

    actual = playlist->canciones;

    while(actual != NULL){

        fprintf(
            archivo,
            "%s|%s|%s|%s\n",
            correoUsuario,
            playlist->nombre,
            actual->cancion->artista,
            actual->cancion->nombre
        );

        actual = actual->sig;
    }
}

/* Guarda todas las playlists de un usuario */
static void guardarPlaylistsUsuario(FILE *archivo, Usuario *usuario){

    Playlist *actual;

    actual = usuario->playlists;

    while(actual != NULL){

        guardarUnaPlaylist(archivo, usuario->correo, actual);

        actual = actual->sig;
    }
}

/* Recorre el ABB de usuarios para guardar playlists */
static void guardarPlaylistsRecursivo(FILE *archivo, Usuario *raizUsuarios){

    if(raizUsuarios != NULL){

        guardarPlaylistsRecursivo(archivo, raizUsuarios->izq);

        guardarPlaylistsUsuario(archivo, raizUsuarios);

        guardarPlaylistsRecursivo(archivo, raizUsuarios->der);
    }
}

/* Guarda todas las playlists en un archivo txt */
void guardarPlaylistsEnArchivo(Usuario *raizUsuarios, char nombreArchivo[]){

    FILE *archivo;

    archivo = fopen(nombreArchivo, "w");

    if(archivo == NULL){
        printf("\nNo se pudo abrir el archivo de playlists para guardar.\n");
        return;
    }

    guardarPlaylistsRecursivo(archivo, raizUsuarios);

    fclose(archivo);

    printf("\nPlaylists guardadas correctamente en %s.\n", nombreArchivo);
}

/* Crea una playlist desde archivo sin pedir datos por teclado */
static Playlist *crearPlaylistDesdeArchivo(char nombrePlaylist[]){

    Playlist *nueva;

    nueva = (Playlist *)malloc(sizeof(Playlist));

    if(nueva == NULL){
        printf("\nNo se pudo reservar memoria para cargar playlist.\n");
        return NULL;
    }

    copiarTexto(nueva->nombre, nombrePlaylist, MAX_NOMBRE);

    nueva->canciones = NULL;
    nueva->sig = NULL;

    return nueva;
}

/* Carga una linea del archivo playlists.txt */
static void cargarLineaPlaylist(Usuario *raizUsuarios, Artista *raizArtistas, char linea[]){

    char *campo;

    char correoUsuario[MAX_CORREO];
    char nombrePlaylist[MAX_NOMBRE];
    char nombreArtista[MAX_NOMBRE];
    char nombreCancion[MAX_NOMBRE];

    Usuario *usuarioEncontrado;
    Playlist *playlistEncontrada;
    Playlist *nuevaPlaylist;
    Cancion *cancionEncontrada;

    campo = strtok(linea, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(correoUsuario, campo, MAX_CORREO);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(nombrePlaylist, campo, MAX_NOMBRE);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(nombreArtista, campo, MAX_NOMBRE);

    campo = strtok(NULL, "|");

    if(campo == NULL){
        return;
    }
    copiarTexto(nombreCancion, campo, MAX_NOMBRE);

    usuarioEncontrado = buscarUsuarioPorCorreo(raizUsuarios, correoUsuario);

    if(usuarioEncontrado == NULL){
        return;
    }

    playlistEncontrada = buscarPlaylist(usuarioEncontrado, nombrePlaylist);

    if(playlistEncontrada == NULL){

        nuevaPlaylist = crearPlaylistDesdeArchivo(nombrePlaylist);

        if(nuevaPlaylist == NULL){
            return;
        }

        agregarPlaylistAUsuario(usuarioEncontrado, nuevaPlaylist);

        playlistEncontrada = nuevaPlaylist;
    }

    if(strcmp(nombreArtista, "VACIO") == 0 && strcmp(nombreCancion, "VACIO") == 0){
        return;
    }

    cancionEncontrada = buscarCancionPorArtistaYNombre(raizArtistas, nombreArtista, nombreCancion);

    if(cancionEncontrada == NULL){
        return;
    }

    agregarCancionAPlaylist(playlistEncontrada, cancionEncontrada);
}

/* Carga playlists desde archivo txt */
void cargarPlaylistsDesdeArchivo(Usuario *raizUsuarios, Artista *raizArtistas, char nombreArchivo[]){

    FILE *archivo;
    char linea[500];

    archivo = fopen(nombreArchivo, "r");

    if(archivo == NULL){
        printf("\nNo se encontro %s. Se iniciara sin playlists guardadas.\n", nombreArchivo);
        return;
    }

    while(fgets(linea, sizeof(linea), archivo) != NULL){

        linea[strcspn(linea, "\n")] = '\0';

        if(strlen(linea) > 0){
            cargarLineaPlaylist(raizUsuarios, raizArtistas, linea);
        }
    }

    fclose(archivo);

    printf("\nPlaylists cargadas correctamente desde %s.\n", nombreArchivo);
}