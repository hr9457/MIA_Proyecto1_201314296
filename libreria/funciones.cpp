#include "funciones.h"

funciones::funciones()
{

}

/*metodo para hacer split en la cadena de la ruta*/
vector<string> funciones::split(string str, char pattern)
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

/*metodo para eliminar comillas de una ruta path*/
string funciones::eliminacionComillas(string ruta)
{
    vector<string> resultado;
    string rutaSinComillas;
    resultado = split(ruta,'\"');
    rutaSinComillas = resultado[1];
    //cout << resultado[1] << endl;
    return rutaSinComillas;
}

/*metodo para saber si un archivo existe en el sistema operativo*/
bool funciones::is_file(string file)
{
    FILE *archivo;
    if(archivo = fopen(file.c_str(),"r"))
    {
        fclose(archivo);
        return true;
    }
    else
    {
        return false;
    }
}


/* metodo par convertir un string a mayusculas */
string funciones::aMayuscula(string cadena)
{
  for (int i = 0; i < cadena.length(); i++) cadena[i] = toupper(cadena[i]);
  return cadena;   
}


/* metodo para convertir un string a minusculas */
string aMinuscula(string cadena) 
{
  for (int i = 0; i < cadena.length(); i++) cadena[i] = tolower(cadena[i]);
  return cadena;
}

/* metodo para limpiar cualquier vector */
void funciones::limpiarVector(string limpieza[])
{
    int tamanio = sizeof(limpieza)/sizeof(*limpieza);
    cout<<"El tamanio del vector a limpiar es de: "<<tamanio<<endl;
}
