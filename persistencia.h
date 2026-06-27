#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "estructuras.h"

void guardarUsuariosEnArchivo(Usuario *raiz, char nombreArchivo[]);
void cargarUsuariosDesdeArchivo(Usuario **raiz, char nombreArchivo[]);

void guardarAnunciosEnArchivo(ColaAnuncios cola, char nombreArchivo[]);
void cargarAnunciosDesdeArchivo(ColaAnuncios *cola, char nombreArchivo[]);

void guardarArtistasEnArchivo(Artista *raiz, char nombreArchivo[]);
void cargarArtistasDesdeArchivo(Artista **raiz, char nombreArchivo[]);

#endif