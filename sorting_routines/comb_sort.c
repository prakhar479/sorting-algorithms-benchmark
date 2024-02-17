#include "./comb_sort.h"
void swap_comb(int* a, int* b) {
    if (*a != *b) {
        *a = *a ^ *b;
        *b = *a ^ *b;
        *a = *a ^ *b;
    }
}

void comb_sort(int arr[], int n) {
    int gap = n;
    float shrink = SHRINK_FACTOR;
    int sorted = 0;

    while (gap > 1 || sorted == 0) {
        gap = (int)(gap / shrink);
        if (gap < 1) {
            gap = 1;
        }

        sorted = 1;
        for (int i = 0; i < n - gap; i++) {
            if (arr[i] > arr[i + gap]) {
                swap_comb(&arr[i], &arr[i + gap]);
                sorted = 0;
            }
        }
    }
}

