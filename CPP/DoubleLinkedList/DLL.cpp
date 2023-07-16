#include <iostream>
#include <cassert>
using namespace std;
struct Node
{
    int data;
    Node *next;
    Node *prev;
    Node(int data) : data(data) {}
};
class DLL
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
    DLL()
    {
        head = nullptr;
        tail = nullptr;
    }

    DLL(Node *head, Node *tail)
    {
        this->head = head;
        this->tail = tail;
    }
    ~DLL()
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
    void link(Node *first, Node *second)
    {
        if (first)
            first->next = second;
        if (second)
            second->prev = first;
    }
    int getLength()
    {
        int counter = 0;
        for (Node *current = head; current; current = current->next)
        {
            counter++;
        }
        length = counter;
        // cout << "\nLength Done\n";
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
    void printReverse()
    {
        assert(head != nullptr);

        for (Node *current = tail; current; current = current->prev)
        {
            cout << current->data << " ";
        }
        cout << "\n";
    }
    void insertEnd(int val)
    {
        Node *n = new Node(val);
        n->prev = tail;
        n->next = nullptr;
        if (!head)
        {
            this->head = n;
            this->tail = n;
        }
        else
        {
            tail->next = n;
            n->prev = tail;
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
        for (Node *current = tail; current; current = current->prev)
        {
            if (counter == nth)
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
        int index = search(val);
        swap(getNTH(index)->data, getNTH(index)->prev->data);
        return index - 1;
    }
    void insertNth(int val, int nth)
    {
        if (nth == 0 || !head)
            insertFront(val);
        else if (nth == getLength())
            insertEnd(val);
        else
        {
            Node *tempCurr = getNTH(nth);
            Node *newNode = new Node(val);
            newNode->prev = tempCurr->prev;
            newNode->next = tempCurr;
            tempCurr->prev->next = newNode;
            length++;
        }
    }
    void insertFront(int val)
    {
        Node *n = new Node(val);
        if (head == nullptr)
        {
            insertEnd(val);
        }
        else
        {
            n->next = head;
            head->prev = n;
            head = n;
            head->prev = nullptr;
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
            Node *temp = tail;
            tail = tail->prev;
            delete temp;
            length--;
            tail->next = nullptr;
        }
    }
    bool isEqual(DLL s)
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
            // cout << "\n1\n";
            Node *tempCurrent = getNTH(nth);
            // delete tempCurrent;
            (tempCurrent->prev)->next = tempCurrent->next;
            (tempCurrent->next)->prev = tempCurrent->prev;
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
        int i = 1;
        while (i < getLength())
        {
            deleteNth(i);
            i = i + 1;
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
    void alternate(DLL alt)
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
    DLL s;
    s.insertEnd(10);
    s.insertEnd(20);
    s.insertEnd(30);
    s.insertEnd(40);
    s.insertEnd(50);

    // cout << "Length:\n";
    // s.print();
    // cout << s.getLength() << endl;

    // cout << "\nPrint Double Linked List with print:\n";
    // s.print();

    // cout << "\nPrint Double Linked List with print[REVERSED]:\n";
    // s.printReverse();

    // cout << "\nPrint Double Linked List after insert Front 200:\n";
    // s.print();
    // s.insertFront(200);
    // s.print();

    // cout << "\nPrint Double Linked List after delete Front:\n";
    // s.print();
    // s.deleteFront();
    // s.print();

    // cout << "\nGet the 2nd node data:\n";
    // s.print();
    // cout << (s.getNTH(2))->data;

    // cout << "\n\nDelete the 3rd node data [0 based]:\n";
    // s.print();
    // s.deleteNth(3);
    // s.print();

    // cout << "\nDelete Key 10:\n";
    // s.insertFront(10);
    // s.print();
    // s.deleteKey(10);
    // s.print();

    // cout << "\nDelete the last node data :\n";
    // s.print();
    // s.deleteBack();
    // s.print();

    // cout << "\nGet the 2nd node data FROM BACK:\n";
    // s.print();
    // cout << (s.getNTHfromBack(2))->data;

    // cout << "\n\nGet the index of node with value 30 [0-based]:\n";
    // s.print();
    // cout << s.search(30);

    // cout << "\n\nGet the index of node with value 30 [IMPROVED SEARCH]:\n";
    // s.print();
    // cout << s.improvedSearch(30) << endl;
    // s.print();

    // cout << "\nSwap Pairs [EVEN]:\n";
    // s.print();
    // s.swapPairs();
    // s.print();

    // cout << "\nSwap Pairs [ODD]:\n";
    // s.insertEnd(80);
    // s.print();
    // s.swapPairs();
    // s.print();

    // cout << "\nInsert 5 in 2nd:\n";
    // s.print();
    // s.insertNth(5, 2);
    // s.print();

    // cout << "\nReverse:\n";
    // s.print();
    // s.reverse();
    // s.print();

    // cout << "\nDelete Even Positions [ODD]:\n";
    // s.print();
    // s.deleteEvenPosition();
    // s.print();

    // cout << "\nDelete Even Positions [EVEN]:\n";
    // s.insertEnd(5);
    // s.print();
    // s.deleteEvenPosition();
    // s.print();

    // cout << "\nCreate new linked list and delete it with destructor:\n";
    // DLL *newDLL = new DLL();
    // cout << "Create: \n";
    // newDLL->insertEnd(100);
    // newDLL->insertEnd(200);
    // newDLL->print();
    // cout << "Delete: \n";
    // delete newDLL;

    // /* Compare Two LinkedLists*/
    // DLL l1, l2, l3;
    // l1.insertEnd(100);
    // l1.insertEnd(50);
    // l1.insertEnd(200);

    // l2.insertEnd(100);
    // l2.insertEnd(50);
    // l2.insertEnd(200);

    // l3.insertEnd(100);
    // l3.insertEnd(50);
    // // l3.insertEnd(300);
    // cout << "\nCompare Lists: " << endl;
    // cout << "l1 = ";
    // l1.print();
    // cout << "l2 = ";
    // l2.print();
    // cout << "l3 = ";
    // l3.print();

    // cout << "Is list1 = list3: ";
    // if (l1.isEqual(l3))
    //     cout << "Equal" << endl;
    // else
    //     cout << "Not Equal" << endl;

    // cout << "Is list1 = list2: ";
    // if (l1.isEqual(l2))
    //     cout << "Equal" << endl;
    // else
    //     cout << "Not Equal" << endl;

    // cout << "\nInsert Sorted 5 10 8 6 1\n";
    // DLL sortedDLL;
    // sortedDLL.insertSorted(5);
    // sortedDLL.print();
    // sortedDLL.insertSorted(10);
    // sortedDLL.print();
    // sortedDLL.insertSorted(8);
    // sortedDLL.print();
    // sortedDLL.insertSorted(6);
    // sortedDLL.print();
    // sortedDLL.insertSorted(1);
    // sortedDLL.print();

    // cout << "\nSwap Head and Tail as nodes: "
    //      << endl;
    // sortedDLL.print();
    // sortedDLL.swapHeadTailNodes();
    // sortedDLL.print();

    // cout << "\nRotate right times 6" << endl;
    // sortedDLL.print();
    // sortedDLL.rightRotateTimes(6);
    // sortedDLL.print();

    DLL dup;
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
    // dup.print();
    // dup.removeDuplicates();
    // dup.print();

    // cout << "\nRemove Last Occur [key = 1]:\n";
    // dup.insertEnd(1);
    // dup.insertEnd(1);
    // dup.insertEnd(1);
    // dup.print();
    // dup.removeLastOccur(1);
    // dup.print();

    // cout << "\nMove to back [key = 2]:\n";
    // dup.insertFront(2);
    // dup.print();
    // dup.movToBack(2);
    // dup.print();

    // cout << "\nODD positions first then EVEN:\n";
    // dup.insertFront(2);
    // dup.insertNth(7, 5);
    // dup.print();
    // dup.arrangeOddEven();
    // dup.print();

    cout << "\nInsert alternating :" << endl;
    s.print();
    dup.print();
    s.alternate(dup);
    s.print();
}