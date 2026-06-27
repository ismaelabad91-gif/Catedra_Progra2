#ifndef USUARIOS_H
#define USUARIOS_H

#include "estructuras.h"

Usuario *crearUsuario(void);
void insertarUsuario(Usuario **raiz, Usuario *nuevo);
Usuario *buscarUsuarioPorCorreo(Usuario *raiz, char correo[]);
void mostrarUsuariosInorden(Usuario *raiz);

int iniciarSesion(Usuario *raiz, char correo[], char contrasena[], Usuario **usuarioActual);

void comprarPremium(Usuario *usuario);
void renovarPremium(Usuario *usuario);

void actualizarUsuario(Usuario *usuario);
void eliminarUsuario(Usuario **raiz, char correo[]);

#endif