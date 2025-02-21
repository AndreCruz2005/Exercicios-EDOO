#include <iostream>
#include <string>
using namespace std;

template <typename T>
class LinkedStack
{
    struct Node
    {
        Node *next;
        T value;

        Node(T v) : value(v), next(nullptr) {}
    };

    Node *head;
    size_t size;

public:
    LinkedStack()
    {
        head = nullptr;
        size = 0;
    }

    ~LinkedStack()
    {
        Clear();
    }

    void Add(T v)
    {
        Node *newNode = new Node(v);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head = newNode;
        }

        size++;
    }

    T Pop()
    {
        if (head)
        {
            T it = head->value;
            Node *temp = head;
            head = head->next;
            delete temp;
            size--;
            return it;
        }
        return T();
    }

    size_t Length()
    {
        return size;
    }

    void Clear()
    {
        while (size)
        {
            Pop();
        }
    }
};

int main()
{
    unsigned int cases;
    cin >> cases;
    cin.ignore();

    for (auto c = 0; c < cases; c++)
    {
        LinkedStack<char> S;
        bool valid = true;
        string input;
        getline(cin, input);

        for (auto ch : input)
        {
            if (ch == '[' || ch == '(')
            {
                S.Add(ch);
                continue;
            }

            char top = S.Pop();
            bool ok = (ch == ')' && top == '(') || (ch == ']' && top == '[');
            if (!ok)
            {
                valid = false;
                break;
            }
        }
        cout << (valid && !S.Length() ? "Yes" : "No") << endl;
    }
    return 0;
}