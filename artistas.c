#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "artistas.h"

/* Limpia el buffer para evitar errores con scanf */
static void limpiarBuffer(void){

    int c;

    while((c = getchar()) != '\n' && c != EOF){
    }
}

/* Lee texto con espacios */
static void leerTexto(char mensaje[], char destino[], int tamanio){

    printf("%s", mensaje);

    fgets(destino, tamanio, stdin);

    destino[strcspn(destino, "\n")] = '\0';
}

/* Crea un artista nuevo */
Artista *crearArtista(void){

    Artista *nuevo;

    nuevo = (Artista *)malloc(sizeof(Artista));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para el artista.\n");
        return NULL;
    }

    printf("\n===== CREAR ARTISTA =====\n");

    leerTexto("Nombre del artista: ", nuevo->nombre, MAX_NOMBRE);

    nuevo->listaDiscos = NULL;

    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

/* Inserta un artista en el ABB usando el nombre como criterio */
void insertarArtista(Artista **raiz, Artista *nuevo){

    int comparacion;

    if(nuevo == NULL){
        return;
    }

    if(*raiz == NULL){
        *raiz = nuevo;
        printf("\nArtista registrado correctamente.\n");
        return;
    }

    comparacion = strcmp(nuevo->nombre, (*raiz)->nombre);

    if(comparacion < 0){
        insertarArtista(&((*raiz)->izq), nuevo);
    }
    else if(comparacion > 0){
        insertarArtista(&((*raiz)->der), nuevo);
    }
    else{
        printf("\nERROR: Ya existe un artista con ese nombre.\n");
        free(nuevo);
    }
}

/* Busca un artista en el ABB por nombre */
Artista *buscarArtista(Artista *raiz, char nombre[]){

    int comparacion;

    if(raiz == NULL){
        return NULL;
    }

    comparacion = strcmp(nombre, raiz->nombre);

    if(comparacion == 0){
        return raiz;
    }
    else if(comparacion < 0){
        return buscarArtista(raiz->izq, nombre);
    }
    else{
        return buscarArtista(raiz->der, nombre);
    }
}

/* Muestra los artistas ordenados por nombre */
void mostrarArtistasInorden(Artista *raiz){

    if(raiz != NULL){

        mostrarArtistasInorden(raiz->izq);

        printf("\n------------------------------\n");
        printf("Artista: %s\n", raiz->nombre);

        if(raiz->listaDiscos == NULL){
            printf("Discos: No tiene discos registrados\n");
        }
        else{
            mostrarDiscosArtista(raiz);
        }

        mostrarArtistasInorden(raiz->der);
    }
}

/* Crea un disco nuevo */
Disco *crearDisco(void){

    Disco *nuevo;

    nuevo = (Disco *)malloc(sizeof(Disco));

    if(nuevo == NULL){
        printf("\nNo se pudo reservar memoria para el disco.\n");
        return NULL;
    }

    printf("\n===== CREAR DISCO =====\n");

    leerTexto("Nombre del disco: ", nuevo->nombre, MAX_NOMBRE);
    leerTexto("Fecha de lanzamiento, formato dd/mm/aaaa: ", nuevo->fechaLanzamiento, MAX_FECHA);

    nuevo->listaCanciones = NULL;
    nuevo->sig = NULL;

    return nuevo;
}

/* Agrega un disco al final de la lista de discos del artista */
void agregarDiscoAArtista(Artista *artista, Disco *nuevoDisco){

    Disco *actual;

    if(artista == NULL){
        printf("\nNo hay artista seleccionado.\n");
        return;
    }

    if(nuevoDisco == NULL){
        return;
    }

    if(artista->listaDiscos == NULL){
        artista->listaDiscos = nuevoDisco;
        printf("\nDisco agregado correctamente al artista.\n");
        return;
    }

    actual = artista->listaDiscos;

    while(actual->sig != NULL){
        actual = actual->sig;
    }

    actual->sig = nuevoDisco;

    printf("\nDisco agregado correctamente al artista.\n");
}

/* Busca un disco dentro de la lista de discos de un artista */
Disco *buscarDisco(Artista *artista, char nombreDisco[]){

    Disco *actual;

    if(artista == NULL){
        return NULL;
    }

    actual = artista->listaDiscos;

    while(actual != NULL){

        if(strcmp(actual->nombre, nombreDisco) == 0){
            return actual;
        }

        actual = actual->sig;
    }

    return NULL;
}

