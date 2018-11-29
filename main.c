#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Census.h"

#define INPUT_LENGTH 80
#define NO_DATA 0
#define OCUPPIED 1
#define UNOCUPPIED 2
#define ECONIMCALYINACTIVE 3

typedef struct {
    int activity;
    int home;
    char department[];
    char Province[];
}Register;

//reads line and returns Register
int recordLineFiles(char line[INPUT_LENGTH], Register* aRegister);

//calls process country - province - department
int processInputRecord();

int processCountry();
int processProvince();
int processDepartment();
int writeFiles();

int main(int argc, char * argv[])
{
    char line[INPUT_LENGTH];
    Register *aRegister;

    FILE* stream = fopen("censo100.csv", "r");//cambiar argumento por lo que viene en cosola
    while (fgets(line, INPUT_LENGTH, stream))
    {
        recordLineFiles(line, aRegister);

    }

}

int recordLineFiles(char line[INPUT_LENGTH], Register* aRegister){

}