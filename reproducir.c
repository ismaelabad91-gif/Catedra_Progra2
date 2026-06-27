#include <stdio.h>
#include <string.h>
#include <time.h>

#include "reproducir.h"
#include "historial.h"
#include "anuncios.h"

/* Cantidad maxima de lineas que se mostraran del archivo txt */
#define MAX_LINEAS_KARAOKE 20

/* Obtiene la fecha actual en formato dd/mm/aaaa */
static void obtenerFechaActual(char fecha[]){

    time_t tiempoActual;
    struct tm *infoFecha;

    tiempoActual = time(NULL);
    infoFecha = localtime(&tiempoActual);

    strftime(fecha, MAX_FECHA, "%d/%m/%Y", infoFecha);
}

/* Muestra las primeras lineas del archivo txt de la cancion */
static void mostrarArchivoCancion(char archivoOrigen[]){

    FILE *archivo;
    char linea[200];
    int contadorLineas;

    archivo = fopen(archivoOrigen, "r");

    if(archivo == NULL){
        printf("\nNo se pudo abrir el archivo de la cancion: %s\n", archivoOrigen);
        printf("La reproduccion continuara sin mostrar letra.\n");
        return;
    }

    printf("\n========== LETRA / KARAOKE ==========\n");

    contadorLineas = 0;

    while(fgets(linea, sizeof(linea), archivo) != NULL && contadorLineas < MAX_LINEAS_KARAOKE){
        printf("%s", linea);
        contadorLineas++;
    }

    if(contadorLineas == MAX_LINEAS_KARAOKE){
        printf("\n... Se muestran solo las primeras %d lineas ...\n", MAX_LINEAS_KARAOKE);
    }

    fclose(archivo);
}

/* Simula la reproduccion de una cancion */
void reproducirCancion(Usuario *usuario, Cancion *cancion, ColaAnuncios *colaAnuncios){

    char fecha[MAX_FECHA];

    if(usuario == NULL){
        printf("\nNo hay usuario activo.\n");
        return;
    }

    if(cancion == NULL){
        printf("\nNo hay cancion seleccionada.\n");
        return;
    }

    printf("\n========== REPRODUCIENDO ==========\n");
    printf("Cancion: %s\n", cancion->nombre);
    printf("Artista: %s\n", cancion->artista);
    printf("Duracion: %d segundos\n", cancion->duracionSegundos);
    printf("Archivo: %s\n", cancion->archivoOrigen);

    mostrarArchivoCancion(cancion->archivoOrigen);

    obtenerFechaActual(fecha);

    pushHistorial(usuario, cancion, fecha);

    cancion->reproducciones++;
    usuario->tiempoTotalReproduccion += cancion->duracionSegundos;

    printf("\nCancion agregada al historial.\n");
    printf("Reproducciones de esta cancion: %d\n", cancion->reproducciones);
    printf("Tiempo total reproducido por el usuario: %d segundos\n", usuario->tiempoTotalReproduccion);

    if(usuario->premiumActivo == 0){

        usuario->cancionesEscuchadasDesdeAnuncio++;

        printf("\nCanciones escuchadas desde el ultimo anuncio: %d/3\n", usuario->cancionesEscuchadasDesdeAnuncio);

        if(usuario->cancionesEscuchadasDesdeAnuncio >= 3){

            printf("\nComo el usuario tiene plan free, corresponde mostrar un anuncio.\n");

            mostrarAnuncio(colaAnuncios, usuario);

            usuario->cancionesEscuchadasDesdeAnuncio = 0;
        }
    }
    else{
        printf("\nUsuario premium: reproduccion sin anuncios.\n");
    }
}