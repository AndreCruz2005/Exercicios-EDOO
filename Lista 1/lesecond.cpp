#include <cstddef>
#include <stdexcept>
#include <iostream>
#include <string>

using namespace std;

template <class T>
class DynamicArray
{
private:
    void expand()
    {
        maxSize *= 2;
        T *temp = new T[maxSize];
        for (size_t i = 0; i < currentSize; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    bool isFull() { return currentSize == maxSize; }

    void isOutOfBounds(size_t idx)
    {
        if (idx > currentSize)
        {
            throw runtime_error("Index out of bounds!");
        }
    }

protected:
    T *arr;
    size_t currentSize;
    size_t maxSize;

public:
    DynamicArray(size_t size)
    {
        maxSize = size;
        currentSize = 0;
        arr = new T[maxSize];
    }

    DynamicArray()
    {
        maxSize = 1;
        currentSize = 0;
        arr = new T[maxSize];
    }

    ~DynamicArray()
    {
        delete[] arr;
    }

    void push(T item, size_t idx)
    {
        isOutOfBounds(idx);

        if (isFull())
        {
            expand();
        }

        for (size_t i = currentSize; i > idx; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[idx] = item;
        currentSize++;
    }

    T remove(size_t idx)
    {
        isOutOfBounds(idx);
        T item = arr[idx];
        for (size_t i = idx; i < currentSize - 1; i++)
        {
            arr[i] = arr[i + 1];
        }
        currentSize--;
        return item;
    }

    T &operator[](size_t idx)
    {
        isOutOfBounds(idx);
        return arr[idx];
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }
};

// Last in, first out
class TokenStack : public DynamicArray<string>
{
private:
    bool valid = true;

public:
    void put(string item)
    {
        if (item == "]" || item == ")")
        {
            bool ok = (!this->isEmpty() &&
                       ((top() == "(" && item == ")") ||
                        (top() == "[" && item == "]")));

            if (ok)
            {
                pop();
            }
            else if (!ok)
            {
                valid = false;
            }
        }
        else
        {
            this->push(item, this->currentSize);
        }
    }

    string &top()
    {
        return this->arr[this->currentSize - 1];
    }

    void pop()
    {
        this->remove(this->currentSize - 1);
    }

    bool isValid()
    {
        return valid;
    }
};

int main()
{
    size_t cases;
    cin >> cases;
    cin.ignore();
    for (size_t c = 0; c < cases; c++)
    {
        TokenStack tokens;
        string input;
        getline(cin, input);

        for (size_t i = 0; i < input.size(); i++)
        {
            if (tokens.isValid())
            {
                string s(1, input[i]);
                tokens.put(s);
            }
            else
            {
                break;
            }
        }

        cout << ((tokens.isValid() && tokens.isEmpty()) ? "Yes" : "No") << endl;
    }
    return 0;
}