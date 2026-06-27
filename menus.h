#ifndef MENUS_H
#define MENUS_H

#include "estructuras.h"

void menuPrincipal(Usuario **raizUsuarios, Artista **raizArtistas, ColaAnuncios *colaAnuncios);
int leerOpcion(void);

void menuIngresar(Usuario **raizUsuarios, Artista **raizArtistas, ColaAnuncios *colaAnuncios);
void menuUsuario(Usuario *usuarioActual, Artista *raizArtistas, ColaAnuncios *colaAnuncios);

void menuDesarrollador(Usuario **raizUsuarios, Artista **raizArtistas, ColaAnuncios *colaAnuncios);
void menuCRUDUsuarios(Usuario **raizUsuarios);
void menuCRUDArtistas(Artista **raizArtistas);
void menuGestionAnuncios(ColaAnuncios *colaAnuncios);

#endif