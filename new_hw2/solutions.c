#include <stdlib.h>
#include <string.h>
#include "solutions.h"

// Shared static variable for running_total and reset_running_total
static int total = 0;

int running_total(int value) {
    total += value;
    return total;
}

void reset_running_total(void) {
    total = 0;
}

int* reverse(int *arr, int len) {
    if (arr == NULL || len <= 0) {
        return NULL;
    }
    
    int *reversed = (int*)calloc(len, sizeof(int));
    if (reversed == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < len; i++) {
        reversed[i] = arr[len - 1 - i];
    }
    
    return reversed;
}

void reverse_in_place(int *arr, int len) {
    if (arr == NULL || len <= 0) {
        return;
    }
    
    int left = 0;
    int right = len - 1;
    
    while (left < right) {
        // Swap elements
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;
        
        left++;
        right--;
    }
}

int num_occurences(int *arr, int len, int value) {
    if (arr == NULL || len <= 0) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    
    return count;
}

int* remove_duplicates(int *arr, int len, int *new_len) {
    if (arr == NULL || len <= 0 || new_len == NULL) {
        if (new_len != NULL) {
            *new_len = 0;
        }
        return NULL;
    }
    
    // First pass: count unique elements
    int unique_count = 0;
    for (int i = 0; i < len; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            unique_count++;
        }
    }
    
    // Allocate memory for result
    int *result = (int*)malloc(unique_count * sizeof(int));
    if (result == NULL) {
        *new_len = 0;
        return NULL;
    }
    
    // Second pass: fill result with unique elements
    int result_idx = 0;
    for (int i = 0; i < len; i++) {
        int is_duplicate = 0;
        for (int j = 0; j < i; j++) {
            if (arr[i] == arr[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            result[result_idx++] = arr[i];
        }
    }
    
    *new_len = unique_count;
    return result;
}

char* string_reverse(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    // Get string length
    int len = strlen(str);
    
    // Allocate memory for reversed string (including null terminator)
    char *reversed = (char*)malloc((len + 1) * sizeof(char));
    if (reversed == NULL) {
        return NULL;
    }
    
    // Reverse the string
    for (int i = 0; i < len; i++) {
        reversed[i] = str[len - 1 - i];
    }
    reversed[len] = '\0';
    
    return reversed;
}

int* transpose(int *matrix, int rows, int cols) {
    if (matrix == NULL || rows <= 0 || cols <= 0) {
        return NULL;
    }
    
    // Allocate memory for transposed matrix (cols x rows)
    int *result = (int*)malloc(rows * cols * sizeof(int));
    if (result == NULL) {
        return NULL;
    }
    
    // Transpose: element at [i][j] goes to [j][i]
    // In 1D: matrix[i*cols + j] goes to result[j*rows + i]
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[j * rows + i] = matrix[i * cols + j];
        }
    }
    
    return result;
}

char** split_string(const char *str, char delim, int *count) {
    if (str == NULL || count == NULL) {
        if (count != NULL) {
            *count = 0;
        }
        return NULL;
    }
    
    // Count the number of tokens
    int token_count = 0;
    int in_token = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim) {
            in_token = 0;
        } else if (!in_token) {
            in_token = 1;
            token_count++;
        }
    }
    
    // Handle empty string
    if (token_count == 0) {
        *count = 0;
        return NULL;
    }
    
    // Allocate array of string pointers
    char **result = (char**)malloc(token_count * sizeof(char*));
    if (result == NULL) {
        *count = 0;
        return NULL;
    }
    
    // Extract tokens
    int token_idx = 0;
    int start = 0;
    in_token = 0;
    
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == delim) {
            if (in_token) {
                // End of token
                int length = i - start;
                result[token_idx] = (char*)malloc((length + 1) * sizeof(char));
                if (result[token_idx] == NULL) {
                    // Cleanup on allocation failure
                    free_string_array(result, token_idx);
                    *count = 0;
                    return NULL;
                }
                strncpy(result[token_idx], &str[start], length);
                result[token_idx][length] = '\0';
                token_idx++;
                in_token = 0;
            }
        } else if (!in_token) {
            // Start of new token
            start = i;
            in_token = 1;
        }
    }
    
    // Handle last token if string doesn't end with delimiter
    if (in_token) {
        int length = strlen(str) - start;
        result[token_idx] = (char*)malloc((length + 1) * sizeof(char));
        if (result[token_idx] == NULL) {
            free_string_array(result, token_idx);
            *count = 0;
            return NULL;
        }
        strncpy(result[token_idx], &str[start], length);
        result[token_idx][length] = '\0';
        token_idx++;
    }
    
    *count = token_count;
    return result;
}

void free_string_array(char **arr, int count) {
    if (arr == NULL) {
        return;
    }
    
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }
    free(arr);
}