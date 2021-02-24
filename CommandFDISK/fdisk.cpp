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
                    // // si viene size o add
                    crearAgregarParticion(parametros);           
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

// metodo para verificacion si se creara una particion o agreagar a una particion espacio
void fdisk::crearAgregarParticion(string parametros[])
{
    // parametro add en posicion 1, parametro size en posicion 3
    if(parametros[3].empty() != true)
    {
        crearParticion();
    }
    else
    {
    }
}



// metodo para crear particion en el disco
void fdisk::crearParticion()
{
    FILE *archivo;
    // apertura del disco para lectura y actualizacion rb+
    archivo = fopen(rutaArchivo.c_str(),"rb+");
    if(archivo==NULL)
        exit(1);

    // lectura del MBR en el disco
    mbr MBR;
    fseek(archivo,0,SEEK_SET); // inicio del archivo
    fread(&MBR,sizeof(mbr),1,archivo);
    // cierre del dico con los cambios
    fclose(archivo);

    /* 
    copia de las particiones dentro del disco para saber su 
    orden segun su poscion dentro del disco 
    status = 0 disco no utilizado
    status = 1 disco utilizado
    */    
    // ordenar el listado de las particiones segun supocicion part_star    
    cout<<"---Datos del Disco---"<<endl;
    for(int i= 0;i<4;i++)
    {
        cout<<"---Particion No."<<i<<endl;
        cout<<"  *"<<MBR.mbr_partitions[i].part_status<<endl; 
        cout<<"  *"<<MBR.mbr_partitions[i].part_star<<endl;
        cout<<"  *"<<MBR.mbr_partitions[i].part_name<<endl; 
    }

        
    for(int i=0;i<4;i++)
    {
        partition particion;
        if(MBR.mbr_partitions[i].part_status == '1')
        {
            particion.part_fit = MBR.mbr_partitions[i].part_fit;
            particion.part_star = MBR.mbr_partitions[i].part_star;
            particion.part_size = MBR.mbr_partitions[i].part_size;
            copia.push_back(particion);
        }        
    }
    cout<<"*****************************************************"<<endl;
    cout<<"-->copia de las particiones utilizadas en el disco"<<endl;
    cout<<"-->Size: "<<copia.size()<<endl;    
    for(int i=0;i<copia.size();i++)
    {
        cout<<"---Particion No."<<i<<endl;
        cout<<"  *"<<copia[i].part_fit<<endl; 
        cout<<"  *"<<copia[i].part_star<<endl; 
        cout<<"  *"<<copia[i].part_size<<endl; 
    }
}