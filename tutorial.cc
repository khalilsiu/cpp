#include <iostream>
using namespace std;

struct Node
{
    int data;
    struct Node *next;
};

void push(struct Node** head, int node_data)
{
    // since you are would like to change the pointer directly
    // and head is a pointer, therefore, you would need to pass in a pointer of pointer
    struct Node* newNode = new Node;
    // other than primitive types, all other objects are pointers
    newNode -> data = node_data;
    // you are changing the pointer of pointer
    newNode->next = (*head);
    (*head) = newNode;
    delete newNode;
    return;
}

void append(struct Node** head, int node_data){
    struct Node* newNode = new Node;
    newNode->data = node_data;
    newNode->next = NULL;
    struct Node* last = *head;

    if((*head) == NULL){
        (*head) = newNode;
        return;
    }
    while(last -> next != NULL){
        last = last -> next;
    }
    last -> next = newNode;
    delete newNode;
    return ;
}

void pop(struct Node** head){
    struct Node* last = *head;
    cout << last << endl;
    if((*head)==NULL){
        cout << "There is no head node, cannot be popped." << endl;
        return ;
    }
    if((*head)->next == NULL){
        (*head)= NULL;
        return;
    }
    while ((*head) -> next != NULL){
        (*head) = (*head) -> next;
        cout << (*head) << endl;
    }
    head = NULL;
    cout << "last" << last->data << endl;
    cout << "last" << last->next->data << endl;
    cout << "head" << head << endl;
    return;
}

void displayList(struct Node *node)
{
    while(node!= NULL){
        cout << node->data << "-->";
        node = node -> next;
    }
    if(node == NULL)
    cout << "null";
}

int main()
{
    struct Node* head = NULL;
    append(&head, 10);
    push(&head, 20);
    pop(&head);
    cout << "Final linked list: "<<endl;
    displayList(head);

}