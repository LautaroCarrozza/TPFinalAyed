//
// Created by lauta on 11/29/2018.
//

#ifndef TPFINALAYED_CENSUS_H
#define TPFINALAYED_CENSUS_H

typedef struct censusCDT *censusADT;

censusADT newCensus(void);

int processInputRecord(censusADT c, int home, char *department, char *province);

int processCountry(censusADT c, int home, char * province);
int processProvince(censusADT c, int home, char *province);
int processDepartment(censusADT c, int home, char *department, char *province);
int writeFiles();

#endif //TPFINALAYED_CENSUS_H
