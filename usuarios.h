#ifndef USUARIOS_H
#define USUARIOS_H

#include "estructuras.h"

Usuario *crearUsuario(void);
void insertarUsuario(Usuario **raiz, Usuario *nuevo);
Usuario *buscarUsuarioPorCorreo(Usuario *raiz, char correo[]);
void mostrarUsuariosInorden(Usuario *raiz);

#endif