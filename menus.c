#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#include "menus.h"
#include "usuarios.h"
#include "historial.h"
#include "anuncios.h"
#include "artistas.h"

/* Limpia el buffer para evitar errores con scanf */
static void limpiarBuffer(void){

    int c;

    while((c = getchar()) != '\n' && c != EOF){
    }
}

/* Lee una opcion entera y valida si el usuario escribio bien */
int leerOpcion(void){

    int opcion;

    if(scanf("%d", &opcion) != 1){
        limpiarBuffer();
        return -1;
    }

    limpiarBuffer();

    return opcion;
}

/* Lee texto con espacios usando fgets */
static void leerTexto(char mensaje[], char destino[], int tamanio){

    printf("%s", mensaje);

    fgets(destino, tamanio, stdin);

    /* Quita el salto de linea que deja fgets */
    destino[strcspn(destino, "\n")] = '\0';
}

/* Menu principal del sistema */
void menuPrincipal(Usuario **raizUsuarios, Artista **raizArtistas, ColaAnuncios *colaAnuncios){

    int opcion;

    do{
        printf("\n===============================\n");
        printf("\n\t S P O T I F Y\n");
        printf("\n===============================\n");

        printf("\n1. Ingresar");
        printf("\n2. Modo desarrollador");
        printf("\n3. Salir");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                menuIngresar(raizUsuarios, raizArtistas, colaAnuncios);
                break;

            case 2:
                menuDesarrollador(raizUsuarios, raizArtistas, colaAnuncios);
                break;

            case 3:
                printf("\nHasta luego.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 3);
}

/* Menu para usuario normal */
void menuIngresar(Usuario **raizUsuarios, Artista **raizArtistas, ColaAnuncios *colaAnuncios){

    int opcion;
    int sesionCorrecta;
    Usuario *nuevo;
    Usuario *usuarioActual;
    char correo[MAX_CORREO];
    char contrasena[MAX_CONTRASENA];

    do{
        printf("\n========== INGRESAR ==========\n");
        printf("\n1. Iniciar sesion");
        printf("\n2. Registrarse");
        printf("\n3. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                leerTexto("\nCorreo electronico: ", correo, MAX_CORREO);
                leerTexto("Contrasena: ", contrasena, MAX_CONTRASENA);

                usuarioActual = NULL;

                sesionCorrecta = iniciarSesion(*raizUsuarios, correo, contrasena, &usuarioActual);

                if(sesionCorrecta == 1){
                    menuUsuario(usuarioActual, *raizArtistas, colaAnuncios);
                }

                break;

            case 2:
                nuevo = crearUsuario();

                if(nuevo != NULL){
                    insertarUsuario(raizUsuarios, nuevo);
                }

                break;

            case 3:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 3);
}

/* Menu del usuario que ya inicio sesion */
void menuUsuario(Usuario *usuarioActual, Artista *raizArtistas, ColaAnuncios *colaAnuncios){

    int opcion;

    (void)raizArtistas;
    (void)colaAnuncios;

    if(usuarioActual == NULL){
        printf("\nNo hay usuario activo.\n");
        return;
    }

    do{
        printf("\n========== MENU USUARIO ==========\n");
        printf("\nUsuario: %s", usuarioActual->nickname);
        printf("\nPlan: %s", usuarioActual->plan);

        printf("\n\n1. Reproducir musica");
        printf("\n2. Ver historial");
        printf("\n3. Mis playlists");
        printf("\n4. Amigos");
        printf("\n5. Comprar premium");
        printf("\n6. Renovar premium");
        printf("\n7. Cerrar sesion");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                printf("\nReproducir musica pendiente de conectar.\n");
                break;

            case 2:
                mostrarHistorial(usuarioActual);
                break;

            case 3:
                printf("\nPlaylists pendiente de implementar.\n");
                break;

            case 4:
                printf("\nAmigos pendiente de implementar.\n");
                break;

            case 5:
                comprarPremium(usuarioActual);
                break;

            case 6:
                renovarPremium(usuarioActual);
                break;

            case 7:
                printf("\nSesion cerrada.\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 7);
}

/* Menu para administrador o desarrollador */
void menuDesarrollador(Usuario **raizUsuarios, Artista **raizArtistas, ColaAnuncios *colaAnuncios){

    int opcion;

    do{
        printf("\n====== MODO DESARROLLADOR ======\n");
        printf("\n1. CRUD usuarios");
        printf("\n2. CRUD artistas");
        printf("\n3. CRUD canciones");
        printf("\n4. Gestionar anuncios");
        printf("\n5. Reportes");
        printf("\n6. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                menuCRUDUsuarios(raizUsuarios);
                break;

            case 2:
                menuCRUDArtistas(raizArtistas);
                break;

            case 3:
                printf("\nCRUD canciones pendiente de implementar.\n");
                break;

            case 4:
                menuGestionAnuncios(colaAnuncios);
                break;

            case 5:
                printf("\nReportes pendiente de implementar.\n");
                break;

            case 6:
                printf("\nVolviendo al menu principal...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 6);
}

/* Menu CRUD de usuarios */
void menuCRUDUsuarios(Usuario **raizUsuarios){

    int opcion;
    Usuario *nuevo;
    Usuario *encontrado;
    char correo[MAX_CORREO];

    do{
        printf("\n========== CRUD USUARIOS ==========\n");
        printf("\n1. Crear usuario");
        printf("\n2. Buscar usuario por correo");
        printf("\n3. Mostrar usuarios");
        printf("\n4. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                nuevo = crearUsuario();

                if(nuevo != NULL){
                    insertarUsuario(raizUsuarios, nuevo);
                }

                break;

            case 2:
                leerTexto("\nIngrese el correo a buscar: ", correo, MAX_CORREO);

                encontrado = buscarUsuarioPorCorreo(*raizUsuarios, correo);

                if(encontrado != NULL){
                    printf("\nUsuario encontrado:\n");
                    printf("Correo: %s\n", encontrado->correo);
                    printf("Nombre: %s\n", encontrado->nombre);
                    printf("Pais: %s\n", encontrado->pais);
                    printf("Nickname: %s\n", encontrado->nickname);
                    printf("Plan: %s\n", encontrado->plan);
                }
                else{
                    printf("\nNo existe un usuario con ese correo.\n");
                }

                break;

            case 3:
                if(*raizUsuarios == NULL){
                    printf("\nNo hay usuarios registrados.\n");
                }
                else{
                    printf("\nUsuarios registrados:\n");
                    mostrarUsuariosInorden(*raizUsuarios);
                }

                break;

            case 4:
                printf("\nVolviendo al modo desarrollador...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 4);
}

/* Menu para gestionar anuncios */
void menuGestionAnuncios(ColaAnuncios *colaAnuncios){

    int opcion;
    char contenido[MAX_ANUNCIO];
    char anunciante[MAX_ANUNCIANTE];

    do{
        printf("\n========== GESTIONAR ANUNCIOS ==========\n");
        printf("\n1. Agregar anuncio");
        printf("\n2. Mostrar anuncios");
        printf("\n3. Probar mostrar un anuncio");
        printf("\n4. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                leerTexto("\nContenido del anuncio: ", contenido, MAX_ANUNCIO);
                leerTexto("Anunciante: ", anunciante, MAX_ANUNCIANTE);

                encolarAnuncio(colaAnuncios, contenido, anunciante);
                break;

            case 2:
                mostrarColaAnuncios(*colaAnuncios);
                break;

            case 3:
                mostrarAnuncio(colaAnuncios, NULL);
                break;

            case 4:
                printf("\nVolviendo al modo desarrollador...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 4);
}

/* Menu CRUD de artistas, discos y canciones */
void menuCRUDArtistas(Artista **raizArtistas){

    int opcion;
    Artista *nuevoArtista;
    Artista *artistaEncontrado;
    Disco *nuevoDisco;
    Disco *discoEncontrado;
    Cancion *nuevaCancion;

    char nombreArtista[MAX_NOMBRE];
    char nombreDisco[MAX_NOMBRE];

    do{
        printf("\n========== CRUD ARTISTAS ==========\n");
        printf("\n1. Crear artista con disco y cancion");
        printf("\n2. Agregar disco a artista");
        printf("\n3. Agregar cancion a disco");
        printf("\n4. Buscar artista");
        printf("\n5. Mostrar artistas");
        printf("\n6. Mostrar discos de un artista");
        printf("\n7. Mostrar canciones de un disco");
        printf("\n8. Volver");

        printf("\n\nSeleccione una opcion: ");
        opcion = leerOpcion();

        switch(opcion){

            case 1:
                nuevoArtista = crearArtista();

                if(nuevoArtista != NULL){

                    if(buscarArtista(*raizArtistas, nuevoArtista->nombre) != NULL){
                        printf("\nERROR: Ya existe un artista con ese nombre.\n");
                        free(nuevoArtista);
                    }
                    else{
                        printf("\nAhora debe ingresar el primer disco del artista.\n");
                        nuevoDisco = crearDisco();

                        if(nuevoDisco != NULL){
                            printf("\nAhora debe ingresar la primera cancion del disco.\n");
                            nuevaCancion = crearCancion(nuevoArtista->nombre);

                            if(nuevaCancion != NULL){
                                agregarCancionADisco(nuevoDisco, nuevaCancion);
                                agregarDiscoAArtista(nuevoArtista, nuevoDisco);
                                insertarArtista(raizArtistas, nuevoArtista);
                            }
                        }
                    }
                }

                break;

            case 2:
                leerTexto("\nNombre del artista: ", nombreArtista, MAX_NOMBRE);

                artistaEncontrado = buscarArtista(*raizArtistas, nombreArtista);

                if(artistaEncontrado == NULL){
                    printf("\nNo existe ese artista.\n");
                }
                else{
                    nuevoDisco = crearDisco();

                    if(nuevoDisco != NULL){
                        printf("\nTodo disco debe tener al menos una cancion.\n");
                        nuevaCancion = crearCancion(artistaEncontrado->nombre);

                        if(nuevaCancion != NULL){
                            agregarCancionADisco(nuevoDisco, nuevaCancion);
                            agregarDiscoAArtista(artistaEncontrado, nuevoDisco);
                        }
                    }
                }

                break;

            case 3:
                leerTexto("\nNombre del artista: ", nombreArtista, MAX_NOMBRE);

                artistaEncontrado = buscarArtista(*raizArtistas, nombreArtista);

                if(artistaEncontrado == NULL){
                    printf("\nNo existe ese artista.\n");
                }
                else{
                    leerTexto("Nombre del disco: ", nombreDisco, MAX_NOMBRE);

                    discoEncontrado = buscarDisco(artistaEncontrado, nombreDisco);

                    if(discoEncontrado == NULL){
                        printf("\nNo existe ese disco para el artista indicado.\n");
                    }
                    else{
                        nuevaCancion = crearCancion(artistaEncontrado->nombre);

                        if(nuevaCancion != NULL){
                            agregarCancionADisco(discoEncontrado, nuevaCancion);
                        }
                    }
                }

                break;

            case 4:
                leerTexto("\nNombre del artista a buscar: ", nombreArtista, MAX_NOMBRE);

                artistaEncontrado = buscarArtista(*raizArtistas, nombreArtista);

                if(artistaEncontrado == NULL){
                    printf("\nNo existe ese artista.\n");
                }
                else{
                    printf("\nArtista encontrado:\n");
                    printf("Nombre: %s\n", artistaEncontrado->nombre);
                    mostrarDiscosArtista(artistaEncontrado);
                }

                break;

            case 5:
                if(*raizArtistas == NULL){
                    printf("\nNo hay artistas registrados.\n");
                }
                else{
                    mostrarArtistasInorden(*raizArtistas);
                }

                break;

            case 6:
                leerTexto("\nNombre del artista: ", nombreArtista, MAX_NOMBRE);

                artistaEncontrado = buscarArtista(*raizArtistas, nombreArtista);

                if(artistaEncontrado == NULL){
                    printf("\nNo existe ese artista.\n");
                }
                else{
                    mostrarDiscosArtista(artistaEncontrado);
                }

                break;

            case 7:
                leerTexto("\nNombre del artista: ", nombreArtista, MAX_NOMBRE);

                artistaEncontrado = buscarArtista(*raizArtistas, nombreArtista);

                if(artistaEncontrado == NULL){
                    printf("\nNo existe ese artista.\n");
                }
                else{
                    leerTexto("Nombre del disco: ", nombreDisco, MAX_NOMBRE);

                    discoEncontrado = buscarDisco(artistaEncontrado, nombreDisco);

                    if(discoEncontrado == NULL){
                        printf("\nNo existe ese disco para el artista indicado.\n");
                    }
                    else{
                        mostrarCancionesDisco(discoEncontrado);
                    }
                }

                break;

            case 8:
                printf("\nVolviendo al modo desarrollador...\n");
                break;

            default:
                printf("\nOpcion invalida.\n");
                break;
        }

    }while(opcion != 8);
}