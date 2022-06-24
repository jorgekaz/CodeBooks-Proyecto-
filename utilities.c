#include "utilities.h"

void MensajesErroresRegistro(char mensaje[], int posX, int posY){
    hidecursor(0);
    color(4);
    gotoxy(36, 20);
    printf("%s", mensaje);
    color(7);
    Sleep(1500);
    gotoxy(36, 20);
    printf("                                          ");
    for (int x = posX; x < 66; x++){
        gotoxy(x, posY);
        printf("%c", BLOCK);
    }
    hidecursor(1);
}

void MensajesAdvertencias(char mensaje[], int posX, int posY){
    hidecursor(0);
    color(4);
    gotoxy(posX, posY);
    printf("%s", mensaje);
    color(7);
    Sleep(1500);
    gotoxy(posX, posY);
    for (int i = 0; i < strlen(mensaje); i++){
        gotoxy(posX + i, posY);
        printf(" ");
    }
    hidecursor(1);
}

int ObtenerFecha(char output[]){
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    return 0;
}

void VaciarVentanas(int posXInicio, int posXFinal, int posYInicio, int posYFinal){
    for (int i = posXInicio; i <= posXFinal; i++ ){
        for (int j = posYInicio; j <= posYFinal; j++){
            gotoxy(i,j);
            color(7);
            printf(" ");
        }
    }
}

int ValidaMailCorrecto(char mail[]){
    //Tiene que tener un @, no puede ser ni el primer, ni el ultimo caracter.
    // Hay mas validaciones como tener un . despues del @ pero no al lado, el . no puede ser el ultimo elemento.
    int mailValido = 0;
    int resultado = strcspn(mail, "@");
    if (resultado >= 1 && resultado < strlen(mail) - 1){
        resultado = strcspn(mail, ".");
        if (resultado >= 1 && resultado < strlen(mail) - 1){
                mailValido = 1;
        }
    }
    return mailValido;
}

int CapturarPalabra(char palabra[], int posX, int posY, int cantidadChar, int type, int modo){
    char tecla = 0;
    int i = 0;
    int lineaActual = 0;
    int posXMovil = 0;
    gotoxy(posX, posY);
    do {
        fflush(stdin);
        tecla = getch();
        if (tecla == BACKSPACE){
            if (i > 0) {
                i--;
                posXMovil--;
                if (posXMovil < 0) {
                  posXMovil = 60;
                  lineaActual--;
                }
                gotoxy(posX+posXMovil,posY+lineaActual);
                if (modo == 0){
                    printf("%c", BLOCK);
                } else {
                    printf(" ");
                }
                gotoxy(posX+posXMovil,posY+lineaActual);
            }
        } else if (tecla != TAB && tecla != ESC && tecla != ENTER && tecla != -32) {
            palabra[i] = (char) tecla;
            if (posXMovil > 60) {
                lineaActual++;
                posXMovil = 0;
            }
            if (type == 0) {
                gotoxy(posX+posXMovil, posY + lineaActual);
                printf("%c", palabra[i]);
            } else {
                gotoxy(posX+posXMovil, posY + lineaActual);
                printf("*");
            }
            posXMovil++;
            i++;
        } else {
            if (tecla != ESC && tecla != -32){
                tecla = ENTER;
            }
            if (tecla == -32){
                tecla = getch(); // tomo esa tecla especial para no hacer nada con ella
                fflush(stdin);
                i--; // Achico el indice para compensar la perdida de la tecla que suma luego.
            }
            i++;
        }
    } while (tecla !=ENTER && tecla != ESC && i < cantidadChar);
    if (i >= cantidadChar){ // SI EL USUARIO USO UN MAIL DEL MAXIMO PERMITIDO CORTA POR TAMAÑO ENTONCES LO IGUALO A APRETAR ENTER
        tecla = ENTER;
    }
    palabra[i-1] = '\0';
    return tecla;
}

