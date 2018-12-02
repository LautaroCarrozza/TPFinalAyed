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
    struct home * homes;
};

struct province{
    char * name;
    long inhabitantPerProvince;
    unsigned long homesPerProvince;
    struct province* next;
    struct department * deptIterator;
    struct department* departmentList;
};

struct censusCDT {
   unsigned long inhabitants;
   unsigned int provinceSize;
   unsigned long totalHomes;
   struct province * provinceList;
   struct province * provIterator;
};

//adds
static struct province* addProvinceRec(censusADT c, struct province *pProvince, char *province, char* department, int homeCode);

static struct department* addDepartmentRec(censusADT c, struct department * pDepartment, char * department, int homeCode, int* addedHomeFlag);

static int addHome(censusADT c, struct department* department, int homeCode);

static struct home* addHomeRec(censusADT c, struct home* pHome, int homeCode, int* flag);

//frees

static void freeProvRec(struct province * pProvince);

static void freeDeptRec(struct department * pDepartment);

static void freeHomeRec(struct home* pHome);

censusADT newCensus(void){
    censusADT c = malloc(sizeof(*c));

    c->inhabitants = 0;
    c->provinceSize = 0;
    c->totalHomes = 0;
    c->provinceList = NULL;
    c->provIterator = NULL;

    return c;
}

void processInputRecord(censusADT c, int homeCode, char *department, char *province) {
c->inhabitants++;
c->provinceList = addProvinceRec(c, c->provinceList, province, department, homeCode);
}

static struct province* addProvinceRec(censusADT c, struct province *pProvince, char *province, char* department, int homeCode){
    int flag;
    if(pProvince == NULL || (strcmp(pProvince->name, province) > 0)){ //agrego si apunto a null o si es mayor a la que estoy parado
        struct province* aux = malloc(sizeof(*aux));
        aux->name = province;
        aux->inhabitantPerProvince = 1; //si creo creo almenos con 1 por la linea que recibo
        aux->homesPerProvince = 1; //same
        aux->next = pProvince;
        aux->departmentList = NULL;

        aux->departmentList = addDepartmentRec(c ,aux->departmentList, department, homeCode, &flag);
        aux->deptIterator = aux->departmentList;

        c->provinceSize++;
        c->totalHomes++;
        return aux;
    }

    if(strcmp(pProvince->name, province) == 0){
        pProvince->departmentList = addDepartmentRec(c, pProvince->departmentList, department, homeCode, &flag);
        if(flag){
            pProvince->homesPerProvince++;
            c->totalHomes++;
        }
        pProvince->inhabitantPerProvince++;
        return pProvince;
    }
    pProvince->next = addProvinceRec(c, pProvince->next, province, department, homeCode);
    return pProvince;
}

static struct department* addDepartmentRec(censusADT c, struct department* pDepartment, char* department, int homeCode, int* flag){
    if(pDepartment == NULL || (strcmp(pDepartment->name, department)) > 0){
        struct department* aux = malloc(sizeof(*aux));
        aux->name = department;
        aux->inhabitantsPerDepartment = 1;
        aux->next = pDepartment;
        aux->homes = NULL;

        *flag = addHome(c, aux, homeCode);
        return aux;
    }
    if(strcmp(pDepartment->name, department) == 0) {
        *flag = addHome(c, pDepartment, homeCode);
        pDepartment->inhabitantsPerDepartment++;
        return pDepartment;
    }
    pDepartment->next = addDepartmentRec(c, pDepartment->next, department, homeCode, flag);
    return pDepartment;
}

static int addHome(censusADT c, struct department* department, int homeCode){
    int flag;
    department->homes = addHomeRec(c, department->homes, homeCode, &flag);
    return flag;
}

static struct home* addHomeRec(censusADT c, struct home* pHome, int homeCode, int* flag){
    if(pHome == NULL || ((pHome->code - homeCode) > 0)){
        struct home * aux = malloc(sizeof(*aux));
        aux->code = homeCode;
        aux->next = pHome;
        *flag = 1;
        return aux;
    }
    if(pHome->code - homeCode == 0){
        *flag = 0;
        return pHome;
    }
    pHome->next = addHomeRec(c, pHome->next, homeCode, flag);
    return pHome;
}

void freeCensus(censusADT c){
    freeProvRec(c->provinceList);
    free(c);
}

static void freeProvRec(struct province * pProvince){
    if(pProvince == NULL) {
        return;
    }
    freeProvRec(pProvince->next);
    freeDeptRec(pProvince->departmentList);
    free(pProvince->name);//PUEDE SER IRRELEVANTE ndeaaaaaaaaaaaa
    free(pProvince);
}

static void freeDeptRec(struct department * pDepartment){
    if (pDepartment == NULL)
        return;
    freeDeptRec(pDepartment->next);
    freeHomeRec(pDepartment->homes);
    free(pDepartment->name);
    free(pDepartment);
}

static void freeHomeRec(struct home* pHome){
    if(pHome == NULL){
        return;
    }
    freeHomeRec(pHome->next);
    free(pHome);
}