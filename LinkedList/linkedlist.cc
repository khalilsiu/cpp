#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>
// #define CATCH_CONFIG_MAIN
// #include "catch.hpp"
using namespace std;

class LinkedList
{
    template <typename T>
    struct Node
    {
        Node(T value)
            : data{value}
        {
        }
        T data;
        Node *prev = nullptr;
        std::unique_ptr<LinkedList::Node<T>> next = nullptr;
    };

private:
    Node<T> *tail = nullptr;
    std::unique_ptr<LinkedList::Node<T>> head = nullptr;
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

    void clear() noexcept
    {
        std::size_t list_length = size();
        for (int i = 0; i < list_length; i++)
        {
            pop_back();
        }
    }

    // // insert is pass by value, tried just passing by value of newNode, but the local variable goes out of scope, could not be accessed outside
    template <typename T>
    void insert(int pos, T value, int counts = 1)
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
                auto *temp_tail = tail;
                auto *cur = head.get();
                auto *pre = cur;
                for (int j = 0; j < pos; j++)
                {
                    pre = cur;
                    cur = cur->next.get();
                }
                auto temp_pre_next = std::move(pre->next);
                tail = pre;
                push_back(value);
                tail->next = std::move(temp_pre_next);
                tail = temp_tail;
            }
        }
    }
    template <typename T>
    void emplace(int pos, T value)
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
            auto *temp_tail = tail;
            auto *cur = head.get();
            auto *pre = cur;
            for (int i = 0; i < pos; i++)
            {
                pre = cur;
                cur = cur->next.get();
            }
            tail = pre;
            auto temp_pre_next = std::move(pre->next);
            push_back(value);
            tail->next = std::move(temp_pre_next);
            tail = temp_tail;
        }
    }

    void erase(int start, int end = 0)
    {
        std::size_t list_length = size();
        int counts = end - start;
        counts <= 0 ? counts = 1 : counts;
        cout << "length" << list_length << endl;
        if (start > list_length || end > list_length)
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
        else if (start == list_length-1 || end == list_length)
        {
            for (int i = 0; i < counts; i++)
            {
                pop_back();
            }
        }
        else
        {
            for (int i = 0; i < counts; i++)
            {
                auto *temp_tail = tail;
                auto *cur = head.get();
                auto *pre = cur;
                for (int i = 0; i < start; i++)
                {
                    pre = cur;
                    cur = cur->next.get();
                }
                auto temp_cur_next = std::move(cur->next);
                tail = cur;
                pop_back();
                temp_cur_next->prev = tail;
                tail->next = std::move(temp_cur_next);
                tail = temp_tail;
            }
        }
    }

    // using tail
    template <typename T>
    void push_back(T value) noexcept
    {
        auto temp = std::make_unique<LinkedList::Node<T>>(value);
        if (empty())
        {
            head = std::move(temp);
            tail = head.get();
            ++length;
            return;
        }
        else
        {
            temp->prev = tail;
            tail->next = std::move(temp);
            tail = tail->next.get();
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
            tail = tail->prev;
            tail->next = nullptr;
            --length;
        }
    }

    template <typename T>
    void push_front(T value) noexcept
    {
        auto temp = std::make_unique<LinkedList::Node>(value);
        if (empty())
        {
            head = std::move(temp);
            tail = head.get();
            length = 1;
        }
        else
        {
            head->prev = temp.get();
            temp->next = std::move(head);
            head = std::move(temp);
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
            if (list_length == 1)
            {
                head->prev = nullptr;
                head->next = nullptr;
                head = nullptr;
                tail = nullptr;
                --length;
            }
            else
            {
                head = std::move(head->next);
                head->prev = nullptr;
                --length;
            }
        }
    }

    void resize(int new_size) noexcept
    {
        std::size_t list_length = size();
        if (new_size == 0)
        {
            clear();
        }
        else if (list_length > new_size)
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

    void swap(LinkedList &another_list) noexcept
    {
        std::swap(head, another_list.head);
        std::swap(tail, another_list.tail);
        std::swap(length, another_list.length);
    }

    int get_value_at(int pos) const
    {
        auto *cur = head.get();
        for (int i = 0; i < pos; i++)
        {
            cur = cur->next.get();
            if (cur == nullptr)
            {
                throw std::runtime_error("Index out of range");
            }
        }
        return cur->data;
    }

    friend std::ostream &operator<<(std::ostream &out, LinkedList &linkedlist);
};
template <typename T>
std::ostream &operator<<(std::ostream &out, LinkedList &linkedlist)
{
    std::unique_ptr<LinkedList::Node<T>> cur = nullptr;
    std::swap(cur, linkedlist.head);
    while (cur != nullptr)
    {
        out << cur->data << "\t";
        std::swap(cur, cur->next);
    }
    return out;
}
// TEST_CASE("Linked list elements could be added and removed", "[LinkedList]")
// {
//     LinkedList new_list;
//     new_list.push_back(2);
//     new_list.push_back(3);
//     new_list.push_back(4);
//     new_list.push_back(5);

