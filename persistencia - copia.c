#include "persistencia.h"

int CantidadRegistros(const char nombreArchivo[], int archivo){ // 0 lectores, 1 libros, 2 mensajes
    int cantidadRegistros = 0;
    FILE* pFile = fopen(nombreArchivo, "rb");
    if (pFile != NULL){
        fseek (pFile, 0, SEEK_END);
        if (archivo == 0) {
            cantidadRegistros = ftell (pFile) / sizeof (stReader);
        } else if (archivo == 1){
            cantidadRegistros = ftell (pFile) / sizeof (stBook);
        } else {
            cantidadRegistros = ftell (pFile) / sizeof (stMensaje);
        }
        fclose(pFile);
    }
    return cantidadRegistros;
}

int RegistrarUsuario(stReader reader, stReader ultimoReader, const char fileName[]){
    int resultado = 0;
    int cantidadRegostros = CantidadRegistros(fileName, 0);
    FILE* pFile = fopen(fileName, "rb");
    if (pFile != NULL){
        fseek(pFile, (cantidadRegostros - 1)*sizeof(stReader), SEEK_SET);
        fread(&ultimoReader, sizeof(stReader), 1, pFile);
        fclose(pFile);
        reader.id = ultimoReader.id + 1;
    } else {
        reader.id = 1;
    }
    pFile = fopen(fileName, "ab");
    if (pFile != NULL){
        resultado = fwrite(&reader, sizeof(stReader), 1, pFile);
        fclose(pFile);
    }
    return resultado;
}

void GuardarInfoLector(const char nombreArchivo[], stReader readerModificated){
    stReader reader;
    int flag = 0;
    FILE* pFile = fopen(nombreArchivo, "r+b");
    if (pFile != NULL){
        while (flag == 0 && fread(&reader, sizeof(stReader), 1, pFile) > 0 ){
            if (reader.id == readerModificated.id) {
                // Encontre el registro que debo sobrescribir
                flag = 1;
                int posicion = ftell(pFile) - sizeof(stReader);
                fseek(pFile,posicion,SEEK_SET);
                if (fwrite(&readerModificated, sizeof(stReader), 1, pFile) > 0){
                    MostrarMensaje("DATOS MODIFICADOS CORRECTAMENTE.");
                } else {
                    MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
                }
            }
        }
        fclose(pFile);
    }else {
        MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
    }
}

int GuardarCambioMensajes(const char nombreArchivo[], stMensaje* mensajeModificated, int validos){
    int i = 0;
    FILE* pFile = fopen(nombreArchivo, "wb");
    if (pFile != NULL){
        while (i < validos){
            fwrite(&mensajeModificated[i], sizeof(stMensaje), 1, pFile);
            i++;
        }
        fclose(pFile);
    }else {
        MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
    }
    return i;
}

int GrabarLibro(const char nombreArchivo[], stBook libroModificado){
    int resultado = 0;
    FILE* pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        if (fwrite(&libroModificado, sizeof(stBook), 1, pFile) > 0){
            resultado = 1;
        } else {
            resultado = 0;
        }
        fclose(pFile);
    }else {
        resultado = 0;
    }
    return resultado;
}

int PasarLibrosActivosAlArreglo(const char nombreArchivo[], stBook* books, char filtro[]){
    FILE* pArchivo = fopen(nombreArchivo, "rb");
    stBook book;
    int i = 0;
    if (pArchivo != NULL){
        while (fread(&book, sizeof(stBook), 1, pArchivo) > 0){
            if (strlen(filtro) == 0 && book.active == 1){
                books[i] = book;
                i++;
            } else {
                if (strstr(book.name, filtro) != NULL && book.active == 1){
                    books[i] = book;
                    i++;
                }
            }
        }
        fclose(pArchivo);

    } else printf("ERROR");
    return i;
}

int PasarLibrosAlArreglo(const char nombreArchivo[], stBook* books, char filtro[]){
    FILE* pArchivo = fopen(nombreArchivo, "rb");
    stBook book;
    int i = 0;
    if (pArchivo != NULL){
        while (fread(&book, sizeof(stBook), 1, pArchivo) > 0){
            if (strlen(filtro) == 0){
                books[i] = book;
                i++;
            } else {
                if (strstr(book.name, filtro) != NULL){
                    books[i] = book;
                    i++;
                }
            }
        }
        fclose(pArchivo);

    } else printf("ERROR");
    return i;
}

