#include "./quick_sort.h"
#include "./insertion_sort.h"

void swap_quick(int *a, int *b)
{
    if (*a != *b)
    {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

int partition(int arr[], int low, int high)
{

    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid])
    {
        swap_quick(&arr[low], &arr[mid]);
    }
    if (arr[low] > arr[high])
    {
        swap_quick(&arr[low], &arr[high]);
    }
    if (arr[mid] > arr[high])
    {
        swap_quick(&arr[mid], &arr[high]);
    }
    swap_quick(&arr[mid], &arr[high]);

    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap_quick(&arr[i], &arr[j]);
        }
    }
    swap_quick(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSortHelper(int arr[], int low, int high)
{
    if (high - low < MIN_SIZE)
    {
        insertion_sort(arr + low, high - low + 1);
        return;
    }
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(int arr[], int size)
{
    quickSortHelper(arr, 0, size - 1);
}
