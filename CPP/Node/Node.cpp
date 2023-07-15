#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int data) : data(data) {}
};
void print(Node *head)
{
    while (head != nullptr)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
void printRecursive(Node *head)
{
    if (head != nullptr)
    {
        cout << head->data << " ";
        printRecursive(head->next);
    }
    else
        cout << "\n";
}
void printRecursiveReversed(Node *head)
{
    if (head != nullptr)
    {
        printRecursiveReversed(head->next);
        cout << head->data << " ";
    }
}
Node *find(Node *head, int val)
{
    while (head != nullptr)
    {
        if (head->data == val)
            return head;
        head = head->next;
    }
}

int main()
{
    Node *n1 = new Node(10);
    Node *n2 = new Node(20);
    Node *n3 = new Node(30);
    Node *n4 = new Node(40);
    Node *n5 = new Node(50);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = nullptr;

    cout << "Print with arrow:\n";
    cout << n1->next->data << endl; // Test 1
    cout << "Print with print function:\n";
    print(n1);
    cout << "Print with print function in recursive way:\n";
    printRecursive(n1);
    cout << "Print with print function in recursive way [REVERSED]:\n";
    printRecursiveReversed(n1);
    cout << "\nFind Value 40 in the nodes:\n";
    cout << (find(n1, 40))->data;
}
