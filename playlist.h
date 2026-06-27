#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "estructuras.h"

Playlist *crearPlaylist(void);
void agregarPlaylistAUsuario(Usuario *usuario, Playlist *nuevaPlaylist);
Playlist *buscarPlaylist(Usuario *usuario, char nombrePlaylist[]);
void mostrarPlaylists(Usuario *usuario);

void agregarCancionAPlaylist(Playlist *playlist, Cancion *cancion);
void quitarCancionDePlaylist(Playlist *playlist, char nombreCancion[]);
void mostrarCancionesPlaylist(Playlist *playlist);

#endif