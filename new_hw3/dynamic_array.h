#ifndef _DYNAMIC_ARRAY
#define _DYNAMIC_ARRAY

#define DYNAMIC_ARRAY_INITIAL_CAPACITY 10
#define EPSILON 1e-9

typedef struct {
    int capacity,
        origin,
        end;
    double * buffer;
} DynamicArray;

/* Constructors / Destructors ************************************************/

DynamicArray * DynamicArray_new(void);
void DynamicArray_destroy(DynamicArray *);

/* Getters / Setters *********************************************************/

void DynamicArray_set(DynamicArray *, int, double);
double DynamicArray_get(const DynamicArray *, int);
int DynamicArray_size(const DynamicArray *);

/* Printing ******************************************************************/

char * DynamicArray_to_string(const DynamicArray *);
void DynamicArray_print_debug_info(const DynamicArray *);

/* Operations ****************************************************************/

void DynamicArray_push(DynamicArray *, double);
void DynamicArray_push_front(DynamicArray *, double);

double DynamicArray_pop(DynamicArray *);
double DynamicArray_pop_front(DynamicArray *);

DynamicArray * DynamicArray_map ( const DynamicArray *, double (*) (double) );

/* EXERCISES: ********************************************************/

/*! Return the first value in the given array. Throw a runtime error if the array is empty.
 *  \param da The array
 */
double DynamicArray_last ( const DynamicArray * da );

/*! Return the first last in the given array. Throw a runtime error if the array is empty.
 *  \param da The array
 */
double DynamicArray_first ( const DynamicArray * da );

/*! Return a copy of the array.
 *  \param da The array
 */
DynamicArray * DynamicArray_copy ( const DynamicArray * da );

/*! Return a new array whose elements span the given range and are step units apart.
 *  \param a The first value
 *  \param b The second value
 *  \param step The different between consecutive elements.
 */
DynamicArray * DynamicArray_range ( double a, double b, double step);

/*! Return a new array that is the concatenation of the given arrays. 
 *  \param a The first array
 *  \param b The second array
 */
DynamicArray * DynamicArray_concat ( const DynamicArray * a, const DynamicArray * b );

/*! Mathematical operations
  */
double DynamicArray_min ( const DynamicArray * da );
double DynamicArray_max ( const DynamicArray * da );
double DynamicArray_mean ( const DynamicArray * da );
double DynamicArray_median ( const DynamicArray * da );
double DynamicArray_sum ( const DynamicArray * da );

/*! Returns 1 if the array is valid (meaning its buffer is not NULL) and 0 otherwize.
 */
int DynamicArray_is_valid(const DynamicArray * da);

/*! Returns the number of arrays that have been constructed to far.
 */
int DynamicArray_num_arrays();

/*! Destroys all arrays that have been constructed so far.
 */
void DynamicArray_destroy_all();

DynamicArray * DynamicArray_subarray(DynamicArray *, int, int);

/* NEW FUNCTIONS - Advanced Memory Management ********************************/

/*! Creates a new array containing only elements that satisfy the predicate function.
 *  Uses a two-pass approach: first counts matching elements, then copies them.
 *  \param da The source array (must not be NULL)
 *  \param predicate Function that returns 1 for elements to keep, 0 to filter out
 *  \return New DynamicArray with filtered elements (caller must destroy)
 *  
 *  Example:
 *    int is_positive(double x) { return x > 0; }
 *    DynamicArray * filtered = DynamicArray_filter(arr, is_positive);
 *    // ... use filtered ...
 *    DynamicArray_destroy(filtered);
 *    free(filtered);
 */
DynamicArray * DynamicArray_filter(const DynamicArray * da, int (*predicate)(double));

/*! Creates a new array with duplicate values removed, preserving order of first occurrences.
 *  Uses epsilon comparison (EPSILON = 1e-9) for floating-point values.
 *  \param da The source array (must not be NULL)
 *  \return New DynamicArray with duplicates removed (caller must destroy)
 *  
 *  Example:
 *    // Input: [1, 2, 2, 3, 1, 4, 2]
 *    DynamicArray * unique = DynamicArray_unique(arr);
 *    // Result: [1, 2, 3, 4]
 *    DynamicArray_destroy(unique);
 *    free(unique);
 */
DynamicArray * DynamicArray_unique(const DynamicArray * da);

/*! Splits an array into n chunks, returning an array of DynamicArray pointers.
 *  The last chunk may be smaller if size doesn't divide evenly.
 *  \param da The source array (must not be NULL)
 *  \param n Number of chunks to create (must be > 0)
 *  \param num_chunks Output parameter: set to actual number of chunks created
 *  \return Array of DynamicArray pointers, or NULL if invalid input
 *  
 *  CRITICAL MEMORY NOTE: Caller must free memory in TWO steps:
 *    1. Call DynamicArray_destroy() and free() on each chunk
 *    2. Call free() on the returned array
 *  
 *  Example:
 *    int n;
 *    DynamicArray ** chunks = DynamicArray_split(arr, 3, &n);
 *    
 *    // Use chunks...
 *    
 *    // MUST cleanup properly:
 *    for (int i = 0; i < n; i++) {
 *        DynamicArray_destroy(chunks[i]);
 *        free(chunks[i]);
 *    }
 *    free(chunks);
 */
DynamicArray ** DynamicArray_split(const DynamicArray * da, int n, int * num_chunks);

#endif