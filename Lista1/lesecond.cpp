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
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void Add(T v)
    {
        Node *newNode = new Node(v);
        newNode->next = head;
        head = newNode;

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
};

int main()
{
    unsigned int cases;
    cin >> cases;

    for (auto c = 0; c < cases; c++)
    {
        LinkedStack<char> S;
        bool valid = true;
        string input;
        cin >> input;

        for (const auto &ch : input)
        {
            if (ch == '[' || ch == '(')
            {
                S.Add(ch);
            }
            else
            {
                char top = S.Pop();
                valid = (ch == ')' && top == '(') || (ch == ']' && top == '[');

                if (!valid)
                    break;
            }
        }
        cout << (valid && !S.Length() ? "Yes" : "No") << endl;
    }
    return 0;
}