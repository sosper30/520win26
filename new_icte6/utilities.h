#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <algorithm>
#include <cmath>

/**
 * @brief Sorts a vector by absolute values (magnitude)
 * 
 * Sorts the input vector in ascending order based on the absolute value
 * of each element.
 * 
 * @param vec Vector to sort (modified in-place)
 * 
 * Example:
 *   std::vector<double> v = {-5.0, 3.0, -8.0, 1.0, -2.0};
 *   sort_by_magnitude(v);
 *   // Result: {1.0, -2.0, 3.0, -5.0, -8.0}
 */
void sort_by_magnitude(std::vector<double>& vec);

/**
 * @brief Partitions a vector by sign while preserving order
 * 
 * Moves all negative numbers before positive numbers (including zero).
 * Preserves the relative order within each partition.
 * 
 * @param vec Vector to partition (modified in-place)
 * @return Iterator pointing to the first non-negative element
 * 
 * Example:
 *   std::vector<double> v = {-1.0, -2.0, 3.0, 4.0, -5.0, 8.0};
 *   auto it = partition_by_sign(v);
 *   // Result: {-1.0, -2.0, -5.0, 3.0, 4.0, 8.0}
 *   //                            ^ iterator points here
 */
std::vector<double>::iterator partition_by_sign(std::vector<double>& vec);

/**
 * @brief Normalizes values and sorts them in ascending order
 * 
 * Finds the maximum absolute value, divides all values by it,
 * and sorts the result in ascending order (negative to positive).
 * 
 * @param vec Input vector (not modified)
 * @return New vector with normalized and sorted values
 * 
 * Example:
 *   std::vector<double> v = {-10.0, 5.0, -2.0, 8.0};
 *   auto result = normalize_and_sort(v);
 *   // Result: {-1.0, -0.2, 0.5, 0.8}
 */
std::vector<double> normalize_and_sort(const std::vector<double>& vec);

#endif // UTILITIES_H