#include <iostream>
#include "Node.h"
#include "LinkedList.h"

using namespace std;

LinkedList::LinkedList()
{
    head = NULL;
};

void LinkedList::push(int elem){
    Node* newNode = new Node(elem);
    Node* ptr = head;
    cout << "head" << head << endl;

    if (!ptr){
        head = newNode;
        cout << "head" << head->value << endl;
        return;
    }

    while (ptr->nextNode != NULL){
        ptr = ptr -> nextNode;
        cout << "ptr" << ptr << endl;
    }

    ptr -> nextNode = newNode;


    cout << "head" << head << endl;
    cout << "head val" << head->value << endl;
    cout << "next" << head->nextNode << endl;
    cout << "newnode"<< newNode<< endl;
    cout << "next val" << head -> nextNode-> value << endl;
    delete newNode;
    return;
}