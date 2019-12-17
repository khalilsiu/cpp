#include <iostream>
#include <memory>
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
using namespace std;

struct node
{
    int data;
    node *next;
};

class LinkedList
{
private:
    node *head;
    node *tail;

public:
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    void createNode(int value)
    {
        node *temp = new node;
        temp->data = value;
        temp->next = nullptr;
        if (head == nullptr)
        {
            head = temp;
            tail = temp;
            temp = nullptr;
            delete temp;
            return;
        }
        else
        {
            tail->next = temp;
            tail = temp;
            temp = nullptr;
            delete temp;
            return;
        }
    }

    void printList()
    {
        node *temp = new node;
        temp = head;
        cout << "List elements: \t";
        while (temp != nullptr)
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }
        cout << endl;
        delete temp;
    }

    // int getValueAt(int pos)
    // {
    //     node *cur = new node;
    //     cur = head;
    //     for (int i = 0; i < pos; i++)
    //     {
    //         cur = cur->next;
    //         if (cur == NULL)
    //         {
    //             return 0;
    //         }
    //     }
    //     return cur->data;
    // }

    void unshift(int value)
    {
        node *temp = new node;
        temp->data = value;
        temp->next = head;
        head = temp;
        temp = nullptr;
        delete temp;
    }

    // void push(int value)
    // {
    //     node *temp = new node;
    //     node *cur = new node;
    //     temp->data = value;
    //     temp->next = nullptr;
    //     cur = head;
    //     while (cur->next != nullptr)
    //     {
    //         cur = cur->next;
    //     }
    //     cur->next = temp;
    //     temp = nullptr;
    //     cur = nullptr;
    //     delete temp;
    //     delete cur;
    // }


    void insertPosition(int pos, int value)
    {
        node *temp = new node;
        node *cur = new node;
        node *pre = new node;
        cur = head;
        for (int i = 0; i < pos; i++)
        {
            pre = cur;
            cur = cur->next;
        }
        temp->data = value;
        temp->next = cur;
        pre->next = temp;
        temp = nullptr;
        cur = nullptr;
        pre = nullptr;
        delete temp;
        delete cur;
        delete pre;

    }

    void shift()
    {
        node *temp = new node;
        temp = head;
        head = head->next;
        temp = nullptr;
        delete temp;
    }

    // void pop()
    // {
    //     node *pre = new node;
    //     node *cur = new node;
    //     cur = head;
    //     while (cur->next != nullptr)
    //     {
    //         pre = cur;
    //         cur = cur->next;
    //     }
    //     pre->next = nullptr;
    //     pre = nullptr;
    //     cur = nullptr;
    //     delete pre;
    //     delete cur;
    // }

    void deletePosition(int pos)
    {
        node *pre = new node;
        node *cur = new node;
        cur = head;
        for (int i = 0; i < pos; i++)
        {
            pre = cur;
            cur = cur->next;
        }
        pre->next = cur->next;
        pre = nullptr;
        cur = nullptr;
        delete pre;
        delete cur;
    } 

    // void createNode(int value)
    // {
    //     node *temp = new node;
    //     temp -> data = value;
    //     temp -> next = NULL;
    //     if(head == NULL)
    //     {
    //         head = temp;
    //         tail = temp;
    //         temp = NULL;
    //     }
    //     else
    //     {
    //         tail-> next = temp;
    //         tail = temp;
    //     }
    // }

    // using tail
    void push(int value)
    {
        node *temp = new node;
        temp->data = value;
        temp->next = nullptr;
        tail-> next = temp;
        tail = temp;
        temp = nullptr;
        delete temp;
    }

    // alternative
    // void pop()
    // {
    //     node *temp = new node;
    //     temp = head;
    //     while(temp != NULL)
    //     {
    //         if(temp->next == tail){
    //             break;
    //         }
    //         temp = temp->next;
    //     }
    //     temp->next = NULL;
    //     delete tail;
    //     tail = temp;
    // }

    // using tail
    void pop()
    {
        node *pre = new node;
        node *cur = new node;
        cur = head;
        while(cur->next != nullptr)
        {
            pre = cur;
            cur = cur->next;
        }
        tail = pre;
        tail->next = nullptr;
        pre = nullptr;
        cur = nullptr;
        delete pre;
        delete cur;
    }

    void sort()
    {
        int counter = -1;
        int traverseCount = 0;
        if (head == nullptr)
        {
            return;
        }
        node *cur = new node;
        node *pre = new node;
        node *prepre = new node;
        node *temp = new node;
        while(counter != 0){
            cur = head;
            counter = 0;
            cout << "counter "<< counter << endl;

            while(cur->next != nullptr)
            {
                cout << "haha " << cur->next << endl;
                prepre = pre;
                pre = cur;
                cur = cur->next;
                traverseCount++;
                cout << "run " << endl;
                if (cur->data < pre->data)
                {
                    cout << "cur data " << cur->data << endl;
                    cout << "pre data " << pre->data << endl;
                    pre->next = cur->next;
                    cur->next = pre;
                    prepre->next = cur;
                    temp = pre;
                    pre = cur;
                    cur = temp;
                    cout << "traverseCount " << traverseCount << endl;
                    cout << "cur next " << cur->next << endl;
                    if (traverseCount == 1)
                    {
                        head = prepre;
                    }
                    counter++;
                    cout << "counter "<< counter << endl;
                }
                this->printList();
                cout << "run " << endl;
                cout << "haha " << cur->next << endl;
            }
            traverseCount = 0;
            tail = cur;
        }
        cur = nullptr;
        pre = nullptr;
        temp = nullptr;
        delete cur;
        delete pre;
        delete temp;
        
    }
};

