#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

class LinkedList
{
    public:
        LinkedList();
        void push(int elem);
    private:
        Node* head;
};


#endif