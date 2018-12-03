#ifndef TPFINALAYED_CENSUS_H
#define TPFINALAYED_CENSUS_H

typedef struct censusCDT *censusADT;

censusADT newCensus(void);

void processInputRecord(censusADT c, int home, char *department, char *provinceName);

void freeCensus(censusADT c);

/*-------------------------------------------------------------------
 * Descripción: 	Cambia los valores por la informacion evaluada de habitantes totales, casas totales y
 *                  provincias totales leidas.
 */

void censusData(censusADT c, unsigned long *totalInhabitants, unsigned long *totalHomes, unsigned int *provinceSize);

/*-------------------------------------------------------------------
 * Descripción: En su primer llamado inicializa un Iterador apuntando al header de la lista de provincias y sino
 *              se cambia el puntero al que apunta iterador por el siguiente en la lista.
 *              Cambia los valores correspondientes del nombre de provincia, habitantes por
 *              provincia y hogares por provincia segun la provincia en la que este apuntando. *
 * -------------------------------------------------------------------
 * Precondicion:	Un i = 0 para su primer llamado
 * Retorna: 0 en caso de que el Iterador sea null y 1 en caso de haber pasado los datos correctamente.
 */

int provinceData(censusADT c, char *provinceName, long *inXprovince, unsigned long *hXprovince, int i);

/*-------------------------------------------------------------------
 * Descripción: En su primer llamado inicializa un Iterador apuntando al header de la lista de departamentos
 *              dentro de una provincia y sino se cambia el puntero del iterador por el siguiente
 *              en la lista.
 *              Cambia los valores correspondientes del nombre de departamento y habitantes por
 *              departamentos segun el departamento al que este apuntando.
 * -------------------------------------------------------------------
 * Precondicion: Un i = 0 para su primer llamado
 * Retorna: 0 en caso de que el Iterador sea null y 1 en caso de haber pasado los datos correctamente.
 */

int departmentData(censusADT c, char deptName[40], unsigned long *inXdept, int i);

#endif //TPFINALAYED_CENSUS_H
