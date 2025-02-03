/*

linkedlist.c 
David Bower

credit: https://www.youtube.com/watch?v=KEV5OuQzgtc

*/

#include "linkedlist.h"

struct Node_int *create_node_int(int data);

void destroy_node_int(struct Node_int *node_to_destroy);

struct Node_int *iterate_int(int index, struct LinkedList_int *curr);



void insert_node_int(int index, int data, struct LinkedList_int *curr);
void remove_node_int(int index, struct LinkedList_int *curr);
int retrieve_data_int(int index, struct LinkedList_int *curr);


struct LinkedList_int linked_list_constructor(){
    struct LinkedList_int new_list;
    new_list.m_head = NULL;
    new_list.m_len = 0;

    // This allows me to change the name of a function

    new_list.insert = insert_node_int;
    new_list.remove = remove_node_int;
    new_list.retrieve = retrieve_data_int;

    //new_list.constructor = linked_list_constructor;


    return new_list;

}



struct Node_int *create_node_int(int data){

    struct Node_int *new_node_address = (struct Node_int *)malloc(sizeof(struct Node_int));
    struct Node_int new_node_instance;

    new_node_instance.m_data = data;
    new_node_instance.m_next = NULL;

    // this variable will hold the address points to instance
    *new_node_address = new_node_instance;

    return new_node_address;
}

void destroy_node_int(struct Node_int *node_to_destroy){
    free(node_to_destroy);
}

struct Node_int *iterate_int(int index, struct LinkedList_int *curr){
    //base case
    //edge case
    //normal case

    if(index < 0 || index >= curr->m_len){
        printf("Index out of bounds: %d How many elements: %d \n", index, curr->m_len);
        exit(0);
    }

    struct Node_int *temp = curr->m_head;

    for(int i = 0; i < index; i++){
        printf("Value at element: %d is: %d\n", i, temp->m_data);
        temp = temp->m_next;
    }

    return temp;

}

void insert_node_int(int index, int data, struct LinkedList_int *curr){
    struct Node_int *node_to_insert = create_node_int(data);
    // no nodes
    // more than zero nodes
    if (index == 0){
        node_to_insert = create_node_int(data);
        curr->m_head = node_to_insert;
    }else{
        struct Node_int *temp = iterate_int(index - 1, curr);
        node_to_insert->m_next = temp->m_next;
        temp->m_next = node_to_insert;
    }
    //increment length
    curr->m_len += 1;
}

void remove_node_int(int index, struct LinkedList_int *curr){

    //similar to insert
    if (index == 0){
        struct Node_int *node_to_remove = curr->m_head;
        curr->m_head = node_to_remove->m_next;
        destroy_node_int(node_to_remove);
    }
    else{

        struct Node_int *temp = iterate_int(index-1, curr);

        /*
            Temp stops at the index before the selected index. So the node to remove will be
            to the next of temp. Dummy will be the name for it.  
        */
        struct Node_int *dummy = temp->m_next;

        //then set the next of next to temp->next
        temp->m_next = dummy->m_next;

        // then delete
        destroy_node_int(dummy);
    }
    //decrement length
    curr->m_len -= 1;

}

int retrieve_data_int(int index, struct LinkedList_int *curr){
    if(index < 0 || index > curr->m_len){
        printf("Index is out of bounds \n");
        exit(0);
    }
    else{
        struct Node_int *temp = iterate_int(index-1, curr);
        printf("Data retrieved: %d \n", temp->m_data);
        return temp->m_data;
    }
}


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