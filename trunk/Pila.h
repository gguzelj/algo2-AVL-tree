#ifndef __PILA_H__
	#define __PILA_H__
	
	#include <malloc.h>
	#include <memory.h>

	#if !defined(NULL)
		#define NULL 0
	#endif
	
	#if !defined(FALSE)
		#define FALSE 0
	#endif
	
	#if !defined(TRUE)
		#define TRUE 1
	#endif

	/**
	 * Estructura auxiliar de la pila. Es privada y no debe usarse bajo ning�n
	 * concepto en la aplicaci�n.
	 */
	typedef struct TNodoPila
	{
		void* Elem;
		struct TNodoPila *Siguiente;
	} TNodoPila;
	
	/**
	 * Estructura cabecera, este es el tipo que se deber� instanciar, aunque
	 * nunca acceder a sus campos.
	 */
	typedef struct
	{
		TNodoPila *Tope;
		int TamanioDato;
	} TPila;
	
	/*P_CREAR
	Pre: P no fue creada.
	Post: P creada y vac�a. */
	void P_Crear(TPila *pP, int TamanioDato);
	
	/*P_VACIAR
	Pre: P creada.
	Post: P vac�a. */
	void P_Vaciar(TPila *pP);
	
	/*P_VACIA
	Pre: P creada.
	Post: Si P est� vac�a devuelve TRUE, sino FALSE. */
	int P_Vacia(TPila P);
	
	/*P_PONER
	Pre: P creada.
	Post: E se agreg� como Tope de P.
	Devuelve FALSE si no pudo ADD E, sino devuelve TRUE.*/
	int P_Poner(TPila *pP, void* pE);
	
	/*P_SACAR
	Pre: P creada y no Vac�a.
	Post: Se extrajo de P el Tope y se devuelve en E.
	Si no pudo extraer el elemento (porque la Stack estaba vac�a) devuelve FALSE,
	sino devuelve TRUE.*/
	int P_Sacar(TPila *pP, void* pE);

#endif

