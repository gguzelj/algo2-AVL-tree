#include <stdio.h>
#include "lexico.h"
#include "sintactico.h"

#ifndef _PARSER_H
    #define _PARSER_H

    #ifndef MAX_DATO
        #define MAX_DATO 256
    #endif

    typedef struct Tparser{

        struct Tlexico     lexico;
        struct Tsintactico sintactico;
        FILE*              Parchivo;
        enum CodigoError   cod_error;
        char               mensaje[MAX_DATO];
        }Tparser;

    /* PROTOTIPOS */
    int Tparser_Crear(struct Tparser *p,char *argv);
    int Tparser_PushChar(struct Tparser *p,char caracter);
    int Tparser_TerminarFlujo(struct Tparser *p);
    int Tparser_GetUltimoError(struct Tparser *p, enum CodigoError *codigo, char mensaje[]);
    int Tparser_destruir(struct Tparser *p);

    /**Funciones TP2*/
    void* Tparser_ObtenerDato(struct Tparser *p);
    Tcallback Tparser_ObtenerCallback(struct Tparser *p);
    /*Se encarga de llamar a Tsintactico_ObtenerCallback.
      Lo que hace es obtener una funcion callback de vector de funciones callback
      que tiene el sintactico.*/


#endif


