#include "TAVL.h"

/**************     INICIO: AVL_CREAR            **************/
void AVL_Crear(TAVL *avl,int tdato, PunteroFuncion comparar){

	avl->tamdato = tdato;
	avl->raiz = NULL;
	avl->cte  = NULL;
	avl->comparar = comparar;
    return;
}
/**************     FIN:    AVL_CREAR            **************/

/**************     INICIO: AVL_VACIO            **************/
int AVL_Vacio(TAVL *a){
    return (a->raiz == NULL);
}
/**************     FIN:    AVL_VACIO            **************/

/**************     INICIO: AVL_MoverCte         **************/
int AVL_MoverCte(TAVL *a,int mov){
	int movio = TRUE;
	switch (mov)
	{
		case IZQ : if (a->cte->izq != NULL)
						a->cte = a->cte->izq;
					else
						movio = FALSE;
					break;
		case DER : if (a->cte->der != NULL)
						a->cte = a->cte->der;
					else
						movio = FALSE;
					break;
		case PAD : if (a->cte != a->raiz)
						a->cte = a->cte->pad;
					else
						movio = FALSE;
					break;
		case RAIZ : if (a->raiz != NULL)
						a->cte = a->raiz;
					else
						movio = FALSE;
					break;
		default : movio = FALSE;
	}
	return movio;
}
/**************     FIN:    AVL_MoverCte         **************/


/**************     INICIO: AVL_ElemCte          **************/
void AVL_ElemCte(TAVL *avl,void *elem){
    memcpy(elem,avl->cte->elem,avl->tamdato);
}
/**************     FIN:    AVL_ElemCte          **************/

/**************     INICIO: AVL_ModifCte         **************/
void AVL_ModifCte(TAVL *a,void *elem){
	memcpy(a->cte->elem,elem,a->tamdato);
}
/**************     FIN:    AVL_ModifCte         **************/


/**************     INICIO: AVL_Insertar         **************/
TNodoAVL* NewNodo(void* elem,size_t tamdato){
    struct TNodoAVL *nodo = (TNodoAVL*) malloc(sizeof(TNodoAVL));

    if(!nodo)
        return NULL;

    nodo->der = NULL;
    nodo->izq = NULL;
    nodo->pad = NULL;
    nodo->FE = 0;

    nodo->elem = malloc(tamdato);
    if(!nodo->elem){
        free(nodo);
        return NULL;
    }

    memcpy(nodo->elem,elem,tamdato);

    return nodo;

}
    /****************    ROTACIONES        ******************/
    /****RSD****/
    void RSD(TNodoAVL *Nodo){
        TNodoAVL *aux;

        aux = Nodo->izq;
        Nodo->izq = aux->der;
        aux->der = Nodo;

        if(Nodo->pad){
            if(Nodo->pad->der == Nodo)
                Nodo->pad->der = aux;
            else
                Nodo->pad->izq = aux;
        }

        /*Actualizo los padres*/
        if(Nodo->izq)
            Nodo->izq->pad = Nodo;

        aux->pad = Nodo->pad;
        Nodo->pad = aux;

        /*Actualizo los FE*/
        aux->FE = 0;
        Nodo->FE = 0;

        return;
    }

    /****RSI****/
    void RSI(TNodoAVL *Nodo){
        TNodoAVL *aux;

        aux = Nodo->der;
        Nodo->der = aux->izq;
        aux->izq = Nodo;

        if(Nodo->pad){
            if(Nodo->pad->der == Nodo)
                Nodo->pad->der = aux;
            else
                Nodo->pad->izq = aux;
        }

        /*Actualizo los padres*/
        if(Nodo->der)
            Nodo->der->pad = Nodo;

        aux->pad = Nodo->pad;
        Nodo->pad = aux;

        /*Actualizo los FE*/
        aux->FE = 0;
        Nodo->FE = 0;

        return;
    }

    /****RDD****/
    void RDD(TNodoAVL *Nodo){
        TNodoAVL *Padre, *Izq, *Ult;

        Padre = Nodo;
        Izq   = Padre->izq;
        Ult   = Izq->der;

        Izq->der = Ult->izq;
        Padre->izq = Ult->der;

        Ult->izq = Izq;
        Ult->der = Padre;

        /*Actualizo los padres*/
        Ult->pad   = Padre->pad;
        Padre->pad = Ult;
        Izq->pad   = Ult;

        if(Izq->der)
            Izq->der->pad = Izq;
        if(Padre->izq)
            Padre->izq->pad = Padre;

        if(Ult->pad){
            if(Ult->pad->der == Padre)
                Ult->pad->der = Ult;
            else
                Ult->pad->izq = Ult;
        }

        /*Actualizo los FE*/
        Padre->FE = 1;
        Izq->FE   = 0;
        Ult->FE   = 0;

        return;
    }

    /****RDI****/
    void RDI(TNodoAVL *Nodo){
        TNodoAVL *Padre, *Der, *Ult;

        Padre = Nodo;
        Der   = Padre->der;
        Ult   = Der->izq;

        Der->izq   = Ult->der;
        Padre->der = Ult->izq;

        Ult->izq = Padre;
        Ult->der = Der;

        /*Actualizo los padres*/
        Ult->pad   = Padre->pad;
        Padre->pad = Ult;
        Der->pad   = Ult;

        if(Der->izq)
            Der->izq->pad = Der;
        if(Padre->der)
            Padre->der->pad = Padre;

        if(Ult->pad){
            if(Ult->pad->der == Padre)
                Ult->pad->der = Ult;
            else
                Ult->pad->izq = Ult;
        }

        /*Actualizo los FE*/
        Padre->FE = -1;
        Der->FE   = 0;
        Ult->FE   = 0;

        return;
    }


