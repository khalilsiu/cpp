#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
using namespace std;

class LinkedList
{

    struct Node
    {
        Node(int value)
            : data{value}
        {
        }
        int data;
        Node *prev = nullptr;
        Node *next = nullptr;
    };

private:
    Node *head = nullptr;
    Node *tail = nullptr;
    std::size_t length = 0;

public:
    LinkedList() = default;

    int front() const
    {
        return head ? head->data : throw std::runtime_error("List is empty.");
    }

    int back() const
    {
        return tail ? tail->data : throw std::runtime_error("List is empty.");
    }

    bool empty() const noexcept
    {
        return !head;
    }

    std::size_t size() const noexcept
    {
        return length;
    }

    void clear()
    {
        std::size_t list_length = size();
        for (int i = 0; i < list_length; i++)
        {
            pop_back();
        }
    }

    // // insert is pass by value, tried just passing by value of newNode, but the local variable goes out of scope, could not be accessed outside
    void insert(int pos, int value, int counts = 1)
    {
        std::size_t list_length = size();
        if (pos > list_length)
        {
            throw std::runtime_error("Position out of range");
        }
        if (pos == 0)
        {
            for (int i = 0; i < counts; i++)
            {
                push_front(value);
            }
        }
        else if (pos == list_length)
        {
            for (int i = 0; i < counts; i++)
            {
                push_back(value);
            }
        }
        else
        {
            for (int i = 0; i < counts; i++)
            {
                auto *temp = new LinkedList::Node{value};
                auto *pre = head;
                auto *cur = head;
                for (int j = 0; j < pos; j++)
                {
                    pre = cur;
                    cur = cur->next;
                }
                pre->next = temp;
                temp->prev = pre;
                temp->next = cur;
                cur->prev = temp;
                ++length;
            }
        }
    }

    void emplace(int pos, int value)
    {
        std::size_t list_length = size();
        if (pos > list_length)
        {
            throw std::runtime_error("Position out of range");
        }
        if (pos == 0)
        {
            push_front(value);
        }
        else if (pos == list_length)
        {
            push_back(value);
        }
        else
        {
            auto *temp = new LinkedList::Node{value};
            auto *pre = head;
            auto *cur = head;
            for (int i = 0; i < pos; i++)
            {
                pre = cur;
                cur = cur->next;
            }
            pre->next = temp;
            temp->prev = pre;
            temp->next = cur;
            cur->prev = temp;
            ++length;
        }
    }

    void erase(int start, int end = 0)
    {
        std::size_t list_length = size();
        int counts = end - start;
        if (start >= list_length || end > list_length)
        {
            throw std::runtime_error("Position out of range");
        }
        if (end != 0 && start >= end)
        {
            throw std::runtime_error("End index must be larger than start");
        }
        if (start == 0)
        {
            for (int i = 0; i < counts; i++)
            {
                pop_front();
            }
        }
        else if (start == list_length - 1)
        {
            pop_back();
        }
        else
        {
            for (int i = 0; i < counts; i++)
            {
                auto *pre = head;
                auto *cur = head;
                for (int i = 0; i < start; i++)
                {
                    pre = cur;
                    cur = cur->next;
                }
                pre->next = cur->next;
                cur->next->prev = pre;
                --length;
                delete cur;
            }
        }
    }

    // using tail
    void push_back(int value)
    {
        auto *temp = new LinkedList::Node{value};
        if (empty())
        {
            head = temp;
            tail = temp;
            ++length;
            return;
        }
        else
        {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
            ++length;
            return;
        }
    }

    // using tail
    void pop_back()
    {
        std::size_t list_length = size();
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        if (list_length == 1)
        {
            pop_front();
        }
        else
        {
            auto *temp = tail;
            tail = temp->prev;
            tail->next = nullptr;
            delete temp;
            --length;
        }
    }

    void push_front(int value)
    {
        if (empty())
        {
            head = new LinkedList::Node{value};
            tail = head;
            length = 1;
        }
        else
        {
            auto *temp = new LinkedList::Node{value};
            temp->next = head;
            head->prev = temp;
            head = temp;
            ++length;
        }
    }

    void pop_front()
    {
        std::size_t list_length = size();
        if (empty())
        {
            throw std::runtime_error("List is empty");
        }
        else
        {
            auto *temp = head;
            if (list_length == 1)
            {
                head->prev = nullptr;
                head->next = nullptr;
                head = nullptr;
                tail = nullptr;
                delete temp;
                --length;
            }
            else
            {
                head = head->next;
                head->prev = nullptr;
                delete temp;
                --length;
            }
        }
    }

    void resize(int new_size)
    {
        std::size_t list_length = size();
        if (new_size == 0)
        {
            clear();
        }
        if (list_length > new_size)
        {
            int counts = list_length - new_size;
            for (int i = 0; i < counts; i++)
            {
                pop_back();
            }
        }
        else if (list_length < new_size)
        {
            int counts = new_size - length;
            for (int i = 0; i < counts; i++)
            {
                push_back(0);
            }
        }
    }

