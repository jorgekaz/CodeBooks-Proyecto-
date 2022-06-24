#ifndef LECTORES_H_INCLUDED
#define LECTORES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "Librerias/pila.h"
#include "constantes.h"
#include "vistas.h"
#include "utilities.h"
#include "libros.h"
#include "mensajes.h"
#include "persistencia.h"


typedef struct{
    int id;
    char name[NAME];
    char surName[SURNAME];
    char address[ADDRESS];
    char phone[PHONE];
    int favourite[FAVOURITE];
    int cantidadFav;
    char mail[MAIL];
    char password[PASSWORD];
    int active;
    int administrator;
} stReader;

int UserRegistration(const char[]);
void ReaderWindow(stReader*, const char[], const char[]);
void ReIniciarVentana(stReader*, stBook[], int, int*, int*);
int CambiarPassword(stReader*);
void LoginLector(const char[]);
void ListarLectores(stReader[], int, int, int);
void ListarLibrosLector(stReader, stBook[], int, int, int);
void MenuPerfil(stReader);
void CambiarTelefonoMenu(stReader);
void CambiarDireccionMenu(stReader);
void AdminLoguin();
void ListarLectores(stReader[], int, int, int);
void AdminReadersWindow(const char[], const char[]);
int BuscarReaderNombreMenor(stReader[], int, int, int);
void IntercambiarValoresLectores(stReader[], int, int);
void OrdenarLectores(stReader[], int, int);
int ModificarLector(stReader* readerAux);
void WatchFavourites(stReader, stBook[], int);
void MostrarInfoLector(stReader);
int ModificarLector(stReader*);

// ESTAN EN PERSISTENCIA PERO SI NO LAS DECLARO ACA DA ERROR
int RegistrarUsuario(stReader, stReader, const char[]);
void GuardarInfoLector(const char[], stReader);
int PasarLectoresAlArreglo(const char[], stReader*, char[]);
void VerificarUserPassword(const char[], stReader*, int*, char[], char[]);
int PasarLibrosActivosAlArreglo(const char[], stBook*, char[]);
int GuardarLectores(const char[], stReader[], int);
void EditarLectorEnArchivo(const char[], stReader);

#endif // LECTORES_H_INCLUDED