void equilibrar(TAVL *a, int mov){
/**Cambio valor del FE*/
    /*Calculo su FE*/
    if(mov == IZQ)
        a->cte->FE--;

    if(mov == DER)
        a->cte->FE++;

/**Condiciones de corte:*/
    /*FE == 2 o FE == -2*/
    if(a->cte->FE == -2){
        if(a->cte->izq->FE == -1){
            RSD(a->cte);/*RSD: Rotacion Simple Derecha*/
            if(a->cte == a->raiz)
                a->raiz = a->cte->pad;
            return;
        }

        if(a->cte->izq->FE == 1){
            RDD(a->cte);/*RDD: Rotacion Doble Derecha*/
            if(a->cte == a->raiz)
                a->raiz = a->cte->pad;
            return;
        }
    }

    if(a->cte->FE == 2){
        if(a->cte->der->FE == -1){
            RDI(a->cte);/*RDI: Rotacion Doble Izquierda*/
            if(a->cte == a->raiz)
                a->raiz = a->cte->pad;
            return;
        }


        if(a->cte->der->FE == 1){
            RSI(a->cte);/*RSI: Rotacin Simple Izquierda*/
            if(a->cte == a->raiz)
                a->raiz = a->cte->pad;
            return;
        }
    }

    /*FE = 0,  o estoy en la raiz*/
    if(a->cte->pad == NULL || a->cte->FE == 0)
        return;

/**Sino, sigo equilibrando*/
    if(a->cte->pad->der == a->cte){
        a->cte = a->cte->pad;
        equilibrar(a, DER);
        return;
    }


    if(a->cte->pad->izq == a->cte){
        a->cte = a->cte->pad;
        equilibrar(a, IZQ);
        return;
    }

    return;
}