/* Muestra los discos de un artista */
void mostrarDiscosArtista(Artista *artista){

    Disco *actual;
    int contador;

    if(artista == NULL){
        printf("\nNo hay artista seleccionado.\n");
        return;
    }

    if(artista->listaDiscos == NULL){
        printf("\nEl artista no tiene discos registrados.\n");
        return;
    }

    actual = artista->listaDiscos;
    contador = 1;

    printf("\nDiscos de %s:\n", artista->nombre);

    while(actual != NULL){

        printf("\n%d. %s", contador, actual->nombre);
        printf("\n   Fecha: %s\n", actual->fechaLanzamiento);

        actual = actual->sig;
        contador++;
    }
}

/* Crea una cancion nueva */
Cancion *crearCancion(char nombreArtista[]){

    Cancion *nueva;

    nueva = (Cancion *)malloc(sizeof(Cancion));

    if(nueva == NULL){
        printf("\nNo se pudo reservar memoria para la cancion.\n");
        return NULL;
    }

    printf("\n===== CREAR CANCION =====\n");

    strcpy(nueva->artista, nombreArtista);

    leerTexto("Nombre de la cancion: ", nueva->nombre, MAX_NOMBRE);

    printf("Duracion en segundos: ");
    if(scanf("%d", &(nueva->duracionSegundos)) != 1){
        limpiarBuffer();
        printf("\nDuracion invalida. Se guardara como 0 segundos.\n");
        nueva->duracionSegundos = 0;
    }
    else{
        limpiarBuffer();
    }

    leerTexto("Archivo de origen, ejemplo canciones/yellow.txt: ", nueva->archivoOrigen, MAX_ORIGEN);

    nueva->reproducciones = 0;
    nueva->enPlaylists = 0;
    nueva->sig = NULL;

    return nueva;
}

/* Agrega una cancion al final de la lista de canciones de un disco */
void agregarCancionADisco(Disco *disco, Cancion *nuevaCancion){

    Cancion *actual;

    if(disco == NULL){
        printf("\nNo hay disco seleccionado.\n");
        return;
    }

    if(nuevaCancion == NULL){
        return;
    }

    if(disco->listaCanciones == NULL){
        disco->listaCanciones = nuevaCancion;
        printf("\nCancion agregada correctamente al disco.\n");
        return;
    }

    actual = disco->listaCanciones;

    while(actual->sig != NULL){
        actual = actual->sig;
    }

    actual->sig = nuevaCancion;

    printf("\nCancion agregada correctamente al disco.\n");
}

/* Busca una cancion dentro de un disco */
Cancion *buscarCancionEnDisco(Disco *disco, char nombreCancion[]){

    Cancion *actual;

    if(disco == NULL){
        return NULL;
    }

    actual = disco->listaCanciones;

    while(actual != NULL){

        if(strcmp(actual->nombre, nombreCancion) == 0){
            return actual;
        }

        actual = actual->sig;
    }

    return NULL;
}

/* Busca una cancion dentro de todos los discos de un artista */
static Cancion *buscarCancionEnListaDiscos(Disco *listaDiscos, char nombreCancion[]){

    Disco *discoActual;
    Cancion *encontrada;

    discoActual = listaDiscos;

    while(discoActual != NULL){

        encontrada = buscarCancionEnDisco(discoActual, nombreCancion);

        if(encontrada != NULL){
            return encontrada;
        }

        discoActual = discoActual->sig;
    }

    return NULL;
}

/* Busca una cancion recorriendo todo el ABB de artistas */
Cancion *buscarCancionEnArtistas(Artista *raiz, char nombreCancion[]){

    Cancion *encontrada;

    if(raiz == NULL){
        return NULL;
    }

    encontrada = buscarCancionEnListaDiscos(raiz->listaDiscos, nombreCancion);

    if(encontrada != NULL){
        return encontrada;
    }

    encontrada = buscarCancionEnArtistas(raiz->izq, nombreCancion);

    if(encontrada != NULL){
        return encontrada;
    }

    return buscarCancionEnArtistas(raiz->der, nombreCancion);
}

