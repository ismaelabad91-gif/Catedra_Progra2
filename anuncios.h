#ifndef ANUNCIOS_H
#define ANUNCIOS_H

#include "estructuras.h"

void inicializarColaAnuncios(ColaAnuncios *cola);
int colaAnunciosVacia(ColaAnuncios cola);

void encolarAnuncio(ColaAnuncios *cola, char contenido[], char anunciante[]);
void mostrarAnuncio(ColaAnuncios *cola, Usuario *usuario);
void mostrarColaAnuncios(ColaAnuncios cola);

#endif