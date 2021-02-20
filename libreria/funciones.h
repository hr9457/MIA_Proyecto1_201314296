#ifndef FUNCIONES_H
#define FUNCIONES_H
#include <iostream>
#include <string>
#include <cstring>
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
};

#endif // FUNCIONES_H
