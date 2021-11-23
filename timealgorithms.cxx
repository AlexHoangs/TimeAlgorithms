#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>


#include "json.hpp"
#include "insertionsort.h"
#include "mergesort.h"
#include "quicksort.h"

class Timer { // construct class Timer
public: // make it public to access it
    clock_t start; // initialize start time
    Timer(); // start timer function
    void reset(); // reset function
    double getElapsedSeconds(); // get time in seconds function

};

Timer::Timer() { // reset timer function
    reset(); // call to reset timer
}

double Timer::getElapsedSeconds() { // get time in seconds
    return ((double)clock() - (double)start) / (double)CLOCKS_PER_SEC; // now - start time / seconds per unit
}

void Timer::reset() { // reset start time to current now
    start = clock(); // make the start equal the start time again
}

int main(int argc, char** argv) {
    std::ifstream file; // initialize file
    nlohmann::json jsonObject; // initialize sample json object

    file.open(argv[1]); // open filename given to us in args

    if (file.is_open()) { // check for successful file open
        file >> jsonObject; // read json file data to our json object
    } else {
        std::cout << "cannot open file"; // display error message to user
        exit(0); // exit program
    }

    std::cout << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess,MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime,QuickSortCompares,QuickSortMemaccess"
              << std::endl; // print csv header

    std::cout << std::fixed << std::showpoint << std::setprecision(6); // set number of decimals wanted

    for (auto itr = jsonObject.begin(); itr != jsonObject.end(); ++itr) { // begin iterating through input json object
        if (itr.key().find("Sample") == 0) { // check if object is a sample (find sample at beginning of object key)

            std::cout << itr.key() << ","; // print sample

            std::vector<int> numbers = itr.value(); // grab the sample as an int vector
            std::vector<int> numbers1 = std::vector<int>(numbers); // copy the sample to pass into func

            int numComp = 0; // initialize compare count
            int numMemAccess = 0; // initialize mem access count
            Timer t; // initialize timer


            InsertionSort(&numbers1, &numComp, &numMemAccess); // insertion sort
            std::cout << t.getElapsedSeconds() << "," << numComp << "," << numMemAccess << ","; // print results

            numbers1 = std::vector<int>(numbers); // reset num array
            t.reset(); // reset timer
            numComp = 0; // reset comp count
            numMemAccess = 0; // reset mem accesses


            MergeSort(&numbers1, &numComp, &numMemAccess); // merge sort
            std::cout << t.getElapsedSeconds() << "," << numComp << "," << numMemAccess << ","; // print results

            numbers1 = std::vector<int>(numbers); // reset
            t.reset(); // reset
            numComp = 0; // reset
            numMemAccess = 0; // reset

            QuickSort(&numbers1, &numComp, &numMemAccess); // quicksort
            std::cout << t.getElapsedSeconds() << "," << numComp << "," << numMemAccess << std::endl; // print results
        }
    }
}

// format std::cout as: sample,
// insertion sort time, # compares, and # of memory accesses
// merge sort time, # compares, and # of memory accesses
// quick sort time, # compares, and # of memory accesses