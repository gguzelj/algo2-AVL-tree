#include "parser.h"
#include "lexico.h"
#include "sintactico.h"
#include <string.h>
#include <ctype.h>

int Tlexico_Crear(struct Tlexico *al){
    al->cod_error = SIN_ERROR;
    al->flag = ' ';
    al->cont_char = 0;
    return 0;
}

int Tlexico_SetAnalizadorSintactico(struct Tlexico *al,struct Tsintactico *as ){
    al->p_sintactico = as;
    return 0;
}

 int Tlexico_GetUltimoError(struct Tlexico *al,enum CodigoError *codigo, char *mensaje){
/*En este caso el unico error posible es el error lexico*/
/*Pero, en caso de haber mas errores, se completa la variable*/
/*mensaje, con la leyenda correspondiente*/
    switch(*codigo){
        case ERROR_LEXICO:
                strcpy(mensaje,"ERROR LEXICO");
                break;
        case SIN_ERROR:
        case ERROR_PARSER_APERTURA: break;
        case ERROR_PARSER_CLAUSURA: break;
        case ERROR_SINTACTICO: break;
    }
    return 0;
}

int Tlexico_VerificarFlag(struct Tlexico *al){
    switch(al->flag){
        case 'S': return 1;
        case 'N':/*Verifico si termino el null*/
                 al->flag = ' ';
                 al->token.dato[al->cont_char] = '\0';
                 if(strlen(al->token.dato)==4){
                    Tsintactico_PushToken(al->p_sintactico,&(al->token));
                    al->cont_char = 0;
                    return 0;
                 }
                 return 1;

        case 'F': /*verifico si termino el false*/
                 al->flag = ' ';
                 if(strlen(al->token.dato)==5){
                    al->token.dato[5] = '\0';
                    Tsintactico_PushToken(al->p_sintactico,&(al->token));
                    al->cont_char = 0;
                    return 0;
                 }
                 return 1;
        case 'T': /*verifico si termino el true*/
                 al->flag = ' ';
                 if(strlen(al->token.dato)==4){
                    al->token.dato[4] = '\0';
                    Tsintactico_PushToken(al->p_sintactico,&(al->token));
                    al->cont_char = 0;
                    return 0;
                 }
                 return 1;

        case 'I':/*finalizo el numero*/
                 al->flag = ' ';
                 al->token.dato[al->cont_char] = '\0';
                 Tsintactico_PushToken(al->p_sintactico,&(al->token));
                 al->cont_char = 0;
                 return 0;
        case ' ': return 0;
    }
    return 0;
}


