
#ifndef _LEXICO_H
    #define _LEXICO_H
    #include <stdio.h>

    #ifndef MAX_DATO
        #define MAX_DATO 256
    #endif


    typedef enum TipoToken{
        TOKEN_STRING,
        TOKEN_NUMERO,
        TOKEN_OBJETO_EMPIEZA,
        TOKEN_OBJETO_TERMINA,
        TOKEN_ARRAY_EMPIEZA,
        TOKEN_ARRAY_TERMINA,
        TOKEN_COMA,
        TOKEN_DOSPUNTOS,
        TOKEN_TRUE,
        TOKEN_FALSE,
        TOKEN_NULL
        }TipoToken;

     typedef enum Evento{
        CB_NO_EVENTO,
        CB_COMIENZA_ARRAY,
        CB_TERMINA_ARRAY,
        CB_COMIENZA_OBJETO,
        CB_TERMINA_OBJETO,
        CB_CLAVE,
        CB_TRUE,
        CB_FALSE,
        CB_NULL,
        CB_NUMERO,
        CB_STRING
    }Evento;

    typedef enum CodigoError{
        SIN_ERROR,
        ERROR_PARSER_APERTURA,
        ERROR_PARSER_CLAUSURA,
        ERROR_LEXICO,
        ERROR_SINTACTICO
        }CodigoError;


    typedef struct Ttoken{
        enum TipoToken  tipo;
        char            dato[MAX_DATO];
        }Ttoken;

    typedef struct Tlexico{
        /**variables TP1*/
        struct Tsintactico  *p_sintactico;
        struct Ttoken       token;
        char                flag;
        int                 cont_char;
        enum CodigoError    cod_error;
    }Tlexico;


    /* PROTOTIPOS */
    int Tlexico_Crear(struct Tlexico *al);
    int Tlexico_SetAnalizadorSintactico(struct Tlexico *al,struct Tsintactico *as);
    int Tlexico_PushChar(struct Tlexico *al,char caracter);
    int Tlexico_TerminarFlujo(struct Tlexico *al);
    int Tlexico_GetUltimoError(struct Tlexico *al,enum CodigoError *codigo, char *mensaje);
    int Tlexico_destruir(struct Tlexico *al);


    int Tlexico_VerificarFlag(struct Tlexico *al);

#endif

