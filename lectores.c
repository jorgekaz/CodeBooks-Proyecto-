#include "lectores.h"

int UserRegistration(const char fileName[]){
    hidecursor(1);
    stReader reader;
    char validatePassword[PASSWORD];
    int validaIngreso = 0; // Valida cada campo del formulario
    RegistrationMenu(); // Mostrar Menu de Registro
    int resultado = 0; // Devolvemos  > 0 si se escribio ok
    int salirRegistro = 0; // Para escapar de la carga de datos

    do {
        salirRegistro = CapturarPalabra(reader.surName, 36, 6, SURNAME, 0, 0);
        if (strlen(reader.surName) == 0 && salirRegistro != ESC){
            MensajesErroresRegistro("ERROR - EL APELLIDO NO PUEDE ESTAR VACIO.", 36, 6);
        } else validaIngreso = 1;
    } while (validaIngreso == 0);

    validaIngreso = 0;
    while (validaIngreso == 0 && salirRegistro != ESC) {
        salirRegistro = CapturarPalabra(reader.name, 36, 8, NAME, 0, 0);
        if (strlen(reader.name) == 0  && salirRegistro != ESC){
            MensajesErroresRegistro("ERROR - EL NOMBRE NO PUEDE ESTAR VACIO.", 36, 8);
        } else validaIngreso = 1;
    }

    if (salirRegistro != ESC){
        salirRegistro = CapturarPalabra(reader.phone, 36, 10, PHONE, 0, 0);
    }
    if (salirRegistro != ESC){
        salirRegistro = CapturarPalabra(reader.address, 36, 12, ADDRESS, 0, 0);
    }

    validaIngreso = 0;
    int validaMail = 0;
    while (validaIngreso == 0 && salirRegistro != ESC){
        salirRegistro = CapturarPalabra(reader.mail, 36, 14, MAIL, 0, 0);
        if (strlen(reader.mail) == 0){
            MensajesErroresRegistro("ERROR - EL MAIL NO PUEDE ESTAR VACIO.", 36, 14);
        } else if (strlen(reader.mail) <= 5) {
            MensajesErroresRegistro("ERROR - EL MAIL NO ES VALIDO.", 36, 14);
        } else {
            // Verificacion del @
            validaMail = ValidaMailCorrecto(reader.mail);
            if (validaMail == 1){
                // Verificar existencia duplicado
                validaIngreso = ValidaExistenciaMail(fileName, reader.mail);
                if (validaIngreso == 0) {
                    MensajesErroresRegistro("ERROR - EL MAIL YA ESTA REGISTRADO.", 36, 14);
                }
            } else {
                MensajesErroresRegistro("ERROR - EL MAIL NO ES VALIDO.", 36, 14);
            }
        }
    }
    validaIngreso = 0;
    int validaPassword;

    while (validaIngreso == 0 && salirRegistro != ESC){
        validaPassword = 0;
        while (validaPassword == 0 && salirRegistro != ESC){
            salirRegistro = CapturarPalabra(reader.password, 36, 16, PASSWORD, 1, 0);
            if (strlen(reader.password) == 0){
                MensajesErroresRegistro("ERROR - EL PASSWORD NO PUEDE ESTAR VACIO.", 36, 16);
            } else {
                validaPassword = 1;
            }
        }

        if (salirRegistro != ESC){
            CapturarPalabra(validatePassword, 36, 18, PASSWORD, 1, 0);
            if (strcmp(reader.password, validatePassword) == 0){
                validaIngreso = 1;
            } else {
                MensajesErroresRegistro("ERROR - LAS CONTRASENIAS NO COINCIDEN.", 36, 16);
                for (int x = 36; x < 66; x++){
                   gotoxy(x, 18);
                   printf("%c", BLOCK);
                }
            }
        }
    }
    reader.active = 1;
    reader.administrator = 0;
    reader.cantidadFav = 0;
    // Buscar id y generar un id nuevo
    // Declaro un lector para guardar el ultimo del archivo
    stReader ultimoReader;
    if (salirRegistro != ESC){
        resultado = RegistrarUsuario(reader, ultimoReader, fileName);
    }
    hidecursor(0);
    return resultado;
}

