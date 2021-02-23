#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <dirent.h>
using namespace std;
class funciones
{
private:
    string rutaArchivo = "";
public:
    funciones();
    vector<string> split(string,char);
    string eliminacionComillas(string);
    bool is_file(string file);
    string aMayuscula(string);
    string aMinuscula(string);
    void limpiarVector(string []);
    bool buscarElemento(string [],string);
};

#endif // FUNCIONES_H
