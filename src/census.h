//
// Created by lauta on 11/29/2018.
//

#ifndef TPFINALAYED_CENSUS_H
#define TPFINALAYED_CENSUS_H

typedef struct censusCDT *censusADT;

censusADT newCensus(void);

void processInputRecord(censusADT c, int home, char *department, char *province);

#endif //TPFINALAYED_CENSUS_H
