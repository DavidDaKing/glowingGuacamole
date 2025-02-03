/*
Node.h for Node.c

David Bower

*/

#ifndef Node_h
#define Node_h

#include <stdlib.h>

struct Node_int{
    int m_data;
    struct Node_int *m_next;
};

#endif 