int ModificarPalabra(char palabra[], char dato[],int posX, int posY, int cantidadChar){
    char tecla = 0;
    int cantidadLetras = strlen(dato);
    strcpy(palabra, dato);
    int cantidadLineas = 0;
    int lineaActual = 0;
    int cantidadLetrasUltimaFila = cantidadLetras;
    gotoxy(posX + cantidadLetras, posY + lineaActual);
    if (cantidadLetras >= 63){
        float longitud = cantidadLetras / 63;
        cantidadLineas = floor(longitud);
        lineaActual = cantidadLineas;
        cantidadLetrasUltimaFila = cantidadLetras - (cantidadLineas * 63);
        gotoxy(posX + cantidadLetrasUltimaFila, posY + cantidadLineas);
    }
    // Tengo cantidad de lineas si el dato es > a 63 caracteres, sino es 0
    // tambien tengo la cantidad de letras de la ultima fila
    // En lineaActual guardo lo mismo que cantidadLineas pero luego lo voy achicando para cambiar de posY
    do {
        fflush(stdin);
        tecla = getch();
        if (tecla == BACKSPACE){
            if (cantidadLetrasUltimaFila > 0 && cantidadLetras <63) { // VERIFICO QUE EL TEXTO NO OCUPE MAS DE 1 LINEA
                cantidadLetrasUltimaFila--;
                cantidadLetras--;
                gotoxy(posX + cantidadLetrasUltimaFila,posY + lineaActual);
                printf(" ");
                gotoxy(posX + cantidadLetrasUltimaFila,posY + lineaActual);
            } else if (cantidadLetras >= 63 ){ // TEXTO LARGO
                if (lineaActual == cantidadLineas && cantidadLetrasUltimaFila > 0){ // ESTOY PARADO EN LA ULTIMA LINEA DEL TEXO LARGO
                    cantidadLetrasUltimaFila--;
                    cantidadLetras--;
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                    printf(" ");
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                } else if (lineaActual == cantidadLineas){ // SIGO EN LA ULTIMA FILA PERO BORRE EL PRIMER CARACTER DE LA ULTIMA FILA
                    lineaActual--;
                    cantidadLetras--;
                    cantidadLetrasUltimaFila = 62;
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                    printf(" ");
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                } else if (lineaActual != cantidadLineas && cantidadLetrasUltimaFila > 0) { // YA NO ES LA ULTIMA FILA PERO PUEDO SEGUIR BORRADO
                    cantidadLetrasUltimaFila--;
                    cantidadLetras--;
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                    printf(" ");
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                } else if (lineaActual != cantidadLineas && lineaActual > 0 && cantidadLetrasUltimaFila <= 0){ // LLEGUE AL INICIO DE OTRA FILA
                    lineaActual--;
                    cantidadLetras--;
                    cantidadLetrasUltimaFila = 62;
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                    printf(" ");
                    gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
                }
            }
        } else if (tecla != TAB && tecla != ESC && tecla != ENTER && tecla != -32 && cantidadLetrasUltimaFila <= cantidadChar) {
            /// Debemos evaluar cuando escriben mas de 63 caracteres en la descripcion
            palabra[cantidadLetras] = (char)tecla;
            gotoxy(posX + cantidadLetrasUltimaFila, posY + lineaActual);
            printf("%c", palabra[cantidadLetras]);
            cantidadLetrasUltimaFila++;
            cantidadLetras++;
            if (cantidadLetrasUltimaFila > 62){
                lineaActual++;
                cantidadLineas++;
                cantidadLetrasUltimaFila = 0;
            }
        } else {
            if (tecla != ESC && tecla != -32){
                tecla = ENTER;
            }
            if (tecla == -32){
                tecla = getch(); // tomo esa tecla especial para no hacer nada con ella
                fflush(stdin);
                cantidadLetrasUltimaFila--; // Achico el indice para compensar la perdida de la tecla que suma luego.
            }
            cantidadLetrasUltimaFila++;
        }
    } while (tecla !=ENTER && tecla != ESC && cantidadLetras <= cantidadChar);
    //cantidadLetras = (lineaActual * 63) + cantidadLetrasUltimaFila;
    if (tecla == ENTER) {
        palabra[cantidadLetras] = '\0';
    }
    return tecla;
}

void MostrarMensaje(char mensaje[]){
    hidecursor(0);
    for (int x = 10; x < 68; x++){
        gotoxy(x,7);
        printf("%c", LINE);
        gotoxy(x,8);
        printf(" ");
        gotoxy(x, 9);
        printf("%c", LINE);
    }
    for (int y = 7; y < 9; y++){
        gotoxy(10,y);
        printf("%c", BORDER);
        gotoxy(68,y);
        printf("%c", BORDER);
    }
    gotoxy(10,7);
    printf("%c", TOPLEFT);
    gotoxy(68,7);
    printf("%c", TOPRIGHT);
    gotoxy(10,9);
    printf("%c", BOTTOMLEFT);
    gotoxy(68,9);
    printf("%c", BOTTOMRIGHT);
    int posicion = (56 - strlen(mensaje)) / 2;
    gotoxy(10 + posicion,8);
    printf("%s", mensaje);
    Sleep(2000);
}

