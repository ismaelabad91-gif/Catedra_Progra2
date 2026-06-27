#ifndef ARTISTAS_H
#define ARTISTAS_H

#include "estructuras.h"

/* Funciones para el ABB de artistas */
Artista *crearArtista(void);
void insertarArtista(Artista **raiz, Artista *nuevo);
Artista *buscarArtista(Artista *raiz, char nombre[]);
void mostrarArtistasInorden(Artista *raiz);

/* Funciones para discos */
Disco *crearDisco(void);
void agregarDiscoAArtista(Artista *artista, Disco *nuevoDisco);
Disco *buscarDisco(Artista *artista, char nombreDisco[]);
void mostrarDiscosArtista(Artista *artista);

/* Funciones para canciones */
Cancion *crearCancion(char nombreArtista[]);
void agregarCancionADisco(Disco *disco, Cancion *nuevaCancion);
Cancion *buscarCancionEnDisco(Disco *disco, char nombreCancion[]);
Cancion *buscarCancionEnArtistas(Artista *raiz, char nombreCancion[]);
void mostrarCancionesDisco(Disco *disco);

#endif