#ifndef MENSAJES_H_INCLUDED
#define MENSAJES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "constantes.h"
#include "Librerias/gotoxy.h"
#include "vistas.h"
#include "persistencia.h"

typedef struct {
    int id;
    char nombreApellido[NOMBREAPELLIDO];
    char mail[MAIL];
    int tipoConsulta; //  0 reset password, 1 desbloqueo usuario
    int estado; // 0 sin leer, 1 leido, 2 resuelto.
    char fecha[DATES];
} stMensaje;

void ListarMensajes(stMensaje[], int, int, int);
void MostrarUnMensaje(stMensaje);
void AdministrarMensajes(const char []);
void MensajesAlAdministrador(int);

/// DECLARADAS ACA PARA OMITIR ADEVERTENCIAS DEL COMPILADOR
int GuardarCambioMensajes(const char[], stMensaje[], int);
int PasarMensajesAlArreglo(const char[], stMensaje*);

#endif // MENSAJES_H_INCLUDED
