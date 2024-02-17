#include "./tim_sort.h"
#include "./insertion_sort.h"


int min(int a, int b) {
    return (a < b) ? a : b;
}

void merge_helper(int arr[], int left, int mid, int right) {
    int len1 = mid - left + 1;
    int len2 = right - mid;
    int leftArr[len1];
    int rightArr[len2];

    for (int i = 0; i < len1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < len2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < len1 && j < len2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }

}

void timSort(int arr[], int n) {
    for (int i = 0; i < n; i += MIN_MERGE)
        insertion_sort(arr + i, min((i + MIN_MERGE - 1), (n - 1)) - i + 1);

    for (int size = MIN_MERGE; size < n; size = 2 * size) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));
            merge_helper(arr, left, mid, right);
        }
    }
}