int Tlexico_PushChar(struct Tlexico *al,char caracter){

/*CARACTERES NUMERICOS*/
    char caracteres_numeros[] = "0123456789";

    switch(caracter){

        case '[':
                /*Cualquier caracter es aceptado por los strings,
                  por eso, cuando se recibe algun caracter especial,
                  se verifica si existe algun string abierto.
                  En ese caso, se guarda el caracter, y se espera el proximo caracter.*/
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                al->token.tipo = TOKEN_ARRAY_EMPIEZA;
                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                al->cont_char = 0;
                break;

        case ']':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                al->token.tipo = TOKEN_ARRAY_TERMINA;
                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                al->cont_char = 0;
                break;

        case '{':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                al->token.tipo = TOKEN_OBJETO_EMPIEZA;
                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                al->cont_char = 0;
                break;

        case '}':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                al->token.tipo = TOKEN_OBJETO_TERMINA;
                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                al->cont_char = 0;
                break;

        case ',':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                al->token.tipo = TOKEN_COMA;
                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                al->cont_char = 0;
                break;

        case ':':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                al->token.tipo = TOKEN_DOSPUNTOS;
                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                al->cont_char = 0;
                break;


        case  ' ':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                return 0;

        case '\n':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                return 0;


        case '\t':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                return 0;

        case '\0':
                if(al->flag == 'S'){
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    break;
                }

                if(Tlexico_VerificarFlag(al)){
                    al->cod_error = ERROR_LEXICO;
                    return 0;
                }

                return 0;

        default:
/*****************************************************************************/
/*********************VERIFICO SI ES UN STRING********************************/
/*****************************************************************************/
                if(caracter == '"' || al->flag == 'S'){
                    if(al->flag == 'S' && caracter == '"'){
                        al->flag = ' ';
                        al->token.dato[al->cont_char] = '\0';
                        Tsintactico_PushToken(al->p_sintactico,&(al->token));
                        al->cont_char = 0;
                        return 0;
                    }else{

                    /*Verifico si falta enviar algun numero*/
                        if(al->flag=='I'){/*finalizo el numero*/
                                al->flag = 'S';
                                al->token.dato[al->cont_char] = '\0';
                                Tsintactico_PushToken(al->p_sintactico,&(al->token));
                                al->cont_char = 0;
                                return 0;
                        }

                    al->flag = 'S';
                    al->token.tipo = TOKEN_STRING;
                    if(caracter!='"'){
                        al->token.dato[al->cont_char] = caracter;
                        al->cont_char++;
                    }
                    return 0;
                    }
                }


/*****************************************************************************/
/*********************VERIFICO SI ES UN INTEGER ******************************/
/*****************************************************************************/
                 if((strchr(caracteres_numeros,caracter) != NULL) || al->flag == 'I'){
                    if(caracter == ' '){
                        al->flag = ' ';
                        al->token.dato[al->cont_char] = '\0';
                        Tsintactico_PushToken(al->p_sintactico,&(al->token));
                        al->cont_char = 0;
                        return 0;
                    }

                    /*Error lexico EJ:  215N*/
                    if(strchr(caracteres_numeros,caracter) == NULL){
                        al->cod_error = ERROR_LEXICO;
                        return 0;
                    }

                    /*Error lexico EJ: TRU1 o FALS7*/
                    if(al->flag=='T' ||
                       al->flag=='F' ||
                       al->flag=='N'){
                        al->cod_error = ERROR_LEXICO;
                        return 0;
                    }

                    al->flag = 'I';
                    al->token.tipo = TOKEN_NUMERO;
                    al->token.dato[al->cont_char] = caracter;
                    al->cont_char++;
                    return 0;
                }

/*****************************************************************************/
/***************VERIFICO SI ES  NULL / TRUE o FALSE***************************/
/*****************************************************************************/
                caracter = toupper(caracter);

                /*NULL*/
                if(caracter == 'N' || al->flag == 'N'){
                    switch(caracter){
                        case 'N':
                                 if(al->token.dato[al->cont_char-1]!='N'){
                                    al->flag = 'N';
                                    al->token.tipo = TOKEN_NULL;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;}
                                else{
                                    al->cod_error = ERROR_LEXICO;
                                    return 0;
                                }
                        case 'U':
                                 if(al->token.dato[al->cont_char-1]=='N'){
                                    al->token.tipo = TOKEN_NULL;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }
                        case 'L':
                                 if(al->token.dato[al->cont_char-1]=='U' &&
                                    al->token.dato[al->cont_char-2]=='N'){
                                        al->token.tipo = TOKEN_NULL;
                                        al->token.dato[al->cont_char] = caracter;
                                        al->cont_char++;
                                        break;
                                 }else{
                                     if(al->token.dato[al->cont_char-1]=='L'){
                                        al->token.tipo = TOKEN_NULL;
                                        al->token.dato[al->cont_char] = caracter;
                                        al->cont_char++;
                                        break;
                                     }
                                 }
                                 al->cod_error = ERROR_LEXICO;
                                 return 0;
                        default:
                                al->cod_error = ERROR_LEXICO;
                                return 0;
                    }
                }

                /*FALSE*/
                if(caracter == 'F' || al->flag == 'F'){
                    switch(caracter){
                        case 'F':
                                 if(al->token.dato[al->cont_char-1]!='F'){
                                    al->flag = 'F';
                                    al->token.tipo = TOKEN_FALSE;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }

                        case 'A':
                                 if(al->token.dato[al->cont_char-1]=='F'){
                                    al->token.tipo = TOKEN_FALSE;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }

                        case 'L':
                                 if(al->token.dato[al->cont_char-2]=='F' &&
                                    al->token.dato[al->cont_char-1]=='A'){
                                    al->token.tipo = TOKEN_FALSE;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }
                        case 'S':
                                 if(al->token.dato[al->cont_char-3]=='F' &&
                                    al->token.dato[al->cont_char-2]=='A' &&
                                    al->token.dato[al->cont_char-1]=='L'){
                                    al->token.tipo = TOKEN_FALSE;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }
                        case 'E':
                                 if(al->token.dato[al->cont_char-4]=='F' &&
                                    al->token.dato[al->cont_char-3]=='A' &&
                                    al->token.dato[al->cont_char-2]=='L' &&
                                    al->token.dato[al->cont_char-1]=='S'){
                                        al->token.tipo = TOKEN_FALSE;
                                        al->token.dato[al->cont_char] = caracter;
                                        al->token.dato[al->cont_char+1] = '\0';
                                        al->cont_char++;
                                    break;
                                 }
                        default:
                                al->cod_error = ERROR_LEXICO;
                                return 0;
                    }

                }


                /*TRUE*/
                if(caracter == 'T' || al->flag == 'T'){

                    switch(caracter){
                        case 'T':
                                 al->flag = 'T';
                                 al->token.tipo = TOKEN_TRUE;
                                 al->token.dato[al->cont_char] = caracter;
                                 al->cont_char++;
                                 break;

                        case 'R':
                                 if(al->token.dato[0]=='T'){
                                    al->token.tipo = TOKEN_TRUE;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }

                        case 'U':
                                 if(al->token.dato[0]=='T' && al->token.dato[1]=='R'){
                                    al->token.tipo = TOKEN_TRUE;
                                    al->token.dato[al->cont_char] = caracter;
                                    al->cont_char++;
                                    break;
                                 }
                        case 'E':
                                 if(al->token.dato[al->cont_char-3]=='T' &&
                                    al->token.dato[al->cont_char-2]=='R' &&
                                    al->token.dato[al->cont_char-1]=='U' ){
                                        al->token.tipo = TOKEN_TRUE;
                                        al->token.dato[al->cont_char] = caracter;
                                        al->token.dato[al->cont_char+1] = '\0';
                                        al->cont_char++;
                                        return 0;
                                }else{
                                    al->cod_error = ERROR_LEXICO;
                                    return 0;
                                }
                        default:
                                al->cod_error = ERROR_LEXICO;
                                return 0;
                    }
                }
    }

    return 0;
}

int Tlexico_TerminarFlujo(struct Tlexico *al){
    if(Tlexico_VerificarFlag(al)){
        al->cod_error = ERROR_LEXICO;
        return 0;
    }
    return 0;
}
int Tlexico_destruir(struct Tlexico*al){
    return 0;
}

