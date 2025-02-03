/*
    linkedlist.h

    for linkedlist.c

    David Bower
*/

#ifndef linkedlist_h
#define linkedlist_h

#include <stdlib.h>
#include <stdio.h>

#include "Node.h"



struct LinkedList_int{
    struct Node_int *m_head;
    int m_len;


    //These functions are the only functions I want the user to have access to.. 
    void (*insert)(int index, int data, struct LinkedList_int *curr);
    void (*remove)(int index, struct LinkedList_int *curr);
    int (*retrieve)(int index, struct LinkedList_int *curr);



    

};

//struct Node_int *iterate(int index, struct LinkedList_int *curr);

// I should  be able to rename these function names itself
// I dont want users calling these functions 
/*
void insert_node_int(int index, int data, struct LinkedList_int *curr);
void remove_node_int(int index, struct LinedList_int *curr);
int retrieve_data_int(int index, struct LinkedList_int *curr);


*/


// Constructors do not exist in C 
//translation of constructors in C

struct LinkedList_int linked_list_constructor();



#endif /*linkedlist*/