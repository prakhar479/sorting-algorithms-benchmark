#include "./shell_sort.h"
void shellSort(int arr[], int size) {
    int gap, i, j, temp;

    // Generate Knuth's sequence for gaps
    for (gap = 1; gap <= size / 3; gap = gap * 3 + 1);

    // Start sorting with decreasing gap sizes
    for (; gap > 0; gap /= 3) {
        for (i = gap; i < size; i++) {
            temp = arr[i];
            j = i;

            // Shift elements that are greater than temp to the right
            while (j >= gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }

            arr[j] = temp;
        }
    }
}
