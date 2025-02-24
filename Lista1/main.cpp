#include <cstddef>
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
        for (int i = 0; i < currentSize; i++)
        {
            temp[i] = arr[i];
        }
        delete[] arr;
        arr = temp;
    }

    bool isFull() { return currentSize == maxSize; }

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
        return arr[idx];
    }

    bool isEmpty()
    {
        return currentSize == 0;
    }
};

// Last in, first out
class Ferry : public DynamicArray<int>
{
private:
    int centimeters;         // Length of the ferry in centimeters
    int carsTotalOccupation; // Total length of cars in the ferry
    bool side;               // 0 = left, 1 = right

public:
    Ferry(int size, int l) : DynamicArray<int>(size), centimeters(l * 100), carsTotalOccupation(0), side(0) {}

    void addCar(int car)
    {
        carsTotalOccupation += car;
        this->push(car, this->currentSize);
    }
    int getCar()
    {
        int car = this->remove(this->currentSize - 1);
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

    bool hasSpace(int sizeOfNewCar) { return centimeters - carsTotalOccupation >= sizeOfNewCar; }
};

// First in, first out
class Shore : public DynamicArray<int>
{
public:
    void addCar(int car)
    {
        this->push(car, this->currentSize);
    }
    int getCar()
    {
        return this->remove(0);
    }
};

int main()
{

    int cases;
    cin >> cases;

    for (auto c = 0; c < cases; c++)
    {
        int trips = 0;
        int l, m;
        cin >> l >> m;

        Ferry Boat(1, l);
        Shore LeftShore;
        Shore RightShore;

        for (int car = 0; car < m; car++)
        {
            int carLength;
            string side;

            cin >> carLength >> side;

            Shore &shore = (side == "left") ? LeftShore : RightShore;
            shore.addCar(carLength);
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

        cout << trips << endl;
    }

    return 0;
}