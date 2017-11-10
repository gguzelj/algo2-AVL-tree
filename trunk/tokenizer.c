#include "tokenizer.h"
#include <ctype.h>

int Ttokenizer_Crear(Ttokenizer* tt){

/**Palabras que no seran indexadas:
    ARTICULOS:
        él, el, la, lo, uno, una, los, las, unos, unas

    DEMOSTRATIVOS:
        este, esta, estos, estas, ese, esa, esos, esas,
        aquel, aquella, aquellos, aquellas

    POSESIVOS:
        mi, tu, su
        mis, tus, sus
        mío, mía, tuyo, tuya, suyo, suya
        míos, mías, tuyos, tuyas, suyos, suyas
        su
        sus
        nuestro, nuestra, vuestro, vuestra, suyo, suya
        nuestros, nuestras, vuestros, vuestras, suyos, suyas

    OTROS:
        a, e, i, o, u, y, que, tal,

*/
/*ARTICULOS:*/
    tt->palabras_noPermitidas[0] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[1] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[2] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[3] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[4] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[5] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[6] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[7] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[8] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[9] = (char*) malloc((sizeof(char)*4) +1);

    strcpy(tt->palabras_noPermitidas[0],"él");
    strcpy(tt->palabras_noPermitidas[1],"el");
    strcpy(tt->palabras_noPermitidas[2],"la");
    strcpy(tt->palabras_noPermitidas[3],"lo");
    strcpy(tt->palabras_noPermitidas[4],"uno");
    strcpy(tt->palabras_noPermitidas[5],"una");
    strcpy(tt->palabras_noPermitidas[6],"los");
    strcpy(tt->palabras_noPermitidas[7],"las");
    strcpy(tt->palabras_noPermitidas[8],"unos");
    strcpy(tt->palabras_noPermitidas[9],"unas");


/*POSESIVOS:*/
    tt->palabras_noPermitidas[10] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[11] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[12] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[13] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[14] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[15] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[16] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[17] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[18] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[19] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[20] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[21] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[22] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[23] = (char*) malloc((sizeof(char)*4) +1);
    tt->palabras_noPermitidas[24] = (char*) malloc((sizeof(char)*5) +1);
    tt->palabras_noPermitidas[25] = (char*) malloc((sizeof(char)*5) +1);
    tt->palabras_noPermitidas[26] = (char*) malloc((sizeof(char)*5) +1);
    tt->palabras_noPermitidas[27] = (char*) malloc((sizeof(char)*5) +1);
    tt->palabras_noPermitidas[28] = (char*) malloc((sizeof(char)*2) +1);
    tt->palabras_noPermitidas[29] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[30] = (char*) malloc((sizeof(char)*7) +1);
    tt->palabras_noPermitidas[31] = (char*) malloc((sizeof(char)*7) +1);
    tt->palabras_noPermitidas[32] = (char*) malloc((sizeof(char)*7) +1);
    tt->palabras_noPermitidas[33] = (char*) malloc((sizeof(char)*7) +1);
    tt->palabras_noPermitidas[34] = (char*) malloc((sizeof(char)*8) +1);
    tt->palabras_noPermitidas[35] = (char*) malloc((sizeof(char)*8) +1);
    tt->palabras_noPermitidas[36] = (char*) malloc((sizeof(char)*8) +1);
    tt->palabras_noPermitidas[37] = (char*) malloc((sizeof(char)*8) +1);

    strcpy(tt->palabras_noPermitidas[10],"mi");
    strcpy(tt->palabras_noPermitidas[11],"tu");
    strcpy(tt->palabras_noPermitidas[12],"su");
    strcpy(tt->palabras_noPermitidas[13],"mis");
    strcpy(tt->palabras_noPermitidas[14],"tus");
    strcpy(tt->palabras_noPermitidas[15],"sus");
    strcpy(tt->palabras_noPermitidas[16],"mio");
    strcpy(tt->palabras_noPermitidas[17],"mia");
    strcpy(tt->palabras_noPermitidas[18],"tuyo");
    strcpy(tt->palabras_noPermitidas[19],"tuya");
    strcpy(tt->palabras_noPermitidas[20],"suyo");
    strcpy(tt->palabras_noPermitidas[21],"suya");
    strcpy(tt->palabras_noPermitidas[22],"mios");
    strcpy(tt->palabras_noPermitidas[23],"mias");
    strcpy(tt->palabras_noPermitidas[24],"tuyos");
    strcpy(tt->palabras_noPermitidas[25],"tuyas");
    strcpy(tt->palabras_noPermitidas[26],"suyos");
    strcpy(tt->palabras_noPermitidas[27],"suyas");
    strcpy(tt->palabras_noPermitidas[28],"su");
    strcpy(tt->palabras_noPermitidas[29],"sus");
    strcpy(tt->palabras_noPermitidas[30],"nuestro");
    strcpy(tt->palabras_noPermitidas[31],"nuestra");
    strcpy(tt->palabras_noPermitidas[32],"vuestro");
    strcpy(tt->palabras_noPermitidas[33],"vuestra");
    strcpy(tt->palabras_noPermitidas[34],"nuestros");
    strcpy(tt->palabras_noPermitidas[35],"nuestras");
    strcpy(tt->palabras_noPermitidas[36],"vuestros");
    strcpy(tt->palabras_noPermitidas[37],"vuestras");

/*OTROS:*/
    tt->palabras_noPermitidas[38] = (char*) malloc((sizeof(char)*1) +1);
    tt->palabras_noPermitidas[39] = (char*) malloc((sizeof(char)*1) +1);
    tt->palabras_noPermitidas[40] = (char*) malloc((sizeof(char)*1) +1);
    tt->palabras_noPermitidas[41] = (char*) malloc((sizeof(char)*1) +1);
    tt->palabras_noPermitidas[42] = (char*) malloc((sizeof(char)*1) +1);
    tt->palabras_noPermitidas[43] = (char*) malloc((sizeof(char)*1) +1);
    tt->palabras_noPermitidas[44] = (char*) malloc((sizeof(char)*3) +1);
    tt->palabras_noPermitidas[45] = (char*) malloc((sizeof(char)*3) +1);

    strcpy(tt->palabras_noPermitidas[38],"a");
    strcpy(tt->palabras_noPermitidas[39],"e");
    strcpy(tt->palabras_noPermitidas[40],"i");
    strcpy(tt->palabras_noPermitidas[41],"o");
    strcpy(tt->palabras_noPermitidas[42],"u");
    strcpy(tt->palabras_noPermitidas[43],"y");
    strcpy(tt->palabras_noPermitidas[44],"que");
    strcpy(tt->palabras_noPermitidas[45],"tal");

    return 0;
}

