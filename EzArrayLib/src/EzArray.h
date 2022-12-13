#ifndef EZARRAY_H
	#define EZARRAY_H

	#ifndef _STRING_H
	#include <string.h>
	#endif

	#ifndef EXIT_SUCCESS
	#include <stdlib.h>
	#endif


	//______________________________________________________________
	//					 STRUTTURA DI BASE
	//______________________________________________________________

	typedef struct{
		int n_elementi;
		int u_dim;
		void *pointer;
		long int actual_dim;
	}List;

	//______________________________________________________________
	//					 FUNZIONI DI CREAZIONE
	//______________________________________________________________

	/*
	Questa funzione crea una lista vuota.

	DEBUG=OK
	*/
	List crea_lista(int dim_elemento);

	/*
	Questa funzione converte un array in una lista dinamica, se qualcosa non va
	ritorner� una lista vuota.

	DEBUG=OK
	*/
	List l_fromArray(void * array, int dim_elemento, int n_elementi);

	/*
	Questa funzione crea una lista da un solo elemento passato come parametro.
	Se qualcosa non va ritorner� una lista vuota.

	DEBUG= OK
	*/
	List l_fromElement(int dim_elemento, void *elemento);

	//______________________________________________________________
	//					 FUNZIONI DI MANIPOLAZIONE
	//______________________________________________________________

	/*
	Questa funzione inserisce l'elemento dato come parametro all'ultimo posto
	della lista.

	!!!! ATTENZIONE: !!!!!
		Non ci sono controlli sull'elemento, esso infatti � necessario che sia dello stesso tipo
		degli elementi che popolano la lista, affinche essa non venga corrotta.

		Genera:
		1   = operazione andata a buon fine;
		(-1)= ALLOCAZIONE NON RIUSCITA
		(-3)= SPOSTAMENTO DATI NON RIUSCITO

	 DEBUG=OK
	*/
	int l_append(List *lista, void *elemento );

	/*
	Questa funzione restituisce il primo elemento della lista rimuovendolo da essa.

	!!!! ATTENZIONE: !!!!
		l'esito v� sempre verificato poich� la funzione potrebbe produrre
		puntatori a null.

	DEBUG=OK
	*/
	void * l_pop(List *lista);

	/*
	Questa funzione clona la lista data come parametro e restituisce una lista clone

	DEBUG=OK
	*/
	List l_clone(List *lista);

	/*
	Questa funzione restituisce una lista composta da elementi comuni tra due liste,
	i doppioni vengono considerati una sola volta.
	Se qualcosa non v� la funzione la funzione restituisce una lista vuota.
	*/
	List l_matches(List *lista1, List *lista2);

	/*
	Questa funzione inserisce una lista all'interno di un' altra
	nella posizione specificata da startIndex.

	!!!!ATTENZIONE!!!!
		La verifica si limita al controllo delle dimensioni dell'elemento singolo,
		tuttavia due liste contenenti elementi di tipo diverso ma della stessa grandezza verranno
		comunque unite, causando comportamenti inaspettati.

	Genera:
	1   = se l'operazione è andata a buon fine
	(-1)= ALLOCAZIONE NON RIUSCITA
	(-2)= INDICE NON CORRETTO
	(-3)= SPOSTAMENTO DATI NON RIUSCITO
	(-4)= LISTE NON COMPATIBILI

	DEBUG=OK
	*/
	int l_insert(List *destinazione, List *da_inserire, int startIndex);

	/*
	Questa funzione rimuove l'elemento nell'indirizzo specificato.

	Genera:
	1   = se l'operazione è andata a buon fine
	(-1)= ALLOCAZIONE NON RIUSCITA
	(-2)= INDICE NON CORRETTO
	(-3)= SPOSTAMENTO DATI NON RIUSCITO

	DEBUG=OK
	*/
	int l_remove(int index, List *lista);

	/*
	Questa funzione rimuove dalla prima lista, gli elementi comuni con la seconda.

	!!!!ATTENZIONE!!!!
		La verifica si limita al controllo delle dimensioni dell'elemento singolo,
		tuttavia due liste contenenti elementi di tipo diverso ma della stessa grandezza verranno
		comunque sottratte, causando comportamenti inaspettati.

		Genera:
		1   = se l'operazione è andata a buon fine
		(-4)= LISTE NON COMPATIBILI

	DEBUG=OK
	*/
	int l_removeElements(List *lista, List *elementi_da_rimuovere);

	/*
	Questa funzione cambia il tipo di dati all'interno dell' array, modificando la dimensione delle unit� che devono
	essere inserite all'interno dell'array.

	Se l'array � pieno viene svuotato.
	*/
	int l_change_type(List *lista, int nuova_dim_elemento);

	/*
	Questa funzione dice se un elemento � presente o meno all'interno di una lista.

	!!!! ATTENZIONE: !!!!
		Non ci sono controlli sul tipo di elemento di cui si controlla la presenza,
		se i tipi delle variabili non sono le stesse potrebbero verificare dei falsi positivi.

	DEBUG=OK
	*/
	int is_in(List *lista, void *elemento);

	/*
	Questa funzione rimpiazza un dato nella lista con un elemento

	!!!! ATTENZIONE: !!!!
		Non ci sono controlli sul tipo di elemento che si inserisce.
		Se i tipi non sono gli stessi l'elemento sostituito si corromper�.

		Genera:
		1   = se l'operazione è andata a buon fine
		(-2)= INDICE NON CORRETTO
		(-3)= SPOSTAMENTO DATI NON RIUSCITO
		(-5)= DATO NULLO

	DEBUG=OK
	*/
	int l_replace(int index, void *elemento, List *lista);

	/*
	Questa funzione controlla gli elementi sulla lista, comparando il numero di byte dato come parametro successivamente
	all'offset per ogni elemento.

	!!!! ATTENZIONE: !!!!
		Non ci sono controlli sul tipo di elemento che si inserisce.
		Se i tipi non sono gli stessi potrebbero verificarsi comportamenti inaspettati.

		Genera:
		n   = l'indirizzo dell'elemento cercato.
		(-6)= ELEMENTO NON TROVATO

		DEBUG=OK
	*/
	int l_find(void *element, int element_size, List *l, int element_offset);

	/*
	Questa funzione lavora allo stesso modo della funzione precedente ma restituisce una lista di indici.

	Se non sono stati trovati elementi la lista sarà vuota.

	DEBUG=OK
	*/
	List l_findall(void *element, int element_size, List *l, int element_offset);

	/*
	Questa funzione restituisce il valore della lista all'indice passato come parametro

	!!!! ATTENZIONE: !!!!
		l'esito v� sempre verificato poich� la funzione potrebbe produrre
		puntatori a null.

	DEBUG=OK
	*/
	void * l_index(int index, List *lista);

	/*
	Questa funzione trasforma una lista in un array di caratteri ma solo se la dimensione dell'unita � di un byte.

	!!!! ATTENZIONE: !!!!
		l'esito v� sempre verificato poich� la funzione potrebbe produrre
		puntatori a null.

	DEBUG=OK
	*/
	char * l_tostring( List *lista);

	/*
	Questa funzione svuota la lista creata, libera la memoria allocata dal puntatore e azzerra il numero di elementi;
	*/
	void destroy(List *lista);
	//______________________________________________________________
	//						FUNZIONI INTERNE
	//______________________________________________________________


	/*
	Questa funzione permette di conoscere le dimensioni della struct comprendendo
	anche i dati referenziati dal pointer.

	DEBUG=0K
	*/
	void aggiorna_dim(List *);


	/*
	______

		ERROR CODES:
		(-1) ALLOCAZIONE NON RIUSCITA
		(-2) INDICE NON CORRETTO
		(-3) SPOSTAMENTO DATI NON RIUSCITO
		(-4) LISTE NON COMPATIBILI
		(-5) DATO NULLOù
		(-6) ELEMENTO NON TROVATO
	______
	*/

	//______________________________________________________________
	//						INIZIO CODICE
	//______________________________________________________________

#endif
