#include "indice.h"
int Tindice_Crear(struct Tindice* ti,struct Ttokenizer *tt){

    ti->PtrTokenizer = tt;

    /*Creo los arboles*/
    AVL_Crear(&(ti->ArbolTweets),sizeof(Tweet),Comparar_Tweets);
    AVL_Crear(&(ti->ArbolTerminos),sizeof(Termino),Comparar_Terminos);

    return 0;
}

int Tindice_Destruir(Tindice* ti){

    AVL_Vaciar(&(ti->ArbolTweets),Borrar_Tweets);
    AVL_Vaciar(&(ti->ArbolTerminos),Borrar_Terminos);

    return 0;
}

/***************************************************************************/
/**                 TINDICE_AGREGAR                                        */
/***************************************************************************/

int Tindice_Agregar(Tindice* ti, TDiccionario *tweet){

    char* screen_name = (char*) malloc((sizeof(char)*strlen("screen_name"))+1);
    char* created_at  = (char*) malloc((sizeof(char)*strlen("created_at"))+1);
    char* text        = (char*) malloc((sizeof(char)*strlen("text"))+1);
    char* Mensaje; /*Variable que contendra el contenido del campo text del Tweet*/
    char* Palabra; /*Variable que contendra cada palabra del tweet*/

    strcpy(screen_name,"screen_name");
    strcpy(created_at,"created_at");
    strcpy(text,"text");

/**GUARDO EN TWEET EN EL ARBOL DE TWEETS*/

    /*Completo la clave del tweet a guardar*/
    ti->A_Tweet.clave.screen_name = (char*) malloc(TDiccionario_SizeDato(tweet, screen_name));
    ti->A_Tweet.clave.fecha       = (char*) malloc(TDiccionario_SizeDato(tweet, created_at));

    TDiccionario_Obtener(tweet, screen_name, ti->A_Tweet.clave.screen_name);
    TDiccionario_Obtener(tweet, created_at , ti->A_Tweet.clave.fecha);

    /*Guardo el tweet dentro del nodo*/
    ti->A_Tweet.tweet = *tweet;

    /*Lo seteo como ACTIVO*/
    ti->A_Tweet.clave.estado = (ESTADO*) malloc(sizeof(ESTADO));
    *(ti->A_Tweet.clave.estado) = ACTIVO;

    /*Inserto tweet en el arbol*/
    if(!AVL_Vacio(&(ti->ArbolTweets)))
        AVL_MoverCte(&(ti->ArbolTweets),RAIZ);

    /*Notar que los tweets repetidos no son guardados*/
    if(!AVL_Insertar(&(ti->ArbolTweets),&(ti->A_Tweet))){

        TDiccionario_Destruir(tweet);

        free(ti->A_Tweet.clave.screen_name);
        free(ti->A_Tweet.clave.fecha);
        free(ti->A_Tweet.clave.estado);
        free(text);
        free(screen_name);
        free(created_at);
        return FALSE;

    }

/**GUARDO LOS TERMINOS EN EL ARBOL DE TERMINOS*/
    /*Leo el mensaje del tweet*/
    Mensaje = (char*) malloc(TDiccionario_SizeDato(tweet, text));
    TDiccionario_Obtener(tweet, text, Mensaje );

    /*Preparo la lista donde voy a guardar los terminos*/
    L_Crear(&(ti->Terminos), sizeof(char*));

    /*Llamo al tokenizer que devolvera una lista con todas las palabras*/
    Ttokenizer_Analizar(ti->PtrTokenizer, Mensaje, &(ti->Terminos));

    /*Guardo la lista en el arbol de Terminos*/
    L_Mover_Cte(&(ti->Terminos), L_Primero);

    do{

        /*Leo la palabra*/
        L_Elem_Cte(ti->Terminos, &Palabra);

        /*Guardo la clave del nodo*/
        ti->A_Termino.clave = Palabra;

        /*Guardo el dato del nodo. Asumo que la palabra no esta en el arbol*/
        L_Crear(&(ti->A_Termino.dato), sizeof(TClave));
        L_Insertar_Cte(&(ti->A_Termino.dato), L_Primero, &(ti->A_Tweet.clave));


        if(!AVL_Vacio(&(ti->ArbolTerminos)))
            AVL_MoverCte(&(ti->ArbolTerminos),RAIZ);

        if(!AVL_Insertar(&(ti->ArbolTerminos),&(ti->A_Termino))){
        /**Si el termino se repite, agrego el usuario a la lista*/

            /*Libero los datos del nodo que iba a guardar*/
            L_Vaciar(&(ti->A_Termino.dato));
            free(ti->A_Termino.clave);

            /*Obtendo el nodo corriente*/
            AVL_ElemCte(&(ti->ArbolTerminos),&(ti->A_Termino));
            /*Agrego el tweet a la lista de datos*/
            L_Insertar_Cte(&(ti->A_Termino.dato), L_Siguiente, &(ti->A_Tweet.clave));
            continue;
        }
    }while(L_Mover_Cte(&(ti->Terminos), L_Siguiente));

    L_Vaciar(&(ti->Terminos));/*Vacio la lista de terminos*/

    /**FREES*/
    free(Mensaje);
    free(text);
    free(screen_name);
    free(created_at);

    return 0;
}

