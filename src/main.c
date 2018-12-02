#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "census.h"

#define INPUT_LENGTH 80
#define COLUMNS_LENGTH 4

typedef struct {
    int activity;
    int home;
    char *department;// o char department[64]
    char *province;// o char province [64]
}Register;

char* getField(char *line, int num);

//reads line and returns Register
int recordLineFiles(char line[], char *newLine[], Register* aRegister);


int main()
{
    censusADT c;
    char line[INPUT_LENGTH];
    Register *aRegister = malloc(sizeof(aRegister));
    char * currentLine [COLUMNS_LENGTH];

    c = newCensus();

    FILE* stream = fopen("censo100.csv", "r");//cambiar argumento por lo que viene en cosola
    while (fgets(line, INPUT_LENGTH, stream))
    {
        char * tmp = strdup(line);
        recordLineFiles(tmp, currentLine, aRegister);
        processInputRecord(c, aRegister->home, aRegister->department, currentLine[3]);
        free(tmp);
    }
}

int recordLineFiles(char line[], char * newLine[], Register *aRegister){
    char * aux = malloc(strlen(line)+1);
    for (int i = 0; i < COLUMNS_LENGTH; i++) {
        strcpy(aux, line);
        newLine[i] = getField(aux, i+1);
    }
    char * currentDepartment = newLine[2];
    char * currentProvince = newLine[3];

    aRegister->department = currentDepartment;
    //aRegister->province = currentProvince; //SI DESCOMENTO ESTE TIRA SEG FAULT
    aRegister->activity = atoi(newLine[0]);
    aRegister->home = atoi(newLine[1]);

    //Con este pruebo que este leyendo bien
    //printf("%s, %s, %s, %s\n", newLine[0], newLine[1], newLine[2], newLine[3]);

    //free(currentDepartment);
    //free(currentProvince);
}

char* getField(char *line, int num){
    char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")){
        if (!--num)
            return tok;
    }
    return NULL;
}