//     SECTION("front returns the first element in the list")
//     {
//         REQUIRE(new_list.front() == 2);
//     }
//     SECTION("back returns the last element in the list")
//     {
//         REQUIRE(new_list.back() == 5);
//     }
//     SECTION("empty returns false if list is not empty")
//     {
//         REQUIRE(!new_list.empty());
//     }
//     SECTION("size returns length of list")
//     {
//         REQUIRE(new_list.size() == 4);
//     }
//     SECTION("clear removes all elements in the list")
//     {
//         new_list.clear();
//         REQUIRE(new_list.empty());
//     }
//     SECTION("push_back adds an element to the end")
//     {
//         new_list.push_back(6);
//         REQUIRE(new_list.get_value_at(4) == 6);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("push_front adds an element to the front")
//     {
//         new_list.push_front(1);
//         REQUIRE(new_list.get_value_at(0) == 1);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("pop_back removes an element from the end")
//     {
//         new_list.pop_back();
//         REQUIRE(new_list.get_value_at(2) == 4);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("pop_front removes an element from the front")
//     {
//         new_list.pop_front();
//         REQUIRE(new_list.get_value_at(0) == 3);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("insert inserts initialized element at position for a number of times")
//     {
//         new_list.insert(0,6,3);
//         bool testPassed = (new_list.get_value_at(0) == 6 && new_list.get_value_at(1) == 6 && new_list.get_value_at(2) == 6);
//         REQUIRE(testPassed);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("emplace insert an element at position")
//     {
//         new_list.emplace(3,8);
//         REQUIRE(new_list.get_value_at(3) == 8);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("erase removes an element at a position if end is not specified")
//     {
//         new_list.erase(2);
//         REQUIRE(new_list.get_value_at(2) == 5);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("erase removes elements from start to end exclusive")
//     {
//         new_list.erase(0,3);
//         REQUIRE(new_list.get_value_at(0) == 5);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("resize resizes list removing elements if size is shorter")
//     {
//         new_list.resize(2);
//         REQUIRE(new_list.get_value_at(1) == 3);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("resize expands list by pushing 0 to the end if size is larger")
//     {
//         new_list.resize(7);
//         REQUIRE(new_list.get_value_at(6) == 0);
//         cout << "List: " << new_list << endl;
//     }
//     SECTION("swap swaps contents of two lists")
//     {
//         LinkedList another_list;
//         another_list.push_back(5);
//         another_list.push_back(4);
//         another_list.push_back(3);
//         another_list.push_back(2);
//         new_list.swap(another_list);
//         bool testPassed = (new_list.get_value_at(0) == 5 && another_list.get_value_at(0) == 2);
//         REQUIRE(testPassed);
//         cout << "List: " << new_list << endl;
//         cout << "List: " << another_list << endl;

//     }
// }

// Create a Node: pointer of Node type, insert value in its data field, next is NULL

// If linkedlist is still empty: check, if head = NULL, empty

// If just one Node: it's called both head and tail

// If list is created already: we would insert at the tail, add newly created Node to a tail

int main()
{
    LinkedList new_list;
    new_list.push_back(2);
    new_list.push_back(3);
    new_list.push_back(4);
    new_list.push_back(5);    


    cout << new_list.get_value_at(6) << endl;

}
