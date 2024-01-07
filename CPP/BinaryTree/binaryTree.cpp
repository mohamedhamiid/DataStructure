#include <iostream>
#include <cassert>
using namespace std;
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
    Node *getHead()
    {
        return head;
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
    int pop()
    {
        int res;
        if (getLength() == 1)
            deleteFront();
        else if (head != nullptr)
        {
            Node *temp = head->next;
            Node *preTemp = head;
            for (; temp->next; temp = temp->next, preTemp = preTemp->next)
            {
            }
            res = temp->data;
            delete temp;
            preTemp->next = nullptr;
            length--;
            tail = preTemp;
            return res;
        }
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
    Node *getBack()
    {
        return tail;
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

class Stack
{
private:
    SLL list;

public:
    Stack();
    ~Stack();
    void push(int x);
    int pop();
    void print();
    int top();
    bool isEmpty();
};
bool Stack::isEmpty()
{
    if (!(list.getHead()))
    {
        return true;
    }
    else
        return false;
}

Stack::Stack()
{
    SLL list();
}

Stack::~Stack()
{
}
void Stack::push(int x)
{
    list.insertEnd(x);
}
int Stack::pop()
{

    return list.pop();
}

void Stack::print()
{
    list.print();
}

int Stack::top()
{
    return list.getBack()->data;
}

struct TreeNode
{
    int data = 0;
    TreeNode *right = nullptr;
    TreeNode *left = nullptr;
    TreeNode(int data) : data(data) {}
};

class BinaryTree
{
private:
    TreeNode *root = nullptr;

public:
    BinaryTree();
    BinaryTree(int data);
    BinaryTree(TreeNode *node);
    ~BinaryTree();
    TreeNode *getRoot();
    void printInOrder(TreeNode *node);   /* In order Traversal */
    void printPreOrder(TreeNode *node);  /* Pre order Traversal */
    void printPostOrder(TreeNode *node); /* Post order Traversal */
    // void printDepthFirst(TreeNode *node);
    void insertLeft(TreeNode *node, int data);
    void insertRight(TreeNode *node, int data);
    TreeNode *insertBST(TreeNode *node, int data);
    TreeNode *searchBST(TreeNode *root, int val);
};
int main()
{
    BinaryTree t;
    // t.insertLeft(t.getRoot(), 1);
    // t.insertLeft(t.getRoot(), 2);
    // t.insertRight(t.getRoot(), 3);
    // t.insertLeft(t.getRoot()->right, 4);
    // t.printInOrder(t.getRoot()); /* In order Traversal */
    // cout << endl;
    // t.printPreOrder(t.getRoot()); /* Pre order Traversal */
    // cout << endl;
    // t.printPostOrder(t.getRoot()); /* Post order Traversal */
    // cout << endl;
    // // t.printDepthFirst(t.getRoot());
    // cout << endl;

    /* BST */
    TreeNode *root;
    t.insertLeft(t.getRoot(), 3);
    t.insertBST(t.getRoot(), 2);
    t.insertBST(t.getRoot(), 4);
    t.insertBST(t.getRoot(), 1);
    t.insertBST(t.getRoot(), 5);

    TreeNode *res = t.searchBST(t.getRoot(), 6);
    if (!res)
        cout << "Not found";
    else
        cout << res->data;
}
BinaryTree::BinaryTree()
{
    BinaryTree bt();
    root = nullptr;
}
BinaryTree::BinaryTree(TreeNode *node)
{
    root = node;
    node->left = nullptr;
    node->right = nullptr;
}

BinaryTree::~BinaryTree()
{
}
void BinaryTree::printInOrder(TreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    printInOrder(node->left);
    cout << node->data << " ";
    printInOrder(node->right);
}

void BinaryTree::printPreOrder(TreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    cout << node->data << " ";
    printInOrder(node->left);
    printInOrder(node->right);
}

void BinaryTree::printPostOrder(TreeNode *node)
{
    if (node == NULL)
    {
        return;
    }
    printInOrder(node->left);
    printInOrder(node->right);
    cout << node->data << " ";
}
void BinaryTree::insertLeft(TreeNode *node, int data)
{
    TreeNode *temp = new TreeNode(data);
    if (this->root == NULL)
    {
        root = temp;
        temp->left = nullptr;
        temp->right = nullptr;
        return;
    }
    if (node->left == NULL)
    {
        node->left = temp;
    }
}
void BinaryTree::insertRight(TreeNode *node, int data)
{
    TreeNode *temp = new TreeNode(data);
    if (this->root == NULL)
    {
        root = temp;
        temp->left = nullptr;
        temp->right = nullptr;
        return;
    }
    if (node->right == NULL)
    {
        node->right = temp;
    }
}
TreeNode *BinaryTree::getRoot()
{
    return root;
}

TreeNode *BinaryTree::insertBST(TreeNode *node, int data)
{
    if (!node)
    {
        return new TreeNode(data);
    }
    if (data <= node->data)
        node->left = insertBST(node->left, data);
    else
        node->right = insertBST(node->right, data);
    return node;
}

TreeNode *BinaryTree::searchBST(TreeNode *root, int val)
{
    if (!root || root->data == val)
    {
        return root;
    }
    else
    {
        if (val < root->data)
            return searchBST(root->left, val);
        else
            return searchBST(root->right, val);
    }
}