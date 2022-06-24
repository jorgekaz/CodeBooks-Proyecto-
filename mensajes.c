#include "mensajes.h"

void ListarMensajes(stMensaje mensajes[], int validos, int primerMensaje, int mensajeSeleccionado){
    int posicionLista = 0;
    for (int i = primerMensaje; i < validos && posicionLista < 10; i++){
        color(7);
        posicionLista++;
        gotoxy(6,6 + posicionLista);
        printf("%s", mensajes[i].fecha);
        gotoxy(36,6 + posicionLista);
        printf("%s", mensajes[i].mail);
        gotoxy(26,6 + posicionLista);
        if (mensajes[i].estado == 0){
            color(4);
            printf("SIN LEER");
        } else if (mensajes[i].estado == 1){
            color(3);
            printf("LEIDO");
        } else {
            color(7);
            printf("RESUELTO");
        }
        color(7);
    }
    // Selecciono el libro
    gotoxy(4,7 + mensajeSeleccionado);
    color(4);
    printf("-%c", 784);
    color(7);

}

void MostrarUnMensaje(stMensaje mensaje){
    char mensajeLinea1[75] = "EL USUARIO ";
    strcat(mensajeLinea1, mensaje.nombreApellido);
    char mensajeLinea2[75] = "DESEA ";
    if (mensaje.tipoConsulta == 0){
    strcat(mensajeLinea2, "RESETEAR SU PASSWORD DE INGRESO.");
    }  else {
    strcat(mensajeLinea2, "VOLVER A ACTIVAR SU USUARIO.");
    }
    gotoxy(5,18);
    printf("%s", mensajeLinea1);
    gotoxy(5,19);
    printf("%s", mensajeLinea2);
}

