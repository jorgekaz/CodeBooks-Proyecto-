#include "libros.h"

void MostrarInfoLibro(stBook book) {
    color(3);
    gotoxy(41,4);
    printf("AUTOR: ");
    gotoxy(41,6);
    printf("EDITORIAL: ");
    gotoxy(41,8);
    printf("GENERO: ");
    gotoxy(41,10);
    printf("ISBN: ");
    color(7);
    gotoxy(41,5);
    printf("%s", book.author);
    gotoxy(41,7);
    printf("%s", book.editorial);
    gotoxy(41,9);
    printf("%s", book.gender);
    gotoxy(41,11);
    printf("%s", book.ISBN);
    // Si la info es muy larga hay que acomodarla en lineas
    if (strlen(book.description) > 28){
        gotoxy(41,12);
        color(3);
        printf("DESC: ");
        color(7);
        float cantidaLineas = strlen(book.description) / 28;
        int longitud = floor(cantidaLineas);
        for (int j = 0; j <= longitud; j++){
            int coordx = 0;
            for (int i = 0 + 28*j; i < 28 + 28*j && book.description[i] != '\0'; i++){
                gotoxy(41 + coordx, 13 + j);
                printf("%c", book.description[i]);
                coordx++;
            }
        }
    } else {
        gotoxy(41,12);
        color(3);
        printf("DESC: ");
        color(7);
        gotoxy(41,13);
        printf("%s", book.description);
    }
}

int BuscarLibroNombreMenor(stBook books[], int validos, int posicionInicial, int campo){
    int i = posicionInicial;
    int posicionMenor = posicionInicial;
    if (campo == 0) {
        char nombre[TITLE];
        strcpy(nombre, books[i].name);
        strupr(nombre);
        while (i < validos){
            char nombreCompara[TITLE]; // UTILIZAMOS OTRA VARIABLE PARA PODER PASARLO A MAYUSCULA Y ORDENAR SIN AFECTAR EL NOMBRE ORIGINAL
            strcpy(nombreCompara, books[i].name);
            strupr(nombreCompara);
            if (strcmp(nombreCompara, nombre) < 0){
                strcpy(nombre, nombreCompara);
                posicionMenor = i;
            }
            i++;
        }
    } else if (campo == 1){
        int id;
        id = books[i].id;
        while (i < validos){
            if (books[i].id < id){
                id = books[i].id;
                posicionMenor = i;
            }
            i++;
        }
    }
    return posicionMenor;
}

void IntercambiarValores(stBook books[], int posicionMenor, int posicionActual){
    stBook bookAux;
    bookAux = books[posicionMenor];
    books[posicionMenor] = books[posicionActual];
    books[posicionActual] = bookAux;
}

void OrdenarLibros(stBook books[], int validos, int campo){
    int posicionMenor = 0;
    int i = 0;
    while (i < validos - 1){
        posicionMenor = BuscarLibroNombreMenor(books, validos, i, campo);
        IntercambiarValores(books, posicionMenor, i);
        i++;
    }
}

void ListarTodosLibros(stBook books[], int validos, int primerLibro, int libroSeleccionado){
    int posicionLista = 0;
    for (int i = primerLibro; i < validos && posicionLista < 11; i++)
    {
        color(7);
        gotoxy(8,9 + posicionLista);
        posicionLista++;
        if (books[i].active == 1){
            printf("%s", books[i].name);
        } else {
            color(4);
            char nombreLibro[30];
            strncpy(nombreLibro, books[i].name + 0, 25);
            nombreLibro[24] = '\0';
            printf("%s %s", nombreLibro, "(X)");
            color(7);
        }
    }
    // Selecciono el libro
    gotoxy(5, 9 + libroSeleccionado);
    color(4);
    printf("-%c", 784);
    color(7);

}

