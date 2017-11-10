
#ifndef _INDICE_H
    #define _INDICE_H
    #include <stdio.h>
    #include "Lista.h"
    #include "diccionario.h"
    #include "tokenizer.h"
    #include "TAVL.h"

    typedef enum ESTADO{INACTIVO,ACTIVO}ESTADO;

    typedef struct TClave{
        char        *screen_name;
        char        *fecha;
        enum ESTADO *estado;
    }TClave;


    typedef struct Tweet{
        /*Clave[0] = SCREEN_NAME
          Clave[1] = FECHA*/
        struct TClave       clave;
        struct TDiccionario tweet;
    }Tweet;

    typedef struct Termino{
        char*               clave;
        struct TListaSimple dato;
    }Termino;


    typedef struct Tindice{
        TAVL                    ArbolTweets;
        TAVL                    ArbolTerminos;
        struct Tweet            A_Tweet;   /*Nodo que se guardara en el arbol*/
        struct Termino          A_Termino; /*Nodo que se guardara en el arbol*/
        struct TListaSimple     Terminos;
        struct Ttokenizer*      PtrTokenizer;
    }Tindice;


    /* PROTOTIPOS */
    int Tindice_Crear(struct Tindice* ti,struct Ttokenizer *tt);
    int Tindice_Destruir(struct Tindice* ti);
    int Tindice_Agregar(struct Tindice* ti, TDiccionario *tweet);
    int Tindice_ListarDocs(struct Tindice* ti, char* termino, TListaSimple * docs);
    int Tindice_EliminarTweet(struct Tindice* ti, char* usuario, char* fecha);
    int Tindice_EliminarUsuario(struct Tindice* ti, char* usuario);
    int Tindice_Optimizar(struct Tindice* ti);


    /*FUNCIONES*/
    void Funcion_Void(void*);

    int Comparar_Tweets(void*,void*);
    int Comparar_Terminos(void*,void*);

    void Borrar_Tweets(void*);
    void Borrar_Terminos(void*);

    void Imprimir_Tweet(void*);
#endif

