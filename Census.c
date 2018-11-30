//
// Created by xXx_juanpisani_xXx on 11/29/2018 with am4 report.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Census.h"

struct department{
    char * name;
    long inhabitantsPerDepartment;
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


censusADT newCensusADT(void){
    return calloc(1, sizeof(struct CensusCDT));
}