int PasarLectoresAlArreglo(const char nombreArchivo[], stReader* readers, char filtro[]){
    FILE* pArchivo = fopen(nombreArchivo, "rb");
    stReader reader;
    int i = 0;
    if (pArchivo != NULL){
        while (fread(&reader, sizeof(stReader), 1, pArchivo) > 0){
            if (strlen(filtro) == 0){
                readers[i] = reader;
                i++;
            } else {
                char surName[SURNAME];
                char name[NAME];
                strcpy(surName, reader.surName);
                strcpy(name, reader.name);
                strupr(surName);
                strupr(name);
                strupr(filtro);
                if (strstr(surName, filtro) != NULL){ // FILTRA X APELLIDO
                    readers[i] = reader;
                    i++;
                } else if (strstr(name, filtro) != NULL){ // FILTRA X NOMBRE
                    readers[i] = reader;
                    i++;
                }
            }
        }
        fclose(pArchivo);

    } else printf("ERROR");
    return i;
}

void VerificarUserPassword(const char fileName[], stReader* readerReturn, int* userLogued, char username[], char password[]){
    stReader reader;
    int flag = 0;
    FILE* pFile = fopen(fileName, "rb");
    if (pFile != NULL){
        while (fread(&reader, sizeof(stReader), 1, pFile) > 0 && flag == 0){
            if (strcmp(username, reader.mail) == 0 && strcmp(password, reader.password) == 0){
                flag = 1;
                *readerReturn = reader;
                if (reader.administrator == 1){
                    *userLogued = 2;
                } else {
                    *userLogued = 1;
                }
                if (reader.active == 0){
                    *userLogued = 3;
                }
            } else if (strcmp(username, "ADMIN") == 0 && strcmp(password, "ADMIN") == 0){
                *userLogued = 2;
                readerReturn->active = 1;
                readerReturn->cantidadFav = 0;
                strcpy(readerReturn->name, "ADMIN");
                strcpy(readerReturn->surName, " ");
                readerReturn->id = -1;
                readerReturn->administrator = 1;

            }
        }
        fclose(pFile);
    }
}

void GrabarMensaje(const char nombreArchivo[], char nombreApellido[], char mail[], int tipoConsulta){
    stMensaje mensaje;
    stMensaje ultimoMensaje;
    mensaje.estado = 0;
    mensaje.tipoConsulta = tipoConsulta;
    strcpy(mensaje.nombreApellido, nombreApellido);
    strcpy(mensaje.mail, mail);
    char fecha[DATES];
    ObtenerFecha(fecha);
    strcpy(mensaje.fecha, fecha);
    int cantidadRegostros = CantidadRegistros(nombreArchivo, 2);
    FILE* pFile = fopen(nombreArchivo, "rb");
    if (pFile != NULL){
        fseek(pFile, (cantidadRegostros-1)* sizeof(stMensaje), SEEK_SET);
        fread(&ultimoMensaje, sizeof(stMensaje), 1, pFile);
        fclose(pFile);
    }
    mensaje.id = ultimoMensaje.id + 1;
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        if (fwrite(&mensaje, sizeof(stMensaje), 1, pFile) > 0){
            MostrarMensaje("DATOS ENVIADOS AL ADMINISTRADOR.");
        }
        fclose(pFile);
    }
}

int PasarMensajesAlArreglo(const char nombreArchivo[], stMensaje* mensajes){
    FILE* pArchivo = fopen(nombreArchivo, "rb");
    stMensaje mensaje;
    int i = 0;
    if (pArchivo != NULL){
        while (fread(&mensaje, sizeof(stMensaje), 1, pArchivo) > 0){
           mensajes[i] = mensaje;
           i++;
        }
        fclose(pArchivo);

    } else printf("ERROR");
    return i;
}

int ValidaExistenciaMail(const char fileName[], char mail[]){
    stReader reader;
    int resultado = 0;
    int flag = 0;
    FILE* pFile = fopen(fileName, "rb");
    if (pFile != NULL){
        while (fread(&reader, sizeof(stReader), 1, pFile) > 0 && flag == 0){
            if (strcmp(reader.mail, mail) == 0 ){
                resultado = 0;
                flag = 1;
            } else {
                resultado = 1;
            }
        }
        fclose(pFile);
    } else {
        resultado = 1;
    }
    return resultado;
}

