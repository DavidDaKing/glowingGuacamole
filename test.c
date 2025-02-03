/*
    test.c

    David Bower

*/


#include <stdio.h>
#include "dataStruc/linkedlist.h"


int main(){
    struct LinkedList_int hiList = linked_list_constructor();

    for(int i = 0; i < 21; i++){
        //pass by reference
        hiList.insert(i, i, &hiList);
    }

    hiList.remove(3, &hiList);
    hiList.remove(7, &hiList);
    hiList.remove(99, &hiList);

    for(int i = 0; i < hiList.m_len; i++){
        printf("(index, val) : (%d, %d)", i, hiList.retrieve(i, &hiList));
    }


    hiList.retrieve(100, &hiList);

    return 0;
}