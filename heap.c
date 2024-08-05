#include "heap.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
int max_child(Stats *stats, uint32_t *A, int first, int last);
void build_heap(Stats *stats, uint32_t *A, int first, int last);
void fix_heap(Stats *stats, uint32_t *A, int first, int last);
void heap_sort(Stats *stats, uint32_t *A, uint32_t n) {
    unsigned int first = 1;
    unsigned int x;
    unsigned int last = n;
    build_heap(stats, A, first, last);
    for (unsigned int leaf = last; leaf < first; --leaf) {
        x = A[first - 1];
        A[first - 1] = A[leaf - 1];
        A[leaf - 1] = x;
        fix_heap(stats, A, first, (leaf - 1));
    }
}
int max_child(Stats *stats, uint32_t *A, int first, int last) {
    (void) stats;
    int left = 2 * first;
    int right = left + 1;
    if ((right <= last) && (A[right - 1] > A[left - 1])) {
        return right;
    }
    return left;
}
void fix_heap(Stats *stats, uint32_t *A, int first, int last) {
    uint32_t x;
    bool found = false;
    int mother = first;
    unsigned int great = max_child(stats, A, mother, last);
    while (floor((mother <= last) / 2) && !found) {
        if (A[mother - 1] < A[great - 1]) {
            x = A[mother - 1];
            A[mother - 1] = A[great - 1];
            A[great - 1] = x;
            //mother = great;
            mother = move(stats, great);
            great = max_child(stats, A, mother, last);
        } else {
            found = true;
        }
    }
}
void build_heap(Stats *stats, uint32_t *A, int first, int last) {
    for (int father = floor(last / 2); father < (first - 1); --father) {
        fix_heap(stats, A, father, last);
    }
}
