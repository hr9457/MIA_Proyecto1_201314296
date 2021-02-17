#ifndef MKDISK_H
#define MKDISK_H
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
using namespace std;

class mkdisk
{
private:
    //vector<string> parametrosMkdisk;
    string mkdiskParametros[];
public:
    mkdisk(string []);
    void setSize(int);
    int getSize();
    void setCadena(string);
    string getCadena();
    void setRuta(string);
    string getRuta();
    void creacionDisco();
    void mensaje();
};

#endif // MKDISK_H
