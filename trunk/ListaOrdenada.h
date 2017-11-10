#include "Lista.h"


#ifndef __LISTAORDENADA_h__
	#define __LISTAORDENADA_h__

    typedef struct Elemento{
        char* Clave;
        char* Valor;
    }Elemento;


    typedef struct TlistaOrdenada{
        struct TListaSimple ListaSimple;
        struct Elemento     Elemento;
    }TlistaOrdenada;

    void TlistaOrdenada_Crear(struct TlistaOrdenada *LO, size_t tamanio);
    void TlistaOrdenada_Vaciar(struct TlistaOrdenada *LO);
    int TlistaOrdenada_Vacia(struct TlistaOrdenada *LO);
    int TlistaOrdenada_Insertar(struct TlistaOrdenada *LO,struct Elemento Elemento);
    int TlistaOrdenada_Obtener(struct TlistaOrdenada *LO,char* clave,char* buffer);
    int TlistaOrdenada_SizeDato(struct TlistaOrdenada *LO,char* clave);

    int TlistaOrdenada_TamanioElemento(struct TlistaOrdenada *LO);

    int TlistaOrdenada_GuardarClave(struct TlistaOrdenada *LO, void *clave);
    int TlistaOrdenada_GuardarValor(struct TlistaOrdenada *LO, void *valor);

    int TlistaOrdenada_LiberarClave(struct TlistaOrdenada *LO);
    int TlistaOrdenada_LiberarValor(struct TlistaOrdenada *LO);
#endif
