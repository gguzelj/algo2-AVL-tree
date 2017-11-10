
#ifndef _TOKENIZER_H
    #define _TOKENIZER_H
    #include "Lista.h"


    typedef struct Ttokenizer{
        char *palabras_noPermitidas[46];

    }Ttokenizer;


    /* PROTOTIPOS */
    int Ttokenizer_Crear(Ttokenizer* tt);
    int Ttokenizer_Destruir(Ttokenizer* tt);
    int Ttokenizer_Analizar(Ttokenizer* tt, char *frase, struct TListaSimple *terminos);

    /*FUNCIONES*/
    int Ttokenizer_VerificarPalabra(Ttokenizer* tt,char *palabra);

#endif