    void swap(LinkedList &another_list)
    {
        std::swap(head, another_list.head);
    }

    void PrintList()
    {
        LinkedList::Node *temp = nullptr;
        temp = head;
        cout << "List elements: \t";
        while (temp != nullptr)
        {
            cout << temp->data << "\t";
            temp = temp->next;
        }
        cout << endl;
        temp = nullptr;
        delete temp;
        return;
    }

    int get_value_at(int pos)
    {
        auto *cur = head;
        for (int i = 0; i < pos; i++)
        {
            cur = cur->next;
            if (cur == nullptr)
            {
                return 0;
            }
        }
        return cur->data;
    }
};

// TEST_CASE("Linked list elements could be added and removed", "[LinkedList]")
// {
//     LinkedList new_list;
//     new_list.push_back(2);
//     new_list.push_back(3);
//     new_list.push_back(4);
//     new_list.push_back(5);

//     SECTION("front returns the first element in the list")
//     {
//         REQUIRE(new_list.Front() == 2);
//     }
//     SECTION("back returns the last element in the list")
//     {
//         REQUIRE(new_list.Back() == 5);
//     }
//     SECTION("empty returns false if list is not empty")
//     {
//         REQUIRE(!new_list.Empty());
//     }
//     SECTION("size returns length of list")
//     {
//         REQUIRE(new_list.Size() == 4);
//     }
//     SECTION("clear removes all elements in the list")
//     {
//         new_list.Clear();
//         REQUIRE(new_list.Empty());
//     }
//     SECTION("getSize returns the number of bytes of the list")
//     {
//         REQUIRE(new_list.GetSize() == 32);
//     }
//     SECTION("push_back adds an element to the end")
//     {
//         new_list.push_back(6);
//         REQUIRE(new_list.GetValueAt(4) == 6);
//         new_list.PrintList();
//     }
//     SECTION("push_front adds an element to the front")
//     {
//         new_list.PushFront(1);
//         REQUIRE(new_list.GetValueAt(0) == 1);
//         new_list.PrintList();
//     }
//     SECTION("pop_back removes an element from the end")
//     {
//         new_list.pop_back();
//         REQUIRE(new_list.GetValueAt(2) == 4);
//         new_list.PrintList();
//     }
//     SECTION("pop_front removes an element from the front")
//     {
//         new_list.PopFront();
//         REQUIRE(new_list.GetValueAt(0) == 3);
//         new_list.PrintList();
//     }
//     SECTION("insert inserts initialized element at position for a number of times")
//     {
//         Node newNode;
//         newNode.data = 6;
//         newNode.next = nullptr;
//         new_list.Insert(0,newNode,3);
//         bool testPassed = (new_list.GetValueAt(0) == 6 && new_list.GetValueAt(1) == 6 && new_list.GetValueAt(2) == 6);
//         REQUIRE(testPassed);
//         new_list.PrintList();
//     }
//     SECTION("emplace insert an element at position")
//     {
//         new_list.Emplace(3,8);
//         REQUIRE(new_list.GetValueAt(3) == 8);
//         new_list.PrintList();
//     }
//     SECTION("erase removes an element at a position if end is not specified")
//     {
//         new_list.Erase(2);
//         REQUIRE(new_list.GetValueAt(2) == 5);
//         new_list.PrintList();
//     }
//     SECTION("erase removes elements from start to end exclusive")
//     {
//         new_list.Erase(0,3);
//         REQUIRE(new_list.GetValueAt(0) == 5);
//         new_list.PrintList();
//     }
//     SECTION("resize resizes list removing elements if size is shorter")
//     {
//         new_list.Resize(2);
//         REQUIRE(new_list.GetValueAt(1) == 3);
//         new_list.PrintList();
//     }
//     SECTION("resize expands list by pushing 0 to the end if size is larger")
//     {
//         new_list.Resize(7);
//         REQUIRE(new_list.GetValueAt(6) == 0);
//         new_list.PrintList();
//     }
//     SECTION("swap swaps contents of two lists")
//     {
//         LinkedList another_list;
//         another_list.push_back(5);
//         another_list.push_back(4);
//         another_list.push_back(3);
//         another_list.push_back(2);
//         new_list.Swap(&another_list);
//         bool testPassed = (new_list.GetValueAt(0) == 5 && another_list.GetValueAt(0) == 2);
//         REQUIRE(testPassed);
//         cout << "Original List: \t";
//         new_list.PrintList();
//         cout << endl;
//         cout << "Another List: \t";
//         another_list.PrintList();
//         cout << endl;

//     }
// }

// Create a Node: pointer of Node type, insert value in its data field, next is NULL

// If linkedlist is still empty: check, if head = NULL, empty

// If just one Node: it's called both head and tail

// If list is created already: we would insert at the tail, add newly created Node to a tail

int main()
{
    LinkedList new_list;
    new_list.push_front(3);
    new_list.push_front(4);
    new_list.push_front(5);
    new_list.push_front(6);
    new_list.push_front(7);


    new_list.PrintList();
    cout << new_list.get_value_at(2) << endl;
}
