#ifndef FDISK_H
#define FDISK_H

//librerias
#include <iostream>
#include <string>
#include <cstring>
#include "libreria/funciones.h"
using namespace std;

class fdisk
{
private:
    string rutaArchivo;
    funciones FUN;
    bool verificacionComillas(string);
    bool verificacionDisco(string);
    bool addDelete(string []);
    bool sizeAdd(string[]);
public:
    fdisk();
    void ejecutarFdisk(string []);
};

#endif // FDISK_H
