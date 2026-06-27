#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "estructuras.h"

void pushHistorial(Usuario *usuario, Cancion *cancion, char fecha[]);
void mostrarHistorial(Usuario *usuario);

#endif