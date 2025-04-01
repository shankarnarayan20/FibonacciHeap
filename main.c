#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "fibonacci_heap.h"

// Reads data from the file and returns an array of "double" values
double* getFileData(char* filename, int size) {
    
    FILE *file;
    double *data = (double*)malloc(size * sizeof(double));
    file = fopen(filename, "r");

    if (file == NULL || data == NULL) {
        free(data);
        return NULL;
    }

    int temp;
    for (int i = 0; i < size; i++) {
        fscanf(file, "%d", &temp);
        data[i] = (double)temp;
    }

    fclose(file);
    return data;
}

// Builds a Fibonacci heap with the data from the given file name
FibonacciHeap* buildFibHeap(char* filename, int size) {
    FibonacciHeap* heap = Create_Fibonacci_Heap();
    double *keys;
    keys = getFileData(filename, size);

    for(int i = 0; i < size; i++) {
        Fib_Heap_Insert(heap, keys[i]);
    }

    return heap;
}

int randomInRange(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Selects a random node from the heap
FibonacciNode* selectRandomNode(FibonacciHeap* heap, FibonacciNode* parentNode) {
    
    // Element can be a node from the root list or can be a node from any depth
    int randomNumber = 0;
    FibonacciNode* current = NULL;
    
    if(parentNode) {
        randomNumber = randomInRange(0, parentNode->degree);
        current = parentNode->child;
    } else {
        randomNumber = randomInRange(0, (int)floor(log2(heap->n)) + 1);
        current = heap->min;
    }

    for(int i = 0; i < randomNumber; i++) {
        current = current->right;
    }

    if (current->degree) {
        int goToChildren = randomInRange(0, 1);
        if(goToChildren) {
            return selectRandomNode(NULL, current);
        } else return current;
    }
    else return current;

}

// Perform the operations in given in the question
void operations(FibonacciHeap* heap, int size) {
    struct timeval start_t, finish_t;
    long extractMinTime = 0, decreaseKeyTime = 0;

    FibonacciNode* minimum = NULL;

    printf("\nRunning with the file keys_%d.txt\n", size);
    for(int i = 0; i < 20; i++) {
        // Extract-Min operation timing in microseconds
        gettimeofday(&start_t, NULL);
        minimum = Fib_Heap_Extract_Min(heap);
        gettimeofday(&finish_t, NULL);
        extractMinTime += (finish_t.tv_usec - start_t.tv_usec);
        printf("\nMinimum after extracting %d times: %.2f", i + 1, minimum->key);

        FibonacciNode* randomNode = selectRandomNode(heap, NULL);
        printf("\nSelected random node: %.2f", randomNode->key);

         // Decrease-Key operation timing in nanoseconds
         struct timespec start_ns, finish_ns;
         clock_gettime(CLOCK_MONOTONIC, &start_ns);
         Fib_Heap_Decrease_Key(heap, randomNode, randomNode->key - 5);
         clock_gettime(CLOCK_MONOTONIC, &finish_ns);
         
         // Calculate the time difference in nanoseconds
         long long decreaseKeyDiff = (finish_ns.tv_sec - start_ns.tv_sec) * 1000000000LL + (finish_ns.tv_nsec - start_ns.tv_nsec);
         decreaseKeyTime += decreaseKeyDiff;
        printf("\nAfter reducing it's key by 5: %.2f", randomNode->key);
    }

    printf("\n\nTotal time for Extract-Min: %ld microseconds", extractMinTime);
    printf("\nTotal time for Decrease-Key: %ld nanoseconds\n", decreaseKeyTime);

    printf("\n\n");

}

int main() {

    srand(time(0));
    int sizes[3] = {100, 1000, 10000};

    for(int i = 0; i < (sizeof(sizes) / sizeof(int)); i++) {
        char keyName[20];
        sprintf(keyName, "keys_%d.txt", sizes[i]);
        FibonacciHeap* heap = buildFibHeap(keyName, sizes[i]);
        operations(heap, sizes[i]);
    }

    return 0;
}