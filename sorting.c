#include "batcher.h"
#include "heap.h"
#include "insert.h"
#include "quick.h"
#include "set.h"
#include "shell.h"
#include "stats.h"

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define OPTIONS "r:n:p:ishaHqb"
// Note: this assignment doesn’t use : in the third argument to getopt
int main(int argc, char **argv) {
    int opt = 0;
    int seed = 0;
    uint8_t casebit = 0;
    int size = 100;
    int sizem = 100;
    srandom(13371453);
    uint32_t mask = (1 << 30) - 1;
    Stats stats;
    uint32_t *p; //move
    uint32_t *casep;
    /*
	p = calloc(size,sizeof(int32_t));
	for (int i=0; i < size; i++){
		uint32_t x =((uint32_t) random() & mask);
		p[i] = x;
	}
*/
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a': casebit = 31; break;
        case 'i':
            casebit = set_union(casebit, 1);
            /*
			reset(&stats);
			casep = calloc(size,sizeof(int32_t));
			for(int i = 0; i < size;i++){
				casep[i] = p[i];
			}
			insertion_sort(&stats, casep, size);
			print_stats(&stats, "Insertion Sort", size);
			for (int i = 0; i < sizem;i++){
				if((i%5)==0 && i != 0){printf("\n");}
				printf("%13" PRIu32, casep[i]);
			}
			printf("\n");
			free(casep);
			*/
            break;
        case 'h':
            casebit = set_union(casebit, 2);
            /*
			reset(&stats);
			casep = calloc(size,sizeof(int32_t));
                        for(int i = 0; i < size;i++){
                                casep[i] = p[i];
			}
			shell_sort(&stats, casep, size);
                        print_stats(&stats, "Shell Sort", size);
			for (int i = 0; i < sizem;i++){
				if((i%5)==0 && i != 0){printf("\n");}
                                printf("%13" PRIu32, casep[i]);
                        }
			printf("\n");
			free(casep);
			*/
            break;
        case 's':
            casebit = set_union(casebit, 4);
            /*
			printf("Heap Sort, 100 elements, 2741 moves, 2638 compares\n");
			reset(&stats);
                        casep = calloc(size,sizeof(int32_t));
                        for(int i = 0; i < size;i++){
                                casep[i] = p[i];
                        }
                        printf("is %d\n", casep[0]);
                        heap_sort(&stats, casep, size);
                        for (int i = 0; i < sizem;i++){
                                if((i%5)==0 && i != 0){printf("\n");}
				printf("%13" PRIu32, casep[i]);
                        }
                        free(casep);
			printf("\n");
			*/
            break;
        case 'q':
            casebit = set_union(casebit, 8);

            /*
			printf("Quick Sort, 100 elements, 2741 moves, 2638 compares\n");
                        reset(&stats);
                        casep = calloc(size,sizeof(int32_t));
                        for(int i = 0; i < size;i++){
                                casep[i] = p[i];
                        }
                        quick_sort(&stats, casep, size);
                        //print_stats(&stats, "Quick Sort", size);
                        for (int i = 0; i < sizem;i++){
                                if((i%5)==0 && i != 0){printf("\n");}
				printf("%13" PRIu32, casep[i]);
                        }
			printf("\n");
                        free(casep);
			*/
            break;
        case 'b':
            casebit = set_union(casebit, 16);
            /*
			printf("Batcher Sort, 100 elements, 2741 moves, 2638 compares\n");
                        reset(&stats);
                        casep = calloc(size,sizeof(int32_t));
                        for(int i = 0; i < size;i++){
                                casep[i] = p[i];
                        }
                        batcher_sort(&stats, casep, size);
                        //print_stats(&stats, "Batcher Sort", 100);
                        for (int i = 0; i < sizem;i++){
                        	if((i%5)==0 && i != 0){printf("\n");}
				printf("%13" PRIu32, casep[i]);
			}
			printf("\n");
                        free(casep);
			*/
            break;
        case 'r':
            seed = strtoul(optarg, NULL, 10);
            srandom(seed);
            break;
        case 'n':
            size = strtoul(optarg, NULL, 10);
            sizem = size;
            break;
        case 'p':
            sizem = strtoul(optarg, NULL, 10);
            if (sizem > size) {
                sizem = size;
            }
            break;
        case 'H':
            printf("-i(insert) -h(heap) -s(shell) -q(quick) -b (batcher) -r(set seed) -n(set array "
                   "size) -p (set how much of array is printed)");
            break;
        }
    }
    //move here
    p = calloc(size, sizeof(int32_t));
    for (int i = 0; i < size; i++) {
        uint32_t x = ((uint32_t) random() & mask);
        p[i] = x;
    }
    if (casebit & (1 << 0)) {
        reset(&stats);
        casep = calloc(size, sizeof(int32_t));
        for (int i = 0; i < size; i++) {
            casep[i] = p[i];
        }
        insertion_sort(&stats, casep, size);
        print_stats(&stats, "Insertion Sort", size);
        for (int i = 0; i < sizem; i++) {
            if ((i % 5) == 0 && i > 0) {
                printf("\n");
            }
            printf("%13" PRIu32, casep[i]);
        }
        if (sizem != 0) {
            printf("\n");
        }
        free(casep);
    }
    if (casebit & (1 << 1)) {
        reset(&stats);
        casep = calloc(size, sizeof(int32_t));
        for (int i = 0; i < size; i++) {
            casep[i] = p[i];
        }
        heap_sort(&stats, casep, size);
        print_stats(&stats, "Heap Sort", size);
        for (int i = 0; i < sizem; i++) {
            if ((i % 5) == 0 && i != 0) {
                printf("\n");
            }
            printf("%13" PRIu32, casep[i]);
        }
        if (sizem != 0) {
            printf("\n");
        }
        free(casep);
    }
    if (casebit & (1 << 2)) {
        reset(&stats);
        casep = calloc(size, sizeof(int32_t));
        for (int i = 0; i < size; i++) {
            casep[i] = p[i];
        }
        shell_sort(&stats, casep, size);
        print_stats(&stats, "Shell Sort", size);
        for (int i = 0; i < sizem; i++) {
            if ((i % 5) == 0 && i != 0) {
                printf("\n");
            }
            printf("%13" PRIu32, casep[i]);
        }
        if (sizem != 0) {
            printf("\n");
        }
        free(casep);
    }
    if (casebit & (1 << 3)) {
        reset(&stats);
        casep = calloc(size, sizeof(int32_t));
        for (int i = 0; i < size; i++) {
            casep[i] = p[i];
        }
        quick_sort(&stats, casep, size);
        print_stats(&stats, "Quick Sort", size);
        for (int i = 0; i < sizem; i++) {
            if ((i % 5) == 0 && i != 0) {
                printf("\n");
            }
            printf("%13" PRIu32, casep[i]);
        }
        if (sizem != 0) {
            printf("\n");
        }
        free(casep);
    }
    if (casebit & (1 << 4)) {
        reset(&stats);
        casep = calloc(size, sizeof(int32_t));
        for (int i = 0; i < size; i++) {
            casep[i] = p[i];
        }
        batcher_sort(&stats, casep, size);
        print_stats(&stats, "Batcher Sort", size);
        for (int i = 0; i < sizem; i++) {
            if ((i % 5) == 0 && i != 0) {
                printf("\n");
            }
            printf("%13" PRIu32, casep[i]);
        }
        if (sizem != 0) {
            printf("\n");
        }
        free(casep);
    }
    free(p);
    return 0;
}
