#include "constructor.h"

int TConstructor_Crear( struct TConstructor *tc){
/**PRE: -Ninguna
 **POST -El constructor ha sido creado*/
    tc->eventoAnterior = CB_NO_EVENTO;
    tc->indicador = 0;

    TConstructor_SetCola(tc,&(tc->cola));
    return 0;
}

int TConstructor_SetIndice(struct TConstructor *tc, struct Tindice *ti){
    tc->PtrIndice = ti;
    return 0;
}

int TConstructor_DiccionarioCrear(struct TConstructor *tc){
    tc->diccionario = (TDiccionario*) malloc(sizeof(TDiccionario));

    if(!tc->diccionario)
        return FALSE;
    return TRUE;
}

int TConstructor_Destruir(struct TConstructor *tc){
/**PRE: -El constructor ha sido creado
 **POST -Se liberan recursos asociados*/
    C_Vaciar(&(tc->cola));
    return 0;
}

int TConstructor_SetCola(struct TConstructor *tc, TCola *cola){
/**PRE: -El constructor ha sido creado
 **POST -Se establece la estructura de cola donde se colocaran los tweets en formato TDiccionario*/
    C_Crear(&(tc->cola), sizeof(TDiccionario));
    return 0;
}


/***********************************************************************************************/
/*********************************EVENTOS*******************************************************/
/***********************************************************************************************/

int TConstructor_ComienzaArray(struct TConstructor *tc, void *dato){
    tc->indicador++;
    return 0;
}

int TConstructor_TerminaArray(struct TConstructor *tc, void *dato){
    tc->indicador--;
    return 0;
}

int TConstructor_ComienzaObjeto(struct TConstructor *tc, void *dato){
    if(tc->indicador++ == 1){
        if(TConstructor_DiccionarioCrear(tc)) /*malloc a tc->diccionario*/
            TDiccionario_Crear(tc->diccionario);
    }
    return 0;
}

int TConstructor_TerminaObjeto(struct TConstructor *tc,  void *dato){
    if(--tc->indicador == 1){
        C_Agregar(&(tc->cola), tc->diccionario);
        free(tc->diccionario);
    }
    return 0;
}


int TConstructor_Clave(struct TConstructor *tc, void *dato){
    if(tc->eventoAnterior == CB_CLAVE)
        TDiccionario_LiberarClave(tc->diccionario);

    TDiccionario_GuardarClave(tc->diccionario,dato);

    tc->eventoAnterior = CB_CLAVE;
    return 0;
}

int TConstructor_True(struct TConstructor *tc, void *dato){
    TDiccionario_GuardarValor(tc->diccionario,"TRUE");
    TDiccionario_Colocar(tc->diccionario);
    tc->eventoAnterior = CB_TRUE;
    return 0;

}

int TConstructor_False(struct TConstructor *tc, void *dato){

    TDiccionario_GuardarValor(tc->diccionario,"FALSE");
    TDiccionario_Colocar(tc->diccionario);
    tc->eventoAnterior = CB_FALSE;
    return 0;

}

int TConstructor_Null(struct TConstructor *tc, void *dato){

    TDiccionario_GuardarValor(tc->diccionario,"NULL");
    TDiccionario_Colocar(tc->diccionario);
    tc->eventoAnterior = CB_NULL;
    return 0;
}

int TConstructor_Numero(struct TConstructor *tc, void *dato){

    TDiccionario_GuardarValor(tc->diccionario,dato);
    TDiccionario_Colocar(tc->diccionario);
    tc->eventoAnterior = CB_NUMERO;
    return 0;
}

int TConstructor_String(struct TConstructor *tc, void *dato){
    TDiccionario_GuardarValor(tc->diccionario,dato);
    TDiccionario_Colocar(tc->diccionario);
    tc->eventoAnterior = CB_STRING;
    return 0;

}

int TConstructor_GuardarEnIndice(struct TConstructor *tc){
    struct TDiccionario corriente;

    /*Guardo el tweet en indice*/
    while(C_Sacar(&(tc->cola),&corriente))
        Tindice_Agregar(tc->PtrIndice, &corriente);

    return 0;
}

