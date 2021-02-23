#include "fdisk.h"

// metodo constructor
fdisk::fdisk()
{}


// metodo de ejecuccion principal
void fdisk::ejecutarFdisk(string parametros[])
{
    if(parametros[0].empty() != true)
    {
        this->rutaArchivo = parametros[0];
        // verificacion de comillas en la ruta
        verificacionComillas(this->rutaArchivo);
        // verificacion de la existencia del disco
        if(verificacionDisco(this->rutaArchivo))
        {
            // verificacion comando add y delete no vengan juntos
            if(addDelete(parametros))
            {
                // verificacion que los parametros size y add no vengan juntos
                if(sizeAdd(parametros))
                {                    
                }
            }
        }

    }
    else
    { cout<<"-->Parametros Obligatorios faltantes: path"<<endl;}
}


void fdisk::verificacionComillas(string rutaArchivo)
{
    if(rutaArchivo[0] == '\"')
    {
        this->rutaArchivo = FUN.eliminacionComillas(rutaArchivo);
    }
    else
    {
        this->rutaArchivo = rutaArchivo;
    }
}

// funcion para la verificacion de la existencia del archivo
bool fdisk::verificacionDisco(string rutaArchivo)
{
    if(FUN.is_file(rutaArchivo))
    {return true;}
    else
    {cout<<"-->No es posible acceder al disco"<<endl;return false;}
}


// metodo para la verificacion de que los paremetros add y delete no puedan venir juntos
bool fdisk::addDelete(string parametros[])
{
    // parametro add en posicion 1, parametro delete en posicion 2
    if(parametros[1].empty() != true && parametros[2].empty() != true)
    {   cout<<"-->Erro: parametros add y delete incompatibles"<<endl; return false;  }
    else
    {   return true;  }
}

// metodo para la verificacion de la incompatibilidad de los atributos size y add
bool fdisk::sizeAdd(string parametros[])
{
    // parametro add en posicion 1, parametro size en posicion 3
    if(parametros[1].empty() != true && parametros[3].empty() != true)
    { cout<<"-->parametros size y add incompatibles"<<endl; return false; }
    else
    { return true; } 
}