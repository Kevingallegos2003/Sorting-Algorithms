#include "quick.h"

#include <stdio.h>
int partition(Stats *stats, uint32_t *A, int hi, int lo);
void quick_sorter(Stats *stats, uint32_t *A, int hi, int lo);
void quick_sort(Stats *stats, uint32_t *A, uint32_t n) {
    quick_sorter(stats, A, 1, n);
}
int partition(Stats *stats, uint32_t *A, int lo, int hi) {
    int i;
    //uint32_t x;
    i = lo - 1;
    for (int j = lo; cmp(stats, j, hi) < 0; ++j) { //j < hi
        if (cmp(stats, A[j - 1], A[hi - 1]) < 0) { //A[j-1] < A[hi - 1]
            i = i + 1;
            /*
			x = A[i-1];
			A[i-1] = A[j-1];
			A[j-1] = x;
			*/
            swap(stats, &A[i - 1], &A[j - 1]);
        }
    }
    /*
	x = A[i];
	A[i] = A[hi-1];
	A[hi-1] = x;
	*/
    swap(stats, &A[i], &A[hi - 1]);
    return i + 1;
}
void quick_sorter(Stats *stats, uint32_t *A, int lo, int hi) {
    int p;
    if (cmp(stats, lo, hi) < 0) { //lo < hi
        p = partition(stats, A, lo, hi);
        quick_sorter(stats, A, lo, p - 1);
        quick_sorter(stats, A, p + 1, hi);
    }
}