void AdministrarMensajes(const char archivo[]){
    MensajesMenu();
    stMensaje* mensajes;
    int validos = 0;
    int cantidadMensajes = CantidadRegistros(archivo, sizeof(stMensaje));
    if (cantidadMensajes > 0){
        // Creo arreglo dinamico
        mensajes = (stMensaje*) malloc (cantidadMensajes * sizeof(stMensaje));
        validos = PasarMensajesAlArreglo(archivo, mensajes);
        // Muestro listado con el primero seleccionado
        ListarMensajes(mensajes, validos, 0, 0);
        MostrarUnMensaje(mensajes[0]);
    } else {
        gotoxy(5,7);
        printf("NO HAY MENSAJES.");
    }
    int mensajeKey = 0;
    int posY = 7;
    int posX = 4;
    int posicionLista = 0;
    int posicionExtra = 0; // Posicion pasando los 11 de la lista inicial
    int hizoCambios = 0;

    do{
        fflush(stdin);
        mensajeKey = getch();
        switch (mensajeKey){
        case 0:
            break;
        case -32:
            break;
        case UPARROW: // FLECHA ARRIBA
            if (posY + posicionLista + posicionExtra > posY){
                gotoxy(posX, posY + posicionLista);
                color(7);
                printf("  ");
                if (posicionExtra > 0 && posicionLista == 0) {
                    posicionExtra--;
                    VaciarVentanas(5,75,7,16); // Vacio ventana mensajes
                    ListarMensajes(mensajes, validos, posicionExtra, posicionLista);
                    VaciarVentanas(5, 74, 18, 19); // Vacio el mensaje
                    MostrarUnMensaje(mensajes[posicionLista + posicionExtra]);
                } else {
                    posicionLista--;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Vacio los campos
                    VaciarVentanas(5, 74, 18, 19);
                    // Muestro la data
                    MostrarUnMensaje(mensajes[posicionLista + posicionExtra]);
                }
            }
            break;
        case DOWNARROW: //FLECHA ABAJO
            if (posY + posicionLista < posY + validos - 1){
                if (posicionLista < 9){
                    gotoxy(posX, posY + posicionLista);
                    color(7);
                    printf("  ");
                    posicionLista++;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Vacio los campos
                    VaciarVentanas(5, 74, 18, 19);
                    // Muestro la data
                    MostrarUnMensaje(mensajes[posicionLista]);
                } else if (posicionExtra + posicionLista < validos - 1) {
                    posicionExtra++;
                    VaciarVentanas(5,75,7,16); // Vacio ventana mensajes
                    ListarMensajes(mensajes, validos, posicionExtra, posicionLista);
                    // Vacio los campos
                    VaciarVentanas(5, 74, 18, 19);
                    // Muestro la data
                    MostrarUnMensaje(mensajes[posicionLista + posicionExtra]);
                }
            }
            break;
        case F1: // F1
            if (validos > 0){
                hizoCambios = 1;
                if (mensajes[posicionLista + posicionExtra].estado == 0 ){
                    color(3);
                    gotoxy(26,7 + posicionLista);
                    printf("LEIDO   ");
                    color(7);
                    mensajes[posicionLista + posicionExtra].estado = 1;
                } else if (mensajes[posicionLista + posicionExtra].estado == 1 ){
                    color(4);
                    gotoxy(26,7 + posicionLista);
                    printf("SIN LEER");
                    color(7);
                    mensajes[posicionLista + posicionExtra].estado = 0;
                }
            }
            break;
        case F2: // F2
            if (validos > 0){
                hizoCambios = 1;
                if (mensajes[posicionLista + posicionExtra].estado == 1 ){
                    color(7);
                    gotoxy(26,7 + posicionLista);
                    printf("RESUELTO");
                    color(7);
                    mensajes[posicionLista + posicionExtra].estado = 2;
                } else if (mensajes[posicionLista + posicionExtra].estado == 2 ){
                    color(3);
                    gotoxy(26,7 + posicionLista);
                    printf("LEIDO   ");
                    color(7);
                    mensajes[posicionLista + posicionExtra].estado = 1;
                }
            }
            break;
        case ESC:
            if (hizoCambios == 1){
                MostrarMensaje("HA HECHO CAMBIOS. DESEA GUARDAR? (S/N)");
                int salir = 0;
                do{
                    salir = getch();
                    if (salir == SMAY || salir == SMIN){
                        // Guardar cambios de mensajes
                        GuardarCambioMensajes(archivo, mensajes, validos);
                    }
                }
                while (salir == 0);
            }
            break;
        }
    } while (mensajeKey != ESC);
    if (validos > 0){
        free(mensajes);
    }
}

void MensajesAlAdministrador(int tipo){
    if (tipo == 0){
        color(15);
        gotoxy(2,1);
        printf("RESTABLECER PASSWORD");
        color(3);
        gotoxy(10,11);
        printf("RESTAURAR SU PASSWORD.");
        color(7);
    } else {
        color(15);
        gotoxy(2,1);
        printf("DESBLOQUEAR EL USUARIO");
        color(3);
        gotoxy(10,11);
        printf("DESBLOQUEAR EL USUARIO.");
        color(7);
    }
    hidecursor(1);
    char nombreApellido[NOMBREAPELLIDO];
    char mail[MAIL];
    int tecla = CapturarPalabra(nombreApellido, 36, 6, NOMBREAPELLIDO, 0, 0); // capturo el nombre y apellido
    int correcto = 0;
    if (tecla != ESC){
        tecla = CapturarPalabra(mail, 36, 8, MAIL, 0, 0); // capturo el mail
        if (tecla != ESC){
            correcto = ValidaMailCorrecto(mail);
            if (correcto == 1){
                ValidaExistenciaMail(archivoLectores, mail);
                GrabarMensaje(archivoMensajes, nombreApellido, mail, tipo); // Grabo mensaje al admin
            } else {
                MostrarMensaje("EL MAIL NO ES VALIDO O NO PERTENECE A UN LECTOR.");
            }
        }
    }
    hidecursor(0);
}
