#include "shell.h"

#include "gaps.h"

#include <stdint.h>
#include <stdio.h>
void shell_sort(Stats *stats, uint32_t *A, uint32_t n) {
    /*	(void) stats;
       (void) A;
       (void) n;       
*/
    uint32_t j;
    uint32_t temp;
    for (uint32_t i = 0; i < GAPS; ++i) {
        for (uint32_t x = gaps[i]; cmp(stats, x, n) < 0; ++x) {
            //j =x;
            j = move(stats, x);
            temp = move(stats, A[x]); //temp = A[x];
            while (j >= gaps[i] && temp < A[j - gaps[i]]) {
                A[j] = move(stats, A[j - gaps[i]]); //A[j] = A[j-gaps[i]];
                j = j - gaps[i];
            }
            A[j] = temp;
        }
    }
}
