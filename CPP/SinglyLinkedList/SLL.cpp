#include <iostream>
#include <cassert>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node(int data) : data(data) {}
};
class SLL
{
private:
    Node *head = nullptr;
    Node *tail = nullptr;
    int length = 0;
    Node *reverseWithAddress(Node *cur)
    {
        if (cur && cur->next)
        {
            Node *rem = reverseWithAddress(cur->next);
            rem->next = cur;
            cur->next = nullptr;
        }
        return cur;
    }

public:
    SLL()
    {
        head = nullptr;
        tail = nullptr;
    }

    SLL(Node *head, Node *tail)
    {
        this->head = head;
        this->tail = tail;
    }
    ~SLL()
    {
        while (head)
        {
            Node *current = head->next;
            delete head;
            head = current;
        }
        tail = nullptr;
        length = 0;
    }
    int getLength()
    {
        int counter = 0;
        for (Node *current = head; current; current = current->next)
        {
            counter++;
        }
        length = counter;
        return length;
    }
    void print()
    {
        assert(head != nullptr);

        for (Node *current = head; current; current = current->next)
        {
            cout << current->data << " ";
        }
        cout << "\n";
    }
    void insertEnd(int val)
    {
        Node *n = new Node(val);
        n->next = nullptr;
        if (head == nullptr)
        {
            this->head = n;
            this->tail = n;
        }
        else
        {
            tail->next = n;
            this->tail = n;
        }
        length++;
    }
    Node *getNTH(int nth)
    {
        int counter = 0;
        for (Node *current = head; current; current = current->next)
        {
            if (counter == nth)
                return current;
            counter++;
        }
        return nullptr;
    }
    Node *getNTHfromBack(int nth)
    {
        int counter = 0;
        for (Node *current = head; current; current = current->next)
        {
            if (counter == length - nth - 1)
                return current;
            counter++;
        }
        return nullptr;
    }
    int search(int val)
    {
        int index = 0;
        for (Node *current = head; current; current = current->next)
        {
            if (current->data == val)
                return index;
            index++;
        }
        return -1;
    }
    int improvedSearch(int val)
    {
        int index = 0;
        for (Node *current = head, *previous = nullptr; current; current = current->next, previous = current)
        {
            if (current->data == val)
            {
                if (!previous)
                    return index;
                swap(previous->data, current->data);
                return index - 1;
            }
            index++;
        }
        return -1;
    }
    void insertNth(int val, int nth)
    {
        if (nth == 0 || !head)
            insertFront(val);
        else if (nth == getLength())
            insertEnd(val);
        else
        {
            int counter = 0;
            Node *prev;
            Node *tempCurr;
            Node *newNode = new Node(val);
            for (Node *current = head; current; current = current->next)
            {
                if (counter == nth - 1)
                {
                    prev = current;
                }
                else if (counter == nth)
                {
                    tempCurr = current;
                }
                counter++;
            }
            newNode->next = tempCurr;
            prev->next = newNode;
            length++;
        }
    }
    void insertFront(int val)
    {
        Node *n = new Node(val);
        if (head == nullptr)
        {
            this->head = n;
            this->tail = n;
        }
        else
        {
            n->next = head;
            head = n;
        }
        length++;
    }
    void deleteFront()
    {
        if (head != nullptr)
        {
            Node *tempHead = head;
            head = head->next;
            delete[] tempHead;
            tempHead = nullptr;
        }
        length--;
    }
    void deleteBack()
    {
        if (getLength() == 1)
            deleteFront();
        else if (head != nullptr)
        {
            int counter = 0;
            Node *temp;
            for (Node *current = head; current; current = current->next)
            {
                if (counter == (getLength() - 2))
                    temp = current;
                else if (counter == (getLength() - 1))
                {
                    delete current;
                    break;
                }
                counter++;
            }
            length--;
            temp->next = nullptr;
            tail = temp;
        }
    }
    bool isEqual(SLL s)
    {
        if (getLength() != s.getLength())
            return false;
        else
        {
            Node *passCurrent = s.head;
            for (Node *current = head; current; current = current->next)
            {
                if (current->data != passCurrent->data)
                {
                    return false;
                }
                passCurrent = passCurrent->next;
            }
            return true;
        }
    }
    void deleteNth(int nth)
    {
        assert(nth >= 0 && (nth < getLength()));
        if (nth == 0)
        {
            deleteFront();
        }
        else if (nth == (getLength() - 1))
        {
            deleteBack();
        }
        else
        {
            int counter = 0;
            Node *tempNext;
            Node *tempPrev;
            Node *tempCurrent;
            for (Node *current = head; current; current = current->next)
            {
                if (counter == nth - 1)
                    tempPrev = current;
                else if (counter == nth)
                {
                    tempCurrent = current;
                }
                else if (counter == nth + 1)
                {
                    tempNext = current;
                }
                counter++;
            }
            // delete tempCurrent;
            tempPrev->next = tempNext;
            length--;
        }
    }

    void deleteKey(int val)
    {
        deleteNth(search(val));
    }

