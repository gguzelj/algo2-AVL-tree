#include "parser.h"

int Tparser_Crear(struct Tparser *p, char *archivo){
/*Inicializo las variables del parser*/
    p->cod_error = SIN_ERROR;
/*Inicializo la estructura lexico*/
    Tlexico_Crear(&(p->lexico));
/*Inicializo la estructura sintactico*/
    Tsintactico_Crear(&(p->sintactico));
/*Vinculo el Analizador lexico con el sintactico*/
    Tlexico_SetAnalizadorSintactico(&(p->lexico),&(p->sintactico));
/*Abro el archivo*/
    p->Parchivo=fopen(archivo,"r");
    if (p->Parchivo==NULL){
        p->cod_error=ERROR_PARSER_APERTURA;
    }
    return 0;
}

int Tparser_GetUltimoError(struct Tparser *p, enum CodigoError *codigo, char* mensaje){

    if(p->cod_error == SIN_ERROR){
        if(p->lexico.cod_error == SIN_ERROR){
            if(p->sintactico.cod_error == SIN_ERROR){
                codigo = SIN_ERROR;
                return 0;
            }else{
                Tsintactico_GetUltimoError(&(p->sintactico), &(p->sintactico.cod_error), mensaje);
                p->cod_error = p->sintactico.cod_error;
                return 0;
             }
        }else{
            Tlexico_GetUltimoError(&(p->lexico), &(p->lexico.cod_error), mensaje);
            p->cod_error = p->lexico.cod_error;
            return 0;
        }
    }else{
        switch(*codigo){
            case ERROR_PARSER_APERTURA: strcpy(mensaje,"ERROR EN APERTURA DE ARCHIVO");
                    break;
            case ERROR_PARSER_CLAUSURA: strcpy(mensaje,"ERROR EN CLAUSURA DE ARCHIVO");
                    break;
            case SIN_ERROR: break;
            case ERROR_LEXICO: break;
            case ERROR_SINTACTICO: break;
        }
        return 0;
    }
    return 0;
}

int Tparser_TerminarFlujo(struct Tparser *p){
    if (fclose(p->Parchivo)==!0)
        p->cod_error=ERROR_PARSER_CLAUSURA;    /*Error al cerrar el archivo*/

    Tlexico_TerminarFlujo(&(p->lexico));
    Tsintactico_TerminarFlujo(&(p->sintactico));
    return 0;
}

int Tparser_PushChar(struct Tparser *p,char caracter){
    Tlexico_PushChar(&(p->lexico),caracter);
    return 0;
}

int Tparser_destruir(struct Tparser *p){
    return 0;
}

Tcallback Tparser_ObtenerCallback(struct Tparser *p){
    return Tsintactico_ObtenerCallback(&(p->sintactico));
}

void* Tparser_ObtenerDato(struct Tparser *p){
    return (void*) Tsintactico_ObtenerDato(&(p->sintactico));
}
