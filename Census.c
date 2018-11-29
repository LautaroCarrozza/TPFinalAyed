//
// Created by lauta on 11/29/2018.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Census.h"

struct CensusCDT {
    //todo
};

censusADT newCensusADT(void){
    return calloc(1, sizeof(struct CensusCDT));
}


