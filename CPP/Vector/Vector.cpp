#include <cassert>
#include <iostream>
using namespace std;
class Vector
{
private:
    /* data */
    int *arr = nullptr;
    int size = 0;
    int capacity = 0;

public:
    // Constructor
    Vector(int size) : size(size) // Initialize size with passed value
    {
        if (size < 0) // if there is an error
            size = 1;
        capacity = 2 * size;       // can be changed
        arr = new int[capacity]{}; // create array with the desired size
    }
    // Destructor
    ~Vector()
    {
        delete[] arr;  // Remove Content of array to free memory
        arr = nullptr; // null pointer
    }
    // Vector = {Front , ... , Back}

    // GETTERS
    // Get any value
    int get(int i) // i = index
    {
        assert(i >= 0 && i < size);
        return arr[i];
    }
    // Get First value
    int getFront()
    {
        return arr[0];
    }
    // Get Last Value
    int getBack()
    {
        return arr[size - 1];
    }
    // Get length of Vector
    int length()
    {
        return size;
    }

    // SETTER
    void set(int i, int val)
    {
        assert(i >= 0 && i < size);
        arr[i] = val;
    }

    // PushBack (append)
    void PushBack(int val)
    {
        if (size == capacity) // if the reserved storage of the vector is full extend it
            extendCapcity();
        arr[size++] = val; // push the passed value to the array
    }

    // Insert
    void insert(int val, int index)
    {
        assert(index >= 0 && index < size); // if the passed index is out of range generate error
        if (size == capacity)               // if the reserved storage of the vector is full extend it
            extendCapcity();
        for (int i = size - 1; i >= index; i--) // shift the values after the desired index
        {
            arr[i + 1] = arr[i];
        }
        arr[index] = val; // assign the desired index with the desired value
        size++;           // increase the size
    }

    // Extend the capacity of the vector
    void extendCapcity()
    {
        capacity *= 2;
        int *cpyarr = nullptr;         // New pointer
        cpyarr = new int[capacity];    // New Array with increased size
        for (int i = 0; i < size; i++) // Copy all values of old array to new one
        {
            cpyarr[i] = arr[i];
        }
        delete arr;   // Delete old one from memory (Call the destructor)
        arr = cpyarr; // Make the pointer arr point to the new array
    }

    // Print Vector
    void print()
    {
        cout << "{";
        for (int i = 0; i < size; i++)
        {
            if (i == (size - 1))
                cout << " " << arr[i] << " ";
            else
                cout << " " << arr[i] << " ,";
        }
        cout << "}\n";
    }

    // Find value in the vector return index of it
    // Unless Finding it , return -1
    int find(int val)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == val)
                return i;
        }
        return -1;
    }

    // Rotate Right
    void rightRotate()
    {
        int lastelement = arr[size - 1];
        for (int i = size - 1; i >= 0; i--)
        {
            arr[i] = arr[i - 1];
        }
        arr[0] = lastelement;
    }

    // Rotate Left
    void leftRotate()
    {
        int firstelement = arr[0];
        for (int i = 0; i < size; i++)
        {
            arr[i] = arr[i + 1];
        }
        arr[size - 1] = firstelement;
    }

    // Rotate Right with no of steps
    void rightRotateTimes(int times)
    {

        int noOfRotates = times % size;
        if (noOfRotates != 0)
        {
            int lastelements[noOfRotates] = {};

            for (int i = 0; i < noOfRotates; i++)
            {
                lastelements[i] = arr[size - noOfRotates + i];
            }

            for (int i = size - 1; i >= 0; i--)
            {
                arr[i] = arr[i - noOfRotates];
            }

            for (int i = 0; i < noOfRotates; i++)
            {
                arr[i] = lastelements[i];
            }
        }
    }

    // delete
    void pop(int index)
    {
        assert(index >= 0 && index < size);
        size--;
        for (int i = index; i < size; i++)
        {
            arr[i] = arr[i + 1];
        }
    }

    int findTransposition(int value)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i] == value)
            {
                pop(i);
                insert(value, i - 1);
                return i - 1;
            }
        }
        return -1;
    }
};

int main()
{
    int addedValue = 20;
    int index = 2;

    // Create vector
    Vector v(10);

    // Assign values of vector
    for (int i = 0; i < v.length(); i++)
    {
        v.set(i, i);
    }

    // Print Values
    cout << "\nThe Vector :\n";
    v.print();

    // Right Rotate
    cout << "\nThe Vector After Right Rotate with steps :\n";
    v.rightRotateTimes(27);
    v.print();

    // Push Back (Append)
    cout << "\nThe Vector After Push Back " << addedValue << " :\n";
    v.PushBack(addedValue);
    v.print();

    // Insert
    cout << "\nThe Vector After Insert " << addedValue << " in index " << index << " :\n";
    v.insert(addedValue, index);
    v.print();

    // Right Rotate
    cout << "\nThe Vector After Right Rotate :\n";
    v.rightRotate();
    v.print();

    // Left Rotate
    cout << "\nThe Vector After Left Rotate :\n";
    v.leftRotate();
    v.print();

    // Delete
    cout << "\nThe Vector After Deleting index " << index << " :\n";
    v.pop(index);
    v.print();

    cout << "\nThe index of " << addedValue << " in :\n";
    v.print();
    cout << "is " << v.findTransposition(addedValue);
}