/* Muestra las canciones de un disco */
void mostrarCancionesDisco(Disco *disco){

    Cancion *actual;
    int contador;

    if(disco == NULL){
        printf("\nNo hay disco seleccionado.\n");
        return;
    }

    if(disco->listaCanciones == NULL){
        printf("\nEl disco no tiene canciones registradas.\n");
        return;
    }

    actual = disco->listaCanciones;
    contador = 1;

    printf("\nCanciones del disco %s:\n", disco->nombre);

    while(actual != NULL){

        printf("\n%d. %s", contador, actual->nombre);
        printf("\n   Artista: %s", actual->artista);
        printf("\n   Duracion: %d segundos", actual->duracionSegundos);
        printf("\n   Archivo: %s", actual->archivoOrigen);
        printf("\n   Reproducciones: %d", actual->reproducciones);
        printf("\n   En playlists: %d\n", actual->enPlaylists);

        actual = actual->sig;
        contador++;
    }
}

/* Busca una cancion usando el nombre del artista y el nombre de la cancion */
Cancion *buscarCancionPorArtistaYNombre(Artista *raiz, char nombreArtista[], char nombreCancion[]){

    Artista *artistaEncontrado;
    Disco *discoActual;
    Cancion *cancionActual;

    artistaEncontrado = buscarArtista(raiz, nombreArtista);

    if(artistaEncontrado == NULL){
        return NULL;
    }

    discoActual = artistaEncontrado->listaDiscos;

    while(discoActual != NULL){

        cancionActual = discoActual->listaCanciones;

        while(cancionActual != NULL){

            if(strcmp(cancionActual->nombre, nombreCancion) == 0){
                return cancionActual;
            }

            cancionActual = cancionActual->sig;
        }

        discoActual = discoActual->sig;
    }

    return NULL;
}

/* Actualiza datos editables de una cancion */
void actualizarCancion(Cancion *cancion){

    char nuevoNombre[MAX_NOMBRE];
    char nuevoArchivo[MAX_ORIGEN];
    int nuevaDuracion;

    if(cancion == NULL){
        printf("\nNo hay cancion seleccionada.\n");
        return;
    }

    printf("\n===== ACTUALIZAR CANCION =====\n");
    printf("Cancion actual: %s\n", cancion->nombre);
    printf("Artista: %s\n", cancion->artista);
    printf("Si no desea cambiar texto, presione ENTER.\n");

    leerTexto("Nuevo nombre de la cancion: ", nuevoNombre, MAX_NOMBRE);

    if(strlen(nuevoNombre) > 0){
        strcpy(cancion->nombre, nuevoNombre);
    }

    printf("Nueva duracion en segundos, escriba 0 para no cambiar: ");

    if(scanf("%d", &nuevaDuracion) != 1){
        limpiarBuffer();
        printf("\nDuracion invalida. No se cambio la duracion.\n");
    }
    else{
        limpiarBuffer();

        if(nuevaDuracion > 0){
            cancion->duracionSegundos = nuevaDuracion;
        }
    }

    leerTexto("Nuevo archivo de origen: ", nuevoArchivo, MAX_ORIGEN);

    if(strlen(nuevoArchivo) > 0){
        strcpy(cancion->archivoOrigen, nuevoArchivo);
    }

    printf("\nCancion actualizada correctamente.\n");
}

/* Elimina una cancion de un disco si no pertenece a playlists */
/* Retorna 1 si elimina, 0 si no elimina */
int eliminarCancionDeDisco(Disco *disco, char nombreCancion[]){

    Cancion *actual;
    Cancion *anterior;

    if(disco == NULL){
        printf("\nNo hay disco seleccionado.\n");
        return 0;
    }

    if(disco->listaCanciones == NULL){
        printf("\nEl disco no tiene canciones.\n");
        return 0;
    }

    actual = disco->listaCanciones;
    anterior = NULL;

    while(actual != NULL){

        if(strcmp(actual->nombre, nombreCancion) == 0){

            if(actual->enPlaylists > 0){
                printf("\nNo se puede eliminar la cancion porque pertenece a una playlist.\n");
                printf("Cantidad de playlists donde aparece: %d\n", actual->enPlaylists);
                return 0;
            }

            if(anterior == NULL){
                disco->listaCanciones = actual->sig;
            }
            else{
                anterior->sig = actual->sig;
            }

            free(actual);

            printf("\nCancion eliminada correctamente.\n");
            return 1;
        }

        anterior = actual;
        actual = actual->sig;
    }

    printf("\nNo se encontro esa cancion en el disco.\n");
    return 0;
}