/***************************************************************************/
/**                 TINDICE_LISTARDOCS                                     */
/***************************************************************************/

int Tindice_ListarDocs(Tindice* ti, char* termino, TListaSimple *docs){

    struct Termino          corriente;
    struct TClave           clave;

    if(AVL_Vacio(&(ti->ArbolTweets)))
        return FALSE;

    if(AVL_Vacio(&(ti->ArbolTerminos)))
        return FALSE;

    corriente.clave = termino;

    /*Busco el nodo que contenga al termino*/
    AVL_MoverCte(&(ti->ArbolTerminos),RAIZ);
    if(!AVL_BuscarNodo(&(ti->ArbolTerminos),&corriente))
        return FALSE;

    /*Obtengo el nodo*/
    AVL_ElemCte(&(ti->ArbolTerminos),&corriente);
    L_Mover_Cte(&(corriente.dato),L_Primero); /*Recorro los datos del tweet*/
    do{
        /*Leo cada usuario que utilizo ese termino*/
        L_Elem_Cte(corriente.dato,&clave);

        ti->A_Tweet.clave.screen_name = clave.screen_name;
        ti->A_Tweet.clave.fecha       = clave.fecha;

        /*Busco el nodo que contenga al tweet*/
        AVL_MoverCte(&(ti->ArbolTweets),RAIZ);
        if(!AVL_BuscarNodo(&(ti->ArbolTweets),&(ti->A_Tweet)))
            continue;

        AVL_ElemCte(&(ti->ArbolTweets),&(ti->A_Tweet));

        /*Inserto el tweet en la lista docs*/
        if(L_Vacia(*docs)){
            /*Si el tweet esta ACTIVO, lo inserto*/
            if(*(ti->A_Tweet.clave.estado) == ACTIVO)
                L_Insertar_Cte(docs,L_Primero,&(ti->A_Tweet.tweet));
            continue;
        }

        /*Primero verifico que el estado sea ACTIVO*/
        if(*(ti->A_Tweet.clave.estado) == ACTIVO )
            L_Insertar_Cte(docs,L_Siguiente,&(ti->A_Tweet.tweet));

    }while(L_Mover_Cte(&(corriente.dato),L_Siguiente));

    return 0;
}

/***************************************************************************/
/**                 TINDICE_ELIMINARTWEET                                  */
/***************************************************************************/

int Tindice_EliminarTweet(Tindice* ti, char* usuario, char* fecha){

    struct Tweet corriente;

    corriente.clave.screen_name = usuario;
    corriente.clave.fecha       = fecha;

    /*Busco el nodo que contenga al termino*/
    AVL_MoverCte(&(ti->ArbolTweets),RAIZ);
    if(!AVL_BuscarNodo(&(ti->ArbolTweets),&corriente))
        return FALSE;

    /*Obtengo el corriente*/
    AVL_ElemCte(&(ti->ArbolTweets),&corriente);

    /*Lo seteo como INACTIVO*/
    *(corriente.clave.estado) = INACTIVO;

    /*Modifico el corriente*/
    AVL_ModifCte(&(ti->ArbolTweets), &corriente);

    return 0;
}

/***************************************************************************/
/**                 TINDICE_ELIMINARUSUARIO                                */
/***************************************************************************/

