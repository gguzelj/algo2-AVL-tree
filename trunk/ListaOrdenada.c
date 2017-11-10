#include "ListaOrdenada.h"

void TlistaOrdenada_Crear(struct TlistaOrdenada *LO, size_t tamanio){
    L_Crear(&(LO->ListaSimple), tamanio);
}

void TlistaOrdenada_Vaciar(struct TlistaOrdenada *LO){

    struct Elemento corriente;

    while(!L_Vacia(LO->ListaSimple)){
        L_Mover_Cte(&(LO->ListaSimple), L_Primero);
        if(!L_Vacia(LO->ListaSimple))
            L_Elem_Cte(LO->ListaSimple,&corriente);

        free(corriente.Clave);
        free(corriente.Valor);
        L_Borrar_Cte(&(LO->ListaSimple));
    }
}


int TlistaOrdenada_Vacia(struct TlistaOrdenada *LO){
    return L_Vacia(LO->ListaSimple);
}

int TlistaOrdenada_Insertar(struct TlistaOrdenada *LO, struct Elemento Elemento){
    struct Elemento corriente;

/** Si la lista esta vacia, inserto el elemento primero*/
    if(L_Vacia(LO->ListaSimple))
        return L_Insertar_Cte(&(LO->ListaSimple), L_Primero, &Elemento);

/**Leo el corriente, y en caso de ser menor al elemento recibido, lo muevo al principio*/
    L_Elem_Cte(LO->ListaSimple,&corriente);

    if(strcmp(corriente.Clave,Elemento.Clave)>0)
        L_Mover_Cte(&(LO->ListaSimple), L_Primero);

/**Leo el corriente, y recorro la lista hasta encontrar el lugar correcto*/
    L_Elem_Cte(LO->ListaSimple,&corriente);

    while(((strcmp(corriente.Clave,Elemento.Clave)>0)   ||
           (strcmp(corriente.Clave,Elemento.Clave)>0)) ||
          L_Mover_Cte(&(LO->ListaSimple), L_Siguiente)){
        L_Elem_Cte(LO->ListaSimple,&corriente);
        if(strcmp(Elemento.Clave,corriente.Clave)<0)
            break;
        if(strcmp(Elemento.Clave,corriente.Clave)==0)
            break;
    }

    if(strcmp(Elemento.Clave,corriente.Clave)==0){
        free(corriente.Clave);
        free(corriente.Valor);
        L_Borrar_Cte(&(LO->ListaSimple));
        L_Elem_Cte(LO->ListaSimple,&corriente);
    }

    return (strcmp(Elemento.Clave,corriente.Clave)<0)?
        L_Insertar_Cte(&(LO->ListaSimple), L_Anterior, &Elemento):
        L_Insertar_Cte(&(LO->ListaSimple), L_Siguiente, &Elemento);
}


int TlistaOrdenada_Obtener(struct TlistaOrdenada *LO,char* clave,char* buffer){
    struct Elemento corriente;

/**Leo el corriente, y en caso de ser menor al elemento recibido, lo muevo al principio*/
    L_Elem_Cte(LO->ListaSimple,&corriente);

    if(strcmp(corriente.Clave,clave)>0)
        L_Mover_Cte(&(LO->ListaSimple), L_Primero);

/**Leo el corriente, y recorro la lista hasta encontrar el lugar correcto*/
    L_Elem_Cte(LO->ListaSimple,&corriente);

    while((strcmp(corriente.Clave,clave)==0) || L_Mover_Cte(&(LO->ListaSimple), L_Siguiente)){
        L_Elem_Cte(LO->ListaSimple,&corriente);
        if(strcmp(clave,corriente.Clave)==0)
            break;
    }

    if(strcmp(clave,corriente.Clave)==0)
        strcpy(buffer,corriente.Valor);

    return 0;
}

int TlistaOrdenada_SizeDato(struct TlistaOrdenada *LO,char* clave){

    struct Elemento corriente;
/**Leo el corriente, y en caso de ser menor al elemento recibido, lo muevo al principio*/
    L_Elem_Cte(LO->ListaSimple,&corriente);

    if(strcmp(corriente.Clave,clave)>0)
        L_Mover_Cte(&(LO->ListaSimple), L_Primero);
/**Leo el corriente, y recorro la lista hasta encontrar el lugar correcto*/
    L_Elem_Cte(LO->ListaSimple,&corriente);

    while((strcmp(corriente.Clave,clave)==0) || L_Mover_Cte(&(LO->ListaSimple), L_Siguiente)){
        L_Elem_Cte(LO->ListaSimple,&corriente);
        if(strcmp(clave,corriente.Clave)==0)
            break;
    }
    return (strcmp(clave,corriente.Clave)==0)?
        ((sizeof(char) * strlen(corriente.Valor))+1):
         0;
}

int TlistaOrdenada_TamanioElemento(struct TlistaOrdenada *LO){
    return sizeof(LO->Elemento);
}

int TlistaOrdenada_GuardarClave(struct TlistaOrdenada *LO, void *clave){
    LO->Elemento.Clave = (char*) malloc(sizeof(char) * (strlen(clave)+1));
    strcpy(LO->Elemento.Clave,clave);
    return 0;
}

int TlistaOrdenada_GuardarValor(struct TlistaOrdenada *LO, void *valor){
    LO->Elemento.Valor = (char*) malloc(sizeof(char) * (strlen(valor)+1));
    strcpy(LO->Elemento.Valor,valor);
    return 0;
}

int TlistaOrdenada_LiberarClave(struct TlistaOrdenada *LO){
    free(LO->Elemento.Clave);
    return 0;
}

int TlistaOrdenada_LiberarValor(struct TlistaOrdenada *LO){
    free(LO->Elemento.Valor);
    return 0;
}