int CrearNuevoLibro(stBook* bookAux){
    char teclaNuevoLibro = 0;
    int resultado = 0;
    MenuNuevoLibro();
    do{
        teclaNuevoLibro = CapturarPalabra(bookAux->name, 17, 6, 30, 0, 1);
        if (strlen(bookAux->name) <= 0 && teclaNuevoLibro != ESC){
            MensajesAdvertencias("ESTE CAMPO NO PUEDE ESTAR VACIO.", 17,6);
        }
    } while (strlen(bookAux->name) <= 0 && teclaNuevoLibro != ESC);
    if (teclaNuevoLibro != ESC){
        do{
            teclaNuevoLibro = CapturarPalabra(bookAux->author, 17, 7, 30, 0, 1);
            if (strlen(bookAux->author) <= 0 && teclaNuevoLibro != ESC){
                MensajesAdvertencias("ESTE CAMPO NO PUEDE ESTAR VACIO.", 17,7);
            }
        } while (strlen(bookAux->author) <= 0 && teclaNuevoLibro != ESC);
    }
    if (teclaNuevoLibro != ESC){
        do{
            teclaNuevoLibro = CapturarPalabra(bookAux->editorial, 17, 8, 30, 0, 1);
            if (strlen(bookAux->editorial) <= 0 && teclaNuevoLibro != ESC){
                MensajesAdvertencias("ESTE CAMPO NO PUEDE ESTAR VACIO.", 17,8);
            }
        } while (strlen(bookAux->editorial) <= 0 && teclaNuevoLibro != ESC);
    }
    if (teclaNuevoLibro != ESC){
        do{
            teclaNuevoLibro = CapturarPalabra(bookAux->gender, 17, 9, 20, 0, 1);
            if (strlen(bookAux->gender) <= 0 && teclaNuevoLibro != ESC){
                MensajesAdvertencias("ESTE CAMPO NO PUEDE ESTAR VACIO.", 17,9);
            }
        } while (strlen(bookAux->gender) <= 0 && teclaNuevoLibro != ESC);
    }
    if (teclaNuevoLibro != ESC){
        do{
            teclaNuevoLibro = CapturarPalabra(bookAux->ISBN, 17, 10, 20, 0, 1);
            if (strlen(bookAux->ISBN) <= 0 && teclaNuevoLibro != ESC){
                MensajesAdvertencias("ESTE CAMPO NO PUEDE ESTAR VACIO.", 17,10);
            }
        } while (strlen(bookAux->ISBN) <= 0 && teclaNuevoLibro != ESC);
    }
    if (teclaNuevoLibro != ESC){
        do{
            teclaNuevoLibro = CapturarPalabra(bookAux->description, 17, 11, 200, 0, 1);
            if (strlen(bookAux->description) <= 0 && teclaNuevoLibro != ESC){
                MensajesAdvertencias("ESTE CAMPO NO PUEDE ESTAR VACIO.", 17,11);
            }
        }while (strlen(bookAux->description) <= 0 && teclaNuevoLibro != ESC);
    }
    if (teclaNuevoLibro != ESC){
        resultado = 1;
    }
    return resultado;
}

