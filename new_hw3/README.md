# HW3 Assignment

Within your private Github repository called `520-Assignments`, please make a new directory called `hw_3`.

For this assignment, you should copy the code from the `week3/arrays` directory to `520-Assignments/hw_3` to use as the starting point for your homework. All function prototypes for the methods you need to define are contained in the header files.

**Note**: We highly recommend that you write tests for a method you are creating **before** you implement it. 🧪

---

## Required Functions

#### Mathematical Operations
Implement the following mathematical operations for `DynamicArray`. They should all assert that the array is not empty (except `_sum`).
* `_min`: returns the minimum value in the array.
* `_max`: returns the maximum value in the array.
* `_mean`: returns the average value in the array.
* `_median`: returns the median value in the array.
* `_sum`: returns the sum of the values in the array (does not need to assert non-empty).

#### Element Access
For the `DynamicArray` ADT, write the methods `_last` and `_first` which return the value at the end or beginning of the array, respectively. Note that last and first should assert that the array is not empty.

#### Array Constructors & Manipulators
* Write a `_copy` method that produces a copy of an array. It should return an entirely new `DynamicArray` object.
* Write a method called `_range` that creates a new dynamic array with values as follows:
    ```c
    DynamicArray * a = DynamicArray_range(0, 1, 0.1); /* yields [ 0, 0.1, 0.2, ..., 1.0 ] */
    ```
* Implement the method `_concat`, which concatenates two arrays to produce a new array. For example:
    ```c
    DynamicArray * a = DynamicArray_range(0, 1, 0.1);
    DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
    DynamicArray * c = DynamicArray_concat(a, b); /* yields [ 0, 0.1, ..., 2.0 ] */
    ```
* Implement a method called `_take` that returns a sub-array of `n` elements. If the argument is positive, it takes from the beginning. If it is negative it takes from the end. If there are not enough elements, the method should return as many as it can, and set the rest to zero. For example:
    ```c
    DynamicArray * a = DynamicArray_range(1, 5, 1);
    DynamicArray * b = DynamicArray_take(a, 2);  /* yields [ 1, 2 ] */
    DynamicArray * c = DynamicArray_take(a, -2); /* yields [ 4, 5 ] */
    DynamicArray * d = DynamicArray_take(a, 7);  /* yields [ 1, 2, 3, 4, 5, 0, 0 ] */
    ```

---

## Additional Functions

* **`_filter`**: Creates a new array containing only elements that satisfy a given predicate function.
    ```c
    /* Example: Keep only positive numbers */
    int is_positive(double x) { return x > 0; }
    DynamicArray * filtered = DynamicArray_filter(arr, is_positive);
    ```
* **`_unique`**: Creates a new array with duplicate values removed, preserving the order of the first occurrence of each element.
    ```c
    /* Input: [1, 2, 2, 3, 1, 4, 2] */
    DynamicArray * unique = DynamicArray_unique(arr);
    /* Result: [1, 2, 3, 4] */
    ```
* **`_split`**: Splits an array into `n` equal-sized chunks. The last chunk may be smaller if the total size is not evenly divisible. The second parameter is the **input**: the number of chunks you *want* to create. The third parameter is an **output**: a pointer used by the function to tell you how many chunks it *actually* created. 
    
    ```c
    // Let's split the array into 3 chunks
    int desired_chunks = 3; 

    // This variable will hold the actual number of chunks created by the function
    int actual_chunks; 
    
    DynamicArray ** chunks = DynamicArray_split(arr, desired_chunks, &actual_chunks);
    ```
---

## Extra Credit:

Modify the `DynamicArray` ADT so that all constructors (`_new`, `_copy`, `_range`, `_take`, `_subarray` and `_concat`) count the number of arrays that have been constructed so far.

* Create a method `_num_arrays` that returns the number of currently allocated arrays.
* Create another method `_destroy_all` that destroys all allocated arrays.
* Create a method `_is_valid` that determines whether an array has been deallocated or not (i.e., whether its `buffer` is `NULL`). As an example, the following test should pass:
    ```c
    DynamicArray * a = DynamicArray_range(0, 1, 0.1);
    DynamicArray * b = DynamicArray_range(1.1, 2, 0.1);
    DynamicArray * c = DynamicArray_concat(a, b);

    ASSERT_EQ(DynamicArray_is_valid(a), 1);
    ASSERT_EQ(DynamicArray_num_arrays(), 3);

    DynamicArray_destroy_all();

    ASSERT_EQ(DynamicArray_is_valid(a), 0);
    ASSERT_EQ(DynamicArray_num_arrays(), 0);

    free(a);
    free(b);
    free(c);
    ```