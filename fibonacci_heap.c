#include "fibonacci_heap.h"

#include <math.h>

FibonacciHeap* Create_Fibonacci_Heap() {
    FibonacciHeap* heap = (FibonacciHeap*)malloc(sizeof(FibonacciHeap));
    heap->min = NULL;
    heap->n = 0;
    return heap;
}

FibonacciNode* Create_Node(double key) {
    FibonacciNode* node = (FibonacciNode*)malloc(sizeof(FibonacciNode));
    node->key = key;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->degree = 0;
    node->mark = false;
    return node;
}

void Fib_Heap_Insert(FibonacciHeap* heap, double key) {
    FibonacciNode* node = Create_Node(key);
    
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        // Set pointers of the node being inserted
        node->left = heap->min->left;
        node->right = heap->min;

        // Adjust the left and right pointers of the adjacent elements 
        // to point to the newly created node
        heap->min->left->right = node;
        heap->min->left = node;

        if (key < heap->min->key) {
            heap->min = node;
        }
    }

    (heap->n)++;
}

FibonacciNode* Fib_Heap_Extract_Min(FibonacciHeap* heap) {
    FibonacciNode* min = heap->min;
 
    if (min != NULL) {
        if (min->child != NULL) {
            FibonacciNode* child = min->child;
            FibonacciNode* start = child;
            do {
                FibonacciNode* next = child->right;
            
                // Insert the node to the left of min
                min->left->right = child;
                child->right = min;
                child->left = min->left;
                min->left = child;

                // Set parent pointer of the child to NULL
                child->parent = NULL;
                child = next;
            } while (child != start);
        }

        // Remove the min element from the root list
        min->left->right = min->right;
        min->right->left = min->left;

        // Check if min is the only node in the root list
        if (min == min->right && min->child == NULL)
            heap->min = NULL;
        else {
            heap->min = min->right;
            Consolidate(heap);
        }
        heap->n--;
        
        return min;
    } else {
        return NULL;
    }
}

void Consolidate(FibonacciHeap* heap) {

    // Setting heap->min to the minimum element so that the loop terminates properly 
    
    // We can use this to declare an array with the size of maxDegree as the 
    // highest degree in a fibonacci heap is upper bounded by log2(n) 
    int maxDegree = (int)floor(log2(heap->n)) + 1; 

    FibonacciNode* degreeArray[maxDegree];

    for (int i = 0; i < maxDegree; i++) {
        degreeArray[i] = NULL;
    }

    FibonacciNode* w = heap->min; 
    int degree = 0;

    do {
        FibonacciNode* x = w;
        degree = x->degree;
        FibonacciNode* next = w->right;

        while(degreeArray[degree] != NULL) {
            FibonacciNode* y = degreeArray[degree];

            if(x->key > y->key) {
                FibonacciNode* temp = x;
                x = y;
                y = temp;
            }

            // Updating h->min when it becomes a child
            if(y == heap->min) {
                heap->min = heap->min->right;
            }

            // If the next element becomes the child, we update next
            // so that the loop continues
            if(y == next) {
                next = y->right;
            }

            // Removing y from the root list
            y->left->right = y->right;
            y->right->left = y->left;
            y->parent = x;
            y->mark = false;

            // Making y the child of x
            if (x->child == NULL) {
                x->child = y;
                y->left = y;
                y->right = y;
            } else {
                FibonacciNode* child = x->child;
                y->left = child;
                y->right = child->right;
                child->right->left = y;
                child->right = y;
            }

            x->degree++;

            degreeArray[degree] = NULL;
            degree++;
        }

        degreeArray[degree] = x;
        w = next;
    } while(w != heap->min);

    //Updates the heap->min to the new lowest element from the root list
    Update_Minimum(heap);

}

void Fib_Heap_Decrease_Key(FibonacciHeap* heap, FibonacciNode* x, double key) {
    x->key = key;
    FibonacciNode* y = x->parent;

    if (y != NULL && x->key < y->key) {
        Cut(heap, x, y);
        Cascading_Cut(heap, y);
    }

    if (x->key < heap->min->key) {
        heap->min = x;
    }
}

void Cut(FibonacciHeap* heap, FibonacciNode* x, FibonacciNode* y) {
    // Remove x from the child list of y
    if (y->child == x) {
        y->child = (x->right != x) ? x->right : NULL;
    }
    x->left->right = x->right;
    x->right->left = x->left;

    y->degree--;

    // Add x to the root list of H
    if (heap->min == NULL) {
        x->left = x->right = x;
        heap->min = x;
    } else {
        x->right = heap->min->right;
        x->left = heap->min;
        heap->min->right->left = x;
        heap->min->right = x;
    }

    x->parent = NULL; 
    x->mark = false;
}

void Cascading_Cut(FibonacciHeap *heap, FibonacciNode *y) {
    FibonacciNode* z = y->parent;
    
    if (z != NULL) {
        if (y->mark == false) {
            y->mark = true;
        } else {
            Cut(heap, y, z);
            Cascading_Cut(heap, z);
        }
    }
}

void Update_Minimum(FibonacciHeap* heap) {
    FibonacciNode* cur = heap->min;
    FibonacciNode* curMin = heap->min; 
    do {
        if(cur->key < heap->min->key) {
            heap->min = cur;
        }
        cur = cur->right;
    } while(cur != curMin);
}