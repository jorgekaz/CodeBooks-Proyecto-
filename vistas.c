#include "vistas.h"

void InitialMenu(){
    setlocale(LC_ALL,"en_EN");
    // DIMENSIONA LA PNATALLA DE LA CONSOLA EN 80 X 25
    system("mode con cols=80 lines=25 ");
    // ESCRIBE EL NOMBRE EN LA CONSOLA
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    color(15);
    gotoxy(2,1);
    printf("BIENVENIDO");
    color(12);
    gotoxy(65, 24);
    printf("ESC - Salir");
    color(8);
    gotoxy(3, 24);
    printf("%cBERMUDEZ-GENOVA-KARP-OLIVERA", 1720);
    color(6);
    gotoxy(15,3);
    printf("SISTEMA PARA ADMINISTRACION DE LIBROS Y LECTORES");

    gotoxy(15,13);
    printf("ELIJA UNA OPCION DEL MENU:");
    color(15);
    gotoxy(15,15);
    printf("1");
    gotoxy(15,17);
    printf("2");
    gotoxy(15,20);
    printf("8");
    gotoxy(15,22);
    printf("9");

    color(7);
    gotoxy(16,15);
    printf(" - INGRESAR AL SISTEMA.");
    gotoxy(16,17);
    printf(" - REGISTRARSE.");
    gotoxy(16,20);
    printf(" - OLVIDE MI PASSWORD.");
    gotoxy(16,22);
    printf(" - REACTIVAR USUARIO.");
    /// LOGO
    NombreProyecto();
    LogoLibro();
}

void LoguinMenu(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    gotoxy(2,1);
    printf("INGRESO AL SISTEMA");
    gotoxy(15,10);
    printf("USUARIO: ");
    gotoxy(15,12);
    printf("PASSWORD:");
    for (int x = 24; x < 64; x++){
        gotoxy(x, 10);
        printf("%c", BLOCK);
        gotoxy(x, 12);
        printf("%c", BLOCK);
    }
    color(12);
    gotoxy(65,24);
    printf("ESC - Volver");
    color(7);
    /// LOGO
    //NombreProyecto();
    LogoLibro();
}

void RegistrationMenu(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    color(12);
    gotoxy(65, 24);
    printf("ESC - Salir");
    color(7);
    gotoxy(2,1);
    printf("REGISTRO DE USUARIO");
    gotoxy(5,6);
    printf("APELLIDO: ");
    gotoxy(5,8);
    printf("NOMBRE:");
    gotoxy(5,10);
    printf("TELEFONO (SIN 0 Y SIN 15): ");
    gotoxy(5,12);
    printf("DIRECCION:");
    gotoxy(5,14);
    printf("CORREO ELECTRONICO (USERNAME): ");
    gotoxy(5,16);
    printf("PASSWORD:");
    gotoxy(5,18);
    printf("REINGRESE PASSWORD:");
    for (int x = 36; x < 66; x++){
        gotoxy(x, 6);
        printf("%c", BLOCK);
        gotoxy(x, 8);
        printf("%c", BLOCK);
        gotoxy(x, 10);
        printf("%c", BLOCK);
        gotoxy(x, 12);
        printf("%c", BLOCK);
        gotoxy(x, 14);
        printf("%c", BLOCK);
        gotoxy(x, 16);
        printf("%c", BLOCK);
        gotoxy(x, 18);
        printf("%c", BLOCK);
    }
}

void MensajeAdminMenu(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    color(12);
    gotoxy(65, 24);
    printf("ESC - Salir");
    color(7);
    gotoxy(5,6);
    printf("APELLIDO Y NOMBRE");
    gotoxy(5,8);
    printf("MAIL:");
    for (int x = 36; x < 66; x++){
        gotoxy(x, 6);
        printf("%c", BLOCK);
        gotoxy(x, 8);
        printf("%c", BLOCK);
    }
    color(3);
    gotoxy(10,10);
    printf("COMPLETE SUS DATOS Y EL ADMINISTRADOR SE CONTACTARA PARA");
    color(7);
}

