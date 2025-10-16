#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
        free(a);  // Free after all death tests complete
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);
        free(da);
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        char * str = DynamicArray_to_string(da);
        printf("Push test Intermediate Result: %s\n", str);
        free(str);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);
        free(da);
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);
        free(da);
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);
        free(t);
        DynamicArray_destroy(y);
        free(y);
    }

    /* ====================================================================== */
    /* NEW TESTS - Filter, Unique, Split                                     */
    /* ====================================================================== */

    /* Helper predicates for filter tests */
    int is_positive(double x) {
        return x > 0;
    }

    int is_negative(double x) {
        return x < 0;
    }

    int is_even_integer(double x) {
        return fabs(x - round(x)) < EPSILON && ((int)round(x) % 2 == 0);
    }

    int always_true(double x) {
        (void)x;
        return 1;
    }

    int always_false(double x) {
        (void)x;
        return 0;
    }

    int is_greater_than_five(double x) {
        return x > 5.0;
    }

    /* DynamicArray_filter tests *********************************************/

    TEST(DynamicArrayFilter, Basic) {
        DynamicArray * a = DynamicArray_new();
        for (int i = -5; i <= 5; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        DynamicArray * positive = DynamicArray_filter(a, is_positive);
        ASSERT_EQ(DynamicArray_size(positive), 5);
        ASSERT_EQ(DynamicArray_get(positive, 0), 1.0);
        ASSERT_EQ(DynamicArray_get(positive, 4), 5.0);
        
        DynamicArray * negative = DynamicArray_filter(a, is_negative);
        ASSERT_EQ(DynamicArray_size(negative), 5);
        ASSERT_EQ(DynamicArray_get(negative, 0), -5.0);
        ASSERT_EQ(DynamicArray_get(negative, 4), -1.0);
        
        DynamicArray_destroy(positive);
        free(positive);
        DynamicArray_destroy(negative);
        free(negative);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayFilter, MatchAll) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 10; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        DynamicArray * all = DynamicArray_filter(a, always_true);
        ASSERT_EQ(DynamicArray_size(all), 10);
        for (int i = 0; i < 10; i++) {
            ASSERT_EQ(DynamicArray_get(all, i), (double)(i+1));
        }
        
        DynamicArray_destroy(all);
        free(all);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayFilter, MatchNone) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 10; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        DynamicArray * none = DynamicArray_filter(a, always_false);
        ASSERT_EQ(DynamicArray_size(none), 0);
        
        DynamicArray_destroy(none);
        free(none);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayFilter, EvenIntegers) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 10; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        DynamicArray * evens = DynamicArray_filter(a, is_even_integer);
        ASSERT_EQ(DynamicArray_size(evens), 5);
        ASSERT_EQ(DynamicArray_get(evens, 0), 2.0);
        ASSERT_EQ(DynamicArray_get(evens, 1), 4.0);
        ASSERT_EQ(DynamicArray_get(evens, 4), 10.0);
        
        DynamicArray_destroy(evens);
        free(evens);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayFilter, EmptyArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray * filtered = DynamicArray_filter(a, is_positive);
        ASSERT_EQ(DynamicArray_size(filtered), 0);
        
        DynamicArray_destroy(filtered);
        free(filtered);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayFilter, LargeArray) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 0; i < 1000; i++) {
            DynamicArray_push(a, (double)(i - 500));
        }
        
        DynamicArray * positive = DynamicArray_filter(a, is_positive);
        ASSERT_EQ(DynamicArray_size(positive), 499);
        
        DynamicArray_destroy(positive);
        free(positive);
        DynamicArray_destroy(a);
        free(a);
    }

    /* DynamicArray_unique tests *********************************************/

    TEST(DynamicArrayUnique, Basic) {
        DynamicArray * a = DynamicArray_new();
        double values[] = {1, 2, 2, 3, 1, 4, 2, 5};
        for (int i = 0; i < 8; i++) {
            DynamicArray_push(a, values[i]);
        }
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 5);
        ASSERT_EQ(DynamicArray_get(unique, 0), 1.0);
        ASSERT_EQ(DynamicArray_get(unique, 1), 2.0);
        ASSERT_EQ(DynamicArray_get(unique, 2), 3.0);
        ASSERT_EQ(DynamicArray_get(unique, 3), 4.0);
        ASSERT_EQ(DynamicArray_get(unique, 4), 5.0);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayUnique, NoDuplicates) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 5; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 5);
        for (int i = 0; i < 5; i++) {
            ASSERT_EQ(DynamicArray_get(unique, i), (double)(i+1));
        }
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayUnique, AllSame) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 0; i < 10; i++) {
            DynamicArray_push(a, 7.0);
        }
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 1);
        ASSERT_EQ(DynamicArray_get(unique, 0), 7.0);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayUnique, FloatingPointEpsilon) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 1.0);
        DynamicArray_push(a, 1.0 + EPSILON / 2);  // Within epsilon
        DynamicArray_push(a, 2.0);
        DynamicArray_push(a, 2.0 + EPSILON / 2);  // Within epsilon
        DynamicArray_push(a, 3.0);
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 3);
        ASSERT_NEAR(DynamicArray_get(unique, 0), 1.0, EPSILON);
        ASSERT_NEAR(DynamicArray_get(unique, 1), 2.0, EPSILON);
        ASSERT_NEAR(DynamicArray_get(unique, 2), 3.0, EPSILON);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayUnique, EmptyArray) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 0);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayUnique, PreservesOrder) {
        DynamicArray * a = DynamicArray_new();
        double values[] = {5, 3, 5, 1, 3, 2, 1};
        for (int i = 0; i < 7; i++) {
            DynamicArray_push(a, values[i]);
        }
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 4);
        ASSERT_EQ(DynamicArray_get(unique, 0), 5.0);
        ASSERT_EQ(DynamicArray_get(unique, 1), 3.0);
        ASSERT_EQ(DynamicArray_get(unique, 2), 1.0);
        ASSERT_EQ(DynamicArray_get(unique, 3), 2.0);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayUnique, Negatives) {
        DynamicArray * a = DynamicArray_new();
        double values[] = {-1, -2, -1, -3, -2, -1};
        for (int i = 0; i < 6; i++) {
            DynamicArray_push(a, values[i]);
        }
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 3);
        ASSERT_EQ(DynamicArray_get(unique, 0), -1.0);
        ASSERT_EQ(DynamicArray_get(unique, 1), -2.0);
        ASSERT_EQ(DynamicArray_get(unique, 2), -3.0);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    /* DynamicArray_split tests **********************************************/

    TEST(DynamicArraySplit, BasicThreeChunks) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 0; i < 10; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 3, &num_chunks);
        
        ASSERT_EQ(num_chunks, 3);
        ASSERT_EQ(DynamicArray_size(chunks[0]), 4);
        ASSERT_EQ(DynamicArray_size(chunks[1]), 4);
        ASSERT_EQ(DynamicArray_size(chunks[2]), 2);
        
        ASSERT_EQ(DynamicArray_get(chunks[0], 0), 0.0);
        ASSERT_EQ(DynamicArray_get(chunks[0], 3), 3.0);
        ASSERT_EQ(DynamicArray_get(chunks[1], 0), 4.0);
        ASSERT_EQ(DynamicArray_get(chunks[2], 1), 9.0);
        
        for (int i = 0; i < num_chunks; i++) {
            DynamicArray_destroy(chunks[i]);
            free(chunks[i]);
        }
        free(chunks);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, TwoChunks) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 7; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 2, &num_chunks);
        
        ASSERT_EQ(num_chunks, 2);
        ASSERT_EQ(DynamicArray_size(chunks[0]), 4);
        ASSERT_EQ(DynamicArray_size(chunks[1]), 3);
        
        for (int i = 0; i < num_chunks; i++) {
            DynamicArray_destroy(chunks[i]);
            free(chunks[i]);
        }
        free(chunks);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, OneChunk) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 5; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 1, &num_chunks);
        
        ASSERT_EQ(num_chunks, 1);
        ASSERT_EQ(DynamicArray_size(chunks[0]), 5);
        for (int i = 0; i < 5; i++) {
            ASSERT_EQ(DynamicArray_get(chunks[0], i), (double)(i+1));
        }
        
        DynamicArray_destroy(chunks[0]);
        free(chunks[0]);
        free(chunks);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, MoreChunksThanElements) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 3; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 5, &num_chunks);
        
        ASSERT_EQ(num_chunks, 3);
        ASSERT_EQ(DynamicArray_size(chunks[0]), 1);
        ASSERT_EQ(DynamicArray_size(chunks[1]), 1);
        ASSERT_EQ(DynamicArray_size(chunks[2]), 1);
        
        for (int i = 0; i < num_chunks; i++) {
            DynamicArray_destroy(chunks[i]);
            free(chunks[i]);
        }
        free(chunks);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, EmptyArray) {
        DynamicArray * a = DynamicArray_new();
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 3, &num_chunks);
        
        ASSERT_EQ(chunks, nullptr);
        ASSERT_EQ(num_chunks, 0);
        
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, InvalidN) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 1; i <= 5; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 0, &num_chunks);
        ASSERT_EQ(chunks, nullptr);
        ASSERT_EQ(num_chunks, 0);
        
        chunks = DynamicArray_split(a, -1, &num_chunks);
        ASSERT_EQ(chunks, nullptr);
        ASSERT_EQ(num_chunks, 0);
        
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, LargeArray) {
        DynamicArray * a = DynamicArray_new();
        for (int i = 0; i < 100; i++) {
            DynamicArray_push(a, (double)i);
        }
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 7, &num_chunks);
        
        ASSERT_EQ(num_chunks, 7);
        
        // Verify total elements are preserved
        int total = 0;
        for (int i = 0; i < num_chunks; i++) {
            total += DynamicArray_size(chunks[i]);
        }
        ASSERT_EQ(total, 100);
        
        for (int i = 0; i < num_chunks; i++) {
            DynamicArray_destroy(chunks[i]);
            free(chunks[i]);
        }
        free(chunks);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArraySplit, SingleElement) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_push(a, 42.0);
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(a, 3, &num_chunks);
        
        ASSERT_EQ(num_chunks, 1);
        ASSERT_EQ(DynamicArray_size(chunks[0]), 1);
        ASSERT_EQ(DynamicArray_get(chunks[0], 0), 42.0);
        
        DynamicArray_destroy(chunks[0]);
        free(chunks[0]);
        free(chunks);
        DynamicArray_destroy(a);
        free(a);
    }

    /* Combined operations tests *********************************************/

    TEST(DynamicArrayCombined, FilterThenUnique) {
        DynamicArray * a = DynamicArray_new();
        double values[] = {-5, -3, -1, 0, 1, 1, 2, 2, 3, 5, 5, 7};
        for (int i = 0; i < 12; i++) {
            DynamicArray_push(a, values[i]);
        }
        
        DynamicArray * positive = DynamicArray_filter(a, is_positive);
        ASSERT_EQ(DynamicArray_size(positive), 8);  // 1,1,2,2,3,5,5,7
        
        DynamicArray * unique = DynamicArray_unique(positive);
        ASSERT_EQ(DynamicArray_size(unique), 5);  // 1,2,3,5,7
        ASSERT_EQ(DynamicArray_get(unique, 0), 1.0);
        ASSERT_EQ(DynamicArray_get(unique, 1), 2.0);
        ASSERT_EQ(DynamicArray_get(unique, 2), 3.0);
        ASSERT_EQ(DynamicArray_get(unique, 3), 5.0);
        ASSERT_EQ(DynamicArray_get(unique, 4), 7.0);
        
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(positive);
        free(positive);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayCombined, UniqueThenSplit) {
        DynamicArray * a = DynamicArray_new();
        double values[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4};
        for (int i = 0; i < 10; i++) {
            DynamicArray_push(a, values[i]);
        }
        
        DynamicArray * unique = DynamicArray_unique(a);
        ASSERT_EQ(DynamicArray_size(unique), 4);
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(unique, 2, &num_chunks);
        ASSERT_EQ(num_chunks, 2);
        ASSERT_EQ(DynamicArray_size(chunks[0]), 2);
        ASSERT_EQ(DynamicArray_size(chunks[1]), 2);
        
        for (int i = 0; i < num_chunks; i++) {
            DynamicArray_destroy(chunks[i]);
            free(chunks[i]);
        }
        free(chunks);
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(a);
        free(a);
    }

    TEST(DynamicArrayCombined, FilterUniqueSplit) {
        DynamicArray * a = DynamicArray_new();
        for (int i = -10; i <= 10; i++) {
            DynamicArray_push(a, (double)i);
            if (i > 0 && i <= 5) {
                DynamicArray_push(a, (double)i);  // Add duplicates for positive small numbers
            }
        }
        
        DynamicArray * positive = DynamicArray_filter(a, is_greater_than_five);
        DynamicArray * unique = DynamicArray_unique(positive);
        
        int num_chunks;
        DynamicArray ** chunks = DynamicArray_split(unique, 2, &num_chunks);
        
        ASSERT_EQ(num_chunks, 2);
        
        for (int i = 0; i < num_chunks; i++) {
            DynamicArray_destroy(chunks[i]);
            free(chunks[i]);
        }
        free(chunks);
        DynamicArray_destroy(unique);
        free(unique);
        DynamicArray_destroy(positive);
        free(positive);
        DynamicArray_destroy(a);
        free(a);
    }

    /* Stress test ***********************************************************/

    TEST(DynamicArrayStress, ManyOperations) {
        for (int iter = 0; iter < 100; iter++) {
            DynamicArray * a = DynamicArray_new();
            for (int i = 0; i < 20; i++) {
                DynamicArray_push(a, (double)(i % 7));
            }
            
            DynamicArray * filtered = DynamicArray_filter(a, is_positive);
            DynamicArray * unique = DynamicArray_unique(filtered);
            
            int num_chunks;
            DynamicArray ** chunks = DynamicArray_split(unique, 2, &num_chunks);
            
            for (int i = 0; i < num_chunks; i++) {
                DynamicArray_destroy(chunks[i]);
                free(chunks[i]);
            }
            free(chunks);
            
            DynamicArray_destroy(unique);
            free(unique);
            DynamicArray_destroy(filtered);
            free(filtered);
            DynamicArray_destroy(a);
            free(a);
        }
    }

}