void ReaderWindow(stReader* reader, const char archivoLibros[], const char archivoLectores[]){
    char tecla = 0;
    int validos = 0;
    int activeWindow = 0; // Me va a indicar donde estoy parado de la ventana 0, o en la 1 buscar
    Pila pilaFavoritos;   // Vamos a guardar los favoritos para eliminar un libro de FAV
    inicpila(&pilaFavoritos);
    int hizoCambios = 0;
    stBook* books;
    hidecursor(0);
    gotoxy(13, 1);
    printf("%s %s\n", strupr(reader->surName), strupr(reader->name));
    // Leer los libros para saber la cantidad y generar un arreglo dinamico
    int cantidadLibros = CantidadRegistros(archivoLibros, sizeof(stBook));
    if (cantidadLibros > 0){
        // Creo arreglo dinamico
        books = (stBook*) malloc (cantidadLibros * sizeof(stBook));
        validos = PasarLibrosActivosAlArreglo(archivoLibros, books, "");
        // Muestro listado con el primero seleccionado
        ListarLibrosLector(*reader, books, validos, 0, 0);
        // Muestro la data del primer libro.

    } else {
        gotoxy(5,9);
        printf("NO HAY LIBROS EN LA B.D.");
    }
    if (validos == 0 && cantidadLibros > 0){ // NO HAY LIBROS ACTIVOS PERO SI EN LA BD
        gotoxy(5,9);
        printf("NO HAY LIBROS ACTIVOS.");
    } else if (validos > 0) { // SI CORTO POR CANTIDA DE LIBROS = 0 NO PUEDO HACER LO DE ABAJO, SOLO SI HAY LIBROS ACTIVOS
        MostrarInfoLibro(books[0]);
    }

    int posY = 9;
    int posX = 5;
    int posicionLista = 0;
    int posicionExtra = 0; // Posicion pasando los 11 de la lista inicial
    int campo = 0;
    do{
        fflush(stdin);
        tecla = getch();
        switch (tecla){
        case 0: // SE CAPTURA PARA RESOLVER FALLA EN ALGUNOS TECLADOS
            break;
        case -32: // SE CAPTURA PARA RESOLVER FALLA EN ALGUNOS TECLADOS
            break;
        case ENTER: // Tecla ENTER marca o desmarca un favorito
            if (activeWindow == 0 && validos > 0){
                // Cuando da enter en la ventana de libros lo pinta y marca
                int isFavourite = 0;
                // Indica que genero algun cambio para cuando guarde las modificaciones
                hizoCambios = 1;
                // Recorrer el arreglo de favoritos del lector y si es un favorito lo desmarco
                for (int j = 0; j < reader->cantidadFav; j++){
                    if (books[posicionLista + posicionExtra].id == reader->favourite[j]){
                       isFavourite = 1;
                    }
                }
                if (isFavourite == 0 && reader->cantidadFav < 8) {
                    color(3);
                    gotoxy(8, posY + posicionLista);
                    char nombreLibro[30];
                    strncpy(nombreLibro, books[posicionLista + posicionExtra].name + 0, 25);
                    nombreLibro[24] = '\0';
                    printf("%s %s", nombreLibro, "(Fav)");
                    reader->favourite[reader->cantidadFav] = books[posicionLista + posicionExtra].id;
                    reader->cantidadFav++;
                    color(7);
                } else if (isFavourite == 1){
                    color(7);
                    gotoxy(8, posY + posicionLista);
                    printf("                             "); // borro el libro marcado
                    gotoxy(8, posY + posicionLista);
                    printf("%s", books[posicionLista + posicionExtra].name);
                    // Tengo que buscar el favorito y sacarlo del arreglo
                    for (int i = 0; i < reader->cantidadFav; i++) {
                        if (books[posicionLista + posicionExtra].id != reader->favourite[i]) {
                            apilar(&pilaFavoritos, reader->favourite[i]);
                        }
                    }
                    reader->favourite[reader->cantidadFav] = 0;
                    reader->cantidadFav--;
                    int fav = 0;
                    while (!pilavacia(&pilaFavoritos)){
                        reader->favourite[fav] = desapilar(&pilaFavoritos);
                        fav++;
                    }
                } else {
                    MensajesAdvertencias("HAS ALCANZADO EL LIMITE DE FAVORITOS", 3, 22);
                }
            }
            break;
        case TAB: // Tecla TAB
            if (validos > 0){
                switch (activeWindow){
                case 1:
                    gotoxy(5,6);
                    printf("  "); // borra flecha
                    activeWindow = 0;
                    posX = 5;
                    posY = 9;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    for (int x = 7; x < 37; x++){
                        gotoxy(x, 6);
                        printf(" ");
                    }
                    break;
                case 0:
                    // ALGORITMO DE BUSQUEDA
                    hidecursor(1);
                    ReaderMenu(1);
                    gotoxy(13, 1);
                    printf("%s %s\n", strupr(reader->surName), strupr(reader->name));
                    ListarLibrosLector(*reader, books, validos, posicionExtra, posicionLista);
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                    gotoxy(5,9 + posicionLista);
                    printf("  "); // borra flecha
                    activeWindow = 1;
                    posX = 5;
                    posY = 6;
                    gotoxy(posX, posY);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Estoy en la barra de busqueda
                    for (int x = 7; x < 37; x++){
                        gotoxy(x, 6);
                        printf("%c", BLOCK);
                    }
                    // Capturo lo que escriban
                    char filtro[30];
                    gotoxy(7,6);
                    char teclaBusqueda = 0;
                    do {
                      teclaBusqueda = CapturarPalabra(filtro, 7, 6, 30, 0, 0);
                    } while (teclaBusqueda != ESC && teclaBusqueda != ENTER);
                    if (teclaBusqueda == ESC){
                        strcpy(filtro, "");
                    }
                    validos = PasarLibrosActivosAlArreglo(archivoLibros, books, filtro);
                    if (validos > 0){
                        ReaderMenu(0);
                        VaciarVentanas(5,36,9,19); // Vacio ventana libros
                        VaciarVentanas(41,74,4,20); // Vacio ventana info libros
                        ListarLibrosLector(*reader, books, validos,0 ,0);
                        MostrarInfoLibro(books[0]);
                        VaciarVentanas(5,36,6,6); // Vacio ventana busqueda
                        posX = 5;
                        posY = 9;
                        gotoxy(posX, posY);
                        activeWindow = 0;
                        posicionLista = 0;
                        posicionExtra = 0;
                    } else {
                        ReaderMenu(0);
                        MensajesAdvertencias("NO SE ENCONTRARON COINCIDENCIAS", 4,22);
                        gotoxy(13, 1);
                        printf("%s %s\n", strupr(reader->surName), strupr(reader->name));
                        validos = PasarLibrosActivosAlArreglo(archivoLibros, books, "");
                        ListarLibrosLector(*reader, books, validos, 0, 0);
                        MostrarInfoLibro(books[0]);
                        posicionLista = 0;
                        posicionExtra = 0;
                        activeWindow = 0;
                        posX = 5;
                        posY = 9;
                    }
                    gotoxy(13, 1);
                    printf("%s %s\n", strupr(reader->surName), strupr(reader->name));
                    hidecursor(0);
                }
                break;
            }
            break;
        case UPARROW:
            if (posY + posicionLista + posicionExtra > posY && activeWindow == 0 && validos > 0){
                gotoxy(posX, posY + posicionLista);
                color(7);
                printf("  ");
                if (posicionExtra > 0 && posicionLista == 0) {
                    posicionExtra--;
                    VaciarVentanas(5,36,9,19); // Vacio ventana libros
                    ListarLibrosLector(*reader, books, validos, posicionExtra, posicionLista);
                    // Vacio los campos
                    VaciarVentanas(41, 74, 4, 20);
                    // Muestro la data
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                } else {
                    posicionLista--;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Vacio los campos
                    VaciarVentanas(41, 74, 4, 20);
                    // Muestro la data
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                }
            }
            break;
        case DOWNARROW:
            if (posY + posicionLista < posY + validos - 1  && activeWindow == 0 && validos > 0){
                if (posicionLista < 10){
                    gotoxy(posX, posY + posicionLista);
                    color(7);
                    printf("  ");
                    posicionLista++;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Vacio los campos
                    VaciarVentanas(41,74,4,20);
                    // Muestro la data
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                } else if (posicionExtra + posicionLista < validos - 1) {
                    posicionExtra++;
                    VaciarVentanas(5,36,9,19); // Vacio ventana libros
                    ListarLibrosLector(*reader, books, validos, posicionExtra, posicionLista);
                    VaciarVentanas(41,74,4,20);
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                }
            }
            break;
        case F1: // F1 Perfil
            MenuPerfil(*reader);
            hidecursor(0);
            char teclaPerfil=0;
            do
            {
                int cambioOk = 0;
                teclaPerfil=getch();
                switch(teclaPerfil)
                {
                case F1:
                    hidecursor(1);
                    CambiarTelefonoMenu(*reader);
                    char newPhone[PHONE];
                    int ultimaTecla = 0;
                    ultimaTecla = CapturarPalabra(newPhone,36,10,PHONE,0, 0);
                    if (ultimaTecla == ENTER && strlen(newPhone) > 0){
                        strcpy(reader->phone, newPhone);
                        GuardarInfoLector(archivoLectores, *reader);
                    } else {
                        MostrarMensaje("NO SE REALIZO NINGUN CAMBIO.");
                    }
                    // Volver al menu anterior
                    hidecursor(0);
                    MenuPerfil(*reader);
                    break;
                case F2:
                    hidecursor(1);
                    CambiarDireccionMenu(*reader);
                    char newAddress[ADDRESS];
                    ultimaTecla = 0;
                    ultimaTecla = CapturarPalabra(newAddress,36,10,ADDRESS,0, 0);
                    if (ultimaTecla == ENTER && strlen(newAddress) > 0){
                        strcpy(reader->address, newAddress);
                        GuardarInfoLector(archivoLectores, *reader);
                    } else {
                        MostrarMensaje("NO SE REALIZO NINGUN CAMBIO.");
                    }
                    // Volver al menu anterior
                    hidecursor(0);
                    MenuPerfil(*reader);
                    break;
                case F3:
                    hidecursor(1);
                    MenuCambioPassword();
                    cambioOk = CambiarPassword(reader);
                    if (cambioOk == 1 ){
                        GuardarInfoLector(archivoLectores, *reader);
                    }
                    hidecursor(0);
                    MenuPerfil(*reader);
                break;
                }
            }
            while(teclaPerfil!=ESC);
            hidecursor(0);
            ReIniciarVentana(reader, books, validos, &posicionLista, &posicionExtra);
            break;
        case F2:
            GuardarInfoLector(archivoLectores, *reader);
            hizoCambios = 0;
            ReIniciarVentana(reader, books, validos, &posicionLista, &posicionExtra);
            break;
        case F3:
            // Dar de baja usuario
            MostrarMensaje("DAR DE BAJA CUENTA. ESTA SEGURO? (S/N)");
            int salir = 0;
            do{
                salir = getch();
                if (salir == SMAY || salir == SMIN){
                    // Guardar cambios del reader
                    reader->active = 0;
                    GuardarInfoLector(archivoLectores, *reader);
                    MostrarMensaje("USUARIO DADO DE BAJA EN FORMA CORRECTA.");
                    tecla = ESC;
                } else {
                    salir = 1;
                    ReIniciarVentana(reader, books, validos, &posicionLista, &posicionExtra);
                }
             } while (salir == 0);
             hizoCambios = 0;
            break;
        case F4:
            if (validos > 0) {
                OrdenarLibros(books, validos, campo); // campo 0 ordena por nombre, campo 1 ordena por ID
                ReIniciarVentana(reader, books, validos, &posicionLista, &posicionExtra);
                if (campo == 0){
                    campo = 1;
                    gotoxy(40, 24);
                    printf("%c F4-VOLVER  %c", LINECUTR, LINECUTL);
				} else if (campo == 1){
					campo = 0;
					gotoxy(40, 24);
					printf("%c F4-ORDENAR %c", LINECUTR, LINECUTL);
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
                        // Guardar cambios del reader
                        GuardarInfoLector(archivoLectores, *reader);
                    }
                }
                while (salir == 0);
            }
            break;
        }
    } while (tecla != ESC);
    if (validos > 0){
        free(books);
    }
}

