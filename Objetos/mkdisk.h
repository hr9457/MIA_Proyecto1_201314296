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
using namespace std;

class mkdisk
{
private:
    int size;
    string rutaArchivo = "";
    const char separador = '/';
    string nombreDisco = "";
    string pesoArchivo = "m";
    
public:
    mkdisk();
    void crearDisco(string[]);
    vector<string> split(string, char);
    void crearCarpeta(string);
    string directorioDisco(vector<string>);
    string eliminacionComillas(string);
    void crearFichero(string);
};

#endif // MKDISK_H
