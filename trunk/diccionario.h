#ifndef _DICCIONARIO_H
    #define _DICCIONARIO_H
    #include "ListaOrdenada.h"


    typedef struct TDiccionario {
        TlistaOrdenada    lista;
    } TDiccionario;

    /* PROTOTIPOS */

    int TDiccionario_Crear(struct TDiccionario *td);
    int TDiccionario_Destruir(struct TDiccionario *td);
    int TDiccionario_Colocar(struct TDiccionario *td);
    int TDiccionario_Obtener(struct TDiccionario *td, char *clave, char *buffer);
    int TDiccionario_SizeDato(struct TDiccionario *td, char *clave);

    int TDiccionario_GuardarClave(struct TDiccionario *td, void *clave);
    int TDiccionario_GuardarValor(struct TDiccionario *td, void *valor);

    int TDiccionario_LiberarClave(struct TDiccionario *td);
    int TDiccionario_LiberarValor(struct TDiccionario *td);
#endif

