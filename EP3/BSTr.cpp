#include <string>
#include <iostream>
#include <vector>

using namespace std;

class BinarySearchTree {
    struct node {
        int key;
        struct node *left = nullptr;
        struct node *right = nullptr;

        node(int v) {
            key = v;
        }
    };

    node *root = nullptr;
    unsigned int occupation = 0;

    node *add(node *n, int value) {
        if (!n) {
            occupation++;
            return new node(value);
        }
        if (n->key > value) {
            n->left = add(n->left, value);
        } else {
            n->right = add(n->right, value);
        }
        return n;
    }

    node *getmin(node *n) {
        if (n->left == nullptr) return n;
        return getmin(n->left);
    }

    node *deletemin(node *n) {
        if (n->left == nullptr) return n->right;
        n->left = deletemin(n->left);
        return n;
    }


    node *remove(node *n, int rem) {
        if (!n) {
            return n;
        }

        if (n->key > rem) {
            n->left = remove(n->left, rem);
        } else if (n->key < rem) {
            n->right = remove(n->right, rem);
        } else {
            occupation--;
            if (n->left == nullptr) {
                return n->right;
            } else if (n->right == nullptr) {
                return n->left;
            } else {
                node *temp = getmin(n->right);
                n->key = temp->key;
                n->right = deletemin(n->right);
                delete temp;
            }
        }

        return n;
    }

    void post(node *n) {
        if (!n) {
            return;
        }
        post(n->left);
        post(n->right);
        cout << n->key << endl;
    }

public:
    void add(int value) {
        root = add(root, value);
    }

    void remove(int rem) {
        root = remove(root, rem);
    }

    void printout() {
        cout << occupation << endl;
        post(root);
    }
};

int main() {
    BinarySearchTree BST;
    int cases;
    cin >> cases;
    while (cases--) {
        string command;
        int value;
        cin >> command >> value;
        if (command == "ins") {
            BST.add(value);
        } else {
            BST.remove(value);
        }
    }
    BST.printout();
    return 0;
}
