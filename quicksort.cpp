// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"

int Partition(std::vector<int>* numbers, int i, int k, int* compCount, int* memAccessCount) { // pass compCount and memAccessCount to count and iterate
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;

    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = (*numbers)[midpoint];
    (*memAccessCount)++;// count comp mem access

    l = i;
    h = k;

    while (!done) {

        /* Increment l while numbers[l] < pivot */
        while (((*memAccessCount)++, (*compCount)++, (*numbers)[l] < pivot)) {// count comp and memaccess
            ++l;
        }

        /* Decrement h while pivot < numbers[h] */
        while (((*memAccessCount)++, (*compCount)++, pivot < (*numbers)[h])) {// count comp and memaccess
            --h;
        }

        /* If there are zero or one elements remaining,
         all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
             update l and h */
            temp = (*numbers)[l];
            (*numbers)[l] = (*numbers)[h];
            (*numbers)[h] = temp;

            (*memAccessCount) += 4;// count comp mem access

            ++l;
            --h;
        }
    }

    return h;
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int* compCount, int* memAccessCount) {
    int j = 0;

    /* Base case: If there are 1 or zero elements to sort,
     partition is already sorted */
    if (i >= k) {
        return;
    }

    /* Partition the data within the array. Value j returned
     from partitioning is location of last element in low partition. */
    j = Partition(numbers, i, k, compCount, memAccessCount); // pass countCount and memAccessCount as parameter to keep count

    /* Recursively sort low partition (i to j) and
     high partition (j + 1 to k) */
    QuickSortRecurse(numbers, i, j, compCount, memAccessCount); // pass countCount and memAccessCount as parameter to keep count
    QuickSortRecurse(numbers, j + 1, k, compCount, memAccessCount); // pass countCount and memAccessCount as parameter to keep count

    return;
}

void QuickSort(std::vector<int>* numbers, int* compCount, int* memAccessCount) {
   QuickSortRecurse(numbers, 0, numbers->size() - 1, compCount, memAccessCount); // pass countCount and memAccessCount as parameter to keep count
}