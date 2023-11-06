#include <iostream>
#include <assert.h>

using namespace std;

/*********************** Quick Sort *********************/
/* Algorithm: Select a pivot and make smaller left      */
/* and bigger right then do this for the left and right */
/* with its corresponding one in the other half         */
/* Complexity => O(nlogn)                               */
/********************************************************/

void quickSort(int arr[], int left, int right)
{
    /* Basis Step */
    if (left >= right)
        return;

    /* Select Pivot Value */
    int pivot = arr[right];

    /* Set two indeces pointers  */
    int indexOfLastSmaller = left, indexOfLastGreater = right - 1; // In the greater pointer
                                                                   // we choose the index before pivot

    /* Use the two pointers to determine the index of last smaller and greater */
    while (indexOfLastSmaller <= indexOfLastGreater)
    {
        /* The Smaller pointer */
        while (arr[indexOfLastSmaller] <= pivot && indexOfLastSmaller <= right - 1)
        {
            indexOfLastSmaller++;
        }
        /* The greater pointer */
        while (arr[indexOfLastGreater] > pivot && indexOfLastGreater >= left)
        {
            indexOfLastGreater--;
        }
        /* Swap the last greater with the last smaller */
        if (indexOfLastSmaller < indexOfLastGreater)
        {
            swap(arr[indexOfLastSmaller], arr[indexOfLastGreater]);
        }
    }
    /* Now, Swap the last greater with pivot  */
    swap(arr[right], arr[indexOfLastSmaller]);
    /* Do the same for the right and left */
    quickSort(arr, left, indexOfLastGreater);
    quickSort(arr, indexOfLastSmaller + 1, right);
}

int main()
{
    int arr[5] = {85, 24, 63, 45, 17};
    int res[5] = {0};
    cout << "The original array is: " << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";

    quickSort(arr, 0, 4);

    cout << "\nThe sorted array is:" << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";
}