#include "CCDSALG_MCO1.c"

#define REPEAT 1000
#define LENGTH 1024

#define VERBOSE 1
#define SHORT 2

long int runInsertionSort(String inputString, int printStyle) {

    int insertionSuffixArray[LENGTH];

    // Note Start Time
    long insertionTime = getMicroTime();

    // Run Bubble Sort
    InsertionSort(inputString, LENGTH, insertionSuffixArray);

    // Note End Time
    insertionTime = getMicroTime() - insertionTime;


    // Print Time
    switch (printStyle) {
        case VERBOSE:
            printf("\nInsertion Sort Runtime:      %15ld microseconds\n", insertionTime);
            break;
        case SHORT:
            printf("%ld ", insertionTime);
            break;
    }

    return insertionTime;
}

long runMergeSort(String inputString, int printStyle) {

    int insertionSuffixArray[LENGTH];

    // Note Start Time
    long quickTime = getMicroTime();

    // Run Merge Sort
    QuickSort(inputString, LENGTH, insertionSuffixArray);

    // Note End Time
    quickTime = getMicroTime() - quickTime;


    // Print Time
    switch (printStyle) {
        case VERBOSE:
            printf("Quick Sort Runtime:          %15ld microseconds\n", quickTime);
            break;
        case SHORT:
            printf("%ld ", quickTime);
            break;
    }

    return quickTime;
}

void printAverageTime(int printStyle, long insertionAvgTime, long quickAvgTime) {

    printf("\n");

    switch (printStyle) {

        case VERBOSE:
            if (0 < insertionAvgTime)
                printf("Average Insertion Sort Runtime: %15.2f microseconds\n",
                        ((double)(insertionAvgTime) / REPEAT));
            if (0 < quickAvgTime)
                printf("Average Quick Sort Runtime:     %15.2f microseconds\n",
                        ((double)(quickAvgTime) / REPEAT));
            break;

        case SHORT:
            if (0 < insertionAvgTime)
                printf("%15.7f ", (double)(insertionAvgTime) / REPEAT);
            if (0 < quickAvgTime)
                printf("%15.7f ", (double)(quickAvgTime) / REPEAT);
            break;
    }
}

int main()
{
    String inputString = "";
    // Declare Monitor Variables
    // Initiate Average Time Values
    long insertionAvgTime = 0;
    long quickAvgTime = 0;
    int i;



    // For loop to repeat the program
    // Needs to start from negative to reduce effects of 1st few runs being slower
    for (i = 0; i < REPEAT; i++) {

        // Randomize the String
        generateRandomString(LENGTH, inputString);
            // Default String
        // strcpy(inputString, "tgtgtgtgcaccg");



        // Add Time Differences to Average
        if (i >= 0) {
            insertionAvgTime += runInsertionSort(inputString, 2);
            // quickAvgTime += runMergeSort(inputString, 2);
        }
        else {
            runInsertionSort(inputString, 0);
            runMergeSort(inputString, 0);
        }
    }



    // Display Average Time Differences
    printAverageTime(VERBOSE, insertionAvgTime, quickAvgTime);
}
