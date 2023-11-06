#include <iostream>
#include <assert.h>
using namespace std;

/**************** Bubble Sort ****************/
/* Algorithm: Compare each element with the  */
/* whole array and make the max in the right */
/* Complexity ==> O(n^2)                     */
/*********************************************/
void BubbleSort(int arr[], int length)
{
    assert(arr != nullptr);
    if (length < 2)
    {
        return;
    }
    int maxIndex = length - 1; // Intially, assume the max at the end
    bool sorted = true;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < (length - i); j++)
        {
            /* To prevent comparing same value */
            if (i == j)
                continue;
            /* Detect the max value */
            if (arr[j] > arr[maxIndex])
            {
                maxIndex = j;
                sorted = false;
            }
        }
        /* Swap the max with the "next" last element in array */
        if (maxIndex != (length - 1 - i)) // Because if the max in the correct position
        {
            int temp = arr[length - 1 - i];
            arr[length - 1 - i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
        if (sorted)
        {
            break;
        }
    }
}

int main()
{
    int arr[5] = {12, 10, -3, 120, 5};
    cout << "The original array is:" << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";

    /* Sorting */
    BubbleSort(arr, 5);

    cout << "\nThe Sorted array is:" << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";
}