int AVL_Insertar(TAVL *a,void *elem){

    int resultado;

/**Busco Nodo donde insertar**/
    /*Si el arbol esta vacio, lo hago la insercion en la raiz*/
    if(!a->raiz){
        if((a->raiz = NewNodo(elem,a->tamdato))!= NULL){
            a->cte = a->raiz;
            return TRUE;
        }
        return TRUE;
    }

    resultado = (a->comparar)(a->cte->elem, elem);

    switch(resultado){
        case 0: return FALSE; /*Devuelvo FALSE si los nodos son iguales*/

        case 1: /*Muevo a la izquierda*/
                if(a->cte->izq != NULL){
                    a->cte = a->cte->izq;
                    return AVL_Insertar(a, elem)?TRUE:FALSE;
                }
                /*reservo lugar para el nodo*/
                a->cte->izq = NewNodo(elem,a->tamdato);
                /*Guardo el padre*/
                a->cte->izq->pad = a->cte;

                /**ACA EQUILIBRO*/
                equilibrar(a,IZQ);

                return TRUE;

        case -1: /*muevo a la derecha*/
                if(a->cte->der != NULL){
                    a->cte = a->cte->der;
                    return AVL_Insertar(a, elem)?TRUE:FALSE;
                }
                /*reservo lugar para el nodo*/
                a->cte->der = NewNodo(elem,a->tamdato);
                /*Guardo el padre*/
                a->cte->der->pad = a->cte;

                /**ACA EQUILIBRO*/
                equilibrar(a,DER);

                return TRUE;
    }
    return TRUE;
}
/**************     FIN:    AVL_Insertar         **************/

/************** EMPIEZA:    AVL_Vaciar           **************/
void VaciarSub(TNodoAVL *pnodo)
{
	if (pnodo != NULL)
	{
		if (!((pnodo->izq == NULL) && (pnodo->der == NULL)))
		{
			VaciarSub(pnodo->izq);
			VaciarSub(pnodo->der);
		}
		free(pnodo->elem);
		free(pnodo);
	}
}

void AVL_Vaciar(TAVL *a, Funcion func){

    if(!a->raiz)
        return;

    a->cte = a->raiz;
    AVL_PostOrder(a,func);

	VaciarSub(a->raiz);
	a->raiz = NULL;
	a->cte = NULL;

    return;
}
/**************     FIN:    AVL_Vaciar           **************/


/************** EMPIEZA:    AVL_Inorder          **************/
void AVL_InOrder(TAVL *a, Funcion func){

    if(!a->raiz)
        return;

    if(a->cte->izq != NULL){
        a->cte = a->cte->izq;
        AVL_InOrder(a, func);
        a->cte = a->cte->pad;
    }

    func(a->cte->elem);

    if(a->cte->der != NULL){
        a->cte = a->cte->der;
        AVL_InOrder(a,func);
        a->cte = a->cte->pad;
    }
}
/**************     FIN:    AVL_Inorder          **************/

/************** EMPIEZA:    AVL_PostOrder        **************/
void AVL_PostOrder(TAVL *a, Funcion func){

    if(!a->raiz)
        return;

    if(a->cte->izq != NULL){
        a->cte = a->cte->izq;
        AVL_PostOrder(a, func);
        a->cte = a->cte->pad;
    }

    if(a->cte->der != NULL){
        a->cte = a->cte->der;
        AVL_PostOrder(a,func);
        a->cte = a->cte->pad;
    }

    func(a->cte->elem);
}
/**************     FIN:    AVL_PostOrder        **************/

/************** EMPIEZA:    AVL_PreOrder         **************/
void AVL_PreOrder(TAVL *a, Funcion func){

    if(!a->raiz)
        return;

    func(a->cte->elem);

    if(a->cte->izq != NULL){
        a->cte = a->cte->izq;
        AVL_PreOrder(a, func);
        a->cte = a->cte->pad;
    }

    if(a->cte->der != NULL){
        a->cte = a->cte->der;
        AVL_PreOrder(a,func);
        a->cte = a->cte->pad;
    }
}
/**************     FIN:    AVL_PreOrder         **************/


int AVL_BuscarNodo(TAVL *a,void* elem){
    int resultado = (a->comparar)(a->cte->elem, elem);;

    switch(resultado){
        case 0: return TRUE; /*Encontre la posicion si los nodos son iguales*/

        case 1: /*Muevo a la izquierda*/
                if(AVL_MoverCte(a,IZQ))
                    return AVL_BuscarNodo(a, elem);
                return FALSE;

        case -1: /*muevo a la derecha*/
                if(AVL_MoverCte(a,DER))
                    return AVL_BuscarNodo(a, elem);
                return FALSE;
    }
    return FALSE;
}
