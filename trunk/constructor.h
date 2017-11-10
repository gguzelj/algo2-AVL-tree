#ifndef _CONSTRUCTOR_H
    #define _CONSTRUCTOR_H

    #include <stdio.h>
    #include "diccionario.h"
    #include "Cola.h"
    #include "lexico.h"
    #include "indice.h"


    typedef struct TConstructor{
        struct TDiccionario*        diccionario;
        struct TCola                cola;
        enum Evento                 eventoAnterior;
        int                         indicador;
        struct Tindice*             PtrIndice;
    } TConstructor;

    /* PROTOTIPOS */
    int TConstructor_Crear(struct TConstructor *tc);
    int TConstructor_Destruir(struct TConstructor *tc);
    int TConstructor_SetCola(struct TConstructor *tc, TCola *cola);


    int TConstructor_GuardarEnIndice(struct TConstructor *tc);
    int TConstructor_DiccionarioCrear(struct TConstructor *tc);


    /**Trabajo practico n° 3*/
    /*Guarda el puntero del indice, para posteriormente, poder guardar los tweets en el indice*/
    int TConstructor_SetIndice(struct TConstructor *tc, struct Tindice *ti);


    /*DIFERENTES EVENTOS*/
    /**NOTA: El parametro evento ya no era necesario,
             porque se esta utilizando una funcion distinta para
             cada evento posible.
    */
    int TConstructor_ComienzaArray(struct TConstructor *tc, void *dato);
    int TConstructor_TerminaArray(struct TConstructor *tc, void *dato);
    int TConstructor_ComienzaObjeto(struct TConstructor *tc, void *dato);
    int TConstructor_TerminaObjeto(struct TConstructor *tc, void *dato);
    int TConstructor_Clave(struct TConstructor *tc, void *dato);
    int TConstructor_True(struct TConstructor *tc, void *dato);
    int TConstructor_False(struct TConstructor *tc, void *dato);
    int TConstructor_Null(struct TConstructor *tc, void *dato);
    int TConstructor_Numero(struct TConstructor *tc, void *dato);
    int TConstructor_String(struct TConstructor *tc, void *dato);

#endif

