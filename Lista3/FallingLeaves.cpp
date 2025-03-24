#include <iostream>
#include <string>
#include <vector>
using namespace std;

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
        string character(1, static_cast<char>(n->value));
        std::cout << character;
        pre(n->left);
        pre(n->right);
    }

    void Clear(Node *n)
    {
        if (!n)
        {
            return;
        }
        Clear(n->left);
        Clear(n->right);
        delete n;
    }

public:
    ~BinarySearchTree() { Clear(root); }

    void Add(int value) { root = Add(root, value); }

    void Printout()
    {
        pre(root);
        std::cout << "\n";
    }
};

int main()
{
    vector<vector<string>> Forest;
    vector<string> CurrTree;

    string input;
    while (cin >> input)
    {
        if (input == "*")
        {
            Forest.push_back(CurrTree);
            CurrTree.clear();
            continue;
        }
        if (input == "$")
        {
            Forest.push_back(CurrTree);
            break;
        }
        CurrTree.push_back(input);
    }

    for (const auto &Tree : Forest)
    {
        BinarySearchTree BST;
        for (int i = Tree.size() - 1; i >= 0; i--)
        {
            for (const char c : Tree[i])
            {
                BST.Add(c);
            }
        }
        BST.Printout();
    }
    return 0;
}
