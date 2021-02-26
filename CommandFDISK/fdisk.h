#ifndef FDISK_H
#define FDISK_H

//librerias
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <fstream>
#include <vector>
#include <cstdlib>
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
    vector<partition> copia; 
    vector<blackPartition> particionesLibres;
    void verificacionComillas(string);
    bool verificacionDisco(string);
    bool addDelete(string []);
    bool sizeAdd(string[]);
    void crearAgregarParticion(string []);
    void encontrarEspaciosLibres();
    void ordenarEspaciosLibres();
    void crearParticion();
public:
    fdisk();
    void ejecutarFdisk(string []);
};

#endif // FDISK_H

// fdisk -path=/home/hector/prueba/DiscoPrueba.dk -size=200 -add=200