void ReIniciarVentana(stReader* reader, stBook books[], int validos, int* posicionLista, int* posicionExtra){
    ReaderMenu(0);
    gotoxy(13, 1);
    printf("%s %s\n", strupr(reader->surName), strupr(reader->name));
    ListarLibrosLector(*reader, books, validos, 0, 0);
    if (validos > 0){
        MostrarInfoLibro(books[0]);
    } else {
        gotoxy(5,9);
        printf("NO HAY LIBROS ACTIVOS.");
    }
    *posicionLista = 0;
    *posicionExtra = 0;
}

int CambiarPassword(stReader* reader){
    char passwordVieja[PASSWORD];
    char passwordNueva[PASSWORD];
    char passwordValidacion[PASSWORD];
    int primeraValidacion=0;
    int segundaValidacion=0;
    int teclaCaptura = 0;
    while(primeraValidacion==0 && teclaCaptura ==0)
    {
        teclaCaptura = CapturarPalabra(passwordVieja,36,14,PASSWORD,1, 0);
        if (teclaCaptura != ESC)
        {
            if(strcmp(passwordVieja,reader->password)==0)
            {
                primeraValidacion=1;
            }
            else
            {
                MensajesAdvertencias("LAS CONTRASENIAS NO COINCIDEN", 36,19);
                for (int x = 36; x < 66; x++)
                {
                    gotoxy(x, 14);
                    printf("%c", BLOCK);
                }
            }
        }
    }
    teclaCaptura = 0;
    while(segundaValidacion==0 && primeraValidacion==1 && teclaCaptura == 0)
    {
        CapturarPalabra(passwordNueva,36,16,PASSWORD,1, 0);
        teclaCaptura = CapturarPalabra(passwordValidacion,36,18,PASSWORD,1, 0);
        if (teclaCaptura != ESC)
        {
            if(strcmp(passwordNueva,passwordValidacion)==0)
            {
                MostrarMensaje("CONTRASENIA CAMBIADA CORRECTAMENTE");
                strcpy(reader->password,passwordNueva);
                segundaValidacion=1;
            }
            else
            {
                MensajesAdvertencias("LAS CONTRASENIAS NUEVAS NO COINCIDEN", 36,19);
                for (int x = 36; x < 66; x++)
                {
                    gotoxy(x, 14);
                    printf("%c", BLOCK);
                }
            }
        }
    }
    return segundaValidacion;
}