int GuardarLibros(const char nombreArchivo[], stBook* booksModificated, int validos){
    int i = 0;
    FILE* pFile = fopen(nombreArchivo, "wb");
    if (pFile != NULL){
        while (i < validos){
            fwrite(&booksModificated[i], sizeof(stBook), 1, pFile);
            i++;
        }
        fclose(pFile);
    }else {
        MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
    }
    return i;
}

int GuardarLectores(const char nombreArchivo[], stReader* readersModificated, int validos){
    int i = 0;
    FILE* pFile = fopen(nombreArchivo, "wb");
    if (pFile != NULL){
        while (i < validos){
            fwrite(&readersModificated[i], sizeof(stReader), 1, pFile);
            i++;
        }
        fclose(pFile);
    }else {
        MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
    }
    return i;
}

void EditarLibroEnArchivo (const char nombreArchivo[], stBook libroModificado){
    stBook book;
    int flag = 0;
    FILE* pFile = fopen(nombreArchivo, "r+b");
    if (pFile != NULL){
        while (flag == 0 && fread(&book, sizeof(stBook), 1, pFile) > 0 ){
            if (book.id == libroModificado.id) {
                // Encontre el registro que debo sobrescribir
                flag = 1;
                int posicion = ftell(pFile) - sizeof(stBook);
                fseek(pFile,posicion,SEEK_SET);
                if (fwrite(&libroModificado, sizeof(stBook), 1, pFile) > 0){
                    MostrarMensaje("DATOS MODIFICADOS CORRECTAMENTE.");
                } else {
                    MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
                }
            }
        }
        fclose(pFile);
    }else {
        MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
    }
}

void EditarLectorEnArchivo (const char nombreArchivo[], stReader readerModificado){
    stReader reader;
    int flag = 0;
    FILE* pFile = fopen(nombreArchivo, "r+b");
    if (pFile != NULL){
        while (flag == 0 && fread(&reader, sizeof(stReader), 1, pFile) > 0 ){
            if (reader.id == readerModificado.id) {
                // Encontre el registro que debo sobrescribir
                flag = 1;
                int posicion = ftell(pFile) - sizeof(stReader);
                fseek(pFile,posicion,SEEK_SET);
                if (fwrite(&readerModificado, sizeof(stReader), 1, pFile) > 0){
                    MostrarMensaje("DATOS MODIFICADOS CORRECTAMENTE.");
                } else {
                    MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
                }
            }
        }
        fclose(pFile);
    }else {
        MostrarMensaje("ERROR AL GRABAR LOS CAMBIOS");
    }
}
/// FUNCIONES DE APOYO - NO VAN A TENER USO EN EL SISTEMA FINALIZADO

void MostrarDatosArchivo(const char nombreArchivo[]){
    FILE* pArchivo = fopen(nombreArchivo, "rb");
    stReader reader;
    if (pArchivo != NULL){
        while (fread(&reader, sizeof(stReader), 1, pArchivo) > 0){
            printf("%s \n", reader.surName );
            printf("%s \n", reader.name );
            printf("%s \n", reader.phone );
            printf("%s \n", reader.address );
            printf("%s \n", reader.mail );
            printf("%s \n", reader.password );
        }
        fclose(pArchivo);

    } else printf("ERROR");
    system("pause");
}

