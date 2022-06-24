#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <locale.h>
#include <windows.h>
#include "constantes.h"
#include "vistas.h"
#include "lectores.h"
#include "mensajes.h"
#include "utilities.h"

int main(){
    system("cls");
    hidecursor(0); // OCULTA CURSOR
    char key;
    InitialMenu();
    do{
        fflush(stdin);
        key = getch();
        switch(key)
        {
        case UNO: // INICIO DE SESION
            system("cls");
            LoginLector(archivoLectores);
            InitialMenu();
            break;
        case DOS: // REGISTRO
            system("cls");
            if (UserRegistration(archivoLectores) > 0){// grabo un nuevo usuario al archivo
                MostrarMensaje("USUARIO CREADO SATISFACTORIAMENTE");
            } else {
                MostrarMensaje("CANCELANDO...ESPERE.");
            }
            InitialMenu();
            break;
        case OCHO: // OLIVDE MI PASSWORD
            MensajeAdminMenu();
            MensajesAlAdministrador(0); // el cero es por mensaje de olvide password
            InitialMenu();
            break;
        case NUEVE: // DESBLOQUEAR USUARIO
            MensajeAdminMenu();
            MensajesAlAdministrador(1); // el uno es por mensaje de desbloqueo
            InitialMenu();
            break;
        case ESC: /// SALIR
            system("cls");
            MostrarMensaje("GRACIAS POR USAR NUESTRO SISTEMA.");
            gotoxy(1,23);
            break;
        }
    }
    while (key != ESC);
  return 0;
}
