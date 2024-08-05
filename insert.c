#include "insert.h"

#include <stdio.h>
void insertion_sort(Stats *stats, uint32_t *arr, uint32_t length) {

    unsigned int i;
    unsigned int j;
    unsigned int temp;
    for (i = 1; cmp(stats, i, length) < 0; ++i) {
        //j=i;
        j = move(stats, i);
        //temp = arr[i];
        temp = move(stats, arr[i]);
        while (j > 0 && cmp(stats, temp, arr[j - 1]) < 0) { //temp < arr[j-1]
            arr[j] = move(stats, arr[j - 1]); //arr[j] = arr[j-1];
            j--;
        }
        arr[j] = temp;
    }
}
