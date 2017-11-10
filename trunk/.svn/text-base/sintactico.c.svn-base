#include "parser.h"
#include "sintactico.h"

int Tsintactico_Crear(struct Tsintactico *as){

    as->cod_error = SIN_ERROR;
    as->flag_fin = ' ';
    as->flag_inicio = ' ';
    as->Vec_callbacks[0] = NULL;
    as->Vec_callbacks[1] = NULL;

    as->UltimoDato = NULL;
    P_Crear(&(as->pila), sizeof(char));

    return 0;
}

int Tsintactico_GetUltimoError(struct Tsintactico *as,enum CodigoError *codigo, char *mensaje){
        /*En este caso el unico error posible es el error sintactico*/
        /*Pero, en caso de haber mas errores, se completa la variable*/
        /*mensaje, con la leyenda correspondiente*/
        switch(*codigo){
            case ERROR_SINTACTICO: strcpy(mensaje,"ERROR DE SINTAXIS");
                     break;
            case SIN_ERROR:
            case ERROR_PARSER_APERTURA: break;
            case ERROR_PARSER_CLAUSURA: break;
            case ERROR_LEXICO:          break;

        }
        return 0;
    }


int Tsintactico_PushToken(struct Tsintactico * as,struct Ttoken *token){

    char caracter;

    switch(token->tipo){

        case TOKEN_OBJETO_EMPIEZA:
            as->flag_inicio = 'X';
            if(as->flag_fin == 'X'){
                as->cod_error = ERROR_SINTACTICO;
                return 0;
            }

            as->UltimoDato   = NULL;
            Tsintactico_setCallback(as,CB_COMIENZA_OBJETO,as,as->Vec_callbacks);

            caracter = 'O';
            P_Poner(&(as->pila), &caracter);

            as->tokenAnterior = token->tipo;
        break;


        case TOKEN_OBJETO_TERMINA:

            if(!P_Vacia(as->pila))
                P_Sacar(&(as->pila), &caracter);
            if(caracter=='O'){
                if(as->tokenAnterior == TOKEN_COMA ||
                   as->tokenAnterior == TOKEN_DOSPUNTOS ||
                   as->tokenAnterior == TOKEN_ARRAY_EMPIEZA){
                        as->cod_error = ERROR_SINTACTICO;
                        return 0;
                    }else{

                        as->UltimoDato   = NULL;
                        Tsintactico_setCallback(as,CB_TERMINA_OBJETO,as,as->Vec_callbacks);
                    }
            }else{
                as->cod_error = ERROR_SINTACTICO;
                return 0;
            }

            as->tokenAnterior = token->tipo;
            if(P_Vacia(as->pila)){
                as->flag_fin = 'X';
            }

        break;



        case TOKEN_ARRAY_EMPIEZA:
            as->flag_inicio = 'X';
            if(as->flag_fin == 'X'){
                as->cod_error = ERROR_SINTACTICO;
                return 0;
            }

            as->UltimoDato   = NULL;
            Tsintactico_setCallback(as,CB_COMIENZA_ARRAY,as,as->Vec_callbacks);

            caracter = 'A';
            P_Poner(&(as->pila), &caracter);
            as->tokenAnterior = token->tipo;
        break;



        case TOKEN_ARRAY_TERMINA:
            if(!P_Vacia(as->pila))
                P_Sacar(&(as->pila), &caracter);

            if(caracter=='A'){
                if(as->tokenAnterior == TOKEN_COMA ||
                   as->tokenAnterior == TOKEN_DOSPUNTOS ||
                   as->tokenAnterior == TOKEN_OBJETO_EMPIEZA){
                        as->cod_error = ERROR_SINTACTICO;
                        return 0;
                    }else{
                        as->UltimoDato   = NULL;
                        Tsintactico_setCallback(as,CB_TERMINA_ARRAY,as,as->Vec_callbacks);
                    }
            }else{
                as->cod_error = ERROR_SINTACTICO;
                return 0;
            }

            as->tokenAnterior = token->tipo;
            if(P_Vacia(as->pila)){
                as->flag_fin = 'X';
            }
        break;



        case TOKEN_STRING:
            if(as->flag_inicio=='X'){
                if(!P_Vacia(as->pila))
                    P_Sacar(&(as->pila), &caracter);

                if(as->tokenAnterior == TOKEN_OBJETO_EMPIEZA ||
                   (as->tokenAnterior == TOKEN_COMA &&
                    caracter=='O')){
                    /*CAMPO CLAVE*/
                        as->UltimoDato   = token->dato;
                        Tsintactico_setCallback(as,CB_CLAVE,as,as->Vec_callbacks);
                        /*vuelvo a guardar el caracter leido para que no se rompa la estructura*/
                        P_Poner(&(as->pila), &caracter);
                    }else{
                    /* STRING */
                        as->UltimoDato   = token->dato;
                        Tsintactico_setCallback(as,CB_STRING,as,as->Vec_callbacks);
                        /*vuelvo a guardar el caracter leido para que no se rompa la estructura*/
                        P_Poner(&(as->pila), &caracter);
                }
                as->tokenAnterior = token->tipo;
            }
        break;



        case TOKEN_NUMERO:
            if(as->flag_inicio=='X'){

                if(!P_Vacia(as->pila))
                    P_Sacar(&(as->pila), &caracter);

                if(caracter == 'O'){
                    if(as->tokenAnterior == TOKEN_COMA ||
                       as->tokenAnterior == TOKEN_OBJETO_EMPIEZA){
                            as->cod_error = ERROR_SINTACTICO;
                            return 0;
                    }
                }
                P_Poner(&(as->pila), &caracter);
                as->UltimoDato   = token->dato;
                Tsintactico_setCallback(as,CB_NUMERO,as,as->Vec_callbacks);
                as->tokenAnterior = token->tipo;
            }
        break;



        case TOKEN_NULL:
            if(as->flag_inicio=='X'){

                if(!P_Vacia(as->pila))
                    P_Sacar(&(as->pila), &caracter);

                if(caracter == 'O'){
                    if(as->tokenAnterior == TOKEN_COMA ||
                       as->tokenAnterior == TOKEN_OBJETO_EMPIEZA){
                            as->cod_error = ERROR_SINTACTICO;
                            return 0;
                    }
                }
                P_Poner(&(as->pila), &caracter);
                as->UltimoDato   = token->dato;
                Tsintactico_setCallback(as,CB_NULL,as,as->Vec_callbacks);
                as->tokenAnterior = token->tipo;
            }
        break;



        case TOKEN_FALSE:
            if(as->flag_inicio=='X'){

                if(!P_Vacia(as->pila))
                    P_Sacar(&(as->pila), &caracter);

                if(caracter == 'O'){
                    if(as->tokenAnterior == TOKEN_COMA ||
                       as->tokenAnterior == TOKEN_OBJETO_EMPIEZA){
                            as->cod_error = ERROR_SINTACTICO;
                            return 0;
                    }
                }
                P_Poner(&(as->pila), &caracter);
                as->UltimoDato   = token->dato;
                Tsintactico_setCallback(as,CB_FALSE,as,as->Vec_callbacks);
                as->tokenAnterior = token->tipo;
            }
        break;



        case TOKEN_TRUE:
            if(as->flag_inicio=='X'){

                if(!P_Vacia(as->pila))
                    P_Sacar(&(as->pila), &caracter);

                if(caracter == 'O'){
                    if(as->tokenAnterior == TOKEN_COMA ||
                       as->tokenAnterior == TOKEN_OBJETO_EMPIEZA){
                            as->cod_error = ERROR_SINTACTICO;
                            return 0;
                    }
                }
                P_Poner(&(as->pila), &caracter);
                as->UltimoDato   = token->dato;
                Tsintactico_setCallback(as,CB_TRUE,as,as->Vec_callbacks);
                as->tokenAnterior = token->tipo;
            }
        break;


        case TOKEN_COMA:
            if(as->flag_inicio=='X'){
                as->tokenAnterior = token->tipo;
                as->UltimoDato   = NULL;
            }
        break;


        case TOKEN_DOSPUNTOS:
            if(as->flag_inicio=='X'){
                as->tokenAnterior = token->tipo;
                as->UltimoDato   = NULL;
            }
        break;

        default:
            if(token->dato[0]==EOF && !P_Vacia(as->pila)){
                as->cod_error = ERROR_SINTACTICO;
                return 0;
            }
    }
    return 0;
}

