//
// Created by lauta on 11/29/2018 with am4 report.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Census.h"

#define NO_DATA 0
#define OCUPPIED 1
#define UNOCUPPIED 2
#define ECONIMCALYINACTIVE 3


struct department{
    char * name;
    long habitantsPerDepartment;
    struct department* next;
};

struct province{
    char * name;
    long inhabitantsPerProvince;
//    struct deptCDT * firstDepartment;
//    struct deptCDT * iterative;
    struct province* next;
};

struct CensusCDT {
   long occupiedInhabitants, unoccupiedInhabitants, totalInhabitants;
   int occupiedStatus, unoccupiedStatus, noData, notActive;
   struct province* firstProvince;
//   struct province* iterative;
};

censusADT newCensus(void){
    return calloc(1, sizeof(struct CensusCDT));
}

//calls process country - province - department
int processInputRecord(int activity, int home, char *department, char *province) {
    return 0;
}

int processCountry(){ return 0;}
int processProvince(){ return 0;}
int processDepartment(){ return 0;}
int writeFiles(){ return 0;}