int Ttokenizer_Destruir(Ttokenizer* tt){
    int i;

    for(i=0;i<=45;i++)
        free(tt->palabras_noPermitidas[i]);

    return 0;
}


int Ttokenizer_Analizar(Ttokenizer* tt, char *frase, struct TListaSimple *terminos){

    char* frase_aux = frase;
    int i           = 0;

    char *simbolos  = ".,:;+-<>$%&=!¡¿?()[]{}\"\'/\\";
    char *separador = " ";
    char *palabra   = NULL;
    char *buffer    = NULL; /*aca voy a guardar la palabra que voy a insertar en la lista*/

/**PASO LAS PALABRAS A MINUSCULAS*/
    for (i = 0; frase[i]; i++)
        frase[i] = tolower(frase[i]);


/**VERIFICO LA PALABRA; Y LA GUARDO EN LA LISTA*/
    /*Separo la cadena por espacios*/
    palabra = strtok(frase, separador);

    if(!palabra)
        return FALSE;

    do{
        /*verifico si algun caracter es algun simbolo*/
        if(strstr(simbolos,palabra) != NULL)
            continue;

        /*Verifico si la palabra es alguna palabra NO permitida*/
        if(Ttokenizer_VerificarPalabra(tt,palabra))
            continue;

        /*GUARDO LA PALABRA EN LA LISTA*/
        buffer = malloc((sizeof(char)*strlen(palabra))+1);
        strcpy(buffer,palabra);

        if(L_Vacia(*terminos)){
            L_Insertar_Cte(terminos, L_Primero, &buffer);
            continue;
        }

        L_Insertar_Cte(terminos, L_Siguiente, &buffer);

    }while( (palabra = strtok( NULL, separador )) != NULL );


    frase = frase_aux;
    return 0 ;
}

int Ttokenizer_VerificarPalabra(Ttokenizer* tt,char *palabra){
    int i=0;

    for(i=0;i<46;i++)
        if(strstr(tt->palabras_noPermitidas[i],palabra) != NULL)
            return TRUE;

    return FALSE;
}