// TEST_CASE("Linked list elements could be added and removed", "[LinkedList]")
// {
//     LinkedList newList;
//     newList.createNode(2);
//     newList.push(3);
//     newList.push(4);
//     newList.push(9);

//     SECTION("creating a new node to the linked list adds to the end")
//     {
//         newList.createNode(5);
//         REQUIRE(newList.getValueAt(4) == 5);
//         newList.printList();
//     }
//     SECTION("unshift adds an element to the front")
//     {
//         newList.unshift(1);
//         REQUIRE(newList.getValueAt(0) == 1);
//         newList.printList();
//     }
//     SECTION("push adds an element to the end")
//     {
//         newList.push(6);
//         REQUIRE(newList.getValueAt(4) == 6);
//         newList.printList();
//     }
//     SECTION("insertPosition adds an element to a specified position")
//     {
//         newList.insertPosition(3, 7);
//         REQUIRE(newList.getValueAt(3) == 7);
//         newList.printList();
//     }
//     SECTION("shift removes an element at the front")
//     {
//         newList.shift();
//         REQUIRE(newList.getValueAt(0) == 3);
//         newList.printList();
//     }
//     SECTION("pop removes an element at the end")
//     {
//         newList.pop();
//         REQUIRE(newList.getValueAt(2) == 4);
//         newList.printList();
//     }
//     SECTION("deletePosition removes an element at a position")
//     {
//         newList.deletePosition(2);
//         REQUIRE(newList.getValueAt(2) == 9);
//         newList.printList();
//     }
//     SECTION("getValueAt returns 0 when index is out of range")
//     {
//         REQUIRE(newList.getValueAt(10) == 0);
//     }
// }

// Create a node: pointer of node type, insert value in its data field, next is NULL

// If linkedlist is still empty: check, if head = NULL, empty

// If just one node: it's called both head and tail

// If list is created already: we would insert at the tail, add newly created node to a tail

int main()
{
    LinkedList newList;
    newList.createNode(2);
    newList.createNode(3);

    newList.push(7);
    newList.push(3);
    newList.unshift(9);
    newList.pop();
    newList.insertPosition(1,11);
    newList.shift();
    newList.deletePosition(1);

    newList.printList();
    // cout << newList.getValueAt(2) << endl;
}