void LoginLector(const char fileName[]){
    stReader reader;
    char username[MAIL];
    char password[PASSWORD];
    int userLogued = 0;
    int datosLogueado = 0; // 0 SI FALTA INFORMACION DE LOGUEO, 1 SI EL USUARIO ESCRIBIO USUARIO Y CLAVE
    int teclaUserName = 0;
    int teclaPassword = 0;
    LoguinMenu();
    hidecursor(1);
    do {
        teclaUserName = CapturarPalabra(username, 24, 10, MAIL, 0, 0); // el ultimo parametro es para saber si tiene que escribir el caracter o *
        if (teclaUserName == ENTER){
            teclaPassword = CapturarPalabra(password, 24, 12, PASSWORD, 1, 0);
            if (teclaPassword == ENTER){
                datosLogueado = 1;
            }
        }
    } while (datosLogueado != 1 && teclaUserName != ESC && teclaPassword != ESC);
    if (datosLogueado == 1) {
        VerificarUserPassword(fileName, &reader, &userLogued, username, password);
    }
    if (userLogued == 1) { // USUARIO NORMAL
        ReaderMenu(0);
        ReaderWindow(&reader, archivoLibros, archivoLectores);
    } else if (userLogued == 2){ // USUARIO ADMIN
        AdminLoguin(reader);
    } else if (userLogued == 3) { // DADO DE BAJA
        MostrarMensaje("USUARIO DADO DE BAJA, SOLICITAR REACTIVACION.");
    } else if (teclaUserName != ESC && teclaPassword != ESC) {
        MostrarMensaje("USUARIO INVALIDO");
    } else {
        MostrarMensaje("CANCELANDO...");
    }
    hidecursor(0);
}

void ListarLibrosLector(stReader reader, stBook books[], int validos, int primerLibro, int libroSeleccionado){
    int posicionLista = 0;
    for (int i = primerLibro; i < validos && posicionLista < 11; i++){
        color(7);
        gotoxy(8,9 + posicionLista);
        posicionLista++;
        int isFavourite = 0;
        // Recorrer el arreglo de favoritos del lector y si es un favorito se imprime en otro color
        for (int j = 0; j < reader.cantidadFav; j++){
            if (books[i].id == reader.favourite[j]){
               isFavourite = 1;
            }
        }
        if (isFavourite == 0){
            printf("%s", books[i].name);
        } else {
            color(3);
            // ACORTO EL NOMBRE POR SI ES MUY LARGO. SI LE AGREGO FAV AL FINAL PUEDE PASARSE DE LA VENTANA
            char nombreLibro[NAME];
            strncpy(nombreLibro, books[i].name + 0, 25);
            nombreLibro[24] = '\0';
            printf("%s %s", nombreLibro, "(Fav)");
            color(7);
        }
    }
    // Selecciono el libro
    gotoxy(5, 9 + libroSeleccionado);
    color(4);
    printf("-%c", 784);
    color(7);

}

void MenuPerfil(stReader reader){
    MenuPerfilReader();
    gotoxy(5,4);
    printf("APELLIDO: %s", strupr(reader.surName));
    gotoxy(5,6);
    printf("NOMBRE: %s", strupr(reader.name));
    gotoxy(36,8);
    printf("%s ", strupr(reader.phone));
    gotoxy(36,10);
    printf("%s ", strupr(reader.address));
}

void CambiarTelefonoMenu(stReader reader){
    CambiarTelefonoMenuReader();
    gotoxy(36,8);
    printf("%s ", strupr(reader.phone));
}

void CambiarDireccionMenu(stReader reader){
    CambiarDireccionMenuReader();
    gotoxy(36,8);
    printf("%s ", strupr(reader.address));
}

void AdminLoguin(stReader reader){
    int adminkey = 0;
    hidecursor(0);
    AdminMenu();
    do{
        adminkey=getch();
        switch(adminkey)
        {
        case UNO: /// MODIFICAR LIBROS
            MenuBooksAdmin(0);
            AdministrateBooks(archivoLibros);
            break;
        case DOS: /// MODIFICAR USUARIOS
            MenuUsersAdmin(0);
            AdminReadersWindow(archivoLectores, archivoLibros);
            break;
        case TRES: /// ENTRAR EN MODO LECTOR
            if (strcmp(reader.name, "ADMIN") == 0){
                MostrarMensaje("EL SUPERUSER ADMIN NO TIENE OPCION DE LECTOR.");
            } else {
                ReaderMenu(0);
                ReaderWindow(&reader, archivoLibros, archivoLectores);
            }
            break;
        case CUATRO: /// VER MENSAJES
            AdministrarMensajes(archivoMensajes);
            break;
        case ESC: /// Salir
            break;
        }
        AdminMenu();
    }while(adminkey!=ESC);
}

