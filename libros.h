#ifndef LIBROS_H_INCLUDED
#define LIBROS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include <math.h>
#include "Librerias/gotoxy.h"
#include "constantes.h"
#include "vistas.h"
#include "utilities.h"

typedef struct{
    int id;
    char ISBN[MAXISBN]; /// = ISBN
    char name[TITLE];
    char author[AUTHOR];
    char gender[GENDER]; /// genero
    char editorial[EDITORIAL]; /// publishing house.
    int active; /// Si esta o no disponible
    char description[DESCRIPTION];
} stBook;


void MostrarInfoLibro(stBook);
int BuscarLibroNombreMenor(stBook[], int, int, int);
void IntercambiarValores(stBook[], int, int);
void OrdenarLibros(stBook[], int, int);
void ListarTodosLibros(stBook[], int, int, int);
int CrearNuevoLibro(stBook*);
int ModificarLibro(stBook*);
void AdministrateBooks(const char[]);

// DECLARADAS ACA PORQUE SINO EN PERSISTENCIA TIRA WARNINGS EN LA COMPILACION
int GrabarLibro(const char[], stBook);
int PasarLibrosAlArreglo(const char[], stBook*, char[]);
int CantidadRegistros(const char[], int);
int GuardarLibros(const char[], stBook[], int);
void EditarLibroEnArchivo (const char[], stBook);

#endif // LIBROS_H_INCLUDED
