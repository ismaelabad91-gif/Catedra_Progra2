#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define MAX_CORREO 80
#define MAX_NOMBRE 80
#define MAX_PAIS 50
#define MAX_NICKNAME 50
#define MAX_CONTRASENA 50
#define MAX_PLAN 15
#define MAX_FECHA 15
#define MAX_ORIGEN 150
#define MAX_ANUNCIO 150
#define MAX_ANUNCIANTE 80

/* Declaraciones adelantadas */
typedef struct Usuario Usuario;
typedef struct Artista Artista;
typedef struct Disco Disco;
typedef struct Cancion Cancion;
typedef struct Playlist Playlist;
typedef struct NodoCancionPlaylist NodoCancionPlaylist;
typedef struct NodoHistorial NodoHistorial;
typedef struct NodoAmigo NodoAmigo;
typedef struct Anuncio Anuncio;
typedef struct ColaAnuncios ColaAnuncios;

/* =========================
   CANCIONES
   ========================= */

struct Cancion {
    char artista[MAX_NOMBRE];
    char nombre[MAX_NOMBRE];
    int duracionSegundos;
    char archivoOrigen[MAX_ORIGEN];

    int reproducciones;
    int enPlaylists;

    Cancion *sig;
};

/* =========================
   DISCOS
   ========================= */

struct Disco {
    char nombre[MAX_NOMBRE];
    char fechaLanzamiento[MAX_FECHA];

    Cancion *listaCanciones;

    Disco *sig;
};

/* =========================
   ARTISTAS - ABB
   ========================= */

struct Artista {
    char nombre[MAX_NOMBRE];

    Disco *listaDiscos;

    Artista *izq;
    Artista *der;
};

/* =========================
   PLAYLISTS
   ========================= */

struct NodoCancionPlaylist {
    Cancion *cancion;
    NodoCancionPlaylist *sig;
};

struct Playlist {
    char nombre[MAX_NOMBRE];

    NodoCancionPlaylist *canciones;

    Playlist *sig;
};

/* =========================
   HISTORIAL - PILA
   ========================= */

struct NodoHistorial {
    Cancion *cancion;
    char fecha[MAX_FECHA];

    NodoHistorial *sig;
};

/* =========================
   AMIGOS - LISTA LIGADA
   ========================= */

struct NodoAmigo {
    Usuario *usuarioAmigo;

    NodoAmigo *sig;
};

/* =========================
   USUARIOS - ABB
   ========================= */

struct Usuario {
    char correo[MAX_CORREO];
    char nombre[MAX_NOMBRE];
    char pais[MAX_PAIS];
    char nickname[MAX_NICKNAME];
    char contrasena[MAX_CONTRASENA];

    char plan[MAX_PLAN];

    int premiumActivo;
    char fechaVencimientoPremium[MAX_FECHA];
    float valorPremium;

    int cancionesEscuchadasDesdeAnuncio;
    int anunciosMostrados;
    int tiempoTotalReproduccion;

    Playlist *playlists;
    NodoHistorial *historial;
    NodoAmigo *amigos;

    Usuario *izq;
    Usuario *der;
};

/* =========================
   ANUNCIOS - COLA
   ========================= */

struct Anuncio {
    char contenido[MAX_ANUNCIO];
    char anunciante[MAX_ANUNCIANTE];

    Anuncio *sig;
};

struct ColaAnuncios {
    Anuncio *frente;
    Anuncio *final;
};

#endif