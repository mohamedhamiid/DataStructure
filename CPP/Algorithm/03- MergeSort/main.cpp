#include <iostream>
#include <assert.h>

using namespace std;

/******************* Merge Sort ******************/
/* Algorithm: Sort an array by divide array into */
/* 2 halves and compare each element in one half */
/* with its corresponding one in the other half  */
/* Complexity => O(nlogn)                        */
/*************************************************/

/* Merge ==> used to sort and merge arrays after being divided */
int merge(int arr1[], int left1, int right1, int arr2[], int left2, int right2, int res[], int resIndex)
{

    assert(right1 >= left1 && right2 >= left2 && arr1 != nullptr && arr2 != nullptr);

    /* The indexes used to compare */
    int i1 = left1, i2 = left2, iResult = resIndex;
    while (i1 <= right1 && i2 <= right2)
    {
        if (arr1[i1] <= arr2[i2])
            res[iResult++] = arr1[i1++];
        else if (arr1[i1] > arr2[i2])
            res[iResult++] = arr2[i2++];
    }

    /* If there the size of each half is not equal */
    while (i1 <= right1)
    {
        res[iResult++] = arr1[i1++];
    }
    while (i2 <= right2)
    {
        res[iResult++] = arr2[i2++];
    }
}
void mergeSort(int arr[], int res[], int left, int right)
{

    /* Dynamic array with changable size to store the two halves */
    int TwoHalvesSorted[right + 1] = {0};
    /* Basis Step */
    if (left == right)
    {
        res[left] = arr[left];
        return;
    }
    /* Divide into two halves */
    int mid = (right + left) / 2;
    /* Store the first half */
    mergeSort(arr, TwoHalvesSorted, left, mid);
    /* Store the second half */
    mergeSort(arr, TwoHalvesSorted, mid + 1, right);
    /* Merge with sorting */
    merge(TwoHalvesSorted, left, mid, TwoHalvesSorted, mid + 1, right, res, left);
}

int main()
{
    int arr[5] = {85, 24, 63, 45, 17};
    int res[5] = {0};
    cout << "The original array is: " << endl;
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";

    mergeSort(arr, res, 0, 4);

    cout << "\nThe sorted array is:" << endl;
    for (int i = 0; i < 5; i++)
        cout << res[i] << " ";
}