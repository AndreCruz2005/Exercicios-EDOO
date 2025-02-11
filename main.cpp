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
class Ferry : public DynamicArray<size_t>
{
private:
    size_t centimeters;         // Length of the ferry in centimeters
    size_t carsTotalOccupation; // Total length of cars in the ferry
    bool side;                  // 0 = left, 1 = right

public:
    Ferry(size_t size, size_t l) : DynamicArray<size_t>(size), centimeters(l * 100), carsTotalOccupation(0), side(0) {}

    void addCar(size_t car)
    {
        carsTotalOccupation += car;
        this->push(car, this->currentSize);
    }
    size_t getCar()
    {
        size_t car = this->remove(this->currentSize - 1);
        carsTotalOccupation -= car;
        return car;
    }
    void move()
    {
        side = !side;
    }

    bool isRight()
    {
        return side;
    }

    bool hasSpace(size_t sizeOfNewCar) { return centimeters - carsTotalOccupation >= sizeOfNewCar; }
};

// First in, first out
class Shore : public DynamicArray<size_t>
{
public:
    void addCar(size_t car)
    {
        this->push(car, this->currentSize);
    }
    size_t getCar()
    {
        return this->remove(0);
    }
};

int main()
{

    size_t cases;
    cin >> cases;

    for (size_t c = 0; c < cases; c++)
    {
        size_t trips = 0;
        size_t l, m;
        cin >> l >> m;

        Ferry Boat(1, l);
        Shore LeftShore;
        Shore RightShore;

        for (size_t car = 0; car < m; car++)
        {
            size_t carLength;
            string side;

            cin >> carLength >> side;

            if (side == "left")
            {
                LeftShore.addCar(carLength);
            }
            else
            {
                RightShore.addCar(carLength);
            }
        }

        while (!RightShore.isEmpty() || !LeftShore.isEmpty())
        {
            Shore &currentShore = Boat.isRight() ? RightShore : LeftShore;

            // Load up the cars into the boat
            while (!currentShore.isEmpty() && Boat.hasSpace(currentShore[0]))
            {
                Boat.addCar(currentShore.getCar());
            }

            // Move the boat to the other shore
            Boat.move();
            trips++;

            // Unload the cars
            while (!Boat.isEmpty())
            {
                Boat.getCar();
            }
        }

        cout << "Traversals: " << trips << endl;
    }

    return 0;
}