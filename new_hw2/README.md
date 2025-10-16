# HW2 Assignment

Within your private Github repository called `520-Assignments`, please make a new directory called `hw_2`.

For this assignment, you will write a set of functions that are mostly unrelated, but for convenience, we will put them into one source file and one header file. Your homework 2 directory should look like:

```
- 520-Assignments/
  - hw_2/
    - solutions/
      - main.c
      - unit_tests.c
      - solutions.h
      - solutions.c
      - Makefile
```

In the first directory, the `unit_tests.c` should include `solutions.h` file, which should have all your function declarations in it. The implementations of those functions should be put in `solutions.c`.

## Part 1: Basic Functions

### Exercise 1: Running Total

Write a function called `running_total` that keeps track of the sum of the arguments it has been called with over time. Something like the following test should pass.

```c
TEST(HW2, RunningTotal) {
    ASSERT_EQ(running_total(1),  1);
    ASSERT_EQ(running_total(1),  2);
    ASSERT_EQ(running_total(5),  7);
    ASSERT_EQ(running_total(-3), 4);
}
```

Also write a function called `reset_running_total` that resets the running total back to zero.

### Exercise 2: Reverse Array

Write a function called `reverse` that takes an array and its length, and returns a new array that is the reverse of the given array. The function should use `calloc` to create space for the new array. A test for this might look like:

```c
TEST(HW2, Reverse) {
    int x[] = {10, 20, 30, 40, 50};
    int *y = reverse(x, 5);
    ASSERT_EQ(y[0], 50);
    ASSERT_EQ(y[1], 40);
    ASSERT_EQ(y[2], 30);
    ASSERT_EQ(y[3], 20);
    ASSERT_EQ(y[4], 10);
    free(y);
}
```

### Exercise 3: Reverse In Place

Write a function called `reverse_in_place` which takes an array and its length, and reverses it in place. Something like the following test should pass.

```c
TEST(HW2, ReverseInPlace) {
    int x[] = {10, 20, 30, 40, 50};
    reverse_in_place(x, 5);
    ASSERT_EQ(x[0], 50);
    ASSERT_EQ(x[1], 40);
    ASSERT_EQ(x[2], 30);
    ASSERT_EQ(x[3], 20);
    ASSERT_EQ(x[4], 10);
}
```

### Exercise 4: Count Occurrences

Write a function called `num_occurences` that takes an array of integers, a length, and a value and returns the number of occurrences of that value in the array.

```c
TEST(HW2, NumOccurences) {
    int a[] = {1, 1, 2, 3, 1, 4, 5, 2, 20, 5};
    ASSERT_EQ(num_occurences(a, 10, 1), 3);
}
```
### Exercise 5: Remove Duplicates

Write a function called `remove_duplicates` that takes an array of integers and its length, and returns a new array containing only the unique elements in their order of first occurrence. The function should also update an output parameter to indicate the new array's length. Use `malloc` to allocate space for the new array.

```c
TEST(HW2, RemoveDuplicates) {
    int a[] = {1, 2, 2, 3, 1, 4, 5, 2};
    int new_len;
    int *result = remove_duplicates(a, 8, &new_len);
    ASSERT_EQ(new_len, 5);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 4);
    ASSERT_EQ(result[4], 5);
    free(result);
}
```

### Exercise 6: String Reverse

Write a function called `string_reverse` that takes a C-string and returns a new dynamically allocated string that is the reverse of the input string. Handle NULL input by returning NULL.

```c
TEST(HW2, StringReverse) {
    char *result = string_reverse("hello");
    ASSERT_STREQ(result, "olleh");
    free(result);
}
```

### Exercise 7: Transpose Matrix

Write a function called `transpose` that takes a 2D matrix represented as a 1D array in row-major order, along with the number of rows and columns, and returns a new transposed matrix. For example, a 2×3 matrix becomes a 3×2 matrix.

```c
TEST(HW2, Transpose) {
    // 2x3 matrix: [[1,2,3], [4,5,6]]
    int matrix[] = {1, 2, 3, 4, 5, 6};
    int *result = transpose(matrix, 2, 3);
    // Expected 3x2: [[1,4], [2,5], [3,6]]
    int expected[] = {1, 4, 2, 5, 3, 6};
    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(result[i], expected[i]);
    }
    free(result);
}
```

### Exercise 8: Split String

Write a function called `split_string` that splits a string by a delimiter character and returns an array of strings. The function should also update an output parameter with the count of resulting strings. Consecutive delimiters should be treated as a single separator (skip empty tokens).

Also write a helper function `free_string_array` that properly frees all memory allocated by `split_string`.

```c
TEST(HW2, SplitString) {
    int count;
    char **result = split_string("apple,banana,cherry", ',', &count);
    ASSERT_EQ(count, 3);
    ASSERT_STREQ(result[0], "apple");
    ASSERT_STREQ(result[1], "banana");
    ASSERT_STREQ(result[2], "cherry");
    free_string_array(result, count);
}
```

## Requirements

- All dynamically allocated memory must be properly freed. Your code will be tested to ensure there are no memory leaks.
- All functions should handle edge cases appropriately (NULL pointers, empty arrays, etc.)
