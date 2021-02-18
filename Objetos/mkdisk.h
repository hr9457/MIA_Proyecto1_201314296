#ifndef MKDISK_H
#define MKDISK_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

class mkdisk
{
private:
    int size = 0;
    string rutaArchivo = "";
    const char separador = '/';
    string nombreDisco = "";
public:
    mkdisk();
    void crearDisco(string[]);
    vector<string> split(string, char);
    void crearCarpeta(string);
    void directorioDisco(vector<string>);
    string eliminacionComillas(string);
};

#endif // MKDISK_H