    void swapPairs()
    {
        int counter = 0;
        if (getLength() % 2 == 0) // EVEN
        {
            for (Node *current = head; current; current = current->next->next)
            {
                swap(current->data, current->next->data);
            }
        }
        else
        {
            Node *current = head;
            for (; counter < ((getLength() - 1) / 2); counter++)
            {
                swap(current->data, current->next->data);
                current = current->next->next;
            }
        }
    }

    void reverse()
    {
        reverseWithAddress(head);
        swap(head, tail);
    }

    void deleteEvenPosition()
    {
        int originalLength = getLength();
        for (int i = 1; i <= originalLength; i++)
        {
            if (i % 2 == 0)
            {
                deleteNth(i - (i / 2));
                i++;
            }
        }
    }
    void insertSorted(int val)
    {
        if (!head)
            insertEnd(val);
        else
        {
            Node *biggest;
            int counter = 0;
            int index = 0;
            for (Node *current = head; current; current = current->next)
            {
                counter++;
                if (current->data >= val)
                {
                    biggest = current;
                    index = counter - 1;
                    break;
                }
            }
            if (!biggest && !index)
                insertEnd(val);
            else if (!biggest && index)
                insertFront(val);
            else
                insertNth(val, index);
        }
    }
    void swapHeadTailNodes()
    {
        int counter = 0;
        Node *prevTail;
        Node *tempTail;
        for (Node *current = head; current; current = current->next)
        {
            if (counter == getLength() - 2)
                prevTail = current;
            else if (counter == getLength() - 1)
                tempTail = current;
            counter++;
        }
        prevTail->next = head;
        tempTail->next = head->next;
        head->next = nullptr;
        tail = head;
        head = tempTail;
    }
    void rightRotateTimes(int times)
    {

        int noOfRotates = times % getLength();
        if (noOfRotates != 0)
        {
            for (int rotate = 0; rotate < noOfRotates; rotate++)
            {
                int counter = 0;
                Node *tempTail;
                Node *obj = head;
                for (Node *current = head; current; current = current->next)
                {
                    if (counter == getLength() - 1)
                        tempTail = current;
                    counter++;
                }
                head = head->next;
                tempTail->next = obj;
                obj->next = nullptr;
                tail = obj;
            }
        }
    }
    void removeDuplicates()
    {
        int innerCounter = 1;
        int outerCounter = 1;
        for (Node *element = head; element; element = element->next)
        {
            innerCounter = outerCounter;
            for (Node *current = element->next; current; current = current->next)
            {
                if (element->data == current->data)
                {
                    // cout << "\nDeleted is " << current->data << " with index " << innerCounter << endl;
                    deleteNth(innerCounter);
                    innerCounter--;
                }
                innerCounter++;
            }
            outerCounter++;
            // cout << "\nOuter Counter = " << outerCounter << endl;
        }
    }
    void removeLastOccur(int val)
    {
        int last = -1;
        int counter = 0;
        for (Node *element = head; element; element = element->next)
        {
            if (element->data == val)
                last = counter;
            counter++;
        }
        if (last != -1)
            deleteNth(last);
    }
    void movToBack(int key)
    {
        int oLength = getLength();
        int counter = 0;
        for (Node *element = head; element; element = element->next)
        {

            if (element->data == key)
            {
                insertEnd(key);
                deleteNth(counter);
                counter--;
                oLength--;
            }
            counter++;
            if (counter == oLength)
                break;
        }
    }
    void arrangeOddEven()
    {
        int oLength = getLength();
        int counter = 1;
        for (Node *element = head->next; element; element = element->next->next)
        {
            insertEnd(element->data);
            // cout << "insert= " << element->data << endl;
            deleteNth(counter);
            counter++;
            oLength--;
            if (counter == oLength)
                break;
        }
    }
    void alternate(SLL alt)
    {
        int origLength = getLength();
        int counter = 1;
        for (int i = 0; (i < alt.getLength()) || (i < origLength); i++)
        {
            if (i < origLength)
            {
                insertNth(alt.getNTH(i)->data, counter);
                counter += 2;
                // cout << "LOOP" << endl;
            }
            else if (origLength > alt.getLength())
                insertEnd(getNTH(i)->data);
            else if (origLength < alt.getLength())
                insertEnd(alt.getNTH(i)->data);
        }
    }
};
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

    SLL s(n1, n5);
    cout << "Length:\n";
    s.print();
    cout << s.getLength() << endl;

    SLL emptySll;

    cout << "\nPrint Single Linked List with print:\n";
    s.print();

    cout << "\nPrint Single Linked List after insert End 100:\n";
    s.insertEnd(100);
    s.print();

    cout << "\nPrint Empty Single Linked List after insert End 100:\n";
    emptySll.insertEnd(100);
    emptySll.print();

    cout << "\nPrint Empty Single Linked List after insert End 200:\n";
    emptySll.print();
    emptySll.insertEnd(200);
    emptySll.print();

    cout << "\nPrint Empty Single Linked List after insert Front 200:\n";
    emptySll.print();
    emptySll.insertFront(200);
    emptySll.print();

    cout << "\nPrint Empty Single Linked List after delete Front:\n";
    emptySll.print();
    emptySll.deleteFront();
    emptySll.print();

    cout << "\nGet the 2nd node data:\n";
    s.print();
    cout << (s.getNTH(2))->data;

    cout << "\n\nDelete the 3rd node data [0 based]:\n";
    s.print();
    s.deleteNth(3);
    s.print();

    cout << "\nDelete Key 10:\n";
    s.insertFront(10);
    s.print();
    s.deleteKey(10);
    s.print();

    cout << "\nDelete the last node data :\n";
    s.print();
    s.deleteBack();
    s.print();

    cout << "\nGet the 2nd node data FROM BACK:\n";
    s.print();
    cout << (s.getNTHfromBack(2))->data;

    cout << "\n\nGet the index of node with value 30 [0-based]:\n";
    s.print();
    cout << s.search(30);

    cout << "\n\nGet the index of node with value 30 [IMPROVED SEARCH]:\n";
    s.print();
    cout << s.improvedSearch(30) << endl;
    s.print();

    cout << "\nSwap Pairs [EVEN]:\n";
    s.print();
    s.swapPairs();
    s.print();

    cout << "\nSwap Pairs [ODD]:\n";
    s.insertEnd(80);
    s.print();
    s.swapPairs();
    s.print();

    cout << "\nInsert 5 in 2nd:\n";
    s.print();
    s.insertNth(5, 2);
    s.print();

    cout << "\nReverse:\n";
    s.print();
    s.reverse();
    s.print();

    cout << "\nDelete Even Positions [ODD]:\n";
    s.print();
    s.deleteEvenPosition();
    s.print();

    cout << "\nDelete Even Positions [EVEN]:\n";
    s.insertEnd(5);
    s.print();
    s.deleteEvenPosition();
    s.print();

    cout << "\nCreate new linked list and delete it with destructor:\n";
    SLL *newsll = new SLL();
    cout << "Create: \n";
    newsll->insertEnd(100);
    newsll->insertEnd(200);
    newsll->print();
    cout << "Delete: \n";
    delete newsll;

    /* Compare Two LinkedLists*/
    SLL l1, l2, l3;
    l1.insertEnd(100);
    l1.insertEnd(50);
    l1.insertEnd(200);

    l2.insertEnd(100);
    l2.insertEnd(50);
    l2.insertEnd(200);

    l3.insertEnd(100);
    l3.insertEnd(50);
    // l3.insertEnd(300);
    cout << "\nCompare Lists: " << endl;
    cout << "l1 = ";
    l1.print();
    cout << "l2 = ";
    l2.print();
    cout << "l3 = ";
    l3.print();

    cout << "Is list1 = list3: ";
    if (l1.isEqual(l3))
        cout << "Equal" << endl;
    else
        cout << "Not Equal" << endl;

    cout << "Is list1 = list2: ";
    if (l1.isEqual(l2))
        cout << "Equal" << endl;
    else
        cout << "Not Equal" << endl;

    cout << "\nInsert Sorted 5 10 8 6 1\n";
    SLL sortedSll;
    sortedSll.insertSorted(5);
    sortedSll.print();
    sortedSll.insertSorted(10);
    sortedSll.print();
    sortedSll.insertSorted(8);
    sortedSll.print();
    sortedSll.insertSorted(6);
    sortedSll.print();
    sortedSll.insertSorted(1);
    sortedSll.print();

    cout << "\nSwap Head and Tail as nodes: "
         << endl;
    sortedSll.print();
    sortedSll.swapHeadTailNodes();
    sortedSll.print();

    cout << "\nRotate right times 6" << endl;
    sortedSll.print();
    sortedSll.rightRotateTimes(6);
    sortedSll.print();

    SLL dup;
    cout << "\nRemove Duplicates " << endl;
    dup.insertEnd(4);
    dup.insertEnd(3);
    dup.insertEnd(1);
    dup.insertEnd(1);
    dup.insertEnd(2);
    dup.insertEnd(2);
    dup.insertEnd(1);
    dup.insertEnd(3);
    dup.insertEnd(3);
    dup.insertEnd(3);
    dup.insertEnd(4);
    dup.print();
    dup.removeDuplicates();
    dup.print();

    cout << "\nRemove Last Occur [key = 1]:\n";
    dup.insertEnd(1);
    dup.insertEnd(1);
    dup.insertEnd(1);
    dup.print();
    dup.removeLastOccur(1);
    dup.print();

    cout << "\nMove to back [key = 2]:\n";
    dup.insertFront(2);
    dup.print();
    dup.movToBack(2);
    dup.print();

    cout << "\nODD positions first then EVEN:\n";
    dup.insertFront(2);
    dup.insertNth(7, 5);
    dup.print();
    dup.arrangeOddEven();
    dup.print();

    cout << "\nInsert alternating :" << endl;
    s.print();
    dup.print();
    s.alternate(dup);
    s.print();
}