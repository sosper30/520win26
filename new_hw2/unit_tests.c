#include "solutions.h"
#include "gtest/gtest.h"

namespace {

TEST(HW2, RunningTotal) {
    reset_running_total();  // Reset before test
    ASSERT_EQ(running_total(1), 1);
    ASSERT_EQ(running_total(1), 2);
    ASSERT_EQ(running_total(5), 7);
    ASSERT_EQ(running_total(-3), 4);
}

TEST(HW2, RunningTotalReset) {
    reset_running_total();
    ASSERT_EQ(running_total(10), 10);
    ASSERT_EQ(running_total(5), 15);
    reset_running_total();
    ASSERT_EQ(running_total(1), 1);
}

TEST(HW2, Reverse) {
    int x[] = {10, 20, 30, 40, 50};
    int *y = reverse(x, 5);
    ASSERT_NE(y, nullptr);
    ASSERT_EQ(y[0], 50);
    ASSERT_EQ(y[1], 40);
    ASSERT_EQ(y[2], 30);
    ASSERT_EQ(y[3], 20);
    ASSERT_EQ(y[4], 10);
    free(y);
}

TEST(HW2, ReverseEmpty) {
    int *y = reverse(NULL, 0);
    ASSERT_EQ(y, nullptr);
}

TEST(HW2, ReverseSingleElement) {
    int x[] = {42};
    int *y = reverse(x, 1);
    ASSERT_NE(y, nullptr);
    ASSERT_EQ(y[0], 42);
    free(y);
}

TEST(HW2, ReverseInPlace) {
    int x[] = {10, 20, 30, 40, 50};
    reverse_in_place(x, 5);
    ASSERT_EQ(x[0], 50);
    ASSERT_EQ(x[1], 40);
    ASSERT_EQ(x[2], 30);
    ASSERT_EQ(x[3], 20);
    ASSERT_EQ(x[4], 10);
}

TEST(HW2, ReverseInPlaceEvenLength) {
    int x[] = {1, 2, 3, 4};
    reverse_in_place(x, 4);
    ASSERT_EQ(x[0], 4);
    ASSERT_EQ(x[1], 3);
    ASSERT_EQ(x[2], 2);
    ASSERT_EQ(x[3], 1);
}

TEST(HW2, ReverseInPlaceSingleElement) {
    int x[] = {42};
    reverse_in_place(x, 1);
    ASSERT_EQ(x[0], 42);
}

TEST(HW2, NumOccurences) {
    int a[] = {1, 1, 2, 3, 1, 4, 5, 2, 20, 5};
    ASSERT_EQ(num_occurences(a, 10, 1), 3);
    ASSERT_EQ(num_occurences(a, 10, 2), 2);
    ASSERT_EQ(num_occurences(a, 10, 5), 2);
    ASSERT_EQ(num_occurences(a, 10, 20), 1);
    ASSERT_EQ(num_occurences(a, 10, 99), 0);
}

TEST(HW2, NumOccurencesEmpty) {
    ASSERT_EQ(num_occurences(NULL, 0, 1), 0);
}

TEST(HW2, RemoveDuplicates) {
    int a[] = {1, 2, 2, 3, 1, 4, 5, 2};
    int new_len;
    int *result = remove_duplicates(a, 8, &new_len);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(new_len, 5);
    ASSERT_EQ(result[0], 1);
    ASSERT_EQ(result[1], 2);
    ASSERT_EQ(result[2], 3);
    ASSERT_EQ(result[3], 4);
    ASSERT_EQ(result[4], 5);
    free(result);
}

TEST(HW2, RemoveDuplicatesNoDuplicates) {
    int a[] = {1, 2, 3, 4, 5};
    int new_len;
    int *result = remove_duplicates(a, 5, &new_len);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(new_len, 5);
    for (int i = 0; i < 5; i++) {
        ASSERT_EQ(result[i], a[i]);
    }
    free(result);
}

TEST(HW2, RemoveDuplicatesAllSame) {
    int a[] = {7, 7, 7, 7};
    int new_len;
    int *result = remove_duplicates(a, 4, &new_len);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(new_len, 1);
    ASSERT_EQ(result[0], 7);
    free(result);
}

TEST(HW2, StringReverse) {
    char *result = string_reverse("hello");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result, "olleh");
    free(result);
}

