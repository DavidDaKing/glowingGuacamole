#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

extern int randomNumGen(int seed);

extern int createList();
extern int appendList(int randomNum);

extern void strings2List();
extern char *getPoetry(int s);
extern char *getFirstWord(char *line);



struct num_and_str {
    int number;
    char *poetry;
    struct num_and_str *next;
};

extern void sortLinkedNum();
extern void sortLinkedStr();
extern void insertNode(struct num_and_str *node);
extern void insertNode1(struct num_and_str *node);
extern int getNumber(char *word);

struct num_and_str *ns_list;

//adding pointer array
char *number_map[10] = {"One", "Two", "Three", "Four", "Five", 
                        "Six", "Seven", "Eight", "Nine", "Ten"};

int main(int argc, char* argv[]){
    int randNum;

    char filename[20];
    int len;

    FILE *fp;

    struct num_and_str *temp; 
    //temp = ns_list;

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
    strings2List();

    //sorts Linked list ascending based on number
    sortLinkedNum();
    sortLinkedStr();
    temp = ns_list;

    /*
    char *line = NULL;
    printf("Line: %s \n", line);
    */

    while(temp != NULL){
        printf("List Number: %d\n", temp->number);
        temp = temp->next;
    }
    

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

void strings2List(){
    struct num_and_str *tempNode;
    int i = 0;

    tempNode = ns_list;

    while(tempNode != NULL){
        tempNode->poetry = getPoetry(i);
        if(tempNode->poetry != NULL){printf("i = %d, %s\n", i, tempNode->poetry);}
        i++;
        tempNode = tempNode->next; 
    }
}

char *getPoetry(int num){
    FILE *fp;
    char *line[80];
    char *word, *poetryLine;

    if(num > 9){
        printf("Wrong arg num: %d\n", num);
        return NULL;
    }

    fp = fopen("ten_green_bottles.txt", "r");

    if (fp == NULL){
        printf("Cannot open file\n");
        return NULL;
    }
    while(fgets(line, 70, fp)){
        word = getFirstWord(line);
        if (word != NULL){
            if (strcmp(word, number_map[num]) == 0){
                poetryLine = (char *)malloc(strlen(line)+1);
                if(poetryLine == NULL){
                    printf("Cannot allocate space for line. %d\n", num);
                    fclose(fp);
                    return NULL;
                }
                strcpy(poetryLine, line);
                fclose(fp);
                return poetryLine;
            }
        }
    }
    fclose(fp);
    return NULL;
}

char *getFirstWord(char *line){
    static char word[10]; 
    int i = 0, j = 0;

    while ((line[i] != 0) && isspace(line[i]) ){
        i++;
    }
    if (line[i] == 0){return NULL;}
    while ((line[i] != 0) && isalpha(line[i])){
        word[j] = line[i];
        i++; j++;
    }

    word[j] = 0;
    return word;    
}

void sortLinkedNum(){
    struct num_and_str *curr, *prev, *temp;

    if (ns_list == NULL){return;}

    curr = prev = ns_list;

    while(curr != NULL){
        //already ascending order
        if(curr->number >= prev->number){
            prev = curr;
            curr = curr->next;
        }
        //not ascending order
        else{
            temp = curr;
            prev->next = curr->next;
            curr = curr->next;
            insertNode(temp);
        }
    }
}

void insertNode(struct num_and_str *node){
    struct num_and_str *iprev, *icurr;

    if(ns_list == NULL){return;}

    icurr = iprev = ns_list;

    while(icurr != NULL){
        if(node->number > icurr->number){
            iprev = icurr;
            icurr = icurr->next;
        }
        else{
            //temp must be inserted before curr
            //temp is <= than curr
            if (icurr == iprev){
                //icurr is at the head
                node->next = icurr;
                ns_list = node;
            }else{
                node->next = icurr;
                iprev->next = node;
            }
            return;
        }
    }
    // new node has to be inserted at the end
    node->next = NULL;
    iprev->next = node;
    return;
}


void sortLinkedStr(){
    struct num_and_str *curr, *prev, *temp;
    char *word;
    int currNumber, prevNumber;

    if (ns_list == NULL){return;}

    curr = prev = ns_list;

    while(curr != NULL){

        word = getFirstWord(curr->poetry);
        currNumber = getNumber(word);
        
        word = getFirstWord(prev->poetry);
        prevNumber = getNumber(word);

        //already descending order
        if(curr->number <= prev->number){
            prev = curr;
            curr = curr->next;
        }
        //not descending order
        else{
            temp = curr;
            prev->next = curr->next;
            curr = curr->next;
            insertNode1(temp);
        }
    }
}

void insertNode1(struct num_and_str *node){
    struct num_and_str *iprev, *icurr;
    char *word;
    int icurrNumber, iprevNumber, nodeNumber;

    if(ns_list == NULL){return;}

    icurr = iprev = ns_list;

    while(icurr != NULL){

        word = getFirstWord(icurr->poetry);
        icurrNumber = getNumber(word);
        
        word = getFirstWord(iprev->poetry);
        iprevNumber = getNumber(word);

        word = getFirstWord(node->poetry);
        nodeNumber = getNumber(word);

        if(node->number < icurr->number){
            iprev = icurr;
            icurr = icurr->next;
        }
        else{
            //temp must be inserted before curr
            //temp is <= than curr
            if (icurr == iprev){
                //icurr is at the head
                node->next = icurr;
                ns_list = node;
            }else{
                node->next = icurr;
                iprev->next = node;
            }
            return;
        }
    }
    // new node has to be inserted at the end
    node->next = NULL;
    iprev->next = node;
    return;
}

int getNumber(char *word){
    for(int i = 0; i < 10; i++){
        if(strcmp(word, number_map[i]) == 0){
            return i++;
        }
    }
    return 0;
}