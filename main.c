#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "./sorting_routines/insertion_sort.h"
#include "./sorting_routines/merge_sort.h"
#include "./sorting_routines/quick_sort.h"
#include "./sorting_routines/shell_sort.h"
#include "./sorting_routines/tim_sort.h"
#include "./sorting_routines/radix_sort.h"
#include "./sorting_routines/comb_sort.h"

typedef void (*sort_func)(int *, int);

int main(int argc, char *argv[])
{
    sort_func SortFuncArray[] = {insertion_sort, mergeSort, quickSort, shellSort, timSort, radixSort, comb_sort};
    const int N = argc > 1 ? atoi(argv[1]) : 10000;
    const int iterations = argc > 2 ? atoi(argv[2]) : 10;

    char *sortNames[] = {"Insertion Sort", "Merge Sort", "Quick Sort", "Shell Sort", "Tim Sort", "Radix Sort", "Comb Sort"};

    // Seed the random number generator
    srand(time(NULL));

    printf("Number of elements: %d\n", N);
    printf("Number of iterations: %d\n\n", iterations);

    int k = 0, l = sizeof(SortFuncArray) / sizeof(SortFuncArray[0]);
    if (argc > 3)
    {
        switch (atoi(argv[3]))
        {
        case 1:
            k = 0;
            l = 1;
            break;
        case 2:
            k = 1;
            l = 2;
            break;
        case 3:
            k = 2;
            l = 3;
            break;
        case 4:
            k = 3;
            l = 4;
            break;
        case 5:
            k = 4;
            l = 5;
            break;
        case 6:
            k = 5;
            l = 6;
            break;
        case 7:
            k = 6;
            l = 7;
            break;
        default:
            printf("Invalid sorting algorithm number\n");
            return 1;
        }
    }

    for (; k < l; k++)
    {
        printf("Sorting algorithm: %s\n", sortNames[k]);
        clock_t start, end;
        double total_time = 0;

        for (int i = 0; i < iterations; i++)
        {
            int arr[N];
            // Initialize array with random values
            for (int i = 0; i < N; i++)
            {
                arr[i] = rand() / 1000;
            }

            // Start the timer
            start = clock();

            // Perform the sorting
            SortFuncArray[k](arr, N);

            // Stop the timer
            end = clock();

            // Calculate the elapsed time in seconds
            double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
            total_time += elapsed_time;

            // printf("Iteration %d: %.6f seconds\n", i + 1, elapsed_time);

            // Check the validity of the sorted array
            for (int j = 1; j < N; j++)
            {
                if (arr[j] < arr[j - 1])
                {
                    printf("Sorting failed!\n");
                    return 1;
                }
            }
        }

        // Calculate the average sorting time
        double average_time = total_time / iterations;

        printf("Average sorting time: %.6f seconds\n\n", average_time);
    }

    return 0;
}