void ReaderMenu(int mainWindow){ // con 0 pinto el listado con 1 pinto la busqueda
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=26 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    color(7);
    gotoxy(3,1);
    printf("SESION DE ");
    color(12);
    gotoxy(67, 24);
    printf("ESC-LOGOUT");
    color(7);
    //Area botones
    gotoxy(2,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(2, 24);
    printf("%c F1-PERFIL %c", LINECUTR, LINECUTL);
    gotoxy(2,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(2,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(15,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(15, 24);
    printf("%c F2-GUARDAR %c", LINECUTR, LINECUTL);
    gotoxy(15,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(15,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(29,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(29, 24);
    printf("%c F3-BAJA %c", LINECUTR, LINECUTL);
    gotoxy(29,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(29,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(40,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(40, 24);
    printf("%c F4-ORDENAR %c", LINECUTR, LINECUTL);
    gotoxy(40,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(40,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(54,23);
    printf("%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(54, 24);
    printf("%c %c%c FAV %c", LINECUTR, 785, BOTTOMRIGHT,LINECUTL);
    gotoxy(54,25);
    printf("%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(54,25);
    printf("%c", BOTTOMLEFT);
    // Area Busqueda
    for (int x = 3; x < 38; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 4; y < 21; y++){
        gotoxy(3,y);
        printf("%c", BORDER);
        gotoxy(38,y);
        printf("%c", BORDER);
    }
    gotoxy(3,3);
    printf("%c", TOPLEFT);
    gotoxy(38,3);
    printf("%c", TOPRIGHT);
    gotoxy(3,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(38,21);
    printf("%c", BOTTOMRIGHT);
    gotoxy(4, 3);
    printf("LIBROS");
    if (mainWindow == 0){
        color(7);
    } else {
        color(2);
    }
    for (int x = 4; x < 37; x++){
        gotoxy(x,5);
        printf("%c", LINE);
        gotoxy(x, 7);
        printf("%c", LINE);
    }
    for (int y = 5; y < 7; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(37,y);
        printf("%c", BORDER);
    }
    gotoxy(4,5);
    printf("%c", TOPLEFT);
    gotoxy(37,5);
    printf("%c", TOPRIGHT);
    gotoxy(4,7);
    printf("%c", BOTTOMLEFT);
    gotoxy(37,7);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 5);
    printf("BUSCAR");
    if (mainWindow == 0){
        color(2);
    } else{
        color(7);
    }
    for (int x = 4; x < 37; x++){
        gotoxy(x,8);
        printf("%c", LINE);
        gotoxy(x, 20);
        printf("%c", LINE);
    }
    for (int y = 8; y < 20; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(37,y);
        printf("%c", BORDER);
    }
    gotoxy(4,8);
    printf("%c", TOPLEFT);
    gotoxy(37,8);
    printf("%c", TOPRIGHT);
    gotoxy(4,20);
    printf("%c", BOTTOMLEFT);
    gotoxy(37,20);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 8);
    printf("RESULTADO");
    color(7);
    // Area Detalles
    for (int x = 39; x < 75; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 3; y < 21; y++){
        gotoxy(39,y);
        printf("%c", BORDER);
        gotoxy(75,y);
        printf("%c", BORDER);
    }
    gotoxy(39,3);
    printf("%c", TOPLEFT);
    gotoxy(75,3);
    printf("%c", TOPRIGHT);
    gotoxy(39,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(75,21);
    printf("%c", BOTTOMRIGHT);
    gotoxy(42, 3);
    printf("DETALLES");
}

void MenuPerfilReader(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++)
    {
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 23);
        printf("%c", LINE);
    }
    for (int y = 2; y < 23; y++)
    {
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,23);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,23);
    printf("%c", BOTTOMRIGHT);
    color(12);
    gotoxy(65, 23);
    printf("ESC - Salir");
    color(7);
    gotoxy(2,1);
    printf("MI PERFIL - EDICION");
    gotoxy(5,8);
    printf("TELEFONO (SIN 0 Y SIN 15): ");
    gotoxy(5,10);
    printf("DIRECCION: ");

    //Area botones
    gotoxy(1,21);
    printf("%c%c%cMODIFICAR%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", LINECUTL,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(51,22);
    printf("%c", BORDER);
    gotoxy(51,23);
    printf("%c", 1729);
    gotoxy(3,22);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(3, 23);
    printf("%c F1-TELEFONO %c", LINECUTR, LINECUTL);
    gotoxy(3,24);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(3,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(19,22);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(19, 23);
    printf("%c F2-DIRECCION %c", LINECUTR, LINECUTL);
    gotoxy(19,24);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(19,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(36,22);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(36, 23);
    printf("%c F3-PASSWORD %c", LINECUTR, LINECUTL);
    gotoxy(36,24);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(36,24);
    printf("%c", BOTTOMLEFT);

}

void MenuCambioPassword(){
    color(3);
    gotoxy(5,12);
    printf("CAMBIO DE PASSWORD");
    color(7);
    gotoxy(5,14);
    printf("PASSWORD ANTERIOR:");
    gotoxy(5,16);
    printf("PASSWORD NUEVA:");
    gotoxy(5,18);
    printf("REINGRESE PASSWORD:");
    for (int x = 36; x < 66; x++)
    {
        gotoxy(x, 14);
        printf("%c", BLOCK);
        gotoxy(x, 16);
        printf("%c", BLOCK);
        gotoxy(x, 18);
        printf("%c", BLOCK);
    }
}

void CambiarTelefonoMenuReader(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++)
    {
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 23);
        printf("%c", LINE);
    }
    for (int y = 2; y < 23; y++)
    {
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,23);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,23);
    printf("%c", BOTTOMRIGHT);
    gotoxy(65, 23);
    color(12);
    printf("ESC - Salir");
    color(7);
    gotoxy(2,1);
    printf("CAMBIAR TELEFONO");
    gotoxy(5,8);
    printf("TELEFONO (SIN 0 Y SIN 15): ");
    gotoxy(5,10);
    printf("NUEVO NUMERO DE TELEFONO: ");
    for (int x = 36; x < 66; x++)
    {
        gotoxy(x, 8);
        printf("%c", BLOCK);
        gotoxy(x, 10);
        printf("%c", BLOCK);
    }
}

void CambiarDireccionMenuReader(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++)
    {
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 23);
        printf("%c", LINE);
    }
    for (int y = 2; y < 23; y++)
    {
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,23);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,23);
    printf("%c", BOTTOMRIGHT);
    gotoxy(65, 23);
    color(12);
    printf("ESC - Salir");
    color(7);
    gotoxy(2,1);
    printf("CAMBIAR DIRECCION");
    gotoxy(5,8);
    printf("DIRECCION: ");
    gotoxy(5,10);
    printf("NUEVA DIRECCION: ");

    for (int x = 36; x < 66; x++)
    {
        gotoxy(x, 8);
        printf("%c", BLOCK);
        gotoxy(x, 10);
        printf("%c", BLOCK);
    }
}

void AdminMenu(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=25 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    gotoxy(2,1);
    printf("MENU ADMINISTRACION");
    color(12);
    gotoxy(65, 24);
    printf("ESC - LOGOUT");
    color(6);
    gotoxy(15,4);
    printf("OPCIONES PARA ADMINISTRACION DE LIBROS Y LECTORES");
    gotoxy(15,8);
    printf("ELIJA UNA OPCION DEL MENU:");
    color(7);
    gotoxy(15,10);
    printf("1.- ABM LIBROS.");
    gotoxy(15,12);
    printf("2.- ABM USUARIOS.");
    gotoxy(15,14);
    printf("3.- ENTRAR EN MODO LECTOR.");
    gotoxy(15,16);
    printf("4.- VER MENSAJES.");
    LogoLibro();
}

void MensajesMenu(){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=26 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    gotoxy(2,1);
    printf("MENSAJES DE LOS USUARIOS");
    color(12);
    gotoxy(65, 24);
    printf("ESC-LOGOUT");
    color(7);
    //Area botones
    gotoxy(3,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(3, 24);
    printf("%c F1-LEIDO %c", LINECUTR, LINECUTL);
    gotoxy(3,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(3,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(18,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(18, 24);
    printf("%c F2-RESUELTO %c", LINECUTR, LINECUTL);
    gotoxy(18,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(18,25);
    printf("%c", BOTTOMLEFT);

    for (int x = 3; x < 76; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 22);
        printf("%c", LINE);
    }
    for (int y = 4; y < 22; y++){
        gotoxy(3,y);
        printf("%c", BORDER);
        gotoxy(76,y);
        printf("%c", BORDER);
    }
    gotoxy(3,3);
    printf("%c", TOPLEFT);
    gotoxy(76,3);
    printf("%c", TOPRIGHT);
    gotoxy(3,22);
    printf("%c", BOTTOMLEFT);
    gotoxy(76,22);
    printf("%c", BOTTOMRIGHT);
    gotoxy(4, 3);
    printf("MENSAJES");
    // TABLA
    for (int x = 4; x < 75; x++){
        gotoxy(x,4);
        printf("%c", LINE);
        gotoxy(x, 6);
        printf("%c", LINE);
    }
    gotoxy(4,5);
    printf("%c", BORDER);
    gotoxy(75,5);
    printf("%c", BORDER);
    gotoxy(4,4);
    printf("%c", TOPLEFT);
    gotoxy(75,4);
    printf("%c", TOPRIGHT);
    gotoxy(4,6);
    printf("%c", BOTTOMLEFT);
    gotoxy(75,6);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 5);
    printf("FECHA");
    gotoxy(25, 4);
    printf("%c", 1730);
    gotoxy(25, 5);
    printf("%c ESTADO", BORDER);
    gotoxy(25, 6);
    printf("%c", 1729);
    gotoxy(35, 4);
    printf("%c", 1730);
    gotoxy(35, 5);
    printf("%c MAIL", BORDER);
    gotoxy(35, 6);
    printf("%c", 1729);
    color(3);
    /// Recuadro para texto
    for (int x = 4; x < 75; x++){
        gotoxy(x,17);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 17; y < 21; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(75,y);
        printf("%c", BORDER);
    }
    gotoxy(4,17);
    printf("%c", TOPLEFT);
    gotoxy(75,17);
    printf("%c", TOPRIGHT);
    gotoxy(4,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(75,21);
    printf("%c", BOTTOMRIGHT);
    color(7);
}

void MenuNuevoLibro(){
    for (int i = 0; i < 80; i++){
        gotoxy(i, 5);
        printf("%c", LINE);
        for  (int j = 6; j < 15; j++){
            gotoxy(i,j);
            printf(" ");
        }
        gotoxy(i, 15);
        printf("%c", LINE);
    }
    color(15);
    gotoxy(0,6);
    printf("TITULO      : ");
    gotoxy(0,7);
    printf("AUTOR       : ");
    gotoxy(0,8);
    printf("EDITORIAL   : ");
    gotoxy(0,9);
    printf("GENERO      : ");
    gotoxy(0,10);
    printf("ISBN        : ");
    gotoxy(0,11);
    printf("DESCRIPCION : ");
}

void MenuNuevoLector(){
    for (int i = 0; i < 80; i++){
        gotoxy(i, 5);
        printf("%c", LINE);
        for  (int j = 6; j < 15; j++){
            gotoxy(i,j);
            printf(" ");
        }
        gotoxy(i, 15);
        printf("%c", LINE);
    }
    color(15);
    gotoxy(0,6);
    printf("NOMBRE      : ");
    gotoxy(0,7);
    printf("APELLIDO    : ");
    gotoxy(0,8);
    printf("DIRECCION   : ");
    gotoxy(0,9);
    printf("TELEFONO    : ");
    gotoxy(0,10);
    printf("MAIL        : ");
    gotoxy(0,11);
    printf("PASSWORD    : ");
}

void MenuUsersAdmin(int mainWindow){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=26 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    color(15);
    gotoxy(2,1);
    printf("ADMINISTRACION DE LECTORES");
    color(12);
    gotoxy(67, 1);
    printf("ESC-LOGOUT");
    color(7);
    //Area botones
    gotoxy(2,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(2, 24);
    printf("%c F1-ALTA %c", LINECUTR, LINECUTL);
    gotoxy(2,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(2,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(13,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(13, 24);
    printf("%c F2-DESACT. %c", LINECUTR, LINECUTL);
    gotoxy(13,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(13,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(27,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(27, 24);
    printf("%c F3-MODIF. %c", LINECUTR, LINECUTL);
    gotoxy(27,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(27,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(40,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(40, 24);
    printf("%c F4-ORDENAR %c", LINECUTR, LINECUTL);
    gotoxy(40,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(40,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(54,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(54, 24);
    printf("%c F5-SER ADMIN %c", LINECUTR, LINECUTL);
    gotoxy(54,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(54,25);
    printf("%c", BOTTOMLEFT);
    // Area Busqueda57
    for (int x = 3; x < 38; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 4; y < 21; y++){
        gotoxy(3,y);
        printf("%c", BORDER);
        gotoxy(38,y);
        printf("%c", BORDER);
    }
    gotoxy(3,3);
    printf("%c", TOPLEFT);
    gotoxy(38,3);
    printf("%c", TOPRIGHT);
    gotoxy(3,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(38,21);
    printf("%c", BOTTOMRIGHT);
    color(15);
    gotoxy(4, 3);
    printf("USUARIOS");
    color(7);
    if (mainWindow == 0){
        color(7);
    } else {
        color(2);
    }
    for (int x = 4; x < 37; x++){
        gotoxy(x,5);
        printf("%c", LINE);
        gotoxy(x, 7);
        printf("%c", LINE);
    }
    for (int y = 5; y < 7; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(37,y);
        printf("%c", BORDER);
    }
    gotoxy(4,5);
    printf("%c", TOPLEFT);
    gotoxy(37,5);
    printf("%c", TOPRIGHT);
    gotoxy(4,7);
    printf("%c", BOTTOMLEFT);
    gotoxy(37,7);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 5);
    color(15);
    printf("BUSCAR");
    color(7);
    if (mainWindow == 0){
        color(2);
    } else{
        color(7);
    }
    for (int x = 4; x < 37; x++){
        gotoxy(x,8);
        printf("%c", LINE);
        gotoxy(x, 20);
        printf("%c", LINE);
    }
    for (int y = 8; y < 20; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(37,y);
        printf("%c", BORDER);
    }
    gotoxy(4,8);
    printf("%c", TOPLEFT);
    gotoxy(37,8);
    printf("%c", TOPRIGHT);
    gotoxy(4,20);
    printf("%c", BOTTOMLEFT);
    gotoxy(37,20);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 8);
    color(15);
    printf("RESULTADO");
    color(7);
    // Area Detalles
    for (int x = 39; x < 75; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 9);
        printf("%c", LINE);
    }
    for (int y = 3; y < 9; y++){
        gotoxy(39,y);
        printf("%c", BORDER);
        gotoxy(75,y);
        printf("%c", BORDER);
    }
    gotoxy(39,3);
    printf("%c", TOPLEFT);
    gotoxy(75,3);
    printf("%c", TOPRIGHT);
    gotoxy(39,9);
    printf("%c", BOTTOMLEFT);
    gotoxy(75,9);
    printf("%c", BOTTOMRIGHT);
    gotoxy(42, 3);
    color(15);
    printf("DETALLES");
    color(7);
    // Area Favoritos
    for (int x = 39; x < 75; x++){
        gotoxy(x,10);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 10; y < 21; y++){
        gotoxy(39,y);
        printf("%c", BORDER);
        gotoxy(75,y);
        printf("%c", BORDER);
    }
    gotoxy(39,10);
    printf("%c", TOPLEFT);
    gotoxy(75,10);
    printf("%c", TOPRIGHT);
    gotoxy(39,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(75,21);
    printf("%c", BOTTOMRIGHT);
    gotoxy(42, 10);
    color(15);
    printf("FAVORITOS");
    color(7);
}

void MenuBooksAdmin(int mainWindow){
    setlocale(LC_ALL,"en_EN");
    system("mode con cols=80 lines=26 ");
    SetConsoleTitle("SISTEMA LIBROS Y LECTORES");
    for (int x = 1; x < 78; x++){
        gotoxy(x,1);
        printf("%c", LINE);
        gotoxy(x, 24);
        printf("%c", LINE);
    }
    for (int y = 2; y < 24; y++){
        gotoxy(1,y);
        printf("%c", BORDER);
        gotoxy(78,y);
        printf("%c", BORDER);
    }
    gotoxy(1,1);
    printf("%c", TOPLEFT);
    gotoxy(78,1);
    printf("%c", TOPRIGHT);
    gotoxy(1,24);
    printf("%c", BOTTOMLEFT);
    gotoxy(78,24);
    printf("%c", BOTTOMRIGHT);
    color(15);
    gotoxy(2,1);
    printf("ADMINISTRACION DE LIBROS");
    color(12);
    gotoxy(68, 1);
    printf("ESC-LOGOUT");
    color(7);
    //Area botones
    gotoxy(2,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(2, 24);
    printf("%c F1-ALTA %c", LINECUTR, LINECUTL);
    gotoxy(2,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(2,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(13,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(13, 24);
    printf("%c F2-DESACT. %c", LINECUTR, LINECUTL);
    gotoxy(13,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(13,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(27,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(27, 24);
    printf("%c F3-MODIF. %c", LINECUTR, LINECUTL);
    gotoxy(27,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(27,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(40,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(40, 24);
    printf("%c F4-ORDENAR %c", LINECUTR, LINECUTL);
    gotoxy(40,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(40,25);
    printf("%c", BOTTOMLEFT);
    gotoxy(54,23);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", TOPLEFT, LINE, LINE, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,TOPRIGHT);
    gotoxy(54, 24);
    printf("%c F5-GUARDAR %c", LINECUTR, LINECUTL);
    gotoxy(54,25);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c", BOTTOMLEFT, LINE,LINE, LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,LINE,BOTTOMRIGHT);
    gotoxy(54,25);
    printf("%c", BOTTOMLEFT);
    // Area Busqueda
    for (int x = 3; x < 38; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 4; y < 21; y++){
        gotoxy(3,y);
        printf("%c", BORDER);
        gotoxy(38,y);
        printf("%c", BORDER);
    }
    gotoxy(3,3);
    printf("%c", TOPLEFT);
    gotoxy(38,3);
    printf("%c", TOPRIGHT);
    gotoxy(3,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(38,21);
    printf("%c", BOTTOMRIGHT);
    gotoxy(4, 3);
    printf("LIBROS");
    if (mainWindow == 0){
        color(7);
    } else {
        color(2);
    }
    for (int x = 4; x < 37; x++){
        gotoxy(x,5);
        printf("%c", LINE);
        gotoxy(x, 7);
        printf("%c", LINE);
    }
    for (int y = 5; y < 7; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(37,y);
        printf("%c", BORDER);
    }
    gotoxy(4,5);
    printf("%c", TOPLEFT);
    gotoxy(37,5);
    printf("%c", TOPRIGHT);
    gotoxy(4,7);
    printf("%c", BOTTOMLEFT);
    gotoxy(37,7);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 5);
    printf("BUSCAR");
    if (mainWindow == 0){
        color(2);
    } else{
        color(7);
    }
    for (int x = 4; x < 37; x++){
        gotoxy(x,8);
        printf("%c", LINE);
        gotoxy(x, 20);
        printf("%c", LINE);
    }
    for (int y = 8; y < 20; y++){
        gotoxy(4,y);
        printf("%c", BORDER);
        gotoxy(37,y);
        printf("%c", BORDER);
    }
    gotoxy(4,8);
    printf("%c", TOPLEFT);
    gotoxy(37,8);
    printf("%c", TOPRIGHT);
    gotoxy(4,20);
    printf("%c", BOTTOMLEFT);
    gotoxy(37,20);
    printf("%c", BOTTOMRIGHT);
    gotoxy(5, 8);
    printf("RESULTADO");
    color(7);
    // Area Detalles
    for (int x = 39; x < 75; x++){
        gotoxy(x,3);
        printf("%c", LINE);
        gotoxy(x, 21);
        printf("%c", LINE);
    }
    for (int y = 3; y < 21; y++){
        gotoxy(39,y);
        printf("%c", BORDER);
        gotoxy(75,y);
        printf("%c", BORDER);
    }
    gotoxy(39,3);
    printf("%c", TOPLEFT);
    gotoxy(75,3);
    printf("%c", TOPRIGHT);
    gotoxy(39,21);
    printf("%c", BOTTOMLEFT);
    gotoxy(75,21);
    printf("%c", BOTTOMRIGHT);
    gotoxy(42, 3);
    printf("DETALLES");
}

void CambiarBotonActivar(int activo, int posX){
    if (activo == 0){
        gotoxy(posX, 24);
        printf("%c F2-ACTIVAR %c", LINECUTR, LINECUTL);
    } else{
        gotoxy(posX, 24);
        printf("%c F2-DESACT. %c", LINECUTR, LINECUTL);
    }
}

void CambiarBotonAdmin(int activo){
    if(activo==0){
        gotoxy(54,24);
        printf("%c F5-SER ADMIN %c", LINECUTR, LINECUTL);
    }else{
        gotoxy(54,24);
        printf("%c F5-NO ADMIN  %c", LINECUTR, LINECUTL);
    }
}

void NombreProyecto(){
    int matriz[10][50]={
        {0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0},
        {0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0},
        {0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,0,1,0,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,1,0,0,0,0,0},
        {0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,1,0,0,0,0},
        {0,1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    for(int i=0; i<5; i++){
        gotoxy(15,i+5);
        color(9+i);
        for(int j=0; j<50; j++){
            if(matriz[i][j]==1){
                printf("%c",BLOCK);
            }
            else{
                printf(" ");
            }
        }
        color(7);
        printf("\n");
    }
}

void LogoLibro(){
    gotoxy(60,14);
    printf("     _ _ ");
    gotoxy(60,15);
    printf(".-. | | |");
    gotoxy(60,16);
    printf("|M|_|C|M|");
    gotoxy(60,17);
    printf("|A|s|.|E|");
    gotoxy(60,18);
    printf("|T|p|C|R|");
    gotoxy(60,19);
    printf("|H|d|+|N|");
    gotoxy(60,20);
    printf("| |!|+| |");
    color(6);
    gotoxy(60,21);
    printf("#################");
    color(5);
    gotoxy(69,17);
    printf("<\\");
    gotoxy(70,18);
    printf("\\\\");
    gotoxy(70,19);
    printf(" \\\\");
    gotoxy(70,20);
    printf("  \\>");
    color(7);
}
