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

void writeProvinceFile(censusADT c, FILE *provinceFile);

void writeDepartmentFile(censusADT c, FILE *departmentFile);

int main(){

    censusADT c;
    char line[INPUT_LENGTH];
    char *currentLine [COLUMNS_LENGTH];
    char *tmp;

    FILE* stream = fopen("censo100.csv", "r");//cambiar argumento por lo que viene en consola
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

    //print(c, countryFile);

    writeCountryFile(c, countryFile);
    writeProvinceFile(c, provinceFile);
//    writeDepartmentFile(c, departmentFile);w


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

void writeDepartmentFile(censusADT c, FILE *departmentFile) {
    //Metodo que busque la provincia a la que pertenece el dep y la devuelva
    //Metodo que me de el nombre y cant personas
}

void writeProvinceFile(censusADT c, FILE *provinceFile) {
    //Metodo que me deberia pasar de cada estructura provincia su nombre, cant personas y cant de hogares
    char provinceName [40];
    long inhabitantsPerProvince = 0;
    unsigned long homesPerProvince = 0;
    int iter = 0;
    while (provinceData(c, provinceName, &inhabitantsPerProvince, &homesPerProvince, iter)){
        fprintf(provinceFile, "%s, %lu, %lu\n", provinceName, inhabitantsPerProvince, homesPerProvince);
        strcpy(provinceName, "");
        inhabitantsPerProvince = 0;
        homesPerProvince = 0;
        iter++;
    }

}

int recordLineFiles(char line[], char *newLine[]){ //1 leak en tok
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