#include "buscador.h"

int Tbuscador_Crear(struct Tbuscador* tb, struct Ttokenizer* tt, struct Tindice* ti){
    tb->PtrTokenizer = tt;
    tb->PtrIndice    = ti;
    return 0;
}

int Tbuscador_Destruir(struct Tbuscador* tb){
    return 0;
}

/********************************************************************************/
/****                       UNION                                              **/
/********************************************************************************/
int Tbuscador_Union(struct Tbuscador* tb, char* frase, TListaSimple *docs){

    char*               termino;
    struct TListaSimple terminos;
    struct TListaSimple aux;
    struct TDiccionario diccionario;

    /*Creo las listas necesarias*/
    L_Crear(&aux, sizeof(TDiccionario));
    L_Crear(&terminos,sizeof(char*));

    /*llamo al tokenizer para que separe la frase en terminos*/
    Ttokenizer_Analizar(tb->PtrTokenizer, frase, &terminos);

    if(L_Vacia(terminos))
        return FALSE;

    /*Loopeo todos los terminos*/
    L_Mover_Cte(&terminos, L_Primero);
    do{
        L_Elem_Cte(terminos,&termino);
        /*Obtengo los tweets que pertenezcan a ese termino*/
        Tindice_ListarDocs(tb->PtrIndice, termino, &aux);

        if(L_Vacia(aux)){
            free(termino);
            continue;
        }

/**GUARDO EL TWEET EN LA LISTA DOCUMENTOS*/
        if(L_Vacia(*docs)){
            L_Mover_Cte(&aux, L_Primero);
            do{
                L_Elem_Cte(aux,&diccionario);
                L_Insertar_Cte(docs,L_Primero,&diccionario);
            }while(L_Mover_Cte(&aux, L_Siguiente));
            L_Vaciar(&aux);
            free(termino);
            continue;
        }

        /*      Si la lista DOCS, que voy a devolver como resultado de
            la union, no esta vacia, debo recorrer todos los tweets de
            la lista docs para verificar que no se repitan tweets. */
        L_Mover_Cte(&aux, L_Primero);
        do{
            L_Elem_Cte(aux,&diccionario);

            if(!Tbuscador_ExisteEnDocs(docs,diccionario)) /*Si no existe ese tweet, lo guardo en DOCS*/
                L_Insertar_Cte(docs,L_Siguiente,&diccionario);

        }while(L_Mover_Cte(&aux, L_Siguiente));
        L_Vaciar(&aux);
        free(termino);
    }while(L_Mover_Cte(&terminos, L_Siguiente));

    L_Vaciar(&terminos);
    return 0;
}

/********************************************************************************/
/****                       INTERSECCION                                       **/
/********************************************************************************/
int Tbuscador_Interseccion(struct Tbuscador* tb, char* frase, struct TListaSimple * docs){

    char*               termino;
    struct TListaSimple terminos;
    struct TListaSimple aux;
    struct TListaSimple temporal;
    struct TDiccionario diccionario;


    /*Creo las listas necesarias*/
    L_Crear(&aux     , sizeof(TDiccionario));
    L_Crear(&temporal, sizeof(TDiccionario));
    L_Crear(&terminos, sizeof(char*));

    /*llamo al tokenizer para que separe la frase en terminos*/
    Ttokenizer_Analizar(tb->PtrTokenizer, frase, &terminos);

    if(L_Vacia(terminos))
        return FALSE;

    /*Loopeo todos los terminos*/
    L_Mover_Cte(&terminos, L_Primero);
    do{
        L_Elem_Cte(terminos,&termino);
        /*Obtengo los tweets que pertenezcan a ese termino*/
        Tindice_ListarDocs(tb->PtrIndice, termino, &aux);

        /*Si la lista esta vacia, la interseccion sera vacia*/
        if(L_Vacia(aux)){
            L_Vaciar(&terminos);
            free(termino);
            L_Vaciar(docs);
            break;
        }


/**GUARDO EL TWEET EN LA LISTA DOCUMENTOS*/
        if(L_Vacia(*docs)){

            /*Recorro la lista AUX y la guardo en DOCS*/
            L_Mover_Cte(&aux, L_Primero);
            do{
                L_Elem_Cte(aux,&diccionario);
                L_Insertar_Cte(docs,L_Primero,&diccionario);
            }while(L_Mover_Cte(&aux, L_Siguiente));

            L_Vaciar(&aux);
            free(termino);
            continue;
        }

        /*  Para verificar la interseccion, lo que hago es recorrer toda la
        lista AUX (que contiene los Tdiccionarios devueltos por ListarDocs),
        y guardar solamente los Tdiccionarios que estan en DOCS. */
        L_Mover_Cte(&aux, L_Primero);
        do{
            L_Elem_Cte(aux,&diccionario);

            if(Tbuscador_ExisteEnDocs(docs,diccionario))/*Guardo la interseccion en TEMPORAL*/
                L_Insertar_Cte(&temporal,L_Primero,&diccionario);

        }while(L_Mover_Cte(&aux, L_Siguiente));
        L_Vaciar(docs);

        /*Paso la tabla TEMPORAL a DOCS*/
        if(L_Vacia(temporal)){

            free(termino);
            L_Vaciar(&terminos);
            L_Vaciar(docs);
            L_Vaciar(&aux);
            return FALSE;

        }

        L_Mover_Cte(&temporal,L_Primero);
        do{
            L_Elem_Cte(temporal,&diccionario);
            L_Insertar_Cte(docs,L_Primero,&diccionario);
        }while(L_Mover_Cte(&temporal,L_Siguiente));

        free(termino);
        L_Vaciar(&temporal);
        L_Vaciar(&aux);

    }while(L_Mover_Cte(&terminos, L_Siguiente));

    L_Vaciar(&terminos);

    return 0;
}



