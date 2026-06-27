#include <stdio.h>

#include "estructuras.h"
#include "menus.h"
#include "anuncios.h"
#include "persistencia.h"

int main(void){

    Usuario *raizUsuarios = NULL;
    Artista *raizArtistas = NULL;
    ColaAnuncios colaAnuncios;

    inicializarColaAnuncios(&colaAnuncios);

    cargarUsuariosDesdeArchivo(&raizUsuarios, "usuarios.txt");
    cargarAnunciosDesdeArchivo(&colaAnuncios, "anuncios.txt");
    cargarArtistasDesdeArchivo(&raizArtistas, "artistas.txt");

    menuPrincipal(&raizUsuarios, &raizArtistas, &colaAnuncios);

    guardarUsuariosEnArchivo(raizUsuarios, "usuarios.txt");
    guardarAnunciosEnArchivo(colaAnuncios, "anuncios.txt");
    guardarArtistasEnArchivo(raizArtistas, "artistas.txt");

    return 0;
}