#ifndef FDISK_H
#define FDISK_H

//librerias
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include "libreria/funciones.h"
#include "Estructuras/structs.h"
using namespace std;

class fdisk
{
private:
    string rutaArchivo;
    funciones FUN;
    string tamanioParticion = "k";
    string typeParticion = "p";
    string tipoAjuste = "wf";
    // lista para los espacios en blanco
    list <blackPartition> espaciosLibres; 
    void verificacionComillas(string);
    bool verificacionDisco(string);
    bool addDelete(string []);
    bool sizeAdd(string[]);
    void crearAgregarParticion(string []);
    void crearParticion();
public:
    fdisk();
    void ejecutarFdisk(string []);
};

#endif // FDISK_H