void DarDeAltaLibros(const char nombreArchivo[]){
    stBook book;
    book.active = 0;
    book.id = 1;
    strcpy(book.author, "J.R.R. TOLKIEN");
    strcpy(book.description, "Gandalf se convierte...");
    strcpy(book.editorial, "MINOTAURO");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "LAS DOS TORRES");
    FILE* pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
  	    book.active = 1;
    book.id = 2;
    strcpy(book.author, "J.R.R. TOLKIEN");
    strcpy(book.description, "Inicio de la comunidad");
    strcpy(book.editorial, "MINOTAURO");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "LA COMUNIDAD DEL ANILLO");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
  	    book.active = 1;
    book.id = 3;
    strcpy(book.author, "G.R.R. MARTIN");
    strcpy(book.description, "PRIMER LIBRO");
    strcpy(book.editorial, "PLAZA JANES");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "JUEGO DE TRONOS");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 4;
    strcpy(book.author, "G.R.R. MARTIN");
    strcpy(book.description, "SEGUNDO LIBRO");
    strcpy(book.editorial, "PLAZA JANES");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "CHOQUE DE REYES");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 5;
    strcpy(book.author, "G.R.R. MARTIN");
    strcpy(book.description, "TERCER LIBRO");
    strcpy(book.editorial, "MINOTAURO");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "TORMENTA DE ESPADAS");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 6;
    strcpy(book.author, "G.R.R. MARTIN");
    strcpy(book.description, "CUARTO LIBRO");
    strcpy(book.editorial, "MINOTAURO");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "FESTIN DE CUERVOS");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 7;
    strcpy(book.author, "G.R.R. MARTIN");
    strcpy(book.description, "QUINTO LIBRO");
    strcpy(book.editorial, "MINOTAURO");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "DANZA DE DRAGONES");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 8;
    strcpy(book.author, "G.R.R. MARTIN");
    strcpy(book.description, "PRECUELA");
    strcpy(book.editorial, "MINOTAURO");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-547-065-5");
    strcpy(book.name, "FUEGO Y DRAGONES");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 9;
    strcpy(book.author, "DAVID BALDACCI");
    strcpy(book.description, "un thriller complejo... una extraordinaria lectura para los amantes del misterio");
    strcpy(book.editorial, "GRUPO ZETA");
    strcpy(book.gender, "POLICIAL");
    strcpy(book.ISBN, "978-84-666-5274-2");
    strcpy(book.name, "EL SEXTO HOMBRE");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 10;
    strcpy(book.author, "RONALD CUTLER");
    strcpy(book.description, "QUE OCURRIRIA SI SE ENCONTRARA UNA PRUEBA DE QUE LAS ENSEÑANZAS DE UN UNA DE LAS PRINCIPALES RELIGIONES SE BASAN EN FALSOS PRECEPCTOS?");
    strcpy(book.editorial, "LA FACTORIA DE IDEAS");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-84-9800-475-5");
    strcpy(book.name, "EL SECRETO DE CRISTO");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 11;
    strcpy(book.author, "PAULO COELHO");
    strcpy(book.description, "LAS PERSONAS CREAN UNA REALIDAD Y DESPUES SE VUELVEN VICTIMAS DE ELLA. ATHENA SE REVELO CONTRA ESO Y PAGO UN PRECIO ALTO.");
    strcpy(book.editorial, "PLANETA");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-49-1526-5");
    strcpy(book.name, "LA BRUJA DE PORTOBELLO");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 12;
    strcpy(book.author, "GABRIEL ROLON");
    strcpy(book.description, "HACE POCO MENOS DE UN AÑO QUE PABLO ROUVIOT, UN RECONOCIDO PSICOANALISTA, TERMINO UNA TURBULENTA HISTORIA DE AMOR.");
    strcpy(book.editorial, "EMECE");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-950-04-3287-0");
    strcpy(book.name, "LOS PADECIENTES");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 13;
    strcpy(book.author, "DAVE EGGERS");
    strcpy(book.description, "UNA ADAPTACION DEL LIBRO ILUSTRADO \" DONDE VIVEN LOS MONSTRUOS\"");
    strcpy(book.editorial, "LITERATURA MONDADORI");
    strcpy(book.gender, "NOVELA");
    strcpy(book.ISBN, "978-987-658-040-3");
    strcpy(book.name, "LOS MONSTRUOS");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
    book.active = 1;
    book.id = 14;
    strcpy(book.author, "ADRIAN PAENZA");
    strcpy(book.description, "SOBRE NUMEROS, PERSONAJES, PROBLEMAS Y CURIOSIDADES");
    strcpy(book.editorial, "SIGLO VEITIUNO");
    strcpy(book.gender, "MATEMATICAS");
    strcpy(book.ISBN, "978-987-1220-19-9");
    strcpy(book.name, "MATEMATICA...Estas ahi?");
    pFile = fopen(nombreArchivo, "ab");
    if (pFile != NULL){
        fwrite(&book, sizeof(stBook), 1, pFile);
        fclose(pFile);
  	}
}