void ListarLectores(stReader readers[], int validos, int primerLector, int lectorSeleccionado){
    int posicionLista = 0;
    for (int i = primerLector; i < validos && posicionLista < 10; i++){
        if (readers[i].active == 1){
            color(7);
            posicionLista++;
            gotoxy(8,8 + posicionLista);
            printf("%s %s", readers[i].surName, readers[i].name);
        } else {
        color(7);
            posicionLista++;
            gotoxy(8,8 + posicionLista);
            color(4);
            printf("%s %s %s", readers[i].surName, readers[i].name, "(X)");
        }
        color(7);
    }
    // Selecciono el libro
    gotoxy(5,9 + lectorSeleccionado);
    color(4);
    printf("-%c", 784);
    color(7);

}

void AdminReadersWindow(const char archivoLectores[], const char archivoLibros[]){
    char tecla = 0;
    int activeWindow = 0; // Me va a indicar donde estoy parado de la ventana 0, o en la 1 buscar
    int hizoCambios = 0;
    int campo = 0; // Parametro de la ordenacion, el 0 indica por nombre, el 1 por indice.
    /*
    Creamos un arreglo dinamico con todos los lectores que va a ir almacenando todos los cambios
    y luego es el arreglo que se va a guardar, ya que el arreglo con el que trabajamos va a ir cambiando
    segun el filtro de busqueda que apliquemos y si grabo filtrado solo graba lo que hay en ese arreglo mas chico
    */
    stReader* readers;
    int validos = 0;
    stReader* readersAll;
    int validosAll = 0;
    stBook* books;
    int librosValidos = 0;

    hidecursor(0);
    librosValidos = CantidadRegistros(archivoLibros, sizeof(stBook));
    int cantidadLectores = CantidadRegistros(archivoLectores, sizeof(stReader));
    if (cantidadLectores > 0){
        // Creo arreglo dinamico para los lectores
        readers = (stReader*) malloc (cantidadLectores * sizeof(stReader));
        readersAll = (stReader*) malloc (cantidadLectores * sizeof(stReader));
        validos = PasarLectoresAlArreglo(archivoLectores, readers, "");
        validosAll = PasarLectoresAlArreglo(archivoLectores, readersAll, "");
        //creo un arreglo dinamico para los libros
        books = (stBook*) malloc (librosValidos * sizeof(stBook));
        librosValidos = PasarLibrosAlArreglo(archivoLibros, books, "");
        // Muestro listado con el primero seleccionado
        ListarLectores(readers, validos, 0, 0);
        // Muestro la data del primer libro.
        MostrarInfoLector(readers[0]);
        WatchFavourites(readers[0], books, librosValidos);
        CambiarBotonActivar(readers[0].active, 13);
        CambiarBotonAdmin(readers[0].administrator);
    } else {
        gotoxy(5,9);
        printf("NO HAY LECTORES EN LA B.D.");
    }

    int posX = 5;
    int posY = 9;
    int posicionLista = 0;
    int posicionExtra = 0; // Posicion pasando los 11 de la lista inicial
    int resultado = 0;
    do{
        fflush(stdin);
        tecla = getch();
        switch (tecla){
        case 0: // CAPTURAMOS LAS TECLAS ESPECIALES
            break;
        case -32:
            break;
        case TAB: // Tecla TAB
            switch (activeWindow){
            case 1:
                gotoxy(5,6);
                printf("  "); // borra flecha
                activeWindow = 0;
                posX = 5;
                posY = 9;
                gotoxy(posX, posY + posicionLista);
                color(4);
                printf("-%c", 784);
                color(7);
                for (int x = 7; x < 37; x++){
                    gotoxy(x, 6);
                    printf(" ");
                }
                break;
            case 0:
                // ALGORITMO DE BUSQUEDA
                hidecursor(1);
                MenuUsersAdmin(1);
                ListarLectores(readers, validos, posicionExtra, posicionLista);
                MostrarInfoLector(readers[posicionLista + posicionExtra]);
                WatchFavourites(readers[posicionLista + posicionExtra], books, librosValidos);
                CambiarBotonActivar(readers[posicionLista + posicionExtra].active, 13);
                CambiarBotonAdmin(readers[posicionLista + posicionExtra].administrator);
                gotoxy(5,9 + posicionLista);
                printf("  "); // borra flecha
                activeWindow = 1;
                posX = 5;
                posY = 6;
                gotoxy(posX, posY);
                color(4);
                printf("-%c", 784);
                color(7);
                // Estoy en la barra de busqueda
                for (int x = 7; x < 37; x++){
                    gotoxy(x, 6);
                    printf("%c", 219);
                }
                // Capturo lo que escriban
                char filtro[30];
                gotoxy(7,6);
                char teclaBusqueda = 0;
                do {
                  teclaBusqueda = CapturarPalabra(filtro, 7, 6, 30, 0, 0);
                } while (teclaBusqueda != ESC && teclaBusqueda != ENTER);
                if (teclaBusqueda == ESC){
                    strcpy(filtro, "");
                }
                validos = PasarLectoresAlArreglo(archivoLectores, readers, filtro);
                if (validos > 0){
                    // PASO LOS MODIFICADOS DEL ARREGLO READERSALL AL READERS FILTRADO ASI NO PIERDO LOS CAMBIOS
                    for (int i = 0; i < validos; i++){
                        int readerModificado = 0;
                        for (int j=0; j < validosAll && readerModificado == 0; j++){
                            if (readers[i].id == readersAll[j].id){
                                readerModificado = 1;
                                readers[i].active = readersAll[j].active;
                                readers[i].administrator = readersAll[j].administrator;
                            }
                        }
                    }
                    MenuUsersAdmin(0);
                    VaciarVentanas(5,36,9,19); // Vacio ventana usuarios
                    VaciarVentanas(41, 74, 4, 7); // Vacio ventana info usuarios
                    ListarLectores(readers, validos,0 ,0);
                    MostrarInfoLector(readers[0]);
                    WatchFavourites(readers[0], books, librosValidos);
                    CambiarBotonActivar(readers[0].active, 13);
                    CambiarBotonAdmin(readers[0].administrator);
                    VaciarVentanas(5,36, 6,6); // Vacio ventana busqueda
                    posX = 5;
                    posY = 9;
                    gotoxy(posX, posY);
                    activeWindow = 0;
                    posicionLista = 0;
                    posicionExtra = 0;
                } else {
                    MenuUsersAdmin(0);
                    VaciarVentanas(5,36,9,19);
                    MensajesAdvertencias("NO SE ENCONTRARON COINCIDENCIAS.", 4, 22);
                    validos = PasarLectoresAlArreglo(archivoLectores, readers, "");
                    ListarLectores(readers, validos, 0, 0);
                    MostrarInfoLector(readers[0]);
                    WatchFavourites(readers[0], books, librosValidos);
                    CambiarBotonActivar(readers[0].active, 13);
                    CambiarBotonAdmin(readers[0].administrator);
                    posicionLista = 0;
                    posicionExtra = 0;
                    activeWindow = 0;
                    posX = 5;
                    posY = 9;
                }
                break;
            }
            hidecursor(0);
            break;
        case UPARROW: // FLECHA ARRIBA
            if (posY + posicionLista + posicionExtra > posY && activeWindow == 0){
                gotoxy(posX, posY + posicionLista);
                color(7);
                printf("  ");
                if (posicionExtra > 0 && posicionLista == 0) {
                    posicionExtra--;
                    VaciarVentanas(5,36,9,19); // Vacio ventana usuarios
                    ListarLectores(readers, validos, posicionExtra, posicionLista);
                    // Vacio los campos
                    VaciarVentanas(41, 74, 4, 7);
                    VaciarVentanas(40, 74, 11, 20);
                    // Muestro la data
                    MostrarInfoLector(readers[posicionLista + posicionExtra]);
                    WatchFavourites(readers[posicionLista + posicionExtra], books, librosValidos);
                    CambiarBotonActivar(readers[posicionLista + posicionExtra].active, 13);
                    CambiarBotonAdmin(readers[posicionLista + posicionExtra].administrator);
                } else {
                    posicionLista--;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Vacio los campos
                    VaciarVentanas(41, 74, 4, 7);
                    VaciarVentanas(40, 74, 11, 20);
                    // Muestro la data
                    MostrarInfoLector(readers[posicionLista + posicionExtra]);
                    WatchFavourites(readers[posicionLista + posicionExtra], books, librosValidos);
                    CambiarBotonActivar(readers[posicionLista + posicionExtra].active, 13);
                    CambiarBotonAdmin(readers[posicionLista + posicionExtra].administrator);
                }
            }
            break;
        case DOWNARROW:
            if (posY + posicionLista < posY + validos - 1  && activeWindow == 0){
                if (posicionLista < 10){
                    gotoxy(posX, posY + posicionLista);
                    color(7);
                    printf("  ");
                    posicionLista++;
                    gotoxy(posX, posY + posicionLista);
                    color(4);
                    printf("-%c", 784);
                    color(7);
                    // Vacio los campos
                    VaciarVentanas(41, 74, 4, 7);
                    VaciarVentanas(40, 74, 11, 20);
                    // Muestro la data
                    MostrarInfoLector(readers[posicionLista]);
                    WatchFavourites(readers[posicionLista], books, librosValidos);
                    CambiarBotonActivar(readers[posicionLista].active, 13);
                    CambiarBotonAdmin(readers[posicionLista].administrator);
                } else if (posicionExtra + posicionLista < validos - 1) {
                    posicionExtra++;
                    VaciarVentanas(5,36,9,19); // Vacio ventana libros
                    ListarLectores(readers, validos, posicionExtra, posicionLista);
                    VaciarVentanas(41, 74, 4, 7);
                    VaciarVentanas(40, 74, 11, 20);
                    MostrarInfoLector(readers[posicionLista + posicionExtra]);
                    WatchFavourites(readers[posicionLista + posicionExtra], books, librosValidos);
                    CambiarBotonActivar(readers[posicionLista + posicionExtra].active, 13);
                    CambiarBotonAdmin(readers[posicionLista + posicionExtra].administrator);
                }
            }
            break;
        case F1: // F1 ALTA
            GuardarLectores(archivoLectores, readers, validos); // ANTES DE DAR DE ALTA GUARDO CUALQUIER CAMBIO EFECTUADO
            if (UserRegistration(archivoLectores) > 0){
                MostrarMensaje("USUARIO CREADO SATISFACTORIAMENTE");
                // VACIO LOS ARREGLOS DINAMICOS
                free(readers);
                free(readersAll);
                // VUELVO A CREAR LOS ARREGLOS DINAMICOS
                cantidadLectores = CantidadRegistros(archivoLectores, sizeof(stReader));
                readers = (stReader*) malloc (cantidadLectores * sizeof(stReader));
                validos = PasarLectoresAlArreglo(archivoLectores, readers, "");
                readersAll = (stReader*) malloc (cantidadLectores * sizeof(stReader));
                validosAll = PasarLectoresAlArreglo(archivoLectores, readersAll, "");
            } else {
                MostrarMensaje("CANCELANDO...ESPERE.");
            }
            MenuUsersAdmin(0);
            VaciarVentanas(5,36,9,19); // Vacio ventana libros
            ListarLectores(readers, validos, posicionExtra, posicionLista);
            VaciarVentanas(41, 74, 4, 7);
            VaciarVentanas(40, 74, 11, 20);
            MostrarInfoLector(readers[posicionLista + posicionExtra]);
            WatchFavourites(readers[posicionLista + posicionExtra], books, librosValidos);
            break;
        case F2: // F2 ACTIVA DESACTIVA
            if (readers[posicionLista + posicionExtra].active == 1){
                readers[posicionLista + posicionExtra].active = 0;
                gotoxy(posX + 3, posY + posicionLista);
                color(4);
                char nombreAdaptado[25] = "";;
                char nombreApellidoLector[30] = "";;
                strcat(nombreApellidoLector, readers[posicionLista + posicionExtra].surName);
                strcat(nombreApellidoLector, " ");
                strcat(nombreApellidoLector, readers[posicionLista + posicionExtra].name);
                strncpy(nombreAdaptado, nombreApellidoLector + 0, 25);
                nombreAdaptado[24] = '\0';
                printf("%s %s", nombreAdaptado, "(X)");
                color(7);
                hizoCambios = 1;
                CambiarBotonActivar(readers[posicionLista + posicionExtra].active, 13);
                CambiarBotonAdmin(readers[posicionLista + posicionExtra].administrator);
            } else {
                readers[posicionLista + posicionExtra].active = 1;
                gotoxy(posX + 3, posY + posicionLista);
                color(7);
                printf("                             ");
                gotoxy(posX + 3, posY + posicionLista);
                printf("%s %s", readers[posicionLista + posicionExtra].surName,readers[posicionLista + posicionExtra].name);
                hizoCambios = 1;
                CambiarBotonActivar(readers[posicionLista + posicionExtra].active, 13);
                CambiarBotonAdmin(readers[posicionLista + posicionExtra].administrator);
            }
            int cambioAplicado = 0;
            // RECORRO EL ARREGLO COMPLETO, BUSCO EL QUE COINCIDA CON EL QUE ESTOY MODIFICANDO Y HAGO EL MISMO CAMBIO
            for (int i = 0; i < validosAll && cambioAplicado == 0; i++){
                if (readersAll[i].id == readers[posicionLista + posicionExtra].id){
                    cambioAplicado = 1;
                    readersAll[i].active = readers[posicionLista + posicionExtra].active;
                }
            }
            break;
        case F3: // F3 MODIFICA
            resultado = ModificarLector(&readers[posicionLista + posicionExtra]);
            if (resultado == 1){
                EditarLectorEnArchivo(archivoLectores, readers[posicionLista + posicionExtra]);
            }
            MenuUsersAdmin(0);
            ListarLectores(readers, validos, 0, 0);
            MostrarInfoLector(readers[0]);
            WatchFavourites(readers[0], books, librosValidos);
            CambiarBotonActivar(readers[0].active, 13);
            CambiarBotonAdmin(readers[0].administrator);
            posicionLista = 0;
            posicionExtra = 0;
            break;
        case F4: // F4 ORDENA
            OrdenarLectores(readers, validos, campo); // campo 0 ordena por nombre, campo 1 ordena por ID
            MenuUsersAdmin(0);
            ListarLectores(readers, validos, 0, 0);
            MostrarInfoLector(readers[0]);
            WatchFavourites(readers[0], books, librosValidos);
            CambiarBotonActivar(readers[0].active, 13);
            CambiarBotonAdmin(readers[0].administrator);
            posicionLista = 0;
            posicionExtra = 0;
            if (campo == 0){
                campo = 1;
                gotoxy(40, 24);
                printf("%c F4-VOLVER  %c", LINECUTR, LINECUTL);

            } else if (campo == 1){
                campo = 0;
                gotoxy(40, 24);
                printf("%c F4-ORDENAR %c", LINECUTR, LINECUTL);
            }
            break;
        case F5: // F5 CONVERTIR USUARIO EN ADMINISTRADOR
            if (readers[posicionLista + posicionExtra].administrator == 1){
                readers[posicionLista + posicionExtra].administrator = 0;
                CambiarBotonAdmin(0);
            } else {
                readers[posicionLista + posicionExtra].administrator = 1;
                CambiarBotonAdmin(1);
            }
            hizoCambios = 1;
            MostrarInfoLector(readers[posicionLista + posicionExtra]);
            cambioAplicado = 0;
            // RECORRO EL ARREGLO COMPLETO, BUSCO EL QUE COINCIDA CON EL QUE ESTOY MODIFICANDO Y HAGO EL MISMO CAMBIO
            for (int i = 0; i < validosAll && cambioAplicado == 0; i++){
                if (readersAll[i].id == readers[posicionLista + posicionExtra].id){
                    cambioAplicado = 1;
                    readersAll[i].administrator = readers[posicionLista + posicionExtra].administrator;
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
                        // Guardar cambios del reader
                        GuardarLectores(archivoLectores, readersAll, validosAll);
                    }
                }
                while (salir == 0);
            }
            break;
        }
    } while (tecla != ESC);
    if (validos > 0){
        free(readers);
    }
}