/*******************IMPRIMO DOCUMENTOS*************************/
void Tbuscador_ImprimirDocumentos(struct TListaSimple *docs){

    struct TDiccionario     diccionario;
    char* screen_name   = (char*) malloc((sizeof(char)*strlen("screen_name"))+1);
    char* created_at    = (char*) malloc((sizeof(char)*strlen("created_at"))+1);
    char* text          = (char*) malloc((sizeof(char)*strlen("text"))+1);

    char* Usuario;
    char* Fecha;
    char* Tweet;

    strcpy(screen_name,"screen_name");
    strcpy(created_at,"created_at");
    strcpy(text,"text");

    L_Mover_Cte(docs,L_Primero);
    do{
        L_Elem_Cte(*docs,&diccionario);

        Usuario = (char*) malloc(TDiccionario_SizeDato(&diccionario, screen_name));
        Fecha   = (char*) malloc(TDiccionario_SizeDato(&diccionario, created_at ));
        Tweet   = (char*) malloc(TDiccionario_SizeDato(&diccionario, text       ));

        TDiccionario_Obtener(&diccionario, screen_name, Usuario);
        TDiccionario_Obtener(&diccionario, created_at , Fecha);
        TDiccionario_Obtener(&diccionario, text       , Tweet);

        printf("CLAVE: %s | %s      TWEET: %s\n", Usuario, Fecha, Tweet);

        free(Usuario);
        free(Fecha);
        free(Tweet);

    }while(L_Mover_Cte(docs,L_Siguiente));

    free(screen_name);
    free(created_at);
    free(text);

    return;
}

int Tbuscador_ExisteEnDocs(struct TListaSimple *docs, struct TDiccionario diccionario){

    struct TDiccionario diccionario_corriente;

    char* screen_name   = (char*) malloc((sizeof(char)*strlen("screen_name"))+1);
    char* created_at    = (char*) malloc((sizeof(char)*strlen("created_at"))+1);

    char* Usuario;
    char* Fecha;
    char* Usuario_corriente;
    char* Fecha_corriente;

    strcpy(screen_name,"screen_name");
    strcpy(created_at,"created_at");

    Usuario = (char*) malloc(TDiccionario_SizeDato(&diccionario,screen_name));
    Fecha   = (char*) malloc(TDiccionario_SizeDato(&diccionario,created_at ));
    TDiccionario_Obtener(&diccionario,screen_name,Usuario);
    TDiccionario_Obtener(&diccionario,created_at ,Fecha  );


    L_Mover_Cte(docs,L_Primero);
    do{
        L_Elem_Cte(*docs, &diccionario_corriente);

        Usuario_corriente = (char*) malloc(TDiccionario_SizeDato(&diccionario_corriente,screen_name));
        Fecha_corriente   = (char*) malloc(TDiccionario_SizeDato(&diccionario_corriente,created_at ));
        TDiccionario_Obtener(&diccionario_corriente,screen_name,Usuario_corriente);
        TDiccionario_Obtener(&diccionario_corriente,created_at ,Fecha_corriente  );

        if(strcmp(Usuario,Usuario_corriente) == 0 &&
           strcmp(Fecha  ,Fecha_corriente  ) == 0)
           {
                free(screen_name);
                free(created_at);

                free(Usuario);
                free(Fecha);

                free(Usuario_corriente);
                free(Fecha_corriente);
                return TRUE;
           }
           free(Usuario_corriente);
           free(Fecha_corriente);

    }while(L_Mover_Cte(docs,L_Siguiente));

    free(screen_name);
    free(created_at);

    free(Usuario);
    free(Fecha);

    return FALSE;
}
