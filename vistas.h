#ifndef VISTAS_H_INCLUDED
#define VISTAS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include "Librerias/gotoxy.h"
#include "constantes.h"

void InitialMenu();
void LoguinMenu();
void RegistrationMenu();
void MensajeAdminMenu();
void ReaderMenu(int);
void MenuPerfilReader();
void MenuCambioPassword();
void CambiarTelefonoMenuReader();
void CambiarDireccionMenuReader();
void AdminMenu();
void MensajesMenu();
void MenuNuevoLibro();
void MenuNuevoLector();
void MenuUsersAdmin(int);
void MenuBooksAdmin(int);
void CambiarBotonActivar(int, int);
void CambiarBotonAdmin(int);
void NombreProyecto();
void LogoLibro();

#endif // VISTAS_H_INCLUDED
