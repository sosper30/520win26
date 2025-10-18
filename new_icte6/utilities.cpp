#include "utilities.h"

void sort_by_magnitude(std::vector<double>& vec) {
    // Sort by absolute value using a lambda expression
    std::sort(vec.begin(), vec.end(), 
        [](double a, double b) {
            return std::abs(a) < std::abs(b);
        }
    );
}

std::vector<double>::iterator partition_by_sign(std::vector<double>& vec) {
    // Use stable_partition to move negative numbers before non-negative ones
    // while preserving the relative order within each partition
    return std::stable_partition(vec.begin(), vec.end(), 
        [](double value) {
            return value < 0.0;
        }
    );
}

std::vector<double> normalize_and_sort(const std::vector<double>& vec) {
    // Handle empty vector
    if (vec.empty()) {
        return std::vector<double>();
    }
    
    // Find the maximum absolute value using max_element
    auto max_it = std::max_element(vec.begin(), vec.end(),
        [](double a, double b) {
            return std::abs(a) < std::abs(b);
        }
    );
    
    double max_magnitude = std::abs(*max_it);
    
    // Handle case where all values are zero
    if (max_magnitude == 0.0) {
        return std::vector<double>(vec.size(), 0.0);
    }
    
    // Create a new vector for normalized values
    std::vector<double> normalized;
    normalized.reserve(vec.size());
    
    // Normalize each value by dividing by max magnitude
    std::transform(vec.begin(), vec.end(), std::back_inserter(normalized),
        [max_magnitude](double value) {
            return value / max_magnitude;
        }
    );
    
    // Sort the normalized vector in ascending order
    std::sort(normalized.begin(), normalized.end());
    
    return normalized;
}