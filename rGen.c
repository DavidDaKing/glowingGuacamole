#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int randomNumGen(int seed);

extern int createList();
extern int appendList(int randomNum);

struct num_and_str {
    int number;
    char *poetry;
    struct num_and_str *next;
};

struct num_and_str *ns_list;

int main(int argc, char* argv[]){
    int randNum;

    char filename[20];
    int len;

    FILE *fp;

    //always initilize linked list as null 
    ns_list = NULL;

    for(int i = 0; i < 10; i++){
        randNum = randomNumGen(i);

        //not very safe
        strcpy(filename, "file_");
        len = strlen(filename);
        filename[len] = '0' + i;
        filename[len+1] = '\0';
        //appends to the end of the string. 
        strcat(filename, ".txt");

        fp = fopen(filename, "w");
        if(fp == NULL){
            printf("File does not exist: %s\n", filename);
            return 1;
        }
        fprintf(fp, "%d\n", randNum);
        fclose(fp);
    }
    //new func for link list creation
    createList();

    return 0;
}

int randomNumGen(int seed){
    //assign a random number through seed
    int randomNum = seed * 999111222 + 12345;

    return (unsigned int) (randomNum / 65535) % 3267;
}


int createList(){
    FILE *fp;
    int randNum, len;
    char filename[20];
    struct num_and_str *tempNode;

    for(int i = 0; i < 10; i++){
        //not very safe
        strcpy(filename, "file_");
        len = strlen(filename);
        filename[len] = '0' + i;
        filename[len+1] = '\0';
        //appends to the end of the string. 
        strcat(filename, ".txt");

        fp = fopen(filename, "r");
        if(fp == NULL){
            printf("File does not exist: %s\n", filename);
            return 1;
        }
        fscanf(fp, "%d", &randNum);

        printf("filename = %s number = %d\n", filename, randNum);

        appendList(randNum);

        fclose(fp);
    }
    tempNode = ns_list;

    while(tempNode != NULL){
        printf("number of element = %d\n", tempNode->number);
        tempNode = tempNode->next; 
    }
    return 0;
}

int appendList(int randNum){
    struct num_and_str *newNode, *tempNode;
    newNode = (struct num_and_str *)malloc(sizeof(struct num_and_str));

    if (newNode == NULL){
        printf("Error allocating memory: %d\n", randNum);
        return 1;
    }

    newNode->number = randNum;
    newNode->poetry = NULL;
    newNode->next = NULL;

    //the list is empty
    if (ns_list == NULL){
        ns_list = newNode;
        return 0;
    }
    //list is not empty
    //traverse to the end of the list
    else{
        tempNode = ns_list;
        while(tempNode->next != NULL){
            tempNode = tempNode->next; 
        }
        // tempNode is the last element in the list
        tempNode->next = newNode;
    }   
    return 0;
}