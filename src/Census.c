//
// Created by lauta on 11/29/2018 with am4 report.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Census.h"

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

censusADT newCensus(void){
    censusADT c = malloc(sizeof(*c));

    c->inhabitants = 0;
    c->provinceList = NULL;
    c->iterator = NULL;

    return c;
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
int processProvince(censusADT c, int home, char *province) {

    struct province * aux = malloc(sizeof(*aux));
    aux = c->provinceList;

    return 0;
}
int processDepartment(censusADT c, int home, char *department, char *province) { return 0;}


int writeFiles(){ return 0;}
