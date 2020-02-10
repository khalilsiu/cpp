#include <iostream>
#include <utility>
#include <memory>

template <typename T1, typename T2>
class BST
{
    struct Node
    {
        Node(T1 c, T2 v)
            : key{c}, value{v}
        {
        }
        T1 key;
        T2 value;
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;
        Node *prev = nullptr;
    };

private:
    std::unique_ptr<Node> head;

public:
    BST()
    {
        head = nullptr;
    };

    template <typename T3, typename T4>
    void insert(std::pair<T3, T4> pair) noexcept
    {
        static_assert(std::is_constructible_v<T1,T3>);
        static_assert(std::is_constructible_v<T2,T4>);
        auto temp = std::make_unique<Node>(std::forward<T3>(pair.first ), std::forward<T4>(pair.second));
        if (!head)
        {
            head = std::move(temp);
        }
        else
        {
            auto cur = find(std::forward<T3>(pair.first));
            if (pair.first == cur->key)
            {
                cur->value = pair.second;
            }
            else if (pair.first > cur->key)
            {
                temp->prev = cur;
                cur->right = std::move(temp);
                // std::cout << cur->right->key << "::" << cur->right->value << std::endl;

            }
            else
            {
                temp->prev = cur;
                cur->left = std::move(temp);
                // std::cout << cur->left->key << "::" << cur->left->value << std::endl;

            }
        }
    }

    template <typename ...Args>
    void emplace(Args &&...args){
        // static_assert(std::is_constructible_v<BST, Args...>);
        insert(std::pair<Args ...>(std::forward<Args>(args)...));

    }


    T2& operator[](T1 &&key){
        auto cur = find(std::forward<T1>(key));
        if(key == cur->key){
            return cur->value;
        }else{
            T2 value = 0;
            insert(std::pair<T1,T2>(std::forward<T1>(key), value));
            return value;
        }
    }

    Node *find(T1 key) const noexcept
    {
        auto cur = head.get();
        while (cur)
        {
            if (key > cur->key && cur->right)
            {
                cur = cur->right.get();
            }
            else if (key < cur->key && cur->left)
            {
                cur = cur->left.get();
                // std::cout<< cur->key << "::" << cur->value << std::endl;
            }
            else
            {
                return cur;
            }
        }
        return cur;
    }

    template <typename T5, typename T6>
    friend std::ostream &operator<<(std::ostream &out, const BST<T5,T6> &bst);

    Node* printLeafNodes(std::ostream &out, Node *node) const
    {
        if (!node)
        {
            throw std::runtime_error("BST has no element");
        }

        out << node->key << "::" << node->value << std::endl;
        if (!node->left && !node->right)
        {
            return node;
        }
        
        if (node->right)
        {
            // shouldnt return, if you return, the function ends, then it doesnt go into the next if statement
            printLeafNodes(out, node->right.get());;
        }
        if (node->left)
        {
            printLeafNodes(out, node->left.get());
        }
    }
};

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &out, const BST<T1,T2> &bst)
{
    bst.printLeafNodes(out, bst.head.get());
    return out;
}

int main()
{
    BST<char, int> new_bst;
    new_bst.insert(std::pair<char,int>('e', 10));
    new_bst.insert(std::pair<char,int>('a', 10));
    new_bst.insert(std::pair<char,int>('c', 10));
    new_bst.insert(std::pair<char,int>('b', 10));
    new_bst.insert(std::pair<char,int>('g', 10));
    new_bst.insert(std::pair<char,int>('f', 10));
    new_bst.insert(std::pair<char,int>('h', 10));
    new_bst.emplace('a', 20);



    std::cout << new_bst['q'] <<std::endl;
    std::cout << new_bst <<std::endl;
}