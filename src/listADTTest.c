#include <assert.h>
#include <stdio.h>
#include "listADT.h"

int doble(int n) {
	return 2 * n;
}

/* Programa para probar las funciones de la lista de enteros ordenada 
** sin repeticiones
**/

int
main(void)
{
	listADT myList;

	myList = newList();

	/* La lista creada debe estar vacía */
	assert(listIsEmpty(myList));
	assert(elementBelongs(myList, 5) == 0);

	/* Retorna 0 si no pudo borrar */
	assert(delete(myList,5) == 0);

	/* Insertamos un elemento */
	assert(insert(myList, 5));
	assert(elementBelongs(myList, 1) == 0);
	assert(elementBelongs(myList, 5));
	assert(listIsEmpty(myList) == 0);
	toBegin(myList);
	assert(hasNext(myList));
	assert(next(myList) == 5);
	assert(hasNext(myList)==0);

	/* No debe insertar repetidos */
	assert(insert(myList, 5)==0);
	assert(elementBelongs(myList, 5));
	assert(listIsEmpty(myList) == 0);
	assert(listSize(myList) == 1);

	/* Borrar un único elemento deja la lista vacía */
	assert(delete(myList, 5));
	assert(elementBelongs(myList, 5) == 0);
	assert(listIsEmpty(myList));

	/* Debe insertar en forma ordenada */
	insert(myList, 5);
	insert(myList, 1);
	insert(myList, 2);

	toBegin(myList);
	assert(next(myList)==1);
	assert(next(myList)==2);
	assert(next(myList)==5);
	assert(hasNext(myList) == 0);

	/* probamos map e inject */
	inject(myList, doble);
	toBegin(myList);
	assert(next(myList)==2);
	assert(next(myList)==4);
	assert(next(myList)==10);
	assert(hasNext(myList) == 0);


	listADT cuad = map(myList, doble);
	toBegin(myList);
	assert(next(myList)==2);
	assert(next(myList)==4);
	assert(next(myList)==10);
	assert(hasNext(myList) == 0);

	toBegin(cuad);
	assert(next(cuad)==4);
	assert(next(cuad)==8);
	assert(next(cuad)==20);
	assert(hasNext(myList) == 0);

	freeList(myList);

	printf("Verificado exitosamente\n");

	return 0;
	
}
