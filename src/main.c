#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Census.h"

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


int main(int argc, char * argv[])
{
    censusADT c = newCensus();

    char line[INPUT_LENGTH];
    Register *aRegister = malloc(sizeof(aRegister));
    char * currentLine [COLUMNS_LENGTH];

    FILE* stream = fopen("censo100.csv", "r");//cambiar argumento por lo que viene en cosola
    while (fgets(line, INPUT_LENGTH, stream))
    {

        char * tmp = strdup(line);
        recordLineFiles(tmp, currentLine, aRegister);
        processInputRecord(aRegister->activity, aRegister->home, aRegister->department, aRegister->province);

        free(tmp);
        free(aRegister);
        //free(currentLine);
    }

}

int recordLineFiles(char line[], char * newLine[], Register *aRegister){
    for (int i = 0; i < COLUMNS_LENGTH; ++i) {
        newLine[i] = getField(line, i + 1);
    }
    aRegister->activity = atoi(newLine[0]);
    aRegister->home = atoi(newLine[1]);
    strcpy(aRegister->department, newLine[2]);
    strcpy(aRegister->province, newLine[3]);
}

char* getField(char *line, int num){
    char* tok;
    for (tok = strtok(line, ";");
         tok && *tok;
         tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}
