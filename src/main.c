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
        //processInputRecord(c, aRegister->home, aRegister->department, aRegister->province);
        free(tmp);
    }
}

int recordLineFiles(char line[], char * newLine[], Register *aRegister){
    char * aux = malloc(strlen(line)+1);
    for (int i = 0; i < COLUMNS_LENGTH; i++) {
        strcpy(aux, line);
        newLine[i] = getField(aux, i+1);
    }
    aRegister->department = malloc(sizeof(newLine[2])+1);
    //aRegister->province = malloc(strlen(newLine[3])+1); //SI DESCOMENTO ESTE TIRA SEG FAULT

    aRegister->activity = atoi(newLine[0]);
    aRegister->home = atoi(newLine[1]);
    //strcpy(aRegister->department, newLine[2]); SI DESCOMENTO ESTE TIRA SEG FAULT
    //strcpy(aRegister->province, newLine[3]); Lo mismo
}

char* getField(char *line, int num){
    char* tok;
    for (tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n")){
        if (!--num)
            return tok;
    }
    return NULL;
}
