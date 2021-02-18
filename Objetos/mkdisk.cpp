#include "mkdisk.h"

mkdisk::mkdisk()
{
}

/*metodo para crear un disco*/
void mkdisk::crearDisco(string parametros[])
{
    //cambiar el or a un and
    if(parametros[0] != "" && parametros[1] != "")
    {
        vector<string> rutas;
        this->rutaArchivo = parametros[1];
        if(rutaArchivo[0] == '\"')
        {
            //la ruta path viene entre comillas
            cout<<"la ruta viene entre comillas\n";
            this->rutaArchivo=eliminacionComillas(rutaArchivo);
            rutas = split(rutaArchivo,separador);  
            nombreDisco = rutas[rutas.size()-1];
            directorioDisco(rutas);
            cout<<"Creacion del disco: "<<nombreDisco<<"\n"; 
        }
        else
        {
            //ruta path viene sin comillas
            rutas = split(rutaArchivo,separador);  
            nombreDisco = rutas[rutas.size()-1];
            directorioDisco(rutas);
            cout<<"Creacion del disco: "<<nombreDisco<<"\n";  
        }               
    }
    else
    {
        cout<<"parametro obligatorio faltantes: size,path\n";
    }
}

/*metodo para hacer split en la cadena de la ruta*/
vector<string> mkdisk::split(string str, char pattern)
{
    int posInit = 0;
    int posFound = 0;
    string splitted;
    vector<string> resultados;
    while(posFound >= 0){
        posFound = str.find(pattern, posInit);
        splitted = str.substr(posInit, posFound - posInit);
        posInit = posFound + 1;
        resultados.push_back(splitted);
    }
    return resultados;
}

/*metodo para creacion y verficacion de carpetas*/
void mkdisk::crearCarpeta(string nombreCarpeta)
{
    if(mkdir(nombreCarpeta.c_str(),07777)==-1)
    {
        cout<<"Carpeta Existente\n";
    }
}


void mkdisk::directorioDisco(vector<string> rutas)
{
    string rutaCreacion;
    int i = 0;
    for(i; i < rutas.size()-1; i++)
    {
        rutaCreacion += rutas[i];
        if(i+1<rutas.size()-1)
        {
            rutaCreacion += "/";
        }
    }
    //cout<<rutaCreacion<<"\n";
    crearCarpeta(rutaCreacion);
}

string mkdisk::eliminacionComillas(string ruta)
{
    vector<string> resultado;
    string rutaSinComillas;
    resultado = split(ruta,'\"');
    rutaSinComillas = resultado[1];
    //cout << resultado[1] << endl;
    return rutaSinComillas;
}
/*
for para recorrer un vector
for(int i = 0; i < rutas.size(); i++)
{
    cout << rutas[i] << endl;
}
*/
