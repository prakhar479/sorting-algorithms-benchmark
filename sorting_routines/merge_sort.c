# include "./merge_sort.h"
# include "./insertion_sort.h"


void merge(int arr[], int aux[], int leftStart, int leftEnd, int rightStart, int rightEnd)
{
    int i = leftStart, j = rightStart, k = leftStart;

    while (i <= leftEnd && j <= rightEnd)
    {
        if (arr[i] <= arr[j])
        {
            aux[k++] = arr[i++];
        }
        else
        {
            aux[k++] = arr[j++];
        }
    }

    while (i <= leftEnd)
    {
        aux[k++] = arr[i++];
    }

    while (j <= rightEnd)
    {
        aux[k++] = arr[j++];
    }

    for (i = leftStart; i <= rightEnd; i++)
    {
        arr[i] = aux[i];
    }
}

void mergeSortHelper(int arr[], int aux[], int start, int end)
{
    if (start >= end)
    {
        return;
    }
    else if(end - start < MIN_SIZE)
    {
        insertion_sort(arr + start, end - start + 1);
        return;
    }

    int mid = start + (end - start) / 2;

    mergeSortHelper(arr, aux, start, mid);
    mergeSortHelper(arr, aux, mid + 1, end);

    merge(arr, aux, start, mid, mid + 1, end);
}

void mergeSort(int arr[], int size)
{
    int aux[size];
    mergeSortHelper(arr, aux, 0, size - 1);
}


