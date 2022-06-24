#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <strings.h>
#include <conio.h>
#include <math.h>
#include "constantes.h"
#include "Librerias/gotoxy.h"



void MensajesErroresRegistro(char[], int, int);
void MensajesAdvertencias(char[], int, int);
int ObtenerFecha(char[]);
void VaciarVentanas(int, int, int, int);
int ValidaMailCorrecto(char[]);
int CapturarPalabra(char[], int, int, int, int, int);
int ModificarPalabra(char[], char[],int, int, int);
void MostrarMensaje(char[]);

#endif // UTILITIES_H_INCLUDED
