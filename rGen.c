#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int randomNumGen(int seed);

int main(int argc, char* argv[]){
    int randNum;

    char filename[20];

    //not very safe
    strcpy(filename, "file_"); 
    printf("Filename is: %s\n", filename);


    

    for(int i = 0; i < 10; i++){
        randNum = randomNumGen(i);
        printf("seed = %d rand = %d\n", i, randNum);
    }
    return 0;
}

int randomNumGen(int seed){
    //assign a random number through seed
    int randomNum = seed * 999111222 + 12345;

    return (unsigned int) (randomNum / 65535) % 3267;
}