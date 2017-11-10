#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "diccionario.h"
#include "indice.h"
#include "buscador.h"

int main(int argc, char *argv[]){

    struct Tparser      parser;
    struct TConstructor constructor;
    struct Tindice      indice;
    struct Ttokenizer   tokenizer;
    struct Tbuscador    buscador;
    struct TListaSimple docs;

/************Variables Auxiliares***********************/
    Tcallback callback  = NULL;
    char *comando       = (char *)malloc( sizeof(char ) * 1000);
    char *palabra       = NULL;
    char *separador     = " ";
    int   flag_opcion   = 1;
    int   flag_usuario  = 1;
    int   flag_fecha    = 1;
    char *usuario       = NULL;
    char *fecha         = NULL;
/*******************************************************/

    L_Crear(&docs, sizeof(TDiccionario));
    TConstructor_Crear(&constructor);

    Ttokenizer_Crear(&tokenizer);
    Tindice_Crear(&indice, &tokenizer);
    Tbuscador_Crear(&buscador,&tokenizer,&indice);

    TConstructor_SetIndice(&constructor, &indice);


    while(TRUE){
        printf("Ingrese opcion:\n");
        gets(comando);

     /*   for (i = 0; comando[i]; i++)
            comando[i] = tolower(comando[ i ]);*/


/************************************************************/
/********************AGREGAR*********************************/
/************************************************************/
        if(strstr(comando,"agregar")!= NULL){

            Tparser_Crear(&parser,comando+8);
            Tparser_GetUltimoError(&parser, &(parser.cod_error) , parser.mensaje);

            if(parser.cod_error == SIN_ERROR){ /*UNICO ERROR POSIBLE ES ERROR EN APERTURA*/
                while(!feof(parser.Parchivo)){

                    Tparser_PushChar(&parser,fgetc(parser.Parchivo));

                    while((callback = Tparser_ObtenerCallback(&parser))!=NULL)
                        callback(&constructor,(void*)Tparser_ObtenerDato(&parser));

                    Tparser_GetUltimoError(&parser, &(parser.cod_error), parser.mensaje);
                    if(parser.cod_error != SIN_ERROR){
                        printf("%s\n",parser.mensaje);
                        break;
                    }
                }
                /*TERMINA EL ARCHIVO, Y SE VERIFICA SI QUEDO ALGUN ERROR*/
                if(parser.cod_error == SIN_ERROR){
                    Tparser_TerminarFlujo(&parser);
                    Tparser_GetUltimoError(&parser, &(parser.cod_error), parser.mensaje);

                    if(parser.cod_error != SIN_ERROR){
                        printf("%s\n",parser.mensaje);
                    }
                }
            }else{
                printf("%s\n",parser.mensaje);
            }
            TConstructor_GuardarEnIndice(&constructor);
            continue;
        }


/************************************************************/
/********************AND:************************************/
/************************************************************/

        if(strstr(comando,"and:")!= NULL){
            Tbuscador_Interseccion(&buscador,comando+5,&docs);

            /*Imprimo la lista con las coincidencias:*/
            if(!L_Vacia(docs))
                Tbuscador_ImprimirDocumentos(&docs);
            L_Vaciar(&docs);

            continue;
        }

/************************************************************/
/********************OR:*************************************/
/************************************************************/

        if(strstr(comando,"or:")!= NULL){
            Tbuscador_Union(&buscador,comando+4,&docs);

            /*Imprimo la lista con las coincidencias:*/
            if(!L_Vacia(docs))
                Tbuscador_ImprimirDocumentos(&docs);
            L_Vaciar(&docs);

            continue;
        }

/************************************************************/
/********************ELIMINAR TWEET**************************/
/************************************************************/

        if(strstr(comando,"eliminart:")!= NULL){
            palabra = strtok(comando, separador);
            do{
                if(flag_opcion){
                    flag_opcion = 0;
                    continue;
                }

                if(flag_usuario){
                    usuario = (char*) malloc(sizeof(char)*(strlen(palabra)+1));
                    strcpy(usuario, palabra);
                    flag_usuario = 0;
                    continue;
                }

                if(flag_fecha){
                    fecha = (char*) malloc(sizeof(char)*(strlen(palabra)+1));
                    strcpy(fecha, palabra);
                    flag_fecha = 0;
                    continue;
                }
            }while( (palabra = strtok( NULL, separador )) != NULL );

            Tindice_EliminarTweet(&indice, usuario, fecha);

            free(usuario);
            free(fecha);
            continue;
        }

/************************************************************/
/********************ELIMINAR USUARIO************************/
/************************************************************/

         if(strstr(comando,"eliminaru:")!= NULL){
            Tindice_EliminarUsuario(&indice, comando+11);
            continue;
         }

/************************************************************/
/********************OPTIMIZAR*******************************/
/************************************************************/

         if(strstr(comando,"optimizar")!= NULL){
            Tindice_Optimizar(&indice);
            continue;
         }

/************************************************************/
/********************PREORDER********************************/
/************************************************************/
         if(strstr(comando,"preorder")!= NULL){
            AVL_MoverCte(&(indice.ArbolTweets),RAIZ);
            AVL_PreOrder(&(indice.ArbolTweets),Imprimir_Tweet);
            continue;
         }
/************************************************************/
/********************POSTORDER*******************************/
/************************************************************/
         if(strstr(comando,"postorder")!= NULL){
            AVL_MoverCte(&(indice.ArbolTweets),RAIZ);
            AVL_PostOrder(&(indice.ArbolTweets),Imprimir_Tweet);
            continue;
         }
/************************************************************/
/********************INORDER*********************************/
/************************************************************/
         if(strstr(comando,"inorder")!= NULL){
            AVL_MoverCte(&(indice.ArbolTweets),RAIZ);
            AVL_InOrder(&(indice.ArbolTweets),Imprimir_Tweet);
            continue;
         }




/************************************************************/
/********************SALIR***********************************/
/************************************************************/
        if(strstr(comando,"salir")!= NULL){

            Tparser_destruir(&parser);
            TConstructor_Destruir(&constructor);
            Tindice_Destruir(&indice);
            Ttokenizer_Destruir(&tokenizer);
            free(comando);

            return 0;
        }
    }
    return 0;
}