int BuscarReaderNombreMenor(stReader readers[], int validos, int posicionInicial, int campo){
    int i = posicionInicial;
    int posicionMenor = posicionInicial;
    if (campo == 0) {
        char nombre[SURNAME];
        strcpy(nombre, readers[i].surName);
        while (i < validos){
            if (strcmp(readers[i].surName, nombre) < 0){
                strcpy(nombre, readers[i].surName);
                posicionMenor = i;
            }
            i++;
        }
    } else if (campo == 1){
        int id;
        id = readers[i].id;
        while (i < validos){
            if (readers[i].id < id){
                id = readers[i].id;
                posicionMenor = i;
            }
            i++;
        }
    }
    return posicionMenor;
}

void IntercambiarValoresLectores(stReader readers[], int posicionMenor, int posicionActual){
    stReader readerAux;
    readerAux = readers[posicionMenor];
    readers[posicionMenor] = readers[posicionActual];
    readers[posicionActual] = readerAux;
}

void OrdenarLectores(stReader readers[], int validos, int campo){
    int posicionMenor = 0;
    int i = 0;
    while (i < validos - 1){
        posicionMenor = BuscarReaderNombreMenor(readers, validos, i, campo);
        IntercambiarValoresLectores(readers, posicionMenor, i);
        i++;
    }
}