int Tsintactico_TerminarFlujo(struct Tsintactico *as){

    if((as->tokenAnterior != TOKEN_OBJETO_TERMINA &&
        as->tokenAnterior != TOKEN_ARRAY_TERMINA) ||
        !P_Vacia(as->pila) ){
            as->cod_error = ERROR_SINTACTICO;
            return 0;
    }
    return 0;
}

int Tsintactico_destruir(struct Tsintactico *as){
    P_Vaciar(&(as->pila));
    return 0;
}

int Tsintactico_setCallback(struct Tsintactico *as, enum Evento evento, void* tda_contexto,Tcallback *callback){

    switch(evento){
        case CB_NO_EVENTO: break;
        case CB_COMIENZA_ARRAY:
            if(callback[0]==NULL)
                callback[0] = TConstructor_ComienzaArray;
            else
                callback[1] = TConstructor_ComienzaArray;
            break;

        case CB_TERMINA_ARRAY:
            if(callback[0]==NULL)
                callback[0] = TConstructor_TerminaArray;
            else
                callback[1] = TConstructor_TerminaArray;
            break;

        case CB_COMIENZA_OBJETO:
            if(callback[0]==NULL)
                callback[0] = TConstructor_ComienzaObjeto;
            else
                callback[1] = TConstructor_ComienzaObjeto;
            break;

        case CB_TERMINA_OBJETO:
            if(callback[0]==NULL)
                callback[0] = TConstructor_TerminaObjeto;
            else
                callback[1] = TConstructor_TerminaObjeto;
            break;

        case CB_CLAVE:
            if(callback[0]==NULL)
                callback[0] = TConstructor_Clave;
            else
                callback[1] = TConstructor_Clave;
            break;

        case CB_TRUE:
            if(callback[0]==NULL)
                callback[0] = TConstructor_True;
            else
                callback[1] = TConstructor_True;
            break;

        case CB_FALSE:
            if(callback[0]==NULL)
                callback[0] = TConstructor_False;
            else
                callback[1] = TConstructor_False;
            break;

        case CB_NULL:
            if(callback[0]==NULL)
                callback[0] = TConstructor_Null;
            else
                callback[1] = TConstructor_Null;
            break;

        case CB_NUMERO:
            if(callback[0]==NULL)
                callback[0] = TConstructor_Numero;
            else
                callback[1] = TConstructor_Numero;
            break;

        case CB_STRING:
            if(callback[0]==NULL)
                callback[0] = TConstructor_String;
            else
                callback[1] = TConstructor_String;
            break;
    }
    return 0;
}

Tcallback Tsintactico_ObtenerCallback(struct Tsintactico *as){
    Tcallback callback = (as->Vec_callbacks[1] == NULL)?
                            as->Vec_callbacks[0]:
                            as->Vec_callbacks[1];

    if(as->Vec_callbacks[1] == NULL)
        as->Vec_callbacks[0] = NULL;
    else
        as->Vec_callbacks[1] = NULL;

    return callback;
}

void* Tsintactico_ObtenerDato(struct Tsintactico *as){
    return as->UltimoDato;
}
