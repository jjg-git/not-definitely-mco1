#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#define NUM_LETTERS 1024
// #define NUM_LETTERS 13
// Default String

typedef char String[NUM_LETTERS + 1];

typedef struct Suffix
{
    int index;
    String string;
} SuffixStruct;

/* ----- ----- ----- Method Headers  ----- ----- ----- */

/* ----- ----- ----- General Methods ----- ----- ----- */

/**
 * printArray
 * - Prints the array of integers
 *
 * @param array Array of integers
 * @param length Length of the array
 */
void printArray(int array[], int length) {

    int i;

    // For each element in the array
    for (i = 0; i < length; i++) {

        // Print the element
        printf("%d  ", array[i]);
    }

    printf("\n");
}



/**
 * generateRandomString
 * - Generates a random String of length n
 *
 * @param length Length of the String
 *
 * @return Random String
 */
void generateRandomString(int length, String randomString) {

    // Initialize the String of Possible Characters
    char alphabet[4] = {'a', 'c', 'g', 't'};
    int i;


    // For the length of the string
    for (i = 0; i < length; i++) {

        // Append a random character
        randomString[i] = alphabet[rand() % 4];
    }
}



long int getMicroTime() {

    struct timeval tv;

    gettimeofday(&tv,NULL);

    // printf("microseconds : %ld\n\n", tv.tv_sec * 1000000 + tv.tv_usec);

    return tv.tv_sec * 1000000 + tv.tv_usec;
}



/**
 * initializeSuffixArray
 * - Initializes the suffix array
 *
 * @param text String to be sorted
 *
 * @return SuffixStruct[] Array of suffixes
 */
void initializeSuffixArray(SuffixStruct suffixArray[], String text, int length) {

    int i;

    // For each suffix
    for (i = 0; i < length; i++) {

        // Add the suffix to the array
        strcpy(suffixArray[i].string, &text[i]);
        suffixArray[i].index = i;

        printf("%5d: %s\n", suffixArray[i].index, suffixArray[i].string);
    }
}



/**
 * swapArrayElements
 * - Swaps two elements in an array of SuffixStructs
 *
 * @param suffixArray Array of suffixes
 * @param index1 Index of the first suffix
 * @param index2 Index of the second suffix
 */
void swapArrayElements(SuffixStruct suffixArray[], int index1, int index2) {

    // Swap the elements
    SuffixStruct temp = suffixArray[index1];

    suffixArray[index1] = suffixArray[index2];

    suffixArray[index2] = temp;
}



/**
 * getArrayIndices
 * - Returns an array of the indices of the suffixes
 *
 * @param suffixArray Array of suffixes
 *
 * @return int[] Array of indices
 */
void getArrayIndices(SuffixStruct suffixArray[], int length, int indices[]) {

    int i;

    // For each suffix
    for (i = 0; i < length; i++) {

        // Add the index to the array
        indices[i] = suffixArray[i].index;
    }
}





/* ----- ----- ----- Insertion Sort ----- ----- ----- */

/**
 * InsertionSort
 * - Sorts the suffixes of a string using Insertion Sort
 *
 * @param T String to be sorted
 * @param n Length of the String
 *
 * @return int[] Array of indices of the sorted Suffix Array
 */
void InsertionSort (String T, int n, int indices[]) {

    // Initialize the suffix array
    SuffixStruct* suffixArray = (SuffixStruct*) malloc(n * sizeof(SuffixStruct));
    SuffixStruct key;
    int i, j;


    initializeSuffixArray(suffixArray, T, n);


    // For each suffix
    for (i = 1; i < n; i++) {

        // Set the key
        key = suffixArray[i];
        j = i - 1;


        // While the key is less than the previous suffix
        while (j >= 0 && strcmp(suffixArray[j].string, key.string) > 0) {

            // Move the previous suffix to the right
            suffixArray[j + 1] = suffixArray[j];
            j--;
        }

        // Insert the key
        suffixArray[j+1] = key;
    }


    // Return the sorted suffix array
    getArrayIndices(suffixArray, n, indices);


    // Free the memory
    free(suffixArray);
}





/* ----- ----- ----- Quick Sort ----- ----- ----- */

