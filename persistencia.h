#ifndef PERSISTENCIA_H_INCLUDED
#define PERSISTENCIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"
#include "mensajes.h"
#include "lectores.h"
#include "libros.h"

void GrabarMensaje(const char[], char[], char[], int);
int ValidaExistenciaMail(const char[], char[]);

/// PARA EVITAR WARNINGS EN LA COMPILACION TUVE QUE DECLARAR LAS FUNCIONES EN SUS RESPECTIVOS .H Y LUEGO DEFINIRLAS EN PERSISTENCIA.C
//int CantidadRegistros(const char[], int);
//int RegistrarUsuario(stReader, stReader, const char[]);
//void GuardarInfoLector(const char[], stReader);
//int GuardarCambioMensajes(const char[], stMensaje*, int);
//int GrabarLibro(const char[], stBook);
//int PasarLectoresAlArreglo(const char[], stReader*, char[]);
//int PasarLibrosAlArreglo(const char[], stBook*, char[]);
//int PasarLectoresAlArreglo(const char[], stReader*, char[]);
//void VerificarUserPassword(const char[], stReader*, int*, char[], char[]);
//int PasarMensajesAlArreglo(const char[], stMensaje*);
//int GuardarLibros(const char[], stBook*, int);
//int GuardarLectores(const char [], stReader[], int);
//void EditarLibroEnArchivo (const char [], stBook);
//void EditarLectorEnArchivo (const char [], stReader);

/// Funciones de apoyo
void MostrarDatosArchivo(const char[]);
void DarDeAltaLibros(const char[]);

#endif // PERSISTENCIA_H_INCLUDED
