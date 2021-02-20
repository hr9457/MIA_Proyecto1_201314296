#ifndef MKDISK_H
#define MKDISK_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fstream>
#include <Estructuras/structs.h>
#include <time.h>
using namespace std;

class mkdisk
{
private:
    int size;
    string rutaArchivo = "";
    const char separador = '/';
    string nombreDisco = "";
    string pesoArchivo = "m"; 
    string fit = "bf";   

public:
    mkdisk();
    void crearDisco(string[]);
    vector<string> split(string, char);
    void crearCarpeta(string);
    string directorioDisco(vector<string>);
    string eliminacionComillas(string);
    void crearFichero(string);
    void crearMBR(FILE *,int);
    void cambioAjuste(string);
};

#endif // MKDISK_H
