#ifndef SOLUTIONS_H
#define SOLUTIONS_H

/**
 * Keeps a running total of all values passed to it across multiple calls.
 * @param value The value to add to the running total
 * @return The current running total
 */
int running_total(int value);

/**
 * Resets the running total back to zero.
 */
void reset_running_total(void);

/**
 * Creates a new array that is the reverse of the input array.
 * Uses calloc to allocate memory for the new array.
 * @param arr The input array
 * @param len The length of the input array
 * @return A pointer to the newly allocated reversed array (caller must free)
 */
int* reverse(int *arr, int len);

/**
 * Reverses an array in place without allocating new memory.
 * @param arr The array to reverse
 * @param len The length of the array
 */
void reverse_in_place(int *arr, int len);

/**
 * Counts the number of occurrences of a value in an array.
 * @param arr The input array
 * @param len The length of the array
 * @param value The value to count
 * @return The number of times value appears in the array
 */
int num_occurences(int *arr, int len, int value);

/**
 * Removes duplicate elements from an array, keeping first occurrence.
 * Returns a new dynamically allocated array with unique elements.
 * @param arr The input array
 * @param len The length of the input array
 * @param new_len Pointer to store the length of the result array
 * @return A pointer to the newly allocated array with duplicates removed (caller must free)
 */
int* remove_duplicates(int *arr, int len, int *new_len);

/**
 * Reverses a C-string and returns a new dynamically allocated string.
 * @param str The input string
 * @return A pointer to the newly allocated reversed string (caller must free), or NULL on error
 */
char* string_reverse(const char *str);

/**
 * Transposes a 2D matrix represented as a 1D array in row-major order.
 * @param matrix The input matrix as a 1D array
 * @param rows The number of rows in the input matrix
 * @param cols The number of columns in the input matrix
 * @return A pointer to the newly allocated transposed matrix (caller must free)
 */
int* transpose(int *matrix, int rows, int cols);

/**
 * Splits a string by a delimiter character.
 * Returns an array of dynamically allocated strings.
 * Splits a string by any delimiter character
 * Skips empty tokens (consecutive delimiters treated as one)
 * @param str The input string to split
 * @param delim The delimiter character
 * @param count Pointer to store the number of resulting strings
 * @return Array of strings (each string and the array must be freed using free_string_array)
 */
char** split_string(const char *str, char delim, int *count);

/**
 * Frees a string array created by split_string.
 * @param arr The array of strings to free
 * @param count The number of strings in the array
 */
void free_string_array(char **arr, int count);


#endif // SOLUTIONS_H