/**
 * partition
 * - Partitions the array into two sub-arrays
 *
 * @param suffixArray ArrayOfSuffixes object containing the suffixes of the string
 * @param startIndex Starting index of the array
 * @param endIndex Ending index of the array
 *
 * @return int Index of the partition
 */
int partition(SuffixStruct suffixArray[], int startIndex, int endIndex) {

    String pivotString;
    // Initialize the partition index
    int i = startIndex - 1;
    int j;


    // Set the pivot
    strcpy(pivotString, suffixArray[endIndex].string);


    // For each element in the array
    for (j = startIndex; j < endIndex; j++) {

        // If the element is less than the pivot
        if (strcmp(suffixArray[j].string, pivotString) < 0) {

            // Increment the partition index
            i++;
            // Swap the elements
            swapArrayElements(suffixArray, i, j);
        }
    }

    // Swap the pivot with the partition index
    swapArrayElements(suffixArray, i + 1, endIndex);


    // Return the partition index
    return i + 1;
}

/**
 * quickSort
 * - Sorts the suffixes of a string using Quick Sort
 *
 * @param suffixArray ArrayOfSuffixes object containing the suffixes of the string
 * @param startIndex Starting index of the array
 * @param endIndex Ending index of the array
 */
void quickSort(SuffixStruct suffixArray[], int startIndex, int endIndex) {

    // If the array has more than one element
    if (startIndex < endIndex) {

        // Partition the array
        int partitionIndex = partition(suffixArray, startIndex, endIndex);

        // Sort the left partition
        quickSort(suffixArray, startIndex, partitionIndex - 1);
        // Sort the right partition
        quickSort(suffixArray, partitionIndex + 1, endIndex);
    }
}

/**
 * QuickSort
 * - Sorts the suffixes of a string using Quick Sort
 *
 * @param T String to be sorted
 * @param n Length of the String
 *
 * @return int[] Array of indices of the sorted Suffix Array
 */
void QuickSort (SuffixStruct suffixArray[], String T, int n, int indices[]) {

    // Declare the suffix array
    // SuffixStruct* suffixArray = (SuffixStruct*) malloc(n * sizeof(SuffixStruct));

    // Initialize the array of indices
    // initializeSuffixArray(suffixArray, T, n);

    // Start the quick sort
    quickSort(suffixArray, 0, n - 1);

    // Return the sorted suffix array
    getArrayIndices(suffixArray, n, indices);

    // Free the memory
    // free(suffixArray);
}


/* ----- ----- ----- Main ----- ----- ----- */

int main() {

    // Initialize Random String
    String inputString = "";
    generateRandomString(NUM_LETTERS, inputString);
        // Default String
    // strcpy(inputString, "tgtgtgtgcaccg");

    // Suffix Array Results
    int insertionSuffixArray[NUM_LETTERS];
    int quickSuffixArray[NUM_LETTERS];
    // Time variables
    long insertionSortTime;
    long quickSortTime;

    // Declare the suffix array
    // SuffixStruct suffixArray = (SuffixStruct*) malloc(n * sizeof(SuffixStruct));
    SuffixStruct suffixArray[NUM_LETTERS];

    // Initialize the array of indices
    initializeSuffixArray(suffixArray, inputString, NUM_LETTERS);

    // Get Random Seed
    srand(time(NULL));


    // Print the input string
    printf("Input String: \"%s\"\n\n", inputString);
    
    // printSuffixArray()
    
    // Print Time
    // getMicroTime();


    // Insertion Sort
    // Start Time
    insertionSortTime = getMicroTime();
    // Run Insertion Sort
    InsertionSort(inputString, NUM_LETTERS, insertionSuffixArray);
    // End Time
    insertionSortTime = getMicroTime() - insertionSortTime;
    // Print Results
    // printArray(insertionSuffixArray, strlen(inputString));


    // Quick Sort
    // Start Time
    quickSortTime = getMicroTime();
    // Run Quick Sort
    QuickSort(suffixArray, inputString, NUM_LETTERS, quickSuffixArray);
    // End Time
    quickSortTime = getMicroTime() - quickSortTime;
    // Print Results
    // printArray(quickSuffixArray, strlen(inputString));


    // Print times
    printf("\nInsertion Sort Time: %10ld microseconds\n", insertionSortTime);
    printf("Quick Sort Time:     %10ld microseconds\n", quickSortTime);



    return 0;
}
