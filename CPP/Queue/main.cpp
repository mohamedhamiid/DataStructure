#include <iostream>
#include <cassert>
using namespace std;

class Queue
{
private:
    /* data */
    int front;
    int rear;
    int size = 5;
    int queue[5];

public:
    Queue()
    {
        front = -1;
        rear = -1;
    }
    bool isFull()
    {
        /* Circular */
        if ((rear + 1) % size == front)
            return true;
        else
            return false;
    }
    bool isEmpty()
    {
        if (front == -1)
            return true;
        else
            return false;
    }
    void enqueue(int x)
    {
        if (isFull())
        {
            cout << "The queue is full" << endl;
        }
        else
        {
            if (front == -1)
                front = 0;
            rear = (rear + 1) % size;
            queue[rear] = x;
        }
    }
    int dequeue()
    {
        if (isEmpty())
        {
            cout << "The queue is empty" << endl;
            return -1;
        }
        else
        {
            int element = queue[front];
            front = (front + 1) % size;
            return element;
        }
    }

    void print()
    {
        for (int i = front; i != rear; i = ((i + 1) % size))
        {
            cout << queue[i] << " ";
        }
        cout << queue[rear] << " ";
        cout << endl;
    }
};

int main()
{
    Queue q;
    for (int i = 0; i < 5; i++)
    {
        q.enqueue(i);
    }
    q.print();
    cout << q.dequeue() << endl;
    q.enqueue(10);
    q.print();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();

    q.print();
}
