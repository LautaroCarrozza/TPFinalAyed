#ifndef TPFINALAYED_CENSUS_H
#define TPFINALAYED_CENSUS_H

typedef struct censusCDT *censusADT;

censusADT newCensus(void);

void processInputRecord(censusADT c, int home, char *department, char *provinceName);

void freeCensus(censusADT c);

void censusData(censusADT c, unsigned long *totalInhabitants, unsigned long *totalHomes, unsigned int *provinceSize);

int provinceData(censusADT c, char *provinceName, long *inXprovince, unsigned long *hXprovince, int i);

int departmentData(censusADT c, char deptName[40], unsigned long *inXdept, int i);

#endif //TPFINALAYED_CENSUS_H