int ModificarLibro(stBook* bookAux){
    hidecursor(1);
    char teclaModificarLibro = 0;
    int resultado = 0;
    MenuNuevoLibro();
    gotoxy(17,6);
    printf("%s", bookAux->name);
    gotoxy(17,7);
    printf("%s", bookAux->author);
    gotoxy(17,8);
    printf("%s", bookAux->editorial);
    gotoxy(17,9);
    printf("%s", bookAux->gender);
    gotoxy(17,10);
    printf("%s", bookAux->ISBN);
    if (strlen(bookAux->description) > 63){
        float longitud = strlen(bookAux->description) / 63;
        int cantidadLineas = floor(longitud);
        for (int j = 0; j <= cantidadLineas; j++){ // j = lineas que ocupa la descripcion.. lineas de 28 caracteres.
            int coordx = 0;
            for (int i = 0 + 63*j; i < 63 + 63*j && bookAux->description[i] != '\0'; i++){
                gotoxy(17 + coordx, 11 + j);
                printf("%c", bookAux->description[i]);
                coordx++;
            }
        }
    } else {
        gotoxy(17,11);
        printf("%s", bookAux->description);
    }
    // EMPIEZA EDICION
    char palabra[DESCRIPTION]; // Lo inicializo asi porque es el maximo de caracteres que puedo necesitar
    teclaModificarLibro = ModificarPalabra(palabra, bookAux->name,17, 6, NAME);
    if (strlen(palabra) > 0 && teclaModificarLibro != ESC){
        strcpy(bookAux->name, palabra);
        resultado = 1; // SI YA HUBO CAMBIO SE GUARDA
    }
    if (teclaModificarLibro != ESC){
        teclaModificarLibro = ModificarPalabra(palabra, bookAux->author, 17, 7, AUTHOR);
        if (strlen(palabra) > 0 && teclaModificarLibro != ESC){
            strcpy(bookAux->author, palabra);
            resultado = 1; // SI YA HUBO CAMBIO SE GUARDA
        }
    }

    if (teclaModificarLibro != ESC){
        teclaModificarLibro = ModificarPalabra(palabra, bookAux->editorial, 17, 8, EDITORIAL);
        if (strlen(palabra) > 0 && teclaModificarLibro != ESC){
            strcpy(bookAux->editorial, palabra);
            resultado = 1; // SI YA HUBO CAMBIO SE GUARDA
        }
    }
    if (teclaModificarLibro != ESC){
        teclaModificarLibro = ModificarPalabra(palabra, bookAux->gender, 17, 9, GENDER);
        if (strlen(palabra) > 0 && teclaModificarLibro != ESC){
            strcpy(bookAux->gender, palabra);
            resultado = 1; // SI YA HUBO CAMBIO SE GUARDA
        }
    }
    if (teclaModificarLibro != ESC){
        teclaModificarLibro = ModificarPalabra(palabra, bookAux->ISBN, 17, 10, MAXISBN);
        if (strlen(palabra) > 0 && teclaModificarLibro != ESC){
            strcpy(bookAux->ISBN, palabra);
            resultado = 1; // SI YA HUBO CAMBIO SE GUARDA
        }
    }
    if (teclaModificarLibro != ESC){
        teclaModificarLibro = ModificarPalabra(palabra, bookAux->description, 17, 11, DESCRIPTION);
        if (strlen(palabra) > 0 && teclaModificarLibro != ESC){
            strcpy(bookAux->description, palabra);
            resultado = 1; // SI YA HUBO CAMBIO SE GUARDA
        }
    }

    hidecursor(0);
    return resultado;
}

