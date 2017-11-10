#include "diccionario.h"

int TDiccionario_Crear(struct TDiccionario *td){
/**PRE: -Ninguna
 **POST -El diccionario ha sido creado*/
    TlistaOrdenada_Crear(&(td->lista),
                         TlistaOrdenada_TamanioElemento(&(td->lista)));
    return 0;
}

int TDiccionario_Destruir(struct TDiccionario *td){
/**PRE: -El diccionario ha sido creado.
 **POST -Se liberaron los recursos asociados al diccionario*/
    TlistaOrdenada_Vaciar(&(td->lista));
    return 0;
}

int TDiccionario_Colocar(struct TDiccionario *td){
/**PRE: -El diccionario ha sido creado.
 **POST -Se coloca en el diccionario el equivalente a diccionario[clave] = valor.
        -Si la clave ya existia en el diccionario, su valor se reemplaza por el nuevo*/
    return TlistaOrdenada_Insertar(&(td->lista),td->lista.Elemento);
}

int TDiccionario_Obtener(struct TDiccionario *td, char *clave, char *buffer){
/**PRE: -El diccionario ha sido creado.
        -Existe la entrada "CLAVE" en el diccionario
        -Buffer tiene el tamaño suficiente para guardar el texto
 **POST -Se guarda en Buffer una copia del texto en el diccionario bajo la clave*/
    return TlistaOrdenada_Obtener(&(td->lista),clave,buffer);
}

int TDiccionario_SizeDato(struct TDiccionario *td, char *clave){
    return TlistaOrdenada_SizeDato(&(td->lista), clave);
}

int TDiccionario_GuardarClave(struct TDiccionario *td, void *clave){
    return TlistaOrdenada_GuardarClave(&(td->lista), clave);
}
int TDiccionario_GuardarValor(struct TDiccionario *td, void *valor){
    return TlistaOrdenada_GuardarValor(&(td->lista), valor);
}

int TDiccionario_LiberarClave(struct TDiccionario *td){
    return TlistaOrdenada_LiberarClave(&(td->lista));
}

int TDiccionario_LiberarValor(struct TDiccionario *td){
    return TlistaOrdenada_LiberarValor(&(td->lista));
}