int ModificarLector(stReader* readerAux){
    hidecursor(1);
    char teclaModificarLector = 0;
    int resultado = 0;
    MenuNuevoLector();
    gotoxy(17,6);
    printf("%s", readerAux->name);
    gotoxy(17,7);
    printf("%s", readerAux->surName);
    gotoxy(17,8);
    printf("%s", readerAux->address);
    gotoxy(17,9);
    printf("%s", readerAux->phone);
    gotoxy(17,10);
    printf("%s", readerAux->mail);

    char palabra[MAIL]; // USO LA CONSTANTE MAIL YA QUE ES EL CAMPO MAS GRANDE POR LO TANTO EN ESE ARREGLO ENTRAN TODAS LAS ANTERIORES
    do{
        strcpy(palabra, readerAux->name);
        teclaModificarLector = ModificarPalabra(palabra, readerAux->name,17, 6, NAME);
        if (strlen(palabra) > 0 && teclaModificarLector != ESC){
            strcpy(readerAux->name, palabra); // Si  no aprete esc en el campo anterior, guardo la palabra
        } else if (teclaModificarLector !=ESC) { // Me aseguro que el if rompio por la condicion de strlen
            MensajesAdvertencias("EL NOMBRE NO PUEDE ESTAR VACIO.", 17,12);
            gotoxy(17,6);
            color(15);
            printf("%s", readerAux->name);
            teclaModificarLector = 0;
        }
    } while (teclaModificarLector != ESC && teclaModificarLector != ENTER);

    if (teclaModificarLector != ESC){
        do{
            strcpy(palabra, readerAux->surName);
            teclaModificarLector = ModificarPalabra(palabra, readerAux->surName, 17, 7, SURNAME);
            if (strlen(palabra) > 0 && teclaModificarLector != ESC){
                strcpy(readerAux->surName, palabra); // Si  no aprete esc en el campo anterior, guardo la palabra
            } else if (teclaModificarLector !=ESC) { // Me aseguro que el if rompio por la condicion de strlen
                MensajesAdvertencias("EL APELLIDO NO PUEDE ESTAR VACIO.", 17,12);
                gotoxy(17,7);
                color(15);
                printf("%s", readerAux->surName);
                teclaModificarLector = 0;
            }

        } while (teclaModificarLector != ESC && teclaModificarLector != ENTER);
    }

    if (teclaModificarLector != ESC){
        strcpy(readerAux->surName, palabra); // Si  no aprete esc en el campo anterior, guardo la palabra
        teclaModificarLector = ModificarPalabra(palabra, readerAux->address, 17, 8, ADDRESS);
        if (teclaModificarLector != ESC){
            strcpy(readerAux->address, palabra); // Si  no aprete esc en el campo anterior, guardo la palabra
            teclaModificarLector = ModificarPalabra(palabra, readerAux->phone, 17, 9, PHONE);
            if (teclaModificarLector != ESC){
                strcpy(readerAux->phone, palabra); // Si  no aprete esc en el campo anterior, guardo la palabra
                int mailValido = 0;
                do {
                    teclaModificarLector = ModificarPalabra(palabra, readerAux->mail, 17, 10, MAIL);
                    if (strlen(palabra) > 0 && teclaModificarLector != ESC)
                    {
                        if (strcmp(palabra, readerAux->mail) != 0){
                            int mailOk = ValidaMailCorrecto(palabra);
                            if (mailOk == 1){
                                int mailExiste = ValidaExistenciaMail(archivoLectores, palabra);
                                if (mailExiste == 1){ // SI EL MAIL NO EXISTE ENTRA
                                    strcpy(readerAux->mail, palabra);
                                    mailValido = 1;
                                } else {
                                    MensajesAdvertencias("EL MAIL PERTENECE A OTRO USUARIO.", 17,12);
                                    gotoxy(17,10);
                                    printf("%s", readerAux->mail);
                                }
                            } else {
                                MensajesAdvertencias("EL MAIL NO ES VALIDO.", 17,12);
                                gotoxy(17,10);
                                printf("%s", readerAux->mail);
                            }
                        } else {
                            mailValido = 1;
                        }
                    } else if (teclaModificarLector != ESC){
                        MensajesAdvertencias("EL MAIL NO PUEDE ESTAR VACIO.", 17,12);
                        gotoxy(17,10);
                        printf("%s", readerAux->mail);
                    }
                } while (mailValido == 0 && teclaModificarLector != ESC);
                if (teclaModificarLector !=ESC){
                    teclaModificarLector = CapturarPalabra(palabra, 17, 11, PASSWORD, 0, 0);
                    if (teclaModificarLector != ESC && strlen(palabra) > 0){
                        strcpy(readerAux->password, palabra);
                    }
                }
            }
        }
    }


    if (teclaModificarLector != ESC){
        resultado = 1;
    }
    hidecursor(0);
    return resultado;
}

