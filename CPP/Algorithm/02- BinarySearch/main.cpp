#include <iostream>
#include <assert.h>

using namespace std;

/**************** Binary Search ******************/
/* Algorithm: Find element in SORTED array       */
/* by dividing by 2 and compare the value with   */
/* each half                                     */
/* Complexity => O(logn)                         */
/* Returns -1 if not found                       */
/*************************************************/
int BinarySearch(int value, int arr[], int left, int right)
{
    assert(right >= left && arr != nullptr);
    /* Basis Step */
    if (left == right)
    {
        if (arr[left] == value)
            return left;
        else
            return -1;
    }
    /* Determine middle index of the array */
    int mid = (right + left) / 2;
    /* Compare the value with the mid value */
    if (value < arr[mid])
        BinarySearch(value, arr, left, mid);
    else if (value > arr[mid])
        BinarySearch(value, arr, mid + 1, right);
    else if (value == arr[mid])
        return mid;
    else /* Not Found */
        return -1;
}

int main()
{
    int arr[5] = {1, 5, 7, 12, 15};
    cout << "The index of 7 in the array [0-based]: " << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";

    cout << "\nis:" << endl;
    cout << BinarySearch(7, arr, 0, 5) << " ";
}