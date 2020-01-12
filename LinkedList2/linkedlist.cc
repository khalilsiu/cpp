#include <iostream>
#include <memory>
#include <cstddef>
#include <algorithm>
#include <utility>



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
        std::unique_ptr<Node> head = nullptr;
        Node* tail = nullptr;
        std::size_t length = 0;

    public:
        LinkedList() = default;

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
                std::cout << i << std::endl;
                pop_back();
            }
        }

        template <typename T2>
        void insert(int pos, T2&& value, int counts = 1)
        {
            if (empty())
            {
                push_back(std::forward<T2>(value));
            }
            else
            {
                if(pos < 0 || pos > length)
                {
                    throw std::runtime_error("Position is out of range");
                }
                else if (pos == 0)
                {
                    for(int i = 0; i < counts; i++)
                    {
                        push_front(std::forward<T2>(value));
                    }
                }
                else if (pos == length)
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
                        auto* cur = head.get();
                        for (int i = 0; i < pos-1; i++)
                        {
                            cur = cur->next.get();
                        }
                        auto temp_next = std::move(cur->next);
                        auto* temp_tail = tail;
                        tail = cur;
                        push_back(std::forward<T2>(value));
                        temp_next->prev = tail;
                        tail->next = std::move(temp_next);
                        tail = temp_tail;
                    }
                }
            }
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
    LinkedList<float> new_list;
    new_list.push_back(1.5);
    new_list.push_back(2.5);
    new_list.push_back(3.5);
    new_list.push_back(5.5);
    new_list.insert(1,6.5,2);
    std::cout << new_list << std::endl;

}
