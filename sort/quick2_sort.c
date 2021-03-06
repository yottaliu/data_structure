#include "quick2_sort.h"
#include "insertion_sort.h"

static void swap(Item *a, Item *b)
{
    Item tmp = *a;
    *a = *b;
    *b = tmp;
}

static Item median_of_three(Item *arr, int left, int right)
{
    int center;
    center = (left + right) / 2;
    if (arr[left] > arr[center]) {
        swap(&arr[left], &arr[center]);
    }
    if (arr[left] > arr[right]) {
        swap(&arr[left], &arr[right]);
    }
    if (arr[center] > arr[right]) {
        swap(&arr[center], &arr[right]);
    }
    swap(&arr[center], &arr[right-1]);

    return arr[right-1];
}

#define cutoff (16)     // must >= 3, but better <= 20
static void qsort(Item *arr, int left, int right)
{
    int i, j;
    Item pivot;

    if (left + cutoff <= right) {
        pivot = median_of_three(arr, left, right);
        i = left;
        j = right - 1;
        while (1) {
            while (arr[++i] < pivot) {
                continue;
            }
            while (arr[--j] > pivot) {
                continue;
            }
            if (i < j) {
                swap(&arr[i], &arr[j]);
            } else {
                break;
            }
        }
        swap(&arr[i], &arr[right-1]);

        qsort(arr, left, i-1);
        qsort(arr, i+1, right);
    } else {
        insertion_sort(arr+left, right-left+1);
    }
}

void quick2_sort(Item *arr, int n)
{
    qsort(arr, 0, n-1);
}
