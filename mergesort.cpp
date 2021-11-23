// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h"

void MergeSort(std::vector<int>* numbers, int* compCount, int* memAccessCount) { // pass compCount and memAccessCount to count and iterate
   MergeSortRecurse(numbers, 0, numbers->size() - 1, compCount, memAccessCount); // pass compCount and memAccessCount to count
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int* compCount, int* memAccessCount) {
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, compCount, memAccessCount); // pass compCount and memAccessCount
      MergeSortRecurse(numbers, j + 1, k, compCount, memAccessCount); // pass compCount and memAccessCount
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, compCount, memAccessCount); // pass compCount and memAccessCount
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int* compCount, int* memAccessCount) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if (((*memAccessCount) += 2, (*compCount)++, (*numbers)[leftPos] < (*numbers)[rightPos])) { // count comp and memaccess
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         (*memAccessCount)+= 2;// count mem access
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         (*memAccessCount) += 2;// count mem access
         ++rightPos;

      }
       ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      (*memAccessCount) += 2;// count comp mem access
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      (*memAccessCount) += 2;// count comp mem access
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      (*memAccessCount) += 2;// count comp mem access
   }
}