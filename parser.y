%{
#include "scanner.h"//se importa el header del analisis sintactico
#include <QString>
#include <string>
#include "qdebug.h"
#include <iostream>
#include <vector>
#include "Objetos/mkdisk.h"
#include "Objetos/rmdisk.h"
//#include "obmkdisk.h"
using namespace std;
extern int yylineno; //linea actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern int columna; //columna actual donde se encuentra el parser (analisis lexico) lo maneja BISON
extern char *yytext; //lexema actual donde esta el parser (analisis lexico) lo maneja BISON

/*vectores para los parametros de cada comando*/
vector<string> parametrosMkdisk;
string mkdiskParametros[3];
string rmdiskParametros;

int yyerror(const char* mens)
{
std::cout << mens <<" "<<yytext<< std::endl;
return 0;
}
%}
//error-verbose si se especifica la opcion los errores sintacticos son especificados por BISON
%defines "parser.h"
%output "parser.cpp"
//%error-verbose
%locations
%union{
//se especifican los tipo de valores para los no terminales y lo terminales
//char TEXT [256];
//QString TEXT;
char TEXT[256];
/*objetos para cada comando*/
//class mkdisk *mkdisk;
}

//TERMINALES DE TIPO TEXT, SON STRINGS

%token<TEXT> tk_mkdisk;
%token<TEXT> tk_rmdisk;
%token<TEXT> tk_fdisk;

%token<TEXT> tk_size;
%token<TEXT> tk_path;
%token<TEXT> tk_f;
%token<TEXT> tk_u;

%token<TEXT> guion;
%token<TEXT> igual;
%token<TEXT> interrogacion;
%token<TEXT> por;
%token<TEXT> punto;


%token<TEXT> entero;
%token<TEXT> cadena;
%token<TEXT> identificador;
%token<TEXT> tk_ruta;

//%type<int> PARAMETROS_MKDISK;
//%type<mkdisk> MKDISK;


%start INICIO
%%

INICIO: LISTADO_COMANDOS ;


LISTADO_COMANDOS: LISTADO_COMANDOS COMANDO 
                | COMANDO ; 


COMANDO : MKDISK {mkdisk disco; disco.crearDisco(mkdiskParametros);}
        | RMDSIK {rmdisk eliminacion; eliminacion.eliminarDisco(rmdiskParametros);} ;


MKDISK : tk_mkdisk LIST_PARAMETROS_MKDISK ;


LIST_PARAMETROS_MKDISK  : LIST_PARAMETROS_MKDISK PARAMETROS_MKDISK
                        | PARAMETROS_MKDISK ;


PARAMETROS_MKDISK : guion tk_size igual entero      {mkdiskParametros[0]=$4;}
                  | guion tk_path igual cadena      {mkdiskParametros[1]=$4;}
                  | guion tk_path igual tk_ruta     {mkdiskParametros[1]=$4;}
                  | guion tk_u igual identificador  {mkdiskParametros[2]=$4;}
                  ;

RMDSIK : tk_rmdisk guion tk_path igual cadena  {rmdiskParametros=$5;}
       | tk_rmdisk guion tk_path igual tk_ruta {rmdiskParametros=$5;} ;