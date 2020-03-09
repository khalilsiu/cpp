#include <iostream>
#include <utility>
#include <memory>
#include <optional>
#include <map>

template <typename Key, typename Value>
class BST
{
    struct Node
    {
        Node(const Key& c, const Value& v)
        : key{c}
        , value{v}
        {
        }

        const Key key; // Guess why it should be const?
        Value value;
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;
        Node* prev = nullptr;
    };

public:
    template<typename T>
    struct QueryResult : std::optional<std::reference_wrapper<T>>
    {
        using Base = std::optional<std::reference_wrapper<T>>;

        using Base::Base;
        using Base::operator bool;

        decltype(auto) operator*() const
        {
            if (*this)
            {
                return Base::operator*().operator T&();
                // std::reference_wrapper<T>& a === Base::operator*();
                // a.operator T&() === T&
            }
            throw std::runtime_error("Null optional");
        }
    };

    using key_t = Key;
    using value_t = Value;

    BST() = default;

    template <typename NewKey, typename NewValue>
    void insert(const std::pair<NewKey, NewValue>& pair) noexcept
    // I think it is const std::pair<key3, value3>& because i think both key and value shall not be changed within the function
    // not just the key or the value
    // it is a reference because we do not want to directly copy the pair object, but to use the object's resources directly (faster)
    {
        static_assert(std::is_constructible_v<key_t, NewKey>);
        static_assert(std::is_constructible_v<value_t, NewValue>);
        recursiveInsert(head, nullptr, pair);
    }

    template <typename NewKey, typename ...Args>
    void emplace(NewKey&& key, Args&& ...args) noexcept
    {
        static_assert(std::is_constructible_v<key_t, NewKey>);
        static_assert(std::is_constructible_v<value_t, Args...>);
        recursiveEmplace(head, std::forward<NewKey>(key), std::forward<Args>(args)...);
    }

    // 1. why key_t&&? In this function, key_t is known and it is not a template
    // const std::optional<value_t> operator[](key_t&& key) const noexcept
    // 2. I think you meant
    // std::optional<const value_t&> operator[](key_t&& key) const noexcept
    // See the return value
    // But reference cannot put inside the optional. so, here is a possible way
    QueryResult<const value_t> operator[](const key_t& key) const noexcept
    {
        return getImpl<const value_t>(*this, key);
    }

    QueryResult<value_t> operator[](const key_t& key) noexcept
    {
        return getImpl<value_t>(*this, key);
    }

    // As you have operator [] already, can you name a better difference between [] and find?
    // I know they can be the same, but from the user point of view, how to make it easier to use?
    const Node* find(const key_t& key) const noexcept
    {
        return findImpl(head, key);
    }

    Node* find(const key_t& key) noexcept
    {
        return findImpl(head, key);
    }

    friend std::ostream& operator<<(std::ostream& out, const BST& bst)
    {
        bst.printLeafNodes(out, bst.head);
        return out;
    }

private:
    template <typename key2, typename value2>
    void recursiveInsert(std::unique_ptr<Node>& ptr, Node* parent, const std::pair<key2, value2>& pair) noexcept
    {
        if(auto cur = ptr.get(); ptr)
        {
            if(pair.first > cur->key)
            {
                recursiveInsert(cur->right, cur, pair);
            }
            else if (pair.first < cur-> key)
            {
                recursiveInsert(cur->left, cur, pair);
            }
            else
            {
                cur->value = pair.second;
            }
        }
        else
        {
            ptr = std::make_unique<Node>(pair.first, pair.second);
            ptr->prev = parent;
        }
    }

    // Can you try to finish this function?
    // Key is a const ref
    // Value is created by argument pack
    template <typename ...Args>
    void recursiveEmplace(std::unique_ptr<Node>& ptr, Args&& ...args) noexcept
    {
        // TODO
    }

    template<typename T>
    static auto findImpl(T&& currNode, const key_t& key) noexcept
    {
        auto cur = std::forward<T>(currNode).get();
        while (cur)
        {
            if (key > cur->key)
            {
                cur = cur->right.get();
            }
            else if (key < cur->key)
            {
                cur = cur->left.get();
            }
            else
            {
                return cur;
            }
        }
        return cur = nullptr;
    }

    template<typename T, typename BST_T>
    static auto getImpl(BST_T&& tree, const key_t& key) noexcept
    {
        auto cur = std::forward<BST_T>(tree).find(key);
        if (cur)
        {
            return QueryResult<T>{cur->value};
        }
        else
        {
            return QueryResult<T>{std::nullopt};
        }
    }

    void printLeafNodes(std::ostream& out, const std::unique_ptr<Node>& node) const
    {
        // Check this out, please tell me what is this function
        // https://en.cppreference.com/w/cpp/memory/unique_ptr/operator_bool
        // TODO I need the output to be
        // ROOT_KEY::VALUE
        // --LEVEL1_KEY1::VALUE1
        // ----LEVEL2_KEY2::VALUE2
        // --LEVEL1_RIGHT::VALUE3
        if (node)
        {
            out << node->key << "::" << node->value << std::endl;

            printLeafNodes(out, node->right);
            printLeafNodes(out, node->left);
        }
    }

private:
    std::unique_ptr<Node> head = nullptr;
};

int main()
{
    // Try BST<int, std::string>
    BST<char, int> new_bst;
    std::pair<char,int> pair = std::pair<char,int>('e', 1);
    new_bst.insert(pair);
    new_bst.insert(std::pair<char,int>('a', 2));
    new_bst.insert(std::pair<char,int>('c', 3));
    new_bst.insert(std::pair<char,int>('b', 4));
    new_bst.insert(std::pair<char,int>('g', 5));
    new_bst.insert(std::pair<char,int>('f', 6));
    new_bst.insert(std::pair<char,int>('h', 7));
    new_bst.emplace('k', 8);

    std::cout << (new_bst['i'] ? "true" : "false") << std::endl;
    std::cout << *new_bst['a'] <<std::endl;

    *new_bst['a'] = 100;
    std::cout << *new_bst['a'] << std::endl;
    std::cout << new_bst << std::endl;
    // std::cout << (new_bst.find('k'))->value <<std::endl;

    // std::map<char,int> mapp{std::pair<char, int>('a',2), std::pair<char, int>('b',3)};
    // std::cout << mapp['a'] << std::endl;
    // std::cout << (mapp.find('a')->second) << std::endl;
    // std::cout << (mapp.find('b')->second) << std::endl;
    // mapp.emplace('b',2);
    // std::cout << mapp.find('b')->second << std::endl;



}
