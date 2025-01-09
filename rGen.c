#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int randomNumGen(int seed);

int main(int argc, char* argv[]){
    int randNum;

    char filename[20];
    int len;

    FILE *fp;

    for(int i = 0; i < 10; i++){
        randNum = randomNumGen(i);
        printf("seed = %d rand = %d\n", i, randNum);

        //not very safe
        strcpy(filename, "file_");
        len = strlen(filename);
        filename[len] = '0' + i;
        filename[len+1] = '\0';
        //appends to the end of the string. 
        strcat(filename, ".txt");
        printf("Filename is: %s\n", filename);

        fp = fopen(filename, "w");
        if(fp == NULL){
            printf("File does not exist: %s\n", filename);
            return 1;
        }
        fprintf(fp, "%d\n", randNum);
        fclose(fp);

    }
    return 0;
}

int randomNumGen(int seed){
    //assign a random number through seed
    int randomNum = seed * 999111222 + 12345;

    return (unsigned int) (randomNum / 65535) % 3267;
}