void WatchFavourites(stReader reader, stBook books[], int cantidadLibros){
    int i = 0;
    int j = 0;
    int favoritoEncontrado = 0;
    while (i < reader.cantidadFav) {
        while (j < cantidadLibros && favoritoEncontrado == 0){
            if (reader.favourite[i] == books[j].id){
                gotoxy(43, 11 + i);
                printf("%s", books[j].name);
                favoritoEncontrado = 1;
            }
            j++;
        }
        favoritoEncontrado = 0;
        j = 0;
        i++;
    }
}

void MostrarInfoLector(stReader reader) {
    color(3);
    gotoxy(43,4);
    printf("MAIL:");
    gotoxy(43,5);
    printf("DIRECCION:");
    gotoxy(43,6);
    printf("TELEFONO:");
    gotoxy(43,7);
    printf("ADMINISTRADOR: ");
    gotoxy(43,8);
    printf("CANTIDAD DE FAVORITOS: ");
    color(7);
    gotoxy(49, 4);
    printf("%s", reader.mail);
    gotoxy(54,5);
    printf("%s", reader.address);
    gotoxy(53,6);
    printf("%s", reader.phone);
    if (reader.administrator == 0){
        gotoxy(58,7);
        printf("NO");
    } else {
        gotoxy(58,7);
        printf("SI");
    }
    gotoxy(66,8);
    printf("%i", reader.cantidadFav);
}
