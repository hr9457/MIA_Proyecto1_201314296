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
        sizeParticion = atoi(parametros[3].c_str());
        crearParticion(sizeParticion);
    }
    else
    {
    }
}


// buscar espacios libres dentro del disco
void fdisk::encontrarEspaciosLibres()
{
    int tamanioDisco;
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
    tamanioDisco = MBR.mbr_tamanio;// tamanio del disco que estamos leendo
    ajuste = MBR.mbr_fit;
    // ordenar el listado de las particiones segun supocicion part_star
    // impresion de datos del disco que estamos leendo 
    cout<<"---Datos del Disco---"<<endl;
    for(int i= 0;i<4;i++)
    {
        cout<<"---Particion No."<<i<<endl;
        cout<<"  *"<<MBR.mbr_partitions[i].part_status<<endl; 
        cout<<"  *"<<MBR.mbr_partitions[i].part_star<<endl;
        cout<<"  *"<<MBR.mbr_partitions[i].part_size<<endl;
        cout<<"  *"<<MBR.mbr_partitions[i].part_name<<endl; 
    }
    // busqueda de las particiones utilizadas  
    for(int i=0;i<4;i++)
    {
        partition particion;
        if(MBR.mbr_partitions[i].part_status == '1')
        {
            particion.part_star = MBR.mbr_partitions[i].part_star;
            particion.part_size = MBR.mbr_partitions[i].part_size;
            copia.push_back(particion);
        }        
    }
    
    // ordenamiento de la copia con las particiones llenas en el disco
    // ordenamiento burbuja
    for(int i=0;i<copia.size()-1;i++)
    {
        for(int j=i+1;j<copia.size();j++)
        {
            if(copia[i].part_star > copia[j].part_star)
            {
                partition aux = copia[i];
                copia[i] = copia[j];
                copia[j] = aux;
            }
        }
    }
        
    // crecion de una lista con los espacios en blanco dentro del disco
    int inicio = sizeof(MBR);
    int inicioParticion;
    int sizeDisco;
    int espacioLibre;
    int inicioAnterior;
    for(int disco=0; disco<copia.size(); disco++)
    {
        inicioParticion = copia[disco].part_star;
        espacioLibre = inicioParticion - inicio;
        inicioAnterior = inicio;
        inicio = inicioParticion + copia[disco].part_size;
        if(espacioLibre>0)
        {
            //guardamos los epacios en blanco
            blackPartition particionLibre;
            particionLibre.part_star = inicioAnterior;
            particionLibre.part_size = espacioLibre;
            particionesLibres.push_back(particionLibre); 
        }        
    }    

    // condicion final si llego al final del disco
    if(inicio < MBR.mbr_tamanio)
    {
        espacioLibre = MBR.mbr_tamanio - inicio;
        blackPartition finalLibre;
        finalLibre.part_star = inicio;
        finalLibre.part_size = espacioLibre;
        particionesLibres.push_back(finalLibre);
    }
    
    // impresion de los espacios en blanco dentro del disco
    cout<<"******Espcios en Blanco*********"<<endl;
    cout<<"Tamanio del disco: "<<tamanioDisco<<endl;
    for(int inicio = 0;inicio<particionesLibres.size();inicio++)
    {
        cout<<"Particion Libre No."<<inicio<<endl;
        cout<<"Espacio: "<<particionesLibres[inicio].part_size<<endl;
        cout<<"Inicio: "<<particionesLibres[inicio].part_star<<endl;
        cout<<endl;
        cout<<endl;
    }
}




// ordenar espacios en blanco segun el tipo de ajuste
void fdisk::ordenarEspaciosLibres()
{
    /*
    ordenamiento de los espacios libres
    mejor ajuste -   ascendente
    primer ajuste -  no se ordena 
    peor ajuste -    descedente
    */
   if(ajuste == 'f')
   {
       // primer ajuste no se ordena la lista busca el primer espacio
   }
   else if(ajuste == 'b')
   {
       // mejor ajuste
   }   
   else if(ajuste == 'w')
   {
       // peor ajuste
   }
}


// funcion para buscar dentro de las particiones la que mejor se adecue 
void fdisk::buscarDentroParticion(int sizeParticion)
{
    for(int inicio = 0; inicio < particionesLibres.size(); inicio++)
    {
        if(sizeParticion <= particionesLibres[inicio].part_size )
        {
            cout<<"Particion a insertar en la posicion No."<<inicio<<endl;
            break;
        }
    }
}



// metodo para crear particion en el disco
void fdisk::crearParticion(int sizeParticion)
{
    //  busco los espacios libres dentro del disco
    encontrarEspaciosLibres();
    //  ordeno los espacios en blanco segun el fit del disco
    //ordenarEspaciosLibres(); 
    // busco donde pueda caber la particion que el usuario quiera ingresar
    buscarDentroParticion(sizeParticion);
    // 
}