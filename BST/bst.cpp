#include <iostream>
#include <utility>
#include <memory>

// Better call them, key and value.
template <typename T1, typename T2>
class BST
{
    struct Node
    {
        // Next time, remember the formatting.
        Node(T1 c, T2 v)
        : key{c}
        , value{v}
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
    // check https://en.cppreference.com/w/cpp/container/map
    // usually we will define some type alias here
    // Dont use the T1 and T2 directly, try to use value_type and key_type
    using value_type = T2;
    using key_type = T1;

    // Check what is default
    // Check what is rule of 5
    BST() = default;

    // Question, Why not
    // std::pair<const T3&, T4>
    // std::pair<T3, const T4&>
    // std::pair<T3, T4>&
    // const std::pair<T3, T4>
    // Pick the one you think it is the best suit, and tell me why
    template <typename NewKey, typename T4>
    void insert(std::pair<T3, T4> pair) noexcept
    {
        static_assert(std::is_constructible_v<T1,T3>);
        static_assert(std::is_constructible_v<T2,T4>);

        // Why!!!!!! Dont!!!! what if the node exist? you just need to replace the value. Why a new node always!???
        auto temp = std::make_unique<Node>(std::forward<T3>(pair.first), std::forward<T4>(pair.second));


        // I dont like this implemenation. There is a better way to do it. Rethink
        // Hints:  You can have private function, and do recursive call. ACtually, the tree is the best place to try out recursion
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

    // No, please. Your implemenation loss the meaning of emplace.
    // In short, in ::insert(), just a few lines and it will become emplace. remember, what is emplace?
    // Emplace is the function create the node without any extra overhead. Create the node directly at the location it should be
    template <typename ...Args>
    void emplace(Args &&...args){


        // static_assert(std::is_constructible_v<BST, Args...>);
        insert(std::pair<Args ...>(std::forward<Args>(args)...));

    }

    //1. Why non-cont? where is conf version?
    // what if the key is not found?
    //2. It is not forwarding reference. Please check why it is not forwarding reference
    T2& operator[](T1 &&key){
        auto cur = find(std::forward<T1>(key));
        if(key == cur->key){ // Sometime new line, sometime dont. You should better keep one style only.
            return cur->value;
        }else{
            T2 value = 0;
            insert(std::pair<T1,T2>(std::forward<T1>(key), value)); // Why? what if the user dont want to insert new? what if the tree is `const tree`?
            return value;
        }
    }

    // If const, return const Node*
    // if non-const, return Node*
    // By the way, I dont like Node *find
    // I prefer Node* find
    // By the way. What is the difference between `const Node*`` and `Node const*`` and `const Node const*``
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

    // Why return Node*?
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

// The same, I prefere `std::ostream&` rather than `std::ostream &`
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
    new_bst.emplace('a', 20); // the syntax look alike emplace, but the implemenation is not emplace.


    std::cout << new_bst['q'] <<std::endl;
    std::cout << new_bst <<std::endl;
}

/*
A bit disapointed. Something you did it correctly, but wrong again this time. Check all comments, and reply them one by one.
I dont expect you to have a quick reply, but a detail and correct one. You were able to learn it, why unlearn it again? For instace,
insert vs emplace
forwarding reference vs r-reference
constness
Some function designs

5/10

Sorry to be harsh. but you could do better than this
*/

template<std::size_t MAX_SIZE_V>
class FixLengthString
{
public:
  using value_type = char;
  static constexpr auto MAX_SIZE = MAX_SIZE_V

  explicit FixLengthString(std::string_view str)
  {
    *this = str;
  }

  FixLengthString(const FixLengthString&) noexcept = default;
  FixLengthString(FixLengthString&&) noexcept = default;

  FixLengthString& operator=(const FixLengthString&) noexcept = default;
  FixLengthString& operator=(FixLengthString&&) noexcept = default;

  FixLengthString& operator=(std::string_view str)
  {
    data.fill('\0');
    std::copy(str.begin(), std::min(MAX_SIZE, str.size()), data.begin());
  }

  std::size_t getLength() const noexcept
  {
    return ::strnlen(data.data(), MAX_SIZE);
  }

  operator std::string_view() const noexcept
  {
    return {data.data(), getLength};
  }

  friend std::ostream& operator<<(std::ostream& os, const FixLengthString& str)
  {
    os.write(data.data(), getLength());
    return os;
  }

private:
  std::array<char, MAX_SIZE> data;
};
