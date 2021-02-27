#ifndef FDISK_H
#define FDISK_H

//librerias
#include <iostream>
#include <string>
#include <cstring>
//#include <list>
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
    char ajuste;    
    string name="",u="k",f,type;
    int sizeParticion;
    char fitParticion='w';
    char tipoParticion='p';
    int contadorPrimarias=0,contadorExtendidas=0,contadorLogicas=0,totalParticiones=0;
    // lista para los espacios en blanco
    vector<partition> copia;
    vector<blackPartition> particionesLibres;
    string verificacionComillas(string);
    bool verificacionDisco(string);
    bool addDelete(string []);
    bool sizeAdd(string[]);
    void crearAgregarParticion(string []);
    void encontrarEspaciosLibres();
    void ordenarEspaciosLibres();
    void buscarDentroParticion(int);
    void ordenDescedente();
    void crearParticion(int);
    void insertarParticion();
    void impresionParticionesLibres();
    void parametrosOPcrear(string []);
    void agregarActualizarMBR(char,char,char,int,int,string);
public:
    fdisk();
    void ejecutarFdisk(string []);
};

#endif // FDISK_H

// fdisk -path=/home/hector/prueba/DiscoPrueba.dk -size=200 -add=200 