TEST(HW2, StringReverseEmpty) {
    char *result = string_reverse("");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result, "");
    free(result);
}

TEST(HW2, StringReverseSingleChar) {
    char *result = string_reverse("a");
    ASSERT_NE(result, nullptr);
    ASSERT_STREQ(result, "a");
    free(result);
}

TEST(HW2, StringReverseNull) {
    char *result = string_reverse(NULL);
    ASSERT_EQ(result, nullptr);
}

TEST(HW2, Transpose) {
    // 2x3 matrix: [[1,2,3], [4,5,6]]
    int matrix[] = {1, 2, 3, 4, 5, 6};
    int *result = transpose(matrix, 2, 3);
    ASSERT_NE(result, nullptr);
    // Expected 3x2: [[1,4], [2,5], [3,6]]
    int expected[] = {1, 4, 2, 5, 3, 6};
    for (int i = 0; i < 6; i++) {
        ASSERT_EQ(result[i], expected[i]);
    }
    free(result);
}

TEST(HW2, TransposeSquare) {
    // 3x3 matrix
    int matrix[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int *result = transpose(matrix, 3, 3);
    ASSERT_NE(result, nullptr);
    // Expected: [[1,4,7], [2,5,8], [3,6,9]]
    int expected[] = {1, 4, 7, 2, 5, 8, 3, 6, 9};
    for (int i = 0; i < 9; i++) {
        ASSERT_EQ(result[i], expected[i]);
    }
    free(result);
}

TEST(HW2, TransposeSingleElement) {
    int matrix[] = {42};
    int *result = transpose(matrix, 1, 1);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(result[0], 42);
    free(result);
}

TEST(HW2, SplitString) {
    int count;
    char **result = split_string("apple,banana,cherry", ',', &count);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(count, 3);
    ASSERT_STREQ(result[0], "apple");
    ASSERT_STREQ(result[1], "banana");
    ASSERT_STREQ(result[2], "cherry");
    free_string_array(result, count);
}

TEST(HW2, SplitStringSingleToken) {
    int count;
    char **result = split_string("hello", ',', &count);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(count, 1);
    ASSERT_STREQ(result[0], "hello");
    free_string_array(result, count);
}

TEST(HW2, SplitStringMultipleDelimiters) {
    int count;
    char **result = split_string("one,,two,,,three", ',', &count);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(count, 3);
    ASSERT_STREQ(result[0], "one");
    ASSERT_STREQ(result[1], "two");
    ASSERT_STREQ(result[2], "three");
    free_string_array(result, count);
}

TEST(HW2, SplitStringLeadingTrailing) {
    int count;
    char **result = split_string(",apple,banana,", ',', &count);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(count, 2);
    ASSERT_STREQ(result[0], "apple");
    ASSERT_STREQ(result[1], "banana");
    free_string_array(result, count);
}

TEST(HW2, SplitStringEmpty) {
    int count;
    char **result = split_string("", ',', &count);
    ASSERT_EQ(result, nullptr);
    ASSERT_EQ(count, 0);
}

TEST(HW2, SplitStringSpaceDelimiter) {
    int count;
    char **result = split_string("hello world foo bar", ' ', &count);
    ASSERT_NE(result, nullptr);
    ASSERT_EQ(count, 4);
    ASSERT_STREQ(result[0], "hello");
    ASSERT_STREQ(result[1], "world");
    ASSERT_STREQ(result[2], "foo");
    ASSERT_STREQ(result[3], "bar");
    free_string_array(result, count);
}



}  // namespace

