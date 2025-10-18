#include "utilities.h"
#include <iostream>
#include <cassert>
#include <cmath>

using namespace std;

// Helper function to check if two doubles are approximately equal
bool approx_equal(double a, double b) {
    return abs(a - b) < 0.0001;
}

// Helper to print vector
void print_vector(const vector<double>& vec) {
    cout << "[";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    cout << "\n=== Testing sort_by_magnitude ===\n" << endl;
    
    // Test 1: Basic test
    {
        vector<double> v = {-5.0, 3.0, -8.0, 1.0, -2.0};
        cout << "Test 1 - Before: ";
        print_vector(v);
        sort_by_magnitude(v);
        cout << "Test 1 - After:  ";
        print_vector(v);
        assert(approx_equal(v[0], 1.0));
        assert(approx_equal(abs(v[4]), 8.0));
        cout << "✓ Test 1 passed\n" << endl;
    }
    
    // Test 2: Empty vector
    {
        vector<double> v;
        sort_by_magnitude(v);
        assert(v.empty());
        cout << "✓ Test 2 passed (empty vector)\n" << endl;
    }
    
    // Test 3: Vector with zeros
    {
        vector<double> v = {0.0, -3.0, 2.0, 0.0};
        sort_by_magnitude(v);
        assert(v[0] == 0.0 || v[1] == 0.0); // zeros should be first
        cout << "✓ Test 3 passed (with zeros)\n" << endl;
    }
    
    cout << "\n=== Testing partition_by_sign ===\n" << endl;
    
    // Test 4: Basic partition
    {
        vector<double> v = {-5.0, 3.0, -2.0, 8.0, -1.0, 4.0};
        cout << "Test 4 - Before: ";
        print_vector(v);
        auto it = partition_by_sign(v);
        cout << "Test 4 - After:  ";
        print_vector(v);
        
        // Check all negatives come before positives
        for (auto i = v.begin(); i != it; i++) {
            assert(*i < 0);
        }
        for (auto i = it; i != v.end(); i++) {
            assert(*i >= 0);
        }
        cout << "✓ Test 4 passed\n" << endl;
    }
    
    // Test 5: Partition preserves order
    {
        vector<double> v = {-1.0, -2.0, -5.0, 3.0, 4.0, 8.0};
        auto it = partition_by_sign(v);
        // Order within each partition should be preserved
        assert(v[0] == -1.0 && v[1] == -2.0 && v[2] == -5.0);
        assert(v[3] == 3.0 && v[4] == 4.0 && v[5] == 8.0);
        cout << "✓ Test 5 passed (order preserved)\n" << endl;
    }
    
    // Test 6: All negative numbers
    {
        vector<double> v = {-5.0, -3.0, -1.0};
        auto it = partition_by_sign(v);
        assert(it == v.end());
        cout << "✓ Test 6 passed (all negative)\n" << endl;
    }
    
    // Test 7: All positive numbers
    {
        vector<double> v = {5.0, 3.0, 1.0};
        auto it = partition_by_sign(v);
        assert(it == v.begin());
        cout << "✓ Test 7 passed (all positive)\n" << endl;
    }
    
    cout << "\n=== Testing normalize_and_sort ===\n" << endl;
    
    // Test 8: Basic normalize and sort
    {
        vector<double> v = {-10.0, 5.0, -2.0, 8.0};
        cout << "Test 8 - Before: ";
        print_vector(v);
        auto result = normalize_and_sort(v);
        cout << "Test 8 - After:  ";
        print_vector(result);
        
        // Should be sorted in ascending order: -1.0, -0.2, 0.5, 0.8
        assert(approx_equal(result[0], -1.0));
        assert(approx_equal(result[1], -0.2));
        assert(approx_equal(result[2], 0.5));
        assert(approx_equal(result[3], 0.8));
        cout << "✓ Test 8 passed\n" << endl;
    }
    
    // Test 9: Original vector unchanged
    {
        vector<double> v = {-10.0, 5.0, -2.0};
        auto result = normalize_and_sort(v);
        assert(v[0] == -10.0 && v[1] == 5.0 && v[2] == -2.0);
        cout << "✓ Test 9 passed (original unchanged)\n" << endl;
    }
    
    // Test 10: All zeros
    {
        vector<double> v = {0.0, 0.0, 0.0};
        auto result = normalize_and_sort(v);
        assert(result[0] == 0.0);
        cout << "✓ Test 10 passed (all zeros)\n" << endl;
    }
    
    // Test 11: Empty vector
    {
        vector<double> v;
        auto result = normalize_and_sort(v);
        assert(result.empty());
        cout << "✓ Test 11 passed (empty)\n" << endl;
    }
    
    // Test 12: Values in range [-1, 1] and sorted
    {
        vector<double> v = {-100.0, 50.0, -25.0};
        auto result = normalize_and_sort(v);
        // Check values are in range
        for (double val : result) {
            assert(abs(val) <= 1.0);
        }
        // Check they are sorted in ascending order
        for (size_t i = 1; i < result.size(); i++) {
            assert(result[i] >= result[i-1]);
        }
        cout << "✓ Test 12 passed (values in range and sorted)\n" << endl;
    }
    
    cout << "\n=== All 12 Tests Passed! ===\n" << endl;
    
    return 0;
}