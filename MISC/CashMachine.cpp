#include <iostream>
#include <string>
using namespace std;

template <typename V>
class LinkedList
{
    struct Node
    {
        Node *next;
        V item;

        Node(V val) : next(nullptr), item(val) {}
    };

    Node *getNode(size_t idx)
    {
        size_t pos = 0;
        Node *temp = head;
        while (pos < idx && temp)
        {
            temp = temp->next;
            pos++;
        }
        if (!temp)
        {
            throw std::out_of_range("The index " + std::to_string(idx) + " is out of bounds.");
        }

        return temp;
    }

    void pushAtHead(V item)
    {
        Node *newNode = new Node(item);
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

    Node *head;
    size_t size;

public:
    LinkedList()
    {
        head = nullptr;
        size = 0;
    }

    void push(V item)
    {
        push(item, size);
    }

    void push(V item, const size_t idx)
    {
        if (idx == 0)
        {
            return pushAtHead(item);
        }
        Node *nodeAtPos = getNode(idx - 1);
        Node *newNode = new Node(item);
        newNode->next = nodeAtPos->next;
        nodeAtPos->next = newNode;
        size++;
    }

    V &operator[](const size_t idx)
    {
        return getNode(idx)->item;
    }

    void remove(const size_t idx)
    {
        if (!head || idx >= size)
        {
            throw std::runtime_error(
                "Cannot remove item at index " + std::to_string(idx) + ". Idx is out of bounds.");
        }
        else if (idx == 0)
        {
            const Node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node *nodeAtPos = getNode(idx - 1);
            Node *temp = nodeAtPos->next;
            nodeAtPos->next = temp->next;
            delete temp;
        }
        size--;
    }

    size_t length()
    {
        return size;
    }
};

template <typename K, typename V>
class HashTable
{
private:
    struct Entry
    {
        K key;
        V value;
    };

    typedef LinkedList<Entry> Bucket;

    Bucket *table;
    size_t tableSize;

    size_t hashKey(const std::string &key)
    {
        size_t hash = 0;
        for (const auto &c : key)
        {
            hash += c;
        }
        return hash % tableSize;
    }

    size_t hashKey(const K key)
    {
        string k = std::to_string(key);
        return hashKey(k);
    }

    void Add(const K &key, V value)
    {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.length(); i++)
        {
            if (bucket[i].key == key)
            {
                bucket[i].value = value;
                return;
            }
        }
        Entry newEntry;
        newEntry.key = key;
        newEntry.value = value;
        bucket.push(newEntry);
    }

public:
    HashTable()
    {
        tableSize = 10;
        table = new Bucket[tableSize];
    }

    ~HashTable()
    {
        delete[] table;
    }

    V &operator[](K key)
    {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.length(); i++)
        {
            if (bucket[i].key == key)
            {
                return bucket[i].value;
            }
        }
        Add(key, V());
        return operator[](key);
    }

    void remove(K key)
    {
        Bucket &bucket = table[hashKey(key)];
        for (size_t i = 0; i < bucket.length(); i++)
        {
            if (bucket[i].key == key)
            {
                bucket.remove(i);
            }
        }
    }
};

int findAmountOfMoney(HashTable<int, int> &amounts, LinkedList<int> &bills, int moneyGoal, int closestMoney, int currentMoney)
{
    if (currentMoney > moneyGoal)
    {
        return closestMoney;
    }

    if (closestMoney < currentMoney)
    {
        closestMoney = currentMoney;
    }

    for (auto i = 0; i < bills.length(); i++)
    {
        if (amounts[bills[i]] > 0)
        {
            // Add money
            amounts[bills[i]]--;
            currentMoney += bills[i];

            // Recursion
            const int result = findAmountOfMoney(amounts, bills, moneyGoal, closestMoney, currentMoney);
            closestMoney = result > closestMoney ? result : closestMoney;

            // Backtracking
            currentMoney -= bills[i];
            amounts[bills[i]]++;
        }
        else
        {
            continue;
        }
    }

    return closestMoney;
}

int main()
{
    string input;

    while (getline(cin, input))
    {
        if (input == "")
            break;

        HashTable<int, int> dict;
        LinkedList<int> numbers;
        string number = "";

        for (const auto &ch : input)
        {
            if (ch == ' ')
            {
                if (number != "")
                {
                    numbers.push(stoi(number));
                }
                number = "";
                continue;
            }

            number += ch;
        }

        numbers.push(stoi(number));

        int desiredMoney = numbers[0];
        LinkedList<int> bills;

        for (auto i = 2; i < number.length(); i += 2)
        {
            bills.push(i + 1);
            dict[numbers[i + 1]] = numbers[i];
        }

        cout << findAmountOfMoney(dict, bills, desiredMoney, 0, 0) << endl;
    }

    return 0;
}
