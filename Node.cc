#include "Node.h"
#include <iostream>
#include <typeinfo>
using namespace std;

Node::Node(int elem)
{
    value = elem;
    nextNode = NULL;
};

// void LinkedList::push(int elem)
// {
//     LinkedList *ptr = head;
//     // cout << ptr << endl;
//     LinkedList newNode(elem);
//     // cout << newNode.nextNode << endl;
//     if (!ptr)
//     {
//         head = &newNode;
//         return;
//     }
//     while (ptr->nextNode != NULL)
//     {
//         ptr = ptr->nextNode;
//         // cout << "this ptr" << ptr->nextNode << endl;
//     }
//     cout << newNode.nextNode << endl;
//     cout << newNode.value << endl;
//     ptr->nextNode = &newNode;
//     cout << newNode.nextNode << endl;
//     cout << newNode.value << endl;
//     // cout << head << endl;
//     // cout << ptr << endl;
//     // cout << ptr->nextNode << endl;
//     // cout << newNode.value << endl;


//     return;
// }

// int LinkedList::pop()
// {
//     LinkedList *ptr = head;
//     cout << "newptr " << ptr << endl;
//     if (!ptr)
//     {
//         // cout << "head"<<head->value<< endl;
//         int headValue = head->value;
//         head = NULL;
//         return headValue;
//     }
//     else
//     {

//         cout << "initial" << head->nextNode->nextNode->nextNode << endl;
//         // while(ptr -> nextNode){
//         //     ptr = ptr -> nextNode;
//         //     cout << "haha " <<  ptr<< endl;
//         // }
//     }

//     // cout << "newNode " << ptr <<endl;
//     // cout << "val"<<ptr->value << endl;

//     // ptr = NULL;
//     // return ptr->value ;

//     return 0;
// }