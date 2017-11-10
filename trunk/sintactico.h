#ifndef _SINTACTICO_H
    #define _SINTACTICO_H

    #include "lexico.h"
    #include "constructor.h"
    #include "Pila.h"

    typedef  int (*Tcallback)(struct TConstructor*, void*);

    typedef struct Tsintactico{
        /**variables TP1*/
        enum TipoToken      tokenAnterior;
        char                flag_fin;
        char                flag_inicio;
        enum CodigoError    cod_error;
        /**variables TP2*/
        TPila               pila;             /*Pila creada para controlar el anidamiento de los Objetos/Arrays*/
        Tcallback           Vec_callbacks[2]; /*Se creo un vector que pueda contener 2 funciones callback
                                                El motivo es modificar la menor cantidad de codigo posible del TP anterior.*/
        char*               UltimoDato;       /*Variable utilizada para enviar el ultimo dato recibido*/
    }Tsintactico;


    /* PROTOTIPOS */
    int Tsintactico_Crear(struct Tsintactico *al);
    int Tsintactico_PushToken(struct Tsintactico * as,struct Ttoken *token);
    int Tsintactico_TerminarFlujo(struct Tsintactico *as);
    int Tsintactico_GetUltimoError(struct Tsintactico *al,enum CodigoError *codigo, char *mensaje);
    int Tsintactico_destruir(struct Tsintactico *as);

    /**Funciones TP2*/
    int Tsintactico_setCallback(struct Tsintactico *as, enum Evento evento, void* tda_contexto,Tcallback *callback);
    void* Tsintactico_ObtenerDato(struct Tsintactico *as);
    Tcallback Tsintactico_ObtenerCallback(struct Tsintactico *as);
    /*Devuelve una de las dos callbacks alojadas en su vector de callbacks*/
#endif