void AdministrateBooks(const char archivoLibros[]){
    hidecursor(0);
    char tecla = 0;
    int validos = 0;
    int activeWindow = 0; // Me va a indicar donde estoy parado de la ventana 0, o en la 1 buscar
    int hizoCambios = 0;
    /*
    Creamos un arreglo dinamico con todos los libros que va a ir almacenando todos los cambios
    y luego es el arreglo que se va a guardar, ya que el arreglo con el que trabajamos va a ir cambiando
    segun el filtro de busqueda que apliquemos y si grabo filtrado solo graba lo que hay en ese arreglo mas chico
    */
    stBook book;
    stBook* books;
    stBook* booksAll;
    int validosAll = 0;

    // Leer los libros para saber la cantidad y generar un arreglo dinamico
    int cantidadLibros = CantidadRegistros(archivoLibros, sizeof(stBook));
    if (cantidadLibros > 0){
        // Creo arreglo dinamico
        booksAll = (stBook*) malloc (cantidadLibros * sizeof(stBook));
        books = (stBook*) malloc (cantidadLibros * sizeof(stBook));
        validosAll = PasarLibrosAlArreglo(archivoLibros, booksAll, "");
        validos = PasarLibrosAlArreglo(archivoLibros, books, "");
        // Muestro listado con el primero seleccionado
        ListarTodosLibros(books, validos, 0, 0);
        // Muestro la data del primer libro.
        MostrarInfoLibro(books[0]);
        CambiarBotonActivar(books[0].active, 13);
    } else {
        gotoxy(5,9);
        printf("NO HAY LIBROS EN LA B.D.");
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
        case 0:
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
                for (int x = 7; x < 37; x++){
                    gotoxy(x, 6);
                    printf(" ");
                }
                break;
            case 0:
                // ALGORITMO DE BUSQUEDA
                hidecursor(1);
                MenuBooksAdmin(1);
                ListarTodosLibros(books, validos, posicionExtra, posicionLista);
                MostrarInfoLibro(books[posicionLista + posicionExtra]);
                CambiarBotonActivar(books[posicionLista + posicionExtra].active, 13);
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
                validos = PasarLibrosAlArreglo(archivoLibros, books, filtro);
                if (validos > 0){
                    // PASO LOS MODIFICADOS DEL ARREGLO BOOKSALL AL BOOKS FILTRADO ASI NO PIERDO LOS CAMBIOS
                    for (int i = 0; i < validos; i++){
                        int libroModificado = 0;
                        for (int j=0; j < validosAll && libroModificado == 0; j++){
                            if (books[i].id == booksAll[j].id){
                                libroModificado = 1;
                                books[i].active = booksAll[j].active;
                            }
                        }
                    }
                    MenuBooksAdmin(0);
                    VaciarVentanas(5,36,9,19); // Vacio ventana libros
                    VaciarVentanas(41, 74, 4, 20); // Vacio ventana info libros
                    ListarTodosLibros(books, validos,0 ,0);
                    MostrarInfoLibro(books[0]);
                    CambiarBotonActivar(books[0].active, 13);
                    VaciarVentanas(5,36, 6,6); // Vacio ventana busqueda
                    posX = 5;
                    posY = 9;
                    gotoxy(posX, posY);
                    activeWindow = 0;
                    posicionLista = 0;
                    posicionExtra = 0;
                } else {
                    //VaciarVentanas(5,36,9,19);
                    MenuBooksAdmin(0);
                    MensajesAdvertencias("NO SE ENCONTRARON COINCIDENCIAS", 4, 22);
                    validos = PasarLibrosAlArreglo(archivoLibros, books, "");
                    ListarTodosLibros(books, validos, 0, 0);
                    MostrarInfoLibro(books[0]);
                    CambiarBotonActivar(books[0].active, 13);
                    posicionLista = 0;
                    posicionExtra = 0;
                    activeWindow = 0;
                    posX = 5;
                    posY = 9;
                }
                hidecursor(0);
                break;
            }
            break;
        case UPARROW: // flecha arriba
            if (posY + posicionLista + posicionExtra > posY && activeWindow == 0){
                gotoxy(posX, posY + posicionLista);
                color(7);
                printf("  ");
                if (posicionExtra > 0 && posicionLista == 0) {
                    posicionExtra--;
                    VaciarVentanas(5,36,9,19); // Vacio ventana libros
                    ListarTodosLibros(books, validos, posicionExtra, posicionLista);
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
                CambiarBotonActivar(books[posicionLista+posicionExtra].active, 13);
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
                    VaciarVentanas(41, 74, 4, 20);
                    // Muestro la data
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                } else if (posicionExtra + posicionLista < validos - 1) {
                    posicionExtra++;
                    VaciarVentanas(5,36,9,19); // Vacio ventana libros
                    ListarTodosLibros(books, validos, posicionExtra, posicionLista);
                    VaciarVentanas(41, 74, 4, 20);
                    MostrarInfoLibro(books[posicionLista + posicionExtra]);
                }
                CambiarBotonActivar(books[posicionLista+posicionExtra].active, 13);
            }
            break;
        case F1: // AGREGAR LIBRO
            GuardarLibros(archivoLibros, booksAll, validosAll); // ANTES DE DAR DE ALTA GUARDO CUALQUIER CAMBIO EFECTUADO
            validos = PasarLibrosAlArreglo(archivoLibros, books, ""); // Vuelvo a crear el arreglo con todos los libros por si tenia un valido filtrado en la busqueda
            hidecursor(1);
            int resultado = CrearNuevoLibro(&book);
            hidecursor(0);
            if (resultado == 1){
                if (validos == 0){
                    book.id = 1;
                } else{
                    book.id = books[validos - 1].id + 1;
                }
                book.active = 1;
                int resultado = GrabarLibro(archivoLibros, book);
                if (resultado == 1){
                    MostrarMensaje("LIBRO AGREGADO EN FORMA SATISFACTORIA.");
                    validos++;
                    if (validos > 1){
                        free(books);
                        free(booksAll);
                    }
                    cantidadLibros = CantidadRegistros(archivoLibros, sizeof(stBook));
                    if (cantidadLibros > 0){
                        // VUELVO A CREAR LOS 2 ARREGLOS
                        books = (stBook*) malloc (cantidadLibros * sizeof(stBook));
                        booksAll = (stBook*) malloc (cantidadLibros * sizeof(stBook));
                        validos = PasarLibrosAlArreglo(archivoLibros, books, "");
                        validosAll = PasarLibrosAlArreglo(archivoLibros, booksAll, "");
                    }
                } else {
                    MostrarMensaje("ERROR, NO SE LOGRO AGREGAR EL LIBRO A LA B.D.");
                }
            }
            MenuBooksAdmin(0);
            ListarTodosLibros(books, validos, 0, 0);
            MostrarInfoLibro(books[0]);
            CambiarBotonActivar(books[0].active, 13);
            posicionLista = 0;
            posicionExtra = 0;
            break;
        case F2: // ACTIVAR / DESACTIVAR LIBRO
            if (books[posicionLista + posicionExtra].active == 1){
                books[posicionLista + posicionExtra].active = 0;
                gotoxy(posX + 3, posY + posicionLista);
                color(4);
                char nombreLibro[30];
                strncpy(nombreLibro, books[posicionLista + posicionExtra].name + 0, 25);
                nombreLibro[24] = '\0';
                printf("%s %s", nombreLibro, "(X)");
                color(7);
                hizoCambios = 1;
                CambiarBotonActivar(books[posicionLista + posicionExtra].active, 13);
            } else {
                books[posicionLista + posicionExtra].active = 1;
                gotoxy(posX + 3, posY + posicionLista);
                color(7);
                printf("                             ");
                gotoxy(posX + 3, posY + posicionLista);
                printf("%s", books[posicionLista + posicionExtra].name);
                hizoCambios = 1;
                CambiarBotonActivar(books[posicionLista + posicionExtra].active, 13);
            }
            int cambioAplicado = 0;
            // RECORRO EL ARREGLO COMPLETO, BUSCO EL QUE COINCIDA CON EL QUE ESTOY MODIFICANDO Y HAGO EL MISMO CAMBIO
            for (int i = 0; i < validosAll && cambioAplicado == 0; i++){
                if (booksAll[i].id == books[posicionLista + posicionExtra].id){
                    cambioAplicado = 1;
                    booksAll[i].active = books[posicionLista + posicionExtra].active;
                }
            }
            break;
        case F3: // MODIFICAR
            resultado = ModificarLibro(&books[posicionLista + posicionExtra]);
            if (resultado == 1){
                EditarLibroEnArchivo(archivoLibros, books[posicionLista + posicionExtra]);
            }
            MenuBooksAdmin(0);
            ListarTodosLibros(books, validos, 0, 0);
            MostrarInfoLibro(books[0]);
            CambiarBotonActivar(books[0].active, 13);
            posicionLista = 0;
            posicionExtra = 0;
            break;
        case F4: // ORDENAR
            OrdenarLibros(books, validos, campo); // campo 0 ordena por nombre, campo 1 ordena por ID
            MenuBooksAdmin(0);
            ListarTodosLibros(books, validos, 0, 0);
            MostrarInfoLibro(books[0]);
            CambiarBotonActivar(books[0].active, 13);
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
        case F5: // GUARDAR
            //validos = PasarLibrosAlArreglo(archivoLibros, books, ""); // ANTES DE GUARDAR RESTAURO EL ARREGLO DE LIBROS POR SI ESTA FILTRANDO
            resultado = GuardarLibros(archivoLibros, booksAll, validosAll);
            if (resultado > 0){
                MostrarMensaje("INFORMACION GUARDADA SATISTACTORIAMENTE.");
            } else {
                MostrarMensaje("ERROR AL GUARDAR.");
            }
            hizoCambios = 0;
            MenuBooksAdmin(0);
            ListarTodosLibros(books, validos, 0, 0);
            MostrarInfoLibro(books[0]);
            CambiarBotonActivar(books[0].active, 13);
            posicionLista = 0;
            posicionExtra = 0;
            break;
        case ESC: // SALIR
            if (hizoCambios == 1){
                MostrarMensaje("HA HECHO CAMBIOS. DESEA GUARDAR? (S/N)");
                int salir = 0;
                do{
                    salir = getch();
                    if (salir == 115 || salir == 83){
                        GuardarLibros(archivoLibros, books, validos);
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
    hidecursor(0);
}



