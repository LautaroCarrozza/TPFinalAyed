//
// Created by lauta on 11/29/2018 with am4 report.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "census.h"

struct home{
    int code;
    struct home* next;
};

struct department{
    char * name;
    unsigned long inhabitantsPerDepartment;
    struct department* next;
};

struct province{
    char * name;
    long inhabitantPerProvince;
    unsigned long homesPerProvince;
    struct home * homes;
    struct province* next;
    struct province * iterator;
};

struct censusCDT {
   unsigned long inhabitants;
   unsigned int provinceSize;
   unsigned long totalHomes;
   struct province * provinceList;
   struct province * iterator;
};

struct province *getProvince(censusADT c, char *province);

int addProvince(censusADT c, char *province);

int addHome(censusADT c, int home);

censusADT newCensus(void){
    censusADT c = malloc(sizeof(*c));

    c->inhabitants = 0;
    c->provinceList = NULL;
    c->iterator = NULL;

    return c;
}

struct province *getProvince(censusADT c, char *province) {
    return NULL;
}

//calls process country - province - department
int processInputRecord(censusADT c, int home, char *department, char *province) {
    processCountry(c, home, province);
    processProvince(c, home, province);
    processDepartment(c, home, department, province);
    return 0;
}

int processCountry(censusADT c, int home, char * province){
    c->inhabitants ++;
    if(addProvince(c, province)){
        c->provinceSize ++;
    }
    if(addHome(c, home)){
        c->totalHomes++;
    }
    return 0;
}

static struct province *insertRec(struct province *pProvince, char *province, int *pInt) {
    int c;
    if( pProvince == NULL || (c=strcmp(pProvince-> name, province)) > 0 ){
        struct province * aux = malloc(sizeof(*aux));
        aux->next= pProvince;
        aux->name = province;
        *pInt = 1;
        return aux;
    }

    if( c < 0 )
        pProvince->next = insertRec( pProvince->next, province, pInt);
    return pProvince;
}

int addHome(censusADT c, int home) {
    return 0; // todo
}

int addProvince(censusADT c, char *province) {
    int added = 0 ;
    c->provinceList = insertRec(c->provinceList, province, &added);
    if (added)
        c->provinceSize++;
    return added;
}

int processProvince(censusADT c, int home, char *province) {

    struct province * aux;
    aux = getProvince(c, province);

    if (aux == NULL)
        return 1;
    aux->inhabitantPerProvince ++;

    return 0;
}
int processDepartment(censusADT c, int home, char *department, char *province) { return 0;}


int writeFiles(){
    return 0;//t
}
