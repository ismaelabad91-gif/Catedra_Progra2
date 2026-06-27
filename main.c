#include <stdio.h>
#include <string.h>

#include "menus.h"
#include "usuarios.h"
#include "historial.h"

int main(void){

    Usuario *raizUsuarios = NULL;

    menuPrincipal(&raizUsuarios);//Ver en menus.c

    return 0;
}