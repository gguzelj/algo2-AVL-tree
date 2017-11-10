#ifndef _ARBOL_AVL_H_
	#define _ARBOL_AVL_H_
	#include <stdlib.h>
	#include <memory.h>

	#define IZQ  1
	#define DER  2
	#define PAD  3
	#define RAIZ 4

	#if !defined(NULL)
		#define NULL 0x0
	#endif

	#if !defined(FALSE)
		#define FALSE 0
	#endif

	#if !defined(TRUE)
		#define TRUE 1
	#endif

    typedef int (*PunteroFuncion) (void*, void*);
    typedef void (*Funcion) (void*);

	typedef struct TNodoAVL{
		void* elem;
		struct TNodoAVL *izq,
                        *der,
                        *pad;
        int              FE;
	} TNodoAVL;

	typedef struct TAVL{
	    PunteroFuncion  comparar;
	    struct TNodoAVL *raiz,*cte;
	    int             tamdato;
	}TAVL;


    /***PRIMITIVAS***/
	void AVL_Crear(TAVL *avl,int tdato, PunteroFuncion comparar);
	int  AVL_Vacio(TAVL *a);
	int  AVL_MoverCte(TAVL *a,int mov);
	void AVL_ElemCte(TAVL *avl,void *elem);
	int  AVL_Insertar(TAVL *a,void *elem);
	void AVL_Vaciar(TAVL *a, Funcion func);
	int  AVL_ElimCte(TAVL *a, Funcion func, void* elem);
    void AVL_ModifCte(TAVL *avl,void *elem);

    int AVL_BuscarNodo(TAVL *a,void* elem);

    /***RECORRIDOS***/
    /*Todos reciben un puntero a funcion void(*Funcion)(void*) para poder pasar el elemento en cada recorrido*/
    void AVL_InOrder(TAVL *a, Funcion);
    void AVL_PostOrder(TAVL *a, Funcion);
    void AVL_PreOrder(TAVL *a, Funcion);

#endif
