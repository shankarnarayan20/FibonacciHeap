# Fibonacci Heap Implementation

This project implements a **Fibonacci Heap** in C with the following operations:

- **Insertion** (`Fib_Heap_Insert`)
- **Extract-Min** (`Fib_Heap_Extract_Min`)
- **Decrease-Key** (`Fib_Heap_Decrease_Key`)

## Project Structure

```
├── fibonacci_heap.c      # Fibonacci Heap function implementations
├── fibonacci_heap.h      # Fibonacci Heap data structure definitions
├── main.c                # Main program to test the Fibonacci Heap
├── keys_100.txt          # Sample input file with 100 keys
├── keys_1000.txt         # Sample input file with 1000 keys
├── keys_10000.txt        # Sample input file with 10000 keys
├── README.md             # Documentation
├── output.txt            # Sample output
```

## Data Structures

### FibonacciNode (Defined in `fibonacci_heap.h`)
```c
typedef struct FibonacciNode {
    struct FibonacciNode* parent;
    struct FibonacciNode* child;
    struct FibonacciNode* left;
    struct FibonacciNode* right;
    double key;
    int degree;
    bool mark;
} FibonacciNode;
```

### FibonacciHeap (Defined in `fibonacci_heap.h`)
```c
typedef struct FibonacciHeap {
    FibonacciNode* min;
    int n;
} FibonacciHeap;
```

## Compilation and Execution

### Compilation
Use **GCC** to compile the code:
```sh
gcc fibonacci_heap.c main.c -lm
```

### Execution
Run the compiled executable:
```sh
./a.out
```

## Sample Output
```
Running with the file keys_100.txt

Minimum after extracting 1 times: 604.00
Selected random node: 14275.00
After reducing it's key by 5: 14270.00
...
Total time for Extract-Min: 10 microseconds
Total time for Decrease-Key: 577 nanoseconds
```
## Performance Analysis

The performance of Fibonacci Heap operations varies with the input size.
The table shows the output from one execution.

| Heap Size | Total Extract-Min Time (microseconds) | Total Decrease-Key Time (nanoseconds) |
|-----------|---------------------------------------|---------------------------------------|
| 100       | ~10                                   | ~577                                  |
| 1,000     | ~60                                   | ~585                                  |
| 10,000    | ~195                                  | ~602                                  |

- **Extract-Min Complexity**: The amortized complexity of Extract-Min is **O(log n)**, but the actual time depends on consolidation operations.
- **Decrease-Key Complexity**: The Decrease-Key operation runs in **O(1)** amortized time but can trigger cascading cuts, affecting real-world performance.
- As the heap size increases, Extract-Min takes longer to execute due to increased tree restructuring during the consolidate operation but Decrease-Key time remains constant through all the three runs.

## System Requirements
- **Operating System**: Ubuntu 24.04
- **Compiler**: GCC 13.3.0
