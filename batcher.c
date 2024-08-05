#include "batcher.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
void comparator(Stats *stats, uint32_t *A, int x, int y);
void batcher_sort(Stats *stats, uint32_t *A, uint32_t n) {
    int t = 0;
    int p;
    int q;
    int r;
    int d;
    int n1;
    n1 = n;
    while (n) {
        n >>= 1;
        t++;
    }
    p = (1 << (t - 1));
    while (p > 0) {
        q = (1 << (t - 1));
        r = 0;
        d = p;
        while (d > 0) {
            for (int i = 0; i < (n1 - d); ++i) {
                if ((i & p) == r) {
                    comparator(stats, A, i, (i + d));
                }
            }
            d = q - p;
            q >>= 1;
            r = p;
        }
        p >>= 1;
    }
}
void comparator(Stats *stats, uint32_t *A, int x, int y) {
    //uint32_t z;
    if (cmp(stats, A[y], A[x]) < 0) { //A[x] > A[y]
        /*
        	z = A[x];
        	A[x] = A[y];
        	A[y] = z;
		*/
        swap(stats, &A[x], &A[y]);
    }
}
