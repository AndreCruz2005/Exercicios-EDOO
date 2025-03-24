#include <iostream>
class BinarySearchTree
{
    struct Node
    {
        Node *left = nullptr;
        Node *right = nullptr;
        int value;
        Node(int v) { value = v; }
    };

    Node *root = nullptr;

    Node *Add(Node *curr, int value)
    {
        if (!curr)
        {
            return new Node(value);
        }
        if (curr->value > value)
        {
            curr->left = Add(curr->left, value);
        }
        else
        {
            curr->right = Add(curr->right, value);
        }
        return curr;
    }

    void pre(Node *n)
    {
        if (!n)
            return;
        std::cout << n->value << " ";
        pre(n->left);
        pre(n->right);
    }

    void in(Node *n)
    {
        if (!n)
            return;
        in(n->left);
        std::cout << n->value << " ";
        in(n->right);
    }

    void post(Node *n)
    {
        if (!n)
            return;
        post(n->left);
        post(n->right);
        std::cout << n->value << " ";
    }

public:
    void Add(int value) { root = Add(root, value); }

    void Printout()
    {
        std::cout << "Pre order : ";
        pre(root);
        std::cout << "\n";

        std::cout << "In order  : ";
        in(root);
        std::cout << "\n";

        std::cout << "Post order: ";
        post(root);
        std::cout << "\n";
    }
};

int main()
{

    int amount;
    std::cin >> amount;

    BinarySearchTree BST;

    while (amount--)
    {
        int data;
        std::cin >> data;

        BST.Add(data);
    }

    BST.Printout();

    return 0;
}
