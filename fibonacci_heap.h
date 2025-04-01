#ifndef FIBONACCI_HEAP_H
#define FIBONACCI_HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct FibonacciNode {
    struct FibonacciNode* parent;
    struct FibonacciNode* child;
    struct FibonacciNode* left;
    struct FibonacciNode* right;
    double key;
    int degree;
    bool mark;
} FibonacciNode;

typedef struct FibonacciHeap {
    FibonacciNode* min;
    int n;
} FibonacciHeap;



FibonacciHeap* Create_Fibonacci_Heap();
FibonacciNode* Create_Node(double key);

void Fib_Heap_Insert(FibonacciHeap* heap, double key);

FibonacciNode* Fib_Heap_Extract_Min(FibonacciHeap* heap);
void Consolidate(FibonacciHeap* heap);
void Update_Minimum(FibonacciHeap* heap);

void Fib_Heap_Decrease_Key(FibonacciHeap* heap, FibonacciNode* x, double key);
void Cut(FibonacciHeap* heap, FibonacciNode* x, FibonacciNode* y);
void Cascading_Cut(FibonacciHeap *heap, FibonacciNode *y);

#endif
