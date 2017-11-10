#ifndef _BUSCADOR_H_
	#define _BUSCADOR_H_
    #include "tokenizer.h"
    #include "Lista.h"
    #include "indice.h"

    typedef struct Tbuscador{
        struct Ttokenizer*  PtrTokenizer;
        struct Tindice*     PtrIndice;
    }Tbuscador;





    int Tbuscador_Crear(struct Tbuscador* tb, struct Ttokenizer* tt, struct Tindice *ti);
    int Tbuscador_Destruir(struct Tbuscador* tb);
    int Tbuscador_Union(struct Tbuscador* tb, char* frase, struct TListaSimple * docs);
    int Tbuscador_Interseccion(struct Tbuscador* tb, char* frase, struct TListaSimple * docs);

    void Tbuscador_ImprimirDocumentos(struct TListaSimple * docs);
    int Tbuscador_ExisteEnDocs(struct TListaSimple *docs, struct TDiccionario diccionario);




#endif
