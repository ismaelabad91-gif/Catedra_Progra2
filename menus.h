#ifndef MENUS_H
#define MENUS_H

#include "estructuras.h"

void menuPrincipal(Usuario **raizUsuarios);
int leerOpcion(void);

void menuIngresar(Usuario **raizUsuarios);
void menuDesarrollador(Usuario **raizUsuarios);
void menuCRUDUsuarios(Usuario **raizUsuarios);

#endif