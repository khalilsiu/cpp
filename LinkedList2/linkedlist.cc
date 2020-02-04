#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>
#include <utility>
#include <vector>

class MyClass
{
public:
    MyClass(int num1, int num2)
        : data{num1 * num2}
    {
    }

private:
    int data;

    friend std::ostream &operator<<(std::ostream &out, const MyClass &multiply);
};

std::ostream &operator<<(std::ostream &out, const MyClass &multiply)
{
    out << multiply.data;
    return out;
}

template <typename T>
class LinkedList
{
    struct Node
    {
        Node(T value)
            : data{value} {

              };
        T data;
        std::unique_ptr<Node> next = nullptr;
        Node *prev = nullptr;
    };

private:
    Node *tail = nullptr;
    std::size_t length = 0;

public:
    LinkedList() = default;
    std::unique_ptr<Node> head = nullptr;

    class Iterator
    {
    public:
        Iterator(Node *ptr = nullptr)
            : cur_node_ptr{ptr}
        {
        }

        T& operator*() 
        {
            if (!cur_node_ptr)
            {
                throw std::runtime_error("Null pointer cannot be dereferenced");
            }
            else
            {
                return cur_node_ptr->data;
            }
        }

        Iterator& operator++()
        {
            cur_node_ptr = cur_node_ptr->next.get();
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp(cur_node_ptr);
            cur_node_ptr = cur_node_ptr-> next.get();
            std::cout << *temp << std::endl;
            return temp;
        }

        Iterator& operator--()
        {
            cur_node_ptr = cur_node_ptr->prev;
            return *this;   
        }

        Iterator operator--(int)
        {
            Iterator temp(cur_node_ptr);
            cur_node_ptr = cur_node_ptr->prev;
            return temp;
        }

        Iterator operator+(int num)
        {
            for (int i = 0; i < num; ++i){
                cur_node_ptr = cur_node_ptr->next.get();
            }
            return Iterator(cur_node_ptr);
        }

        Iterator operator-(int num)
        {
            for (int i = 0; i < num; ++i){
                if (cur_node_ptr->prev){
                    cur_node_ptr = cur_node_ptr->prev;
                }else{
                    auto temp = std::make_unique<Node>(0);
                    temp->next = std::move(cur_node_ptr);
                    cur_node_ptr = temp.get();
                }
            }
            return Iterator(cur_node_ptr);
        }

        Iterator operator=(const Iterator &it) noexcept
        {
            cur_node_ptr = it.cur_node_ptr;
            return Iterator(cur_node_ptr);
        }

        bool operator!=(const Iterator &it) noexcept
        {
            return cur_node_ptr != it.cur_node_ptr;
        }

        bool operator==(const Iterator &it) noexcept
        {
            return cur_node_ptr == it.cur_node_ptr;
        }

        Node *get_ptr() const noexcept
        {
            return cur_node_ptr;
        }

    private:
        Node *cur_node_ptr;
    };

    Iterator begin() const noexcept
    {
        return head.get();
    }

    Iterator end() const noexcept
    {
        if (empty())
        {
            return tail;
        }
        else
        {
            return tail->next.get();
        }
    }

    bool empty() const noexcept
    {
        return (!head);
    }

    int front() const
    {
        return head ? head->data : throw std::runtime_error("List is empty.");
    }

    int back() const
    {
        return tail ? tail->data : throw std::runtime_error("List is empty.");
    }

    std::size_t size() const noexcept
    {
        return length;
    }

    void clear()
    {
        const std::size_t list_length = length;
        for (int i = 0; i < list_length; i++)
        {
            pop_back();
        }
    }

