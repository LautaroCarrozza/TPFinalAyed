#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "census.h"

//Holds a pointer to the next home, making a NULL terminated and ordered from highest to lowest list. Code is the code for each home.
struct home{
    int code;
    struct home* next;
};

//Holds a pointer to the next department, making a NULL terminated and alphabetically ordered list and a pointer to its corresponding list of homes.
struct department{
    char * name;
    unsigned long inhabitantsPerDepartment;
    struct department* next;
    struct home * homes;
};

/*
 * Holds a pointer to the next province, making  NULL terminated and alphabetically ordered list, a pointer to its corresponding list of departments
 * and an iterative pointer to that list, that will be used by the data functions.
 */
struct province{
    char * name;
    long inhabitantPerProvince;
    unsigned long homesPerProvince;
    struct province* next;
    struct department* departmentList;
    struct department * deptIterator;
};

/*
 * Holds a pointer to the list of provinces and an iterative pointer.
 * Inhabitants is the total quantity of inhabitants, provinceSize is the total quantity of provinces and totalHomes the total quantity of homes.
 */
struct censusCDT {
    unsigned long inhabitants;
    unsigned int provinceSize;
    unsigned long totalHomes;
    struct province * provinceList;
    struct province * provIterator;
};


//Declarations (all non-static functions used by the main function are declared in census.h).

//Adds a province to the list of provinces recursively. Will call the addDepartmentRec when a department needs to be added.
static struct province* addProvinceRec(censusADT c, struct province *pProvince, char *province, char* department, int homeCode);

//Adds a department to the list of departments of each province recursively. Will call the addHome (and addHomeRec) when a home needs to be added.
static struct department* addDepartmentRec(censusADT c, struct department * pDepartment, char * department, int homeCode, int* addedHomeFlag);

//Returns 1 or 0 based on whether a home was added or not.
static int addHome(censusADT c, struct department* department, int homeCode);

//Will add a home recursively to the list of homes and sets the flag to 1 or 0 if a home was added or not.
static struct home* addHomeRec(censusADT c, struct home* pHome, int homeCode, int* flag);

//Each function frees recursively its corresponding structure. They are called by freeCensus in the main function.

static void freeDeptRec(struct department * pDepartment);

static void freeHomeRec(struct home* pHome);

static void freeProvRec(struct province * pProvince);


//Implementations

//Creation of the census ADT (pointer to the census CDT structure).

censusADT newCensus(void){
    censusADT c = malloc(sizeof(*c));

    c->inhabitants = 0;
    c->provinceSize = 0;
    c->totalHomes = 0;
    c->provinceList = NULL;
    c->provIterator = NULL;

    return c;
}

//Process each line of data and calls addProvinceRec to start storing the data in the corresponding structures.

void processInputRecord(censusADT c, int homeCode, char *department, char *province) {
    c->provinceList = addProvinceRec(c, c->provinceList, province, department, homeCode);
    c->inhabitants++;
}

static struct province* addProvinceRec(censusADT c, struct province *pProvince, char *province, char* department, int homeCode){
    int flag = 0;
    if(pProvince == NULL || (strcmp(pProvince->name, province) > 0)){
        struct province* aux = malloc(sizeof(*aux));

        aux->name = province;
        aux->inhabitantPerProvince = 1;
        aux->homesPerProvince = 1;
        aux->next = pProvince;
        aux->departmentList = NULL;

        aux->departmentList = addDepartmentRec(c, aux->departmentList, department, homeCode, &flag);
        aux->deptIterator = NULL;

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
    int flag = 0;
    department->homes = addHomeRec(c, department->homes, homeCode, &flag);
    return flag;
}

static struct home* addHomeRec(censusADT c, struct home* pHome, int homeCode, int* flag){
    if(pHome == NULL || (pHome->code > homeCode)){
        struct home* aux = malloc(sizeof(*aux));
        aux->code = homeCode;
        aux->next = pHome;
        *flag = 1;
        return aux;
    }
    if(pHome->code == homeCode){
        *flag = 0;
        return pHome;
    }
    pHome->next = addHomeRec(c, pHome->next, homeCode, flag);
    return pHome;
}

//Frees the census from the main function calling the recursive frees for each structure.

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
    free(pProvince);
}

static void freeDeptRec(struct department * pDepartment){
    if (pDepartment == NULL)
        return;
    freeDeptRec(pDepartment->next);
    freeHomeRec(pDepartment->homes);
    free(pDepartment);
}

static void freeHomeRec(struct home* pHome){
    if(pHome == NULL){
        return;
    }
    freeHomeRec(pHome->next);
    free(pHome);
}

void censusData(censusADT c, unsigned long *totalInhabitants, unsigned long *totalHomes, unsigned int *provinceSize){
    *totalInhabitants = c->inhabitants;
    *totalHomes = c->totalHomes;
    *provinceSize = c->provinceSize;
}

int provinceData(censusADT c, char *provinceName, long *inXprovince, unsigned long *hXprovince, int i) {
    if(i == 0) {
        c->provIterator = c->provinceList;
    }
    else{
        c->provIterator = c->provIterator->next;
    }

    if(c->provIterator == NULL){
        c->provIterator = c->provinceList;
        c->provIterator->deptIterator = NULL;
        return 0;
    }

    strcpy(provinceName, c->provIterator->name);
    *inXprovince = c->provIterator->inhabitantPerProvince;
    *hXprovince = c->provIterator->homesPerProvince;
    return 1;
}

int departmentData(censusADT c, char deptName[40], unsigned long *inXdept, int i) {
    if(i == 0){
        c->provIterator->deptIterator = c->provIterator->departmentList;
    }
    if (c->provIterator->deptIterator == NULL){
        return 0;
    }

    strcpy(deptName, c->provIterator->deptIterator->name);
    *inXdept = c->provIterator->deptIterator->inhabitantsPerDepartment;
    c->provIterator->deptIterator = c->provIterator->deptIterator->next;
    return 1;
}