int Tindice_recorrerUsuarios(Tindice* ti, struct Tweet *usuarioBorrar){

    struct Tweet *corriente;

    if(AVL_MoverCte(&(ti->ArbolTweets),IZQ)){
        Tindice_recorrerUsuarios(ti, usuarioBorrar);
        AVL_MoverCte(&(ti->ArbolTweets),PAD);
    }

    if(AVL_MoverCte(&(ti->ArbolTweets),DER)){
        Tindice_recorrerUsuarios(ti, usuarioBorrar);
        AVL_MoverCte(&(ti->ArbolTweets),PAD);
    }

    corriente = (Tweet*) malloc(sizeof(Tweet));
    AVL_ElemCte(&(ti->ArbolTweets),corriente);

    if(strcmp(usuarioBorrar->clave.screen_name, corriente->clave.screen_name)==0 )
        *(corriente->clave.estado) = INACTIVO;

    AVL_ModifCte(&(ti->ArbolTweets), corriente);

    free(corriente);

    return TRUE;
}

int Tindice_EliminarUsuario(Tindice* ti, char* usuario){

    struct Tweet usuarioBorrar;

    usuarioBorrar.clave.screen_name = usuario;

    /*Muevo el corriente a la raiz*/
    AVL_MoverCte(&(ti->ArbolTweets),RAIZ);

    Tindice_recorrerUsuarios(ti, &usuarioBorrar);

    return 0;
}


/***************************************************************************/
/**                 TINDICE_OPTIMIZAR                                      */
/***************************************************************************/

int TIndice_recorroPreOrder(struct TAVL *arbol, struct TListaSimple *Lista, void* corriente){

    AVL_ElemCte(arbol,corriente);

    if(L_Vacia(*Lista))
        L_Insertar_Cte(Lista,L_Primero,corriente);
    else
        L_Insertar_Cte(Lista,L_Siguiente,corriente);

    if(AVL_MoverCte(arbol,IZQ)){
        TIndice_recorroPreOrder(arbol, Lista, corriente);
        AVL_MoverCte(arbol,PAD);
    }

    if(AVL_MoverCte(arbol,DER)){
        TIndice_recorroPreOrder(arbol, Lista, corriente);
        AVL_MoverCte(arbol,PAD);
    }

    return TRUE;
}


int Tindice_Optimizar(Tindice* ti){

    struct TListaSimple ListaTweets;
    struct TListaSimple ListaTerminos;
    struct Tweet        tweet;
    struct Termino      termino;

    if(AVL_Vacio(&(ti->ArbolTweets)))
        return TRUE;

    if(AVL_Vacio(&(ti->ArbolTerminos)))
        return TRUE;


    L_Crear(&ListaTweets,   sizeof(Tweet));
    L_Crear(&ListaTerminos, sizeof(Termino));


/**Arreglo el arbol de Terminos*/
    AVL_MoverCte(&(ti->ArbolTerminos),RAIZ);
    /*Paso todo el arbol a ListaTerminos*/
    TIndice_recorroPreOrder(&(ti->ArbolTerminos), &ListaTerminos, &termino);

    /*Elimino los nodos del arbol, pero NO ELIMINO sus datos*/
    AVL_Vaciar(&(ti->ArbolTerminos),Funcion_Void);

    /*recorro la lista con todos los terminos*/
    L_Mover_Cte(&ListaTerminos, L_Primero);
    do{
        L_Elem_Cte(ListaTerminos,&termino);

        /*Recorro por cada termino, la lista de usuarios que lo utilizaron*/
        L_Mover_Cte(&(termino.dato),L_Primero);
        do{
            L_Elem_Cte(termino.dato, &tweet);

            /*Si el tweet se encuentra INACTIVO, sigo con el siguiente de la lista*/
            if(*(tweet.clave.estado) == INACTIVO){
                printf("Tweet: %s | %s INACTIVO     termino: %s\n",tweet.clave.screen_name,tweet.clave.fecha,termino.clave);
                continue;
            }else{
                /*Sino, guardo los tweets en una lista auxiliar*/
                if(L_Vacia(ListaTweets))
                    L_Insertar_Cte(&ListaTweets,L_Primero,&tweet);
                else
                    L_Insertar_Cte(&ListaTweets,L_Siguiente,&tweet);
            }
        }while(L_Mover_Cte(&(termino.dato),L_Siguiente));


        if(L_Vacia(ListaTweets)){
            /*Si la lista esta vacia, elimino el Termino*/
            Borrar_Terminos(&termino);
            continue; /*Sigo con el prox termino*/
        }else{
            /*Vacio la lista del termino, y la completo con la auxiliar*/
            L_Vaciar(&(termino.dato));

            /*paso la lista auxiliar a la lista del termino*/
            L_Mover_Cte(&ListaTweets,L_Primero);
            do{
                L_Elem_Cte(ListaTweets,&tweet);
                /*Guardo los tweets en una lista auxiliar*/
                if(L_Vacia(ListaTweets))
                    L_Insertar_Cte(&(termino.dato),L_Primero,&tweet);
                else
                    L_Insertar_Cte(&(termino.dato),L_Siguiente,&tweet);
            }while(L_Mover_Cte(&ListaTweets,L_Siguiente));

            L_Vaciar(&(ListaTweets));
        }

        /*Lo guardo en el arbol*/
        AVL_MoverCte(&(ti->ArbolTerminos),RAIZ);

        if(!L_Vacia(termino.dato))
            AVL_Insertar(&(ti->ArbolTerminos),&termino);

    }while(L_Mover_Cte(&ListaTerminos, L_Siguiente));


/**Arreglo el arbol de Tweets*/
    /*Funcion que hace un recorrido PREorder,
    y guarda cada elemento en la lista que le paso como parametro*/
    AVL_MoverCte(&(ti->ArbolTweets),RAIZ);
    TIndice_recorroPreOrder(&(ti->ArbolTweets), &ListaTweets, &tweet);

    /*Elimino los nodos del arbol, pero NO ELIMINO sus datos*/
    AVL_Vaciar(&(ti->ArbolTweets),Funcion_Void);

    /*recorro la lista con todos los tweets*/
    L_Mover_Cte(&ListaTweets, L_Primero);
    do{
        L_Elem_Cte(ListaTweets,&tweet);

        if(*(tweet.clave.estado)==ACTIVO){
            AVL_MoverCte(&(ti->ArbolTweets),RAIZ);
            AVL_Insertar(&(ti->ArbolTweets),&tweet);
            printf("Agrego tweet: %s | %s \n", tweet.clave.screen_name, tweet.clave.fecha);
        }else{
            Borrar_Tweets(&tweet);
        }
    }while(L_Mover_Cte(&ListaTweets, L_Siguiente));

    L_Vaciar(&ListaTerminos);
    L_Vaciar(&ListaTweets);

    return TRUE;
}




/***************************************************************************/
/**                           FUNCIONES                                    */
/***************************************************************************/
void Funcion_Void(void* a){
    return;
}

int Comparar_Tweets(void* a,void* b){
    struct Tweet *var1 =  (Tweet*) a;
    struct Tweet *var2 =  (Tweet*) b;

    if( strcmp(var1->clave.screen_name,var2->clave.screen_name)==0 )
        return strcmp(var1->clave.fecha,var2->clave.fecha);

    return strcmp(var1->clave.screen_name,var2->clave.screen_name);
}

int Comparar_Terminos(void* a,void* b){
    struct Termino *var1 = (Termino*) a;
    struct Termino *var2 = (Termino*) b;

    return strcmp(var1->clave,var2->clave);
}

void Borrar_Tweets(void* tweet){
    struct Tweet *var =  (Tweet*) tweet;

    TDiccionario_Destruir(&(var->tweet));
    free(var->clave.screen_name);
    free(var->clave.fecha);
    free(var->clave.estado);

    return;
}
void Borrar_Terminos(void* termino){
    struct Termino *var = (Termino*) termino;

    L_Vaciar(&(var->dato));
    free(var->clave);

    return;
}

void Imprimir_Tweet(void* tweet){
    struct Tweet *var =  (Tweet*) tweet;
    char* frase;
    char* text          = (char*) malloc((sizeof(char)*strlen("text"))+1);
    strcpy(text,"text");


    frase   = (char*) malloc(TDiccionario_SizeDato(&(var->tweet), text));
    TDiccionario_Obtener(&(var->tweet), text, frase);

    printf("CLAVE: %s | %s      TWEET: %s\n", var->clave.screen_name, var->clave.fecha, frase);


    free(text);
    free(frase);
    return;
}
