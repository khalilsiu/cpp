#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>
#include <utility>

class MyClass
{
    public:
        MyClass(int num1, int num2)
        : data{num1*num2}
        {
        }
    private:
        int data;

    friend std::ostream& operator<< (std::ostream& out, const MyClass& multiply);
};

std::ostream& operator<< (std::ostream& out, const MyClass& multiply)
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
            :data{value}
        {

        };
        T data;
        std::unique_ptr<Node> next = nullptr;
        Node* prev = nullptr;
    };
    private:
        Node* tail = nullptr;
        std::size_t length = 0;

    public:
        LinkedList() = default;
        std::unique_ptr<Node> head = nullptr;


        class Iterator
        {
            public:
                Iterator(Node* ptr = nullptr)
                : cur_node_ptr{ptr}
                {
                }

                T operator* ()
                {
                    return cur_node_ptr->data;
                }

                Iterator operator++ (int)
                {
                    cur_node_ptr = cur_node_ptr->next.get();
                    return cur_node_ptr;
                }

                Iterator operator-- (int)
                {
                    cur_node_ptr = cur_node_ptr->prev;
                    return cur_node_ptr;
                }

                Iterator operator+(int num)
                {
                    for (int i = 0; i < num; i++)
                    {
                        if (cur_node_ptr)
                        {
                            cur_node_ptr = cur_node_ptr->next.get();
                        }
                        else
                        {
                            throw std::runtime_error("Iterator exceeds range of container.");
                        }
                        
                    }
                    return cur_node_ptr;
                }

                Iterator operator-(int num)
                {
                    for (int i = 0; i < num; i++)
                    {
                        if (cur_node_ptr->prev)
                        {
                            cur_node_ptr = cur_node_ptr->prev;
                        }
                        else
                        {
                            throw std::runtime_error("Iterator exceeds range of container.");
                        }
                        
                    }
                    return cur_node_ptr;
                }

                Iterator operator= (const Iterator& it)
                {
                    cur_node_ptr = it.cur_node_ptr;
                    std::cout << "operator = is run" << std::endl;
                    return cur_node_ptr;
                }

                bool operator!=(const Iterator& it)
                {
                    return cur_node_ptr != it.cur_node_ptr;
                }

                bool operator<(const Iterator& it)
                {
                    return cur_node_ptr < it.cur_node_ptr;
                }

                bool operator>(const Iterator& it)
                {
                    return cur_node_ptr > it.cur_node_ptr;
                }

                bool operator>=(const Iterator& it)
                {
                    return cur_node_ptr >= it.cur_node_ptr;
                }

                 bool operator<=(const Iterator& it)
                {
                    return cur_node_ptr <= it.cur_node_ptr;
                }

                bool operator==(const Iterator& it)
                {
                    return cur_node_ptr == it.cur_node_ptr;
                }

                Node* get_ptr()
                {
                    return cur_node_ptr;
                }

            private:
                Node* cur_node_ptr;
        };


        Iterator begin()
        {
            return head.get();
        }

        Iterator end()
        {
            return tail->next.get();
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
        void insert(Iterator it_position, T2&& value, int counts = 1)
        {
            static_assert(std::is_constructible_v<T,T2>);

            if (empty())
            {
                push_back(std::forward<T2>(value));
            }
            else
            {
                if (it_position < begin() && it_position != end())
                {
                    throw std::runtime_error("Position is out of range");
                }
                else if (it_position == begin())
                {
                    for(int i = 0; i < counts; i++)
                    {
                        push_front(std::forward<T2>(value));
                    }
                }
                else if (it_position == end())
                {
                    for(int i = 0; i < counts; i++)
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
                        auto* temp_tail = tail;
                        tail = it_position.get_ptr();
                        push_back(std::forward<T2>(value));
                        temp_next->prev = tail;
                        tail->next = std::move(temp_next);
                        tail = temp_tail;
                    }
                }
        
                
            }
        }

        template <typename ...Args>
        void emplace_back(Args&& ...args)
        {
            static_assert(std::is_constructible_v<T, Args...>);
            push_back(T(std::forward<Args>(args)...));
        }

        template <typename ...Args>
        void emplace_front(Args&& ...args)
        {
            static_assert(std::is_constructible_v<T,Args...>);
            push_front(T(std::forward<Args>(args)...));
        }

        template <typename ...Args>
        void emplace(int pos, Args&&...args)
        {
            static_assert(std::is_constructible_v<T,Args...>);
            insert(pos, T(std::forward<Args>(args)...));
        }

        

        void erase(int start, int end=0)
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
                else if (start == list_length-1)
                {
                    pop_back();
                }
            }
            
        }


        void push_front(T&& value)
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

        void push_back(T&& value)
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
            if(empty())
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
        friend std::ostream& operator<<(std::ostream& out, const LinkedList<T3>& linkedlist);
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const LinkedList<T>& linkedlist)
{
    auto* cur = linkedlist.head.get();
    while(cur)
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

    it = new_list.begin();


    new_list.insert(it-2, 10);


    std::cout << new_list << std::endl;


}
