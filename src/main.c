#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "census.h"

#define INPUT_LENGTH 80
#define COLUMNS_LENGTH 4

#define COUNTRY_PATH "country.csv"
#define PROVINCE_PATH "province.csv"
#define DEPARTMENT_PATH "department.csv"

char* getField(char *line, int num);

//reads line and returns Register
int recordLineFiles(char line[], char *[]);

void writeCountryFile(censusADT c, FILE * countryFile);

void writeProvinceAndDeptFile(censusADT c, FILE *provinceFile, FILE *departmentFile);

int main(int argc, char*argv[]){

    censusADT c;
    char line[INPUT_LENGTH];
    char *currentLine [COLUMNS_LENGTH];
    char *tmp;

    FILE* stream;

    if(argc > 1){
        stream = fopen(argv[1], "r");
    } else {
        stream = fopen("censo100.csv", "r");
    }

    FILE* countryFile = fopen(COUNTRY_PATH, "w");
    FILE* provinceFile = fopen(PROVINCE_PATH, "w");
    FILE* departmentFile = fopen(DEPARTMENT_PATH, "w");

    c = newCensus();

    while (fgets(line, INPUT_LENGTH, stream)){
        tmp = strdup(line);
        recordLineFiles(tmp, currentLine);
        processInputRecord(c, atoi(currentLine[1]), currentLine[2], currentLine[3]);
        free(tmp);
    }

    writeCountryFile(c, countryFile);
    writeProvinceAndDeptFile(c, provinceFile, departmentFile);


    fclose(stream);
    fclose(countryFile);
    fclose(provinceFile);
    fclose(departmentFile);

    freeCensus(c);
    return 0;
}

void writeCountryFile(censusADT c, FILE * countryFile){
    unsigned long totalInhabitants = 0;
    unsigned long totalHomes = 0;
    unsigned int provinceSize = 0;

    censusData(c, &totalInhabitants, &totalHomes, &provinceSize);
    fprintf(countryFile, "%lu, %lu, %.d", totalInhabitants, totalHomes, provinceSize);
}

void writeProvinceAndDeptFile(censusADT c, FILE *provinceFile, FILE *departmentFile) {
    char provinceName [64];
    char deptName [64];
    long inhabitantsPerProvince = 0;
    unsigned long homesPerProvince = 0;
    unsigned long inhabitantsPerDepartment = 0;

    int iter = 0;
    int iter2 = 0;
    while (provinceData(c, provinceName, &inhabitantsPerProvince, &homesPerProvince, iter)) {
        fprintf(provinceFile, "%s, %lu, %lu\n", provinceName, inhabitantsPerProvince, homesPerProvince);
        while (departmentData(c, deptName, &inhabitantsPerDepartment, iter2)){
            fprintf(departmentFile, "%s, %s, %lu\n", provinceName, deptName, inhabitantsPerDepartment);
            iter2++;
        }
        iter2 = 0;
        iter++;
    }

}

int recordLineFiles(char line[], char *newLine[]){
    char * aux = malloc(strlen(line)+1);
    for (int i = 0; i < COLUMNS_LENGTH; i++) {
        strcpy(aux, line);
        newLine[i] = getField(aux, i+1);
    }
    return 0;
}

char* getField(char *line, int num){
    char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")){
        if (!--num)
            return tok;
    }
    return NULL;
}