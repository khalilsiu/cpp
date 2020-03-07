#include <iostream>
#include <utility>
#include <memory>
#include <map>



template <typename key1, typename value1>
class BST
{
    struct Node
    {
        Node(key1 c, value1 v)
            : key{c}, value{v}
        {
        }
        key1 key;
        value1 value;
        std::unique_ptr<Node> left = nullptr;
        std::unique_ptr<Node> right = nullptr;
        Node *prev = nullptr;
    };

private:
    std::unique_ptr<Node> head = nullptr;
    template <typename key2, typename value2>
    void recursiveInsert(std::unique_ptr<Node>& ptr, const std::pair<key2, value2>& pair) noexcept
    {
        // I am using std::unique_ptr<Node>& because I want to be able to use the unique_ptr directly, moving the unique_ptr does not work
        // std::cout << pair.first << "::"<< pair.second << std::endl;
        auto cur = ptr.get();
        if(cur){
            if(pair.first > cur->key){
                recursiveInsert(cur->right, pair);
            }else if (pair.first < cur-> key) {
                recursiveInsert(cur->left, pair);
            }else{
                cur->value = pair.second;
            }
        }else{
            auto temp = std::make_unique<Node>(pair.first, pair.second);
            ptr = std::move(temp);
        }
    }

    template <typename ...Args>
    void recursiveEmplace(std::unique_ptr<Node>& ptr, Args&& ...args) noexcept
    {
        auto cur = ptr.get();

        auto pair = std::pair<Args...>(std::forward<Args>(args)...);
        if (cur){
             if(pair.first > cur->key){
                recursiveEmplace(cur->right, (args)...);
            }else if (pair.first < cur-> key) {
                recursiveEmplace(cur->left, (args)...);
            }else{
                // if key exists, there will be no insertion
                return;
            }
        }else{
            auto temp = std::make_unique<Node>(pair.first, pair.second);
            ptr = std::move(temp);
        }
    }

public:
    using key_t = key1;
    using value_t = value1;
    BST() = default;


    template <typename key3, typename value3>
    void insert(const std::pair<key3, value3>& pair) noexcept
    // I think it is const std::pair<key3, value3>& because i think both key and value shall not be changed within the function
    // not just the key or the value
    // it is a reference because we do not want to directly copy the pair object, but to use the object's resources directly (faster)
    {
        static_assert(std::is_constructible_v<key_t,key3>);
        static_assert(std::is_constructible_v<value_t,value3>);
        recursiveInsert(head, pair);
    }

    template <typename ...Args>
    void emplace(Args&& ...args) noexcept
    {
        recursiveEmplace(head, std::forward<Args>(args)...);
    }

    const std::optional<value_t> operator[](key_t&& key) const noexcept
    {
        auto cur = find(key);
        if (cur && key == cur->key){
            return cur->value;
        }else{
            return std::nullopt;
        }
    }

    const Node* find(const key_t& key) const noexcept
    // const Node* is a variable pointer to a const Node, the Node member data cannot be changed
    // Node const* is the same as the above, a variable pointer to a const Node (because const applies to what is immediately on its left)
    // Node* const is a const pointer to a variable Node, the address of the pointer cannot be changed, but the Node member data can be changed
    // const Node const* should be invalid (duplicate 'const' declaration specifier)
    // const Node * const is a const pointer to a const Node where none of the address and member data could be changed
    {
        auto cur = head.get();
        while (cur)
        {
            if (key > cur->key)
            {
                cur = cur->right.get();
            }
            else if (key < cur->key)
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

    Node* find(const key_t& key) noexcept
    {
        auto cur = head.get();
        while (cur)
        {
            if (key > cur->key)
            {
                cur = cur->right.get();
            }
            else if (key < cur->key)
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

    template <typename key3, typename value3>
    friend std::ostream& operator<<(std::ostream& out, const BST<key3,value3>& bst);

    void printLeafNodes(std::ostream& out, Node *node) const
    {
        if (!node)
        {
            throw std::runtime_error("BST has no element");
        }
        out << node->key << "::" << node->value << std::endl;
        if (!node->left && !node->right)
        {
            return;
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

template <typename key, typename value>
std::ostream& operator<<(std::ostream& out, const BST<key,value> &bst)
{
    bst.printLeafNodes(out, bst.head.get());
    return out;
}

int main()
{
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
    new_bst['i'];




    std::cout << *new_bst['a'] <<std::endl;
    // std::cout << (new_bst.find('k'))->value <<std::endl;

    // std::map<char,int> mapp{std::pair<char, int>('a',2), std::pair<char, int>('b',3)};
    // std::cout << mapp['a'] << std::endl;
    // std::cout << (mapp.find('a')->second) << std::endl;
    // std::cout << (mapp.find('b')->second) << std::endl;
    // mapp.emplace('b',2);
    // std::cout << mapp.find('b')->second << std::endl;



}