//
// Created by lauta on 11/29/2018.
//

#ifndef TPFINALAYED_CENSUS_H
#define TPFINALAYED_CENSUS_H

typedef struct censusCDT *censusADT;

censusADT newCensus(void);

int processInputRecord(int i, int i1, char *string, char *string1);

int processCountry();
int processProvince();
int processDepartment();
int writeFiles();

#endif //TPFINALAYED_CENSUS_H