    template <typename T2>
    void insert(Iterator it_position, T2 &&value, int counts = 1)
    {
        static_assert(std::is_constructible_v<T, T2>);

        if (empty())
        {
            push_back(std::forward<T2>(value));
        }
        else
        {
            if (it_position == begin())
            {
                for (int i = 0; i < counts; i++)
                {
                    push_front(std::forward<T2>(value));
                }
            }
            else if (it_position == end())
            {
                for (int i = 0; i < counts; i++)
                {
                    push_back(std::forward<T2>(value));
                }
            }
            else
            {
                for (int i = 0; i < counts; i++)
                {
                    it_position--;
                    auto temp_next = std::move(it_position.get_ptr()->next);
                    auto *temp_tail = tail;
                    tail = it_position.get_ptr();
                    push_back(std::forward<T2>(value));
                    temp_next->prev = tail;
                    tail->next = std::move(temp_next);
                    tail = temp_tail;
                }
            }
        }
    }

    template <typename... Args>
    void emplace_back(Args &&... args)
    {
        static_assert(std::is_constructible_v<T, Args...>);
        push_back(T(std::forward<Args>(args)...));
    }

    template <typename... Args>
    void emplace_front(Args &&... args)
    {
        static_assert(std::is_constructible_v<T, Args...>);
        push_front(T(std::forward<Args>(args)...));
    }

    template <typename... Args>
    void emplace(int pos, Args &&... args)
    {
        static_assert(std::is_constructible_v<T, Args...>);
        insert(pos, T(std::forward<Args>(args)...));
    }

    void erase(int start, int end = 0)
    {
        std::size_t list_length = length;
        if (start < 0 || start >= list_length)
        {
            throw std::runtime_error("Start position is out of range.");
        }
        else if (end < 0 || end >= list_length)
        {
            throw std::runtime_error("End position is out of range.");
        }
        else if (end != 0 && end < start)
        {
            throw std::runtime_error("End position has to be equal or larger than start position.");
        }
        else
        {
            if (start == 0)
            {
                pop_front();
            }
            else if (start == list_length - 1)
            {
                pop_back();
            }
        }
    }

    void push_front(T &&value)
    {
        if (empty())
        {
            push_back(std::forward<T>(value));
        }
        else
        {
            auto temp = std::make_unique<Node>(std::forward<T>(value));
            head->prev = temp.get();
            temp->next = std::move(head);
            head = std::move(temp);
            ++length;
        }
    }

    void push_back(T &&value)
    {
        auto temp = std::make_unique<Node>(std::forward<T>(value));
        if (empty())
        {
            head = std::move(temp);
            tail = head.get();
            ++length;
        }
        else
        {
            temp->prev = tail;
            tail->next = std::move(temp);
            tail = tail->next.get();
            ++length;
        }
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty.");
        }
        else if (length == 1)
        {
            head = nullptr;
            tail = nullptr;
            --length;
        }
        else
        {
            tail = tail->prev;
            tail->next = nullptr;
            --length;
        }
    }

    void pop_front()
    {
        if (empty())
        {
            throw std::runtime_error("List is empty.");
        }
        else if (length == 1)
        {
            pop_back();
        }
        else
        {
            head = std::move(head->next);
            head->prev = nullptr;
            --length;
        }
    }

    template <typename T3>
    friend std::ostream &operator<<(std::ostream &out, const LinkedList<T3> &linkedlist);
};

template <typename T>
std::ostream &operator<<(std::ostream &out, const LinkedList<T> &linkedlist)
{
    auto *cur = linkedlist.head.get();
    while (cur)
    {
        out << cur->data << '\t';
        cur = cur->next.get();
    }
    return out;
}

int main()
{
    LinkedList<int> new_list;

    LinkedList<int>::Iterator it;
    LinkedList<int>::Iterator it2;

    new_list.push_back(1);
    new_list.push_back(2);

    it = new_list.begin()-1;
    // new_list.insert(it, 3);
    it++;

    std::cout << *it << std::endl;
 


    // std::vector<int>::iterator it;
    // std::vector<int> v {1,2};

    // it = v.begin()-1;
    // // v.insert(it-2,3);

    // // for (it = v.begin()-2; it != (v.end()) ; it++){
    // //     std::cout << *it <<std::endl;
    // // }

    //     std::cout << *it <<std::endl;


    // int a = 1;
    // int b = a++;
    // int c = ++a;

    // std::cout << a++ << std::endl;
    // std::cout << b << std::endl;
    // std::cout << c << std